/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskaggregate.h"

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

} // namespace tasktrackerlib
