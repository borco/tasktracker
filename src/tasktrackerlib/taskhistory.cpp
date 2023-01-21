/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskhistory.h"

#include "taskduration.h"

#include "yaml-cpp/yaml.h" // IWYU pragma: keep

namespace {
static const char* HistoryYamlNode = "history";
}

namespace tasktrackerlib {

TaskHistory::TaskHistory(QObject *parent)
    : QAbstractListModel(parent)
{
}

TaskHistory::~TaskHistory()
{
    qDeleteAll(m_durations);
}

int TaskHistory::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_durations.size();
}

QHash<int, QByteArray> TaskHistory::roleNames() const
{
    return {
        { TrackMode, "trackMode" },
        { DateTime, "dateTime" },
        { Seconds, "seconds" },
        { Date, "date" },
        { Time, "time" },
    };
}

QVariant TaskHistory::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto duration = m_durations[index.row()];

    switch(role) {
    case TrackMode:
        return duration->trackMode();
    case DateTime:
        return duration->dateTime();
    case Seconds:
        return duration->seconds();
    case Date:
        return duration->dateTime().date();
    case Time:
        return duration->dateTime().time().toString();
    }

    return QVariant();
}

bool TaskHistory::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

void TaskHistory::loadFromData(const QByteArray &data)
{
    YAML::Node node = YAML::Load(data.toStdString());
    loadFromYaml(node);
}

void TaskHistory::loadFromYaml(const YAML::Node &node)
{
    assert(node.IsMap() || node.IsNull());

    if (node.IsNull()) {
        clear();
        return;
    }

    auto history_node = node[HistoryYamlNode];
    if (!history_node) {
        clear();
        return;
    }

    if (!history_node.IsSequence()) {
        qCritical().nospace() << "TaskHistory: '" << HistoryYamlNode << "' is not a list";
        clear();
        return;
    }

    beginResetModel();
    qDeleteAll(m_durations);
    m_durations.clear();

    for (unsigned int i = 0; i < history_node.size(); ++i) {
        auto duration = new TaskDuration(this);
        duration->loadFromYaml(history_node[i]);
        insertEvent(i, duration);
    }

    std::sort(m_durations.begin(), m_durations.end(), [](const TaskDuration* e1, const TaskDuration* e2) { return e1->dateTime() < e2->dateTime(); });

    endResetModel();

    emit sizeChanged();
}

TaskDuration *TaskHistory::insertEvent(int row, TaskDuration *duration)
{
    beginInsertRows(QModelIndex(), row, row);
    m_durations.insert(row, duration);
    endInsertRows();
    emit sizeChanged();
    return duration;
}

void TaskHistory::clear()
{
    beginResetModel();
    qDeleteAll(m_durations);
    m_durations.clear();
    endResetModel();
    emit sizeChanged();
}

int TaskHistory::size() const
{
    return m_durations.size();
}

TaskDuration *TaskHistory::get(int index) const
{
    return m_durations[index];
}

} // namespace tasktrackerlib
