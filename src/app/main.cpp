#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "keychainservice.h"

int main(int argc, char *argv[])
{
    KeyChainService keychain_service("toggltracktasks.app");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/TogglTrackTasks/qml/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.rootContext()->setContextProperty("KeyChain", &keychain_service);
    engine.load(url);

    return app.exec();
}
