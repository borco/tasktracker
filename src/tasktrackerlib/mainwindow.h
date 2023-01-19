/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

class QQmlApplicationEngine;
class QQuickWindow;

namespace tasktrackerlib {

class MainWindow
{
public:
    MainWindow(QQmlApplicationEngine& engine);

    void saveGeometry();
    void loadGeometry();

private:
    QQuickWindow* m_mainWindow;
};

} // namespace tasktrackerlib

