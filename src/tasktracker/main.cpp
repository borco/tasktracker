/*
    Copyright 2022 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "qtkeychainadapter/keychainservice.h"
#include "qtplogadapter/setup.h"
#include "tasktrackerlib/config.h"
#include "tasktrackerlib/togglproxy.h"

#include <QCommandLineParser>
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

static const char* DefaultSettingsGroupKey = "Main";
static const char* WindowGeometryKey = "windowGeometry";

QQuickWindow* main_window(QQmlApplicationEngine& engine)
{
    if(engine.rootObjects().size() > 0) {
        return qobject_cast<QQuickWindow*>(engine.rootObjects().at(0));
    }

    return nullptr;
}

void save_window_settings(QQmlApplicationEngine& engine)
{
    auto window = main_window(engine);
    if (!window) return;

    QSettings settings;
    settings.beginGroup(DefaultSettingsGroupKey);
    settings.setValue(WindowGeometryKey, window->geometry());
    settings.endGroup();
}

void load_window_settings(QQmlApplicationEngine& engine)
{
    auto window = main_window(engine);
    if (!window) return;

    QSettings settings;
    settings.beginGroup(DefaultSettingsGroupKey);
    window->setGeometry(settings.value(WindowGeometryKey, QRect(100, 100, 800, 480)).toRect());
    settings.endGroup();
}

}

int main(int argc, char *argv[])
{
    qtplogadapter::init("/tmp/tasktracker.log");
    qDebug() << "----------- Started Task Tracker -----------";

    QStringList raw_arguments;
    for (int i = 0; i < argc; ++i) {
        raw_arguments << argv[i];
    }

    int index = raw_arguments.indexOf("--style");
    if (index >= 0 && (index + 1) < raw_arguments.size()) {
        qDebug() << "Main: style set on command line to:" << raw_arguments[index + 1];
    } else {
        qDebug() << "Main: style set to default style:" << DefaultQuickStyle;
        QQuickStyle::setStyle(DefaultQuickStyle);
    }

    qtkeychainadapter::KeyChainService keychain_service("tasktracker.app");

    QGuiApplication::setOrganizationName("Ioan Calin");
    QGuiApplication::setOrganizationDomain("com.github.borco");
    QGuiApplication::setApplicationName("tasktracker");

    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/TaskTracker/icons/app.svg"));

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
                              UseProxyCommandLineOption,
                              QCoreApplication::translate("main", "Use a proxy for HTTPS connections."),
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

    QNetworkProxy network_proxy;

    if (parser.isSet(UseProxyCommandLineOption)) {
        auto proxy_host = parser.value(ProxyHostCommandLineOption);
        auto proxy_port = parser.value(ProxyPortCommandLineOption).toUShort();

        qWarning().nospace().noquote() << "Main: using custom network proxy: " << proxy_host << ":" << proxy_port;

        network_proxy.setType(QNetworkProxy::HttpProxy);
        network_proxy.setHostName(proxy_host);
        network_proxy.setPort(proxy_port);
        QNetworkProxy::setApplicationProxy(network_proxy);
    }

    QSettings::setDefaultFormat(QSettings::IniFormat);
    qInfo() << "Main: settings file:" << QSettings().fileName();

    tasktrackerlib::Config::get()->load();
    tasktrackerlib::TogglProxy::get()->load();

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/");

    const QUrl url(u"qrc:/TaskTracker/qml/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.rootContext()->setContextProperty("KeyChain", &keychain_service);
    engine.load(url);

    load_window_settings(engine);
    int ret = app.exec();
    save_window_settings(engine);

    tasktrackerlib::TogglProxy::cleanup();

    return ret;
}
