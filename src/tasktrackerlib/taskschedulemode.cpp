/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskschedulemode.h"

namespace tasktrackerlib {

TaskScheduleMode::TaskScheduleMode(QObject *parent)
    : QObject{parent}
{
}

QString TaskScheduleMode::toString(int scheduleMode)
{
    switch(scheduleMode) {
    case Daily:
        return tr("Daily");
    case Weekly:
        return tr("Weekly");
    case Monthly:
        return tr("Monthly");
    case Once:
        return tr("Once");
    case Before:
        return tr("Before");
    case After:
        return tr("After");
    case Between:
        return tr("Between");
    default:
        return tr("Invalid schedule mode: %1").arg(scheduleMode);
    }
}

} // namespace tasktrackerlib
