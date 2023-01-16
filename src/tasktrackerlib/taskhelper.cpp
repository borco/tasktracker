#include "taskhelper.h"

#include "task.h"

namespace tasktrackerlib {

TaskHelper::TaskHelper(QObject *parent)
    : QObject{parent}
{

}

QString TaskHelper::trackModeName(int trackMode) const
{
    switch(trackMode) {
    case Task::NoTracking:
        return tr("No tracking");
    case Task::Repeats:
        return tr("Repeats");
    case Task::MinimumRepeats:
        return tr("Minimum repeats");
    case Task::MaximumRepeats:
        return tr("Maximum repeats");
    case Task::Duration:
        return tr("Duration");
    case Task::MinimumDuration:
        return tr("Minimum duration");
    case Task::MaximumDuration:
        return tr("Maximum duration");
    default:
        return tr("Invalid track mode: %1").arg(trackMode);
    }
}

QString TaskHelper::scheduleModeName(int scheduleMode) const
{
    switch(scheduleMode) {
    case Task::Daily:
        return tr("Daily");
    case Task::Weekly:
        return tr("Weekly");
    case Task::Monthly:
        return tr("Monthly");
    case Task::Once:
        return tr("Once");
    case Task::Before:
        return tr("Before");
    case Task::After:
        return tr("After");
    case Task::Between:
        return tr("Between");
    default:
        return tr("Invalid schedule mode: %1").arg(scheduleMode);
    }
}

}
