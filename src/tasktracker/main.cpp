/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "qtkeychainadapter/keychainservice.h"
#include "qtplogadapter/setup.h"
#include "tasktrackerlib/config.h"
#include "tasktrackerlib/mainwindow.h"
#include "tasktrackerlib/togglproxy.h"

#include <QCommandLineParser>
#include <QFontDatabase>
#include <QGuiApplication>
#include <QIcon>
#include <QNetworkProxy>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QQuickWindow>
#include <QSettings>

namespace {
static const char* DefaultQuickStyle = "iOS";
}

int main(int argc, char *argv[])
{
    qtplogadapter::init("/tmp/tasktracker.log");
//    qDebug() << "----------- Started Task Tracker -----------";

    QStringList raw_arguments;
    for (int i = 0; i < argc; ++i) {
        raw_arguments << argv[i];
    }

    int index = raw_arguments.indexOf("--style");
    if (index >= 0 && (index + 1) < raw_arguments.size()) {
        qDebug() << "Style set on command line to:" << raw_arguments[index + 1];
    } else {
        qDebug() << "Style set to default style:" << DefaultQuickStyle;
        QQuickStyle::setStyle(DefaultQuickStyle);
    }

    qtkeychainadapter::KeyChainService keychain_service("tasktracker.app");

    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/TaskTracker/icons/app.svg"));

    static const char* AppNameCommandLineOption = "appname";
    static const char* QuickStyleCommandLineOption = "style";
    static const char* UseProxyCommandLineOption = "use-proxy";
    static const char* ProxyHostCommandLineOption = "proxy-host";
    static const char* ProxyPortCommandLineOption = "proxy-port";

    QCommandLineParser parser;
    parser.setApplicationDescription("Simple task tracker.");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOptions({
                          {
                              AppNameCommandLineOption,
                              QCoreApplication::translate("main", "Set application name to <NAME>; controls the name of the .ini settings file (default: tasktracker)."),
                              QCoreApplication::translate("main", "NAME"),
                              "tasktracker"
                          },
                          {
                              UseProxyCommandLineOption,
                              QCoreApplication::translate("main", "Use a proxy for HTTPS connections (default: false)."),
                          },
                          {
                              ProxyHostCommandLineOption,
                              QCoreApplication::translate("main", "Proxy <IP> address (default: 127.0.0.1)."),
                              QCoreApplication::translate("main", "IP"),
                              "127.0.0.1"
                          },
                          {
                              ProxyPortCommandLineOption,
                              QCoreApplication::translate("main", "Proxy <PORT> number (default: 8080)."),
                              QCoreApplication::translate("main", "PORT"),
                              "8080"
                          },
                      });
    parser.process(app);

    QGuiApplication::setOrganizationName("Ioan Calin");
    QGuiApplication::setOrganizationDomain("com.github.borco");
    QGuiApplication::setApplicationName(parser.value(AppNameCommandLineOption));

    QNetworkProxy network_proxy;

    if (parser.isSet(UseProxyCommandLineOption)) {
        auto proxy_host = parser.value(ProxyHostCommandLineOption);
        auto proxy_port = parser.value(ProxyPortCommandLineOption).toUShort();

        qWarning().nospace().noquote() << "Using custom network proxy: " << proxy_host << ":" << proxy_port;

        network_proxy.setType(QNetworkProxy::HttpProxy);
        network_proxy.setHostName(proxy_host);
        network_proxy.setPort(proxy_port);
        QNetworkProxy::setApplicationProxy(network_proxy);
    }

    QSettings::setDefaultFormat(QSettings::IniFormat);
    qInfo() << "Settings file:" << QSettings().fileName();

    tasktrackerlib::Config::get()->load();
    tasktrackerlib::TogglProxy::get()->load();

    const QFont fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/");
    engine.rootContext()->setContextProperty("fixedFont", fixedFont);

    const QUrl url(u"qrc:/TaskTracker/qml/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.rootContext()->setContextProperty("KeyChain", &keychain_service);
    engine.load(url);

    tasktrackerlib::MainWindow mainWindow(engine);
    mainWindow.loadGeometry();
    int ret = app.exec();
    mainWindow.saveGeometry();

    tasktrackerlib::TogglProxy::cleanup();

    return ret;
}
