/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskdurationmodel.h"

#include "task.h"
#include "taskdurationsortedlist.h"

#include <QTimeZone>

namespace {
static const char* DurationsYamlNode = "durations";

enum Roles {
    Start = Qt::UserRole + 1,
    StartTime,
    Stop,
    StopTime,
    Seconds,
    Duration, // for modifying start & stop at the same time!
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
        { Duration, "duration" },
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

const TaskDuration *TaskDurationModel::duration(int row) const
{
    return (*m_durations)[row];
}

void TaskDurationModel::setDuration(int row, const TaskDuration *newDuration)
{
    auto duration = (*m_durations)[row];

    const auto& old_start = duration->start();
    const auto& new_start = newDuration->start();

    duration->setStart(newDuration->start());
    duration->setStop(newDuration->stop());

    auto prev_duration = row > 0 ? (*m_durations)[row-1] : nullptr;
    auto next_duration = row < m_durations->size() - 1 ? (*m_durations)[row+1] : nullptr;

    if (old_start == new_start
            || (prev_duration == nullptr && new_start < old_start)
            || (next_duration == nullptr && new_start > old_start)
            ) {
        emit dataChanged(index(row), index(row), QList<int>() << Start << Stop << StartTime << StopTime << Seconds);
        return;
    }

    beginResetModel();
    m_durations->sort();
    endResetModel();
}

bool TaskDurationModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Duration) {
        auto newDuration = value.value<TaskDuration*>();
        if (newDuration) {
            setDuration(index.row(), newDuration);
            return true;
        }
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

void TaskDurationModel::addDuration(const QVariant &value)
{
    // TODO
    auto newDuration = value.value<TaskDuration*>();
    if (newDuration) {
        qDebug() << "trying to add duration:" << newDuration->start() << newDuration->stop();
    } else {
        qCritical() << value << "is not a TaskDuration";
    }

}

QDateTime TaskDurationModel::nextFreeLocalTime() const
{
    QDateTime ret(m_date, QTime(), QTimeZone::UTC);
    ret.setTimeZone(QTimeZone::LocalTime);

    auto last = m_durations->last();
    if (last && last->stop().isValid()) {
        ret.setTime(last->stop().toLocalTime().time());
    } else {
        ret.setTime(QTime(0, 0, 0));
    }

    return ret;
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
