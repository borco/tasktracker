/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QQmlEngine>

namespace tasktrackerlib {

class TaskRepeatMode : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    explicit TaskRepeatMode(QObject *parent = nullptr);

    enum Mode {
        Once = 0, // do it once, without a specific time limit
        Daily,
        Weekly,
        Monthly,
    };
    Q_ENUM(Mode)

    Q_INVOKABLE static QString toString(int repeatMode);

    inline const static Mode DefaultMode = Once;
};

} // namespace tasktrackerlib
