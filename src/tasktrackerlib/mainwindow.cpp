/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "mainwindow.h"

#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QSettings>

namespace {
static const char* DefaultSettingsGroupKey = "Main";
static const char* WindowGeometryKey = "windowGeometry";
}

namespace tasktrackerlib {

MainWindow::MainWindow(QQmlApplicationEngine &engine)
{
    if(engine.rootObjects().size() > 0) {
        m_mainWindow = qobject_cast<QQuickWindow*>(engine.rootObjects().at(0));
    } else {
        qWarning() << "Could not determine main window";
    }
}

void MainWindow::saveGeometry()
{
    if (!m_mainWindow) {
        qWarning() << "Could not save main window geometry";
        return;
    }

    QSettings settings;
    settings.beginGroup(DefaultSettingsGroupKey);
    settings.setValue(WindowGeometryKey, m_mainWindow->geometry());
    settings.endGroup();
}

void MainWindow::loadGeometry()
{
    if (!m_mainWindow) {
        qWarning() << "Could not restore main window geometry";
        return;
    }

    QSettings settings;
    settings.beginGroup(DefaultSettingsGroupKey);
    m_mainWindow->setGeometry(settings.value(WindowGeometryKey, QRect(100, 100, 800, 480)).toRect());
    settings.endGroup();
}

} // namespace tasktrackerlib
