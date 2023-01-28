/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskaggregate.h"

#include <QDate>

namespace {
static int DaysInWeek = 7;
}

namespace tasktrackerlib {

TaskAggregate::TaskAggregate(QObject *parent)
    : QObject{parent}
{
}

QString TaskAggregate::toString(int aggregateMode)
{
    switch(aggregateMode) {
    case Daily:
        return tr("Daily");
    case Weekly:
        return tr("Weekly");
    case Monthly:
        return tr("Monthly");
    default:
        return tr("Invalid schedule mode: %1").arg(aggregateMode);
    }
}

QString TaskAggregate::formattedSeconds(int seconds, bool isoFormat)
{
    if (seconds == 0)
        return isoFormat ? tr("00:00:00") : tr("");

    bool is_negative = seconds < 0;
    seconds = is_negative ? -seconds : seconds;
    int hours = seconds / 3600;
    int mins = (seconds / 60) % 60;
    seconds = seconds % 60;

    if (isoFormat) {
        QString is_negative_repr = is_negative ? "-" : "+";
        return tr("%1%2:%3:%4").arg(is_negative_repr).arg(hours, 2, 10, QChar('0')).arg(mins, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
    } else {
        QString is_negative_repr = is_negative ? "-" : "";
        if (hours > 0) {
            return mins > 0
                    ? tr("%1%2h %3m").arg(is_negative_repr).arg(hours).arg(mins)
                    : tr("%1%2h").arg(is_negative_repr).arg(hours);
        } else if (mins > 0) {
            return seconds > 0
                    ? tr("%1%2m %3s").arg(is_negative_repr).arg(mins).arg(seconds)
                    : tr("%1%2m").arg(is_negative_repr).arg(mins);
        } else {
            return tr("%1%2s").arg(is_negative_repr).arg(seconds);
        }
    }
}

int TaskAggregate::secondsBetween(const QDateTime &start, const QDateTime &stop)
{
    return start.secsTo(stop);
}

QDate TaskAggregate::aggregateBegin(Qt::DayOfWeek weekStart, int aggregateMode, const QDate &date)
{
    switch (aggregateMode) {
    case Weekly: {
        if (date.dayOfWeek() == weekStart) {
            return date;
        }

        auto d = QDate(date).addDays(-1);
        for (int i = 1; i < DaysInWeek; ++i) {
            if (d.dayOfWeek() == weekStart) {
                return d;
            }
            d = d.addDays(-1);
        }

        return date;
    }
    case Monthly: {
        return QDate(date.year(), date.month(), 1);
    }
    default:
        return date;
    }
}

QDate TaskAggregate::aggregateEnd(Qt::DayOfWeek weekStart, int aggregateMode, const QDate &date)
{
    switch (aggregateMode) {
    case Weekly: {
        if (date.dayOfWeek() == weekStart) {
            return date.addDays(DaysInWeek - 1);
        }
        auto d = QDate(date).addDays(1);
        for (int i = 1; i < DaysInWeek; ++i) {
            if (d.dayOfWeek() == weekStart) {
                return d.addDays(-1);
            }
            d = d.addDays(1);
        }
        return date;
    }
    case Monthly: {
        return QDate(date.year(), date.month(), date.daysInMonth());
    }
    default:
        return date;
    }
}

} // namespace tasktrackerlib
