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
