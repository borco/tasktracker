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

    Q_INVOKABLE static QString formattedSeconds(int seconds, bool isoFormat = false);
    Q_INVOKABLE static int secondsBetween(const QDateTime& start, const QDateTime& stop);

    static QDate aggregateBegin(Qt::DayOfWeek weekStart, int aggregateMode, const QDate& date);
    static QDate aggregateEnd(Qt::DayOfWeek weekStart, int aggregateMode, const QDate& date);

    inline const static Mode DefaultMode = Daily;
};

} // namespace tasktrackerlib
