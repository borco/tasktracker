/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskrepeatmode.h"

namespace tasktrackerlib {

TaskRepeatMode::TaskRepeatMode(QObject *parent)
    : QObject{parent}
{
}

QString TaskRepeatMode::toString(int repeatMode)
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
    case Before:
        return tr("Before");
    case After:
        return tr("After");
    case Between:
        return tr("Between");
    default:
        return tr("Invalid schedule mode: %1").arg(repeatMode);
    }
}

} // namespace tasktrackerlib
