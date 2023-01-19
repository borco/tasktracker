/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "qtplogadapter/setup.h"
#include "tasktrackerlib/mainwindow.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QSettings>

namespace {
static const char* DefaultQuickStyle = "iOS";
static const char* DefaultSettingsGroupKey = "Main";
static const char* WindowGeometryKey = "windowGeometry";
}

int main(int argc, char *argv[])
{
    qtplogadapter::init("/tmp/tasktracker_calendar.log");

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

    tasktrackerlib::MainWindow mainWindow(engine);
    mainWindow.loadGeometry();
    int ret = app.exec();
    mainWindow.saveGeometry();
    return ret;
}
