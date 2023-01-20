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
        Daily = 0,
        Weekly,
        Monthly,
        Once, // do it once, without a specific time limit
        Before, // before a set date; shown as "Overdue" after end date
        After,  // after a set date; not shown by default before start date
        Between, // between 2 date; not shown by default before start date; shown as"Overdue" after end date
    };
    Q_ENUM(Mode)

    Q_INVOKABLE static QString toString(int repeatMode);
};

} // namespace tasktrackerlib
