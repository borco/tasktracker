/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskdurationmodel.h"

namespace {
static const char* DurationsYamlNode = "durations";

enum Roles {
    Time = Qt::UserRole + 1,
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
}

int TaskDurationModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_durations.size();
}

QHash<int, QByteArray> TaskDurationModel::roleNames() const
{
    return {
        { Time, "time" },
        { Seconds, "seconds" },
    };
}

QVariant TaskDurationModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto duration = m_durations[index.row()];

    switch(role) {
    case Seconds:
        return duration.seconds;
    case Time:
        return duration.time.toString();
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

void TaskDurationModel::clear()
{
    beginResetModel();
    m_durations.clear();
    endResetModel();
    emit sizeChanged();
}

void TaskDurationModel::setTimeDurations(const TimeDurations &timeDurations)
{
    beginResetModel();
    m_durations.clear();
    for (auto it = timeDurations.cbegin(); it != timeDurations.cend(); ++it) {
        m_durations << Duration { it.key(), it.value() };
    }
    endResetModel();
    emit sizeChanged();
}

int TaskDurationModel::size() const
{
    return m_durations.size();
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
    emit dateChanged();
}

} // namespace tasktrackerlib
