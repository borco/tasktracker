/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskmodel.h"

#include "task.h"
#include "taskdurationmodel.h"

#include "yaml-cpp/yaml.h" // IWYU pragma: keep

#include <QDir>
#include <QFileInfo>

using namespace tasktrackerlib;

namespace {
static const char* TasksYamlNode = "tasks";

enum Roles {
    Name = Qt::UserRole + 1,
    IsEdited,
    IsDone,
    IsArchived,
    RepeatMode,
    TrackMode,
    Durations,
    Counts,
};
}

TaskModel::TaskModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

TaskModel::~TaskModel()
{
    qDeleteAll(m_tasks);
}

int TaskModel::rowCount(const QModelIndex &parent) const
{
    return m_tasks.count();
}

QHash<int, QByteArray> TaskModel::roleNames() const
{
    return {
        { Name, "name"},
        { IsEdited, "isEdited"},
        { IsArchived, "isArchived"},
        { IsDone, "isDone"},
        { RepeatMode, "repeatMode"},
        { TrackMode, "trackMode"},
        { Durations, "durations" },
        { Counts, "counts" },
    };
}

QVariant TaskModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto task = m_tasks[index.row()];

    switch(role) {
    case Name:
        return task->name();
    case IsEdited:
        return task->isEdited();
    case IsDone:
        return task->isDone();
    case IsArchived:
        return task->isArchived();
    case RepeatMode:
        return task->repeatMode();
    case TrackMode:
        return task->trackMode();
    case Durations:
        return QVariant::fromValue(task->durations());
    case Counts:
        return QVariant::fromValue(task->counts());
    }

    return QVariant();
}

bool TaskModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        QList<int> roles = {};

        switch(role) {
        case Name:
            m_tasks[index.row()]->setName(value.toString());
            roles << role;
            break;
        case IsEdited:
            m_tasks[index.row()]->setIsEdited(value.toBool());
            roles << role;
            break;
        case IsDone:
            m_tasks[index.row()]->setIsDone(value.toBool());
            roles << role;
            break;
        case IsArchived:
            m_tasks[index.row()]->setIsArchived(value.toBool());
            roles << role;
            break;
        case TrackMode:
            m_tasks[index.row()]->setTrackMode(TaskTrack::Mode(value.toInt()));
            roles << role;
            break;
        }

        if (!roles.isEmpty()) {
            emit dataChanged(index, index, roles);
            return true;
        } else {
            return false;
        }
    }
    return false;
}

Task* TaskModel::insertTask(int row, Task* task)
{
    beginInsertRows(QModelIndex(), row, row);
    if (row >= m_tasks.size()) {
        m_tasks.append(task);
    } else if (row == 0) {
        m_tasks.prepend(task);
    } else {
        m_tasks.insert(row, task);
    }
    setSize(m_tasks.size());
    endInsertRows();

    return task;
}

Task* TaskModel::prependTask()
{
    return insertTask(0, new Task(this));
}

void TaskModel::setSize(int newSize)
{
    if (m_size == newSize)
        return;
    m_size = newSize;
    emit sizeChanged();
}

void TaskModel::loadFromData(const QByteArray &data)
{
    YAML::Node node = YAML::Load(data.toStdString());
    auto tasks_node = node[TasksYamlNode];
    if (tasks_node) {
        if (!tasks_node.IsSequence()) {
            qCritical().nospace() << "TaskModel: '" << TasksYamlNode << "' is not a list";
        } else {
            loadTasks(tasks_node);
        }
    }
}

void TaskModel::loadTasks(const YAML::Node &node)
{
    assert(node.IsSequence());

    beginResetModel();
    qDeleteAll(m_tasks);
    m_tasks.clear();

    for (unsigned int i = 0; i < node.size(); ++i) {
        auto task = new Task(this);
        task->loadFromYaml(node[i]);
        insertTask(i, task);
    }

    setSize(m_tasks.size());
    endResetModel();
}

QByteArray TaskModel::saveToData() const
{
    return QByteArray();
}

void TaskModel::load(const QString &path, const QString &fileName)
{
    auto dir = QDir(path);
    auto info = QFileInfo(dir.filePath(fileName));
    auto absolute_file_path = info.absoluteFilePath();
    if (info.exists()) {
        qInfo() << "TaskModel: loading tasks from:" << absolute_file_path;
        auto file = QFile(absolute_file_path);
        file.open(QIODeviceBase::ReadOnly);
        loadFromData(file.readAll());
    } else {
        qInfo() << "TaskModel: tasks file not found:" << absolute_file_path;
    }
}

void TaskModel::save(const QString &path, const QString &fileName)
{
    QDir dir(path);
    QString absolute_file_path = QFileInfo(dir.filePath(fileName)).absoluteFilePath();
    qInfo() << "TaskModel: saving tasks to:" << absolute_file_path;
}
