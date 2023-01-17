/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QQmlEngine>

namespace tasktrackerlib {

class TaskTrackMode : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    explicit TaskTrackMode(QObject *parent = nullptr);

    enum Mode {
        NoTracking = 0, // needs to be done once; marked as done after doing it
        Repeats,
        MinimumRepeats,
        MaximumRepeats,
        Duration,
        MinimumDuration,
        MaximumDuration,
    };
    Q_ENUM(Mode)

    Q_INVOKABLE static QString toString(int trackMode);
};

} // namespace tasktrackerlib
