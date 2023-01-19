#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QSettings>

namespace {
static const char* DefaultQuickStyle = "iOS";
}

int main(int argc, char *argv[])
{
    QQuickStyle::setStyle(DefaultQuickStyle);
    QGuiApplication::setOrganizationName("Ioan Calin");
    QGuiApplication::setOrganizationDomain("com.github.borco");
    QGuiApplication::setApplicationName("tasktracker");
    QSettings::setDefaultFormat(QSettings::IniFormat);
    qInfo() << "Main: settings file:" << QSettings().fileName();

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/");
    const QUrl url(u"qrc:/Calendar/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
