/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskrepeat.h"

namespace tasktrackerlib {

TaskRepeat::TaskRepeat(QObject *parent)
    : QObject{parent}
{
}

QString TaskRepeat::toString(int repeatMode)
{
    switch(repeatMode) {
    case Daily:
        return tr("Daily");
    case Weekly:
        return tr("Weekly");
    case Monthly:
        return tr("Monthly");
    case Once:
        return tr("Once");
    default:
        return tr("Invalid schedule mode: %1").arg(repeatMode);
    }
}

} // namespace tasktrackerlib
