/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskmodel.h"

#include "task.h"

#include "yaml-cpp/yaml.h" // IWYU pragma: keep

#include <QDir>
#include <QFileInfo>

#include <fstream>

namespace {
static const char* TasksYamlNode = "tasks";

enum Roles {
    Task = Qt::UserRole + 1,
    IsEdited,
    IsDone,
    IsArchived,
};
}

namespace tasktrackerlib {

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
        { ::Task, "task" },
        { IsEdited, "isEdited"},
        { IsArchived, "isArchived"},
        { IsDone, "isDone"},
    };
}

QVariant TaskModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto task = m_tasks[index.row()];
    switch(role) {
    case ::Task:
        return QVariant::fromValue(task);
            case IsEdited:
        return task->isEdited();
    case IsDone:
        return task->isDone();
    case IsArchived:
        return task->isArchived();
    }

    return QVariant();
}

bool TaskModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        QList<int> roles = {};

        switch(role) {
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

void TaskModel::deleteTask(Task *task)
{
    if (!task)
        return;

    auto row = m_tasks.indexOf(task);
    if (row < 0) {
        qCritical().nospace() << "Could not find task \"" << task->name() << "\"and delete it";
        return;
    }

    beginRemoveRows(QModelIndex(), row, row);
    m_tasks.removeAt(row);
    task->deleteLater();
    endRemoveRows();
}

void TaskModel::moveTask(int oldRow, const int newRow)
{
    beginMoveRows(QModelIndex(), oldRow, oldRow, QModelIndex(), oldRow < newRow ? newRow + 1: newRow);
    m_tasks.move(oldRow, newRow);
    endMoveRows();
}

void TaskModel::setSize(int newSize)
{
    if (m_size == newSize)
        return;
    m_size = newSize;
    emit sizeChanged();
}

void TaskModel::loadFromYaml(const YAML::Node &node)
{
    auto tasks_node = node[TasksYamlNode];
    if (tasks_node) {
        if (!tasks_node.IsSequence()) {
            qCritical() << TasksYamlNode << "is not a list";
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

void TaskModel::load(const QString &path, const QString &fileName)
{
    auto dir = QDir(path);
    auto info = QFileInfo(dir.filePath(fileName));
    auto absolute_file_path = info.absoluteFilePath();
    if (info.exists()) {
        qInfo() << "Loading tasks from:" << absolute_file_path;
        auto file = QFile(absolute_file_path);
        file.open(QIODeviceBase::ReadOnly);
        loadFromData(file.readAll());
    } else {
        qCritical() << "Tasks file not found:" << absolute_file_path;
    }
}

void TaskModel::saveToYaml(YAML::Emitter& out) const
{
    if (m_tasks.empty())
        return;

    out << YAML::BeginMap;
    out << YAML::Key << TasksYamlNode;
    out << YAML::Value << YAML::BeginSeq;
    for (const auto& task: m_tasks) {
        task->saveToYaml(out);
    }
    out << YAML::EndSeq;
    out << YAML::EndMap;
}

void TaskModel::save(const QString &path, const QString &fileName)
{
    QDir dir(path);
    QString absolute_file_path = QFileInfo(dir.filePath(fileName)).absoluteFilePath();

    std::ofstream ofs;
    ofs.open(absolute_file_path.toStdString(), std::ofstream::out | std::ofstream::trunc);

    if (ofs) {
        qInfo() << "Saving tasks to:" << absolute_file_path;
        YAML::Emitter out(ofs);
        saveToYaml(out);
    } else {
        qCritical() << "Counld not open file for writing:" << absolute_file_path;
    }
}

} // tasktrackerlib
