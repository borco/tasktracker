/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QQmlEngine>

namespace tasktrackerlib {

class TaskAggregate : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    explicit TaskAggregate(QObject *parent = nullptr);

    enum Mode {
        Daily = 0,
        Weekly,
        Monthly,
    };
    Q_ENUM(Mode)

    Q_INVOKABLE static QString toString(int aggregateMode);

    inline const static Mode DefaultMode = Daily;
};

} // namespace tasktrackerlib
