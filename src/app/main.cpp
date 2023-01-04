/*
    Copyright 2022 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "config.h"
#include "keychainservice.h"
#include "messagehandler.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>

int main(int argc, char *argv[])
{
    qInstallMessageHandler(message_handler);

    KeyChainService keychain_service("toggltracktasks.app");

    QGuiApplication::setOrganizationName("Ioan Calin");
    QGuiApplication::setOrganizationDomain("com.github.borco");
    QGuiApplication::setApplicationName("toggltracktasks");

    QGuiApplication app(argc, argv);

    QSettings::setDefaultFormat(QSettings::IniFormat);
    qInfo() << "Settings file:" << QSettings().fileName();

    Config::get()->load();

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
