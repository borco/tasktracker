/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "tasktrack.h"

namespace tasktrackerlib {

TaskTrack::TaskTrack(QObject *parent)
    : QObject{parent}
{
}

QString TaskTrack::toString(int trackMode)
{
    switch(trackMode) {
    case Count:
        return tr("Count");
    case Duration:
        return tr("Duration");
    default:
        return tr("Invalid track mode: %1").arg(trackMode);
    }
}

} // namespace tasktrackerlib
