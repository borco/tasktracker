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
    case NoTracking:
        return tr("No tracking");
    case Repeats:
        return tr("Repeats");
    case MinimumRepeats:
        return tr("Minimum repeats");
    case MaximumRepeats:
        return tr("Maximum repeats");
    case Duration:
        return tr("Duration");
    case MinimumDuration:
        return tr("Minimum duration");
    case MaximumDuration:
        return tr("Maximum duration");
    default:
        return tr("Invalid track mode: %1").arg(trackMode);
    }
}

} // namespace tasktrackerlib
