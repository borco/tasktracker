/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QQmlEngine>

namespace tasktrackerlib {

class TaskHelper : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    explicit TaskHelper(QObject *parent = nullptr);

    Q_INVOKABLE static QString trackModeName(int trackMode);
    Q_INVOKABLE static QString scheduleModeName(int scheduleMode);
};

}
