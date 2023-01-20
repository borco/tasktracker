/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "tasktrackmode.h"

namespace tasktrackerlib {

TaskTrackMode::TaskTrackMode(QObject *parent)
    : QObject{parent}
{
}

QString TaskTrackMode::toString(int trackMode)
{
    switch(trackMode) {
    case Repeats:
        return tr("Repeats");
    case Duration:
        return tr("Duration");
    default:
        return tr("Invalid track mode: %1").arg(trackMode);
    }
}

} // namespace tasktrackerlib
