/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSettings>

int main(int argc, char *argv[])
{
    QGuiApplication::setOrganizationName("Ioan Calin");
    QGuiApplication::setOrganizationDomain("com.github.borco");
    QGuiApplication::setApplicationName("tasktracker_listviewordering");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/");
    const QUrl url(u"qrc:/ListViewOrdering/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}
