/*
    Copyright 2022 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "config.h"
#include "keychainservice.h"
#include "qtplogadapter/setup.h"

#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>

int main(int argc, char *argv[])
{
    qtplogadapter::init("/tmp/tasktracker.log");
    qDebug() << "----------- Started Task Tracker -----------";

    KeyChainService keychain_service("tasktracker.app");

    QGuiApplication::setOrganizationName("Ioan Calin");
    QGuiApplication::setOrganizationDomain("com.github.borco");
    QGuiApplication::setApplicationName("tasktracker");

    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/TaskTracker/icons/app.svg"));

    QSettings::setDefaultFormat(QSettings::IniFormat);
    qInfo() << "Settings file:" << QSettings().fileName();

    Config::get()->load();

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

    return app.exec();
}
