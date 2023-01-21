/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskdurationmodel.h"

#include "taskduration.h"

#include "yaml-cpp/yaml.h" // IWYU pragma: keep

namespace {
static const char* DurationsYamlNode = "durations";

enum Roles {
    DateTime = Qt::UserRole + 1,
    Seconds,
    Date,
    Time,
};
}

namespace tasktrackerlib {

TaskDurationModel::TaskDurationModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

TaskDurationModel::~TaskDurationModel()
{
    qDeleteAll(m_durations);
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
        { DateTime, "dateTime" },
        { Seconds, "seconds" },
        { Date, "date" },
        { Time, "time" },
    };
}

QVariant TaskDurationModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto duration = m_durations[index.row()];

    switch(role) {
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

bool TaskDurationModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

void TaskDurationModel::loadFromData(const QByteArray &data)
{
    YAML::Node node = YAML::Load(data.toStdString());
    loadFromYaml(node);
}

void TaskDurationModel::loadFromYaml(const YAML::Node &node)
{
    assert(node.IsMap() || node.IsNull());

    if (node.IsNull()) {
        clear();
        return;
    }

    auto durations_node = node[DurationsYamlNode];
    if (!durations_node) {
        clear();
        return;
    }

    if (!durations_node.IsSequence()) {
        qCritical().nospace() << "TaskDurationModel: '" << DurationsYamlNode << "' is not a list";
        clear();
        return;
    }

    beginResetModel();
    qDeleteAll(m_durations);
    m_durations.clear();

    for (unsigned int i = 0; i < durations_node.size(); ++i) {
        auto duration = new TaskDuration(this);
        duration->loadFromYaml(durations_node[i]);
        insertDuration(i, duration);
    }

    std::sort(m_durations.begin(), m_durations.end(), [](const TaskDuration* e1, const TaskDuration* e2) { return e1->dateTime() < e2->dateTime(); });

    endResetModel();

    emit sizeChanged();
}

void TaskDurationModel::insertDuration(int row, TaskDuration *duration)
{
    beginInsertRows(QModelIndex(), row, row);
    m_durations.insert(row, duration);
    endInsertRows();
    emit sizeChanged();
}

void TaskDurationModel::clear()
{
    beginResetModel();
    qDeleteAll(m_durations);
    m_durations.clear();
    endResetModel();
    emit sizeChanged();
}

int TaskDurationModel::size() const
{
    return m_durations.size();
}

TaskDuration *TaskDurationModel::get(int index) const
{
    return m_durations[index];
}

} // namespace tasktrackerlib
