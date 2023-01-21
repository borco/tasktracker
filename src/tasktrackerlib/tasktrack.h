/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QQmlEngine>

namespace tasktrackerlib {

class TaskTrack : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    explicit TaskTrack(QObject *parent = nullptr);

    enum Mode {
        Count = 0,
        Duration,
    };
    Q_ENUM(Mode)

    Q_INVOKABLE static QString toString(int trackMode);

    inline const static Mode DefaultMode = Count;
};

} // namespace tasktrackerlib
