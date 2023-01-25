/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskdurationmodel.h"

#include "task.h"
#include "taskdurationsortedlist.h"

namespace {
static const char* DurationsYamlNode = "durations";

enum Roles {
    Start = Qt::UserRole + 1,
    StartTime,
    Stop,
    StopTime,
    Seconds,
};
}

namespace tasktrackerlib {

TaskDurationModel::TaskDurationModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

TaskDurationModel::~TaskDurationModel()
{
    if (m_durations) {
        delete m_durations;
    }
}

int TaskDurationModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return size();
}

QHash<int, QByteArray> TaskDurationModel::roleNames() const
{
    return {
        { Start, "start" },
        { StartTime, "startTime" },
        { Stop, "stop" },
        { StopTime, "stopTime" },
        { Seconds, "seconds" },
    };
}

QVariant TaskDurationModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (m_durations) {
        auto duration = (*m_durations)[index.row()];

        switch(role) {
        case Start:
            return duration->start();
        case Stop:
            return duration->stop();
        case StartTime: {
            return duration->start().toLocalTime().time().toString();
        }
        case StopTime:
            return duration->stop().toLocalTime().time().toString();
        case Seconds:
            return duration->seconds();
        }
    }

    return QVariant();
}

bool TaskDurationModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

int TaskDurationModel::size() const
{
    return m_durations ? m_durations->size() : 0;
}

Task *TaskDurationModel::task() const
{
    return m_task;
}

void TaskDurationModel::setTask(Task *newTask)
{
    if (m_task == newTask)
        return;
    m_task = newTask;
    updateDurations();
    emit taskChanged();
}

QDate TaskDurationModel::date() const
{
    return m_date;
}

void TaskDurationModel::setDate(const QDate &newDate)
{
    if (m_date == newDate)
        return;
    m_date = newDate;
    updateDurations();
    emit dateChanged();
}

int TaskDurationModel::seconds() const
{
    return m_seconds;
}

void TaskDurationModel::setSeconds(int newSeconds)
{
    if (m_seconds == newSeconds)
        return;
    m_seconds = newSeconds;
    emit secondsChanged();
}

int TaskDurationModel::aggregateSeconds() const
{
    return m_aggregateSeconds;
}

void TaskDurationModel::setAggregateSeconds(int newAggregateSeconds)
{
    if (m_aggregateSeconds == newAggregateSeconds)
        return;
    m_aggregateSeconds = newAggregateSeconds;
    emit aggregateSecondsChanged();
}

void TaskDurationModel::updateDurations()
{
    beginResetModel();

    if (m_durations) {
        delete m_durations;
        m_durations = nullptr;
    }

    if (m_task && m_date.isValid()) {
        auto sorted_durations = m_task->sortedDurations();
        m_durations = sorted_durations->forDate(m_date);
    }

    emit sizeChanged();
    endResetModel();
}

} // namespace tasktrackerlib
