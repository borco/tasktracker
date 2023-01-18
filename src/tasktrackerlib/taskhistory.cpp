/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskhistory.h"

#include "taskevent.h"

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
    qDeleteAll(m_events);
}

int TaskHistory::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_events.size();
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

    auto event = m_events[index.row()];

    switch(role) {
    case TrackMode:
        return event->trackMode();
    case DateTime:
        return event->dateTime();
    case Seconds:
        return event->seconds();
    case Date:
        return event->dateTime().date();
    case Time:
        return event->dateTime().time().toString();
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
    assert(node.IsMap());

    auto history_node = node[HistoryYamlNode];
    if (!history_node) {
        return;
    }

    if (!history_node.IsSequence()) {
        qCritical().nospace() << "TaskHistory: '" << HistoryYamlNode << "' is not a list";
        return;
    }

    beginResetModel();
    qDeleteAll(m_events);
    m_events.clear();

    for (unsigned int i = 0; i < history_node.size(); ++i) {
        auto event = new TaskEvent(this);
        event->loadFromYaml(history_node[i]);
        insertEvent(i, event);
    }

    endResetModel();
}

TaskEvent *TaskHistory::insertEvent(int row, TaskEvent *event)
{
    beginInsertRows(QModelIndex(), row, row);
    m_events.insert(row, event);
    endInsertRows();
    return event;
}

} // namespace tasktrackerlib
