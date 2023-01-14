/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "tasklistmodel.h"

#include "qtyamlcppadapter/enumhelper.h"
#include "task.h"
#include "yaml-cpp/yaml.h" // IWYU pragma: keep

#include <QDir>
#include <QFileInfo>

using namespace tasktrackerlib;

namespace {
static const char* TasksYamlNode = "tasks";
}

TaskListModel::TaskListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

TaskListModel::~TaskListModel()
{
    qDeleteAll(m_tasks);
}

int TaskListModel::rowCount(const QModelIndex &parent) const
{
    return m_tasks.count();
}

QHash<int, QByteArray> TaskListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Name] = "name";
    roles[IsArchived] = "isArchived";
    roles[ScheduleMode] = "scheduleMode";
    roles[ScheduleModeText] = "scheduleModeText";
    roles[TrackMode] = "trackMode";
    roles[TrackModeText] = "trackModeText";
    return roles;
}

QVariant TaskListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto task = m_tasks[index.row()];

    switch(role) {
    case Name:
        return task->name();
    case IsArchived:
        return task->isArchived();
    case ScheduleMode:
        return task->scheduleMode();
    case ScheduleModeText:
        return qtyamlcppadapter::toString(task->scheduleMode());
    case TrackMode:
        return task->trackMode();
    case TrackModeText:
        return qtyamlcppadapter::toString(task->trackMode());
    }

    return QVariant();
}

bool TaskListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        bool changed = false;

        switch(role) {
        case Name:
            m_tasks[index.row()]->setName(value.toString());
            changed = true;
            break;
        }

        if (changed) {
            emit dataChanged(index, index, {role});
            return true;
        } else {
            return false;
        }
    }
    return false;
}

Task* TaskListModel::insertTask(int row, Task* task)
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

Task* TaskListModel::prependTask()
{
    return insertTask(0, new Task(this));
}

void TaskListModel::setSize(int newSize)
{
    if (m_size == newSize)
        return;
    m_size = newSize;
    emit sizeChanged();
}

void TaskListModel::loadFromData(const QByteArray &data)
{
    beginResetModel();
    qDeleteAll(m_tasks);
    m_tasks.clear();

    YAML::Node node = YAML::Load(data.toStdString());
    auto tasks_node = node[TasksYamlNode];
    if (tasks_node) {
        if (!tasks_node.IsSequence()) {
            qCritical().nospace() << "TaskListModel: '" << TasksYamlNode << "' is not a list";
        } else {
            loadTasks(tasks_node);
        }
    }

    setSize(m_tasks.size());
    endResetModel();
}

void TaskListModel::loadTasks(const YAML::Node &node)
{
    assert(node.IsSequence());

    for (unsigned int i = 0; i < node.size(); ++i) {
        auto task = new Task(this);
        task->loadFromYaml(node[i]);
        insertTask(i, task);
    }
}

QByteArray TaskListModel::saveToData() const
{
    return QByteArray();
}

void TaskListModel::load(const QString &path, const QString &fileName)
{
    auto dir = QDir(path);
    auto info = QFileInfo(dir.filePath(fileName));
    auto absolute_file_path = info.absoluteFilePath();
    if (info.exists()) {
        qInfo() << "TaskListModel: loading tasks from:" << absolute_file_path;
        auto file = QFile(absolute_file_path);
        file.open(QIODeviceBase::ReadOnly);
        loadFromData(file.readAll());
    } else {
        qInfo() << "TaskListModel: tasks file not found:" << absolute_file_path;
    }
}

void TaskListModel::save(const QString &path, const QString &fileName)
{
    QDir dir(path);
    QString absolute_file_path = QFileInfo(dir.filePath(fileName)).absoluteFilePath();
    qInfo() << "TaskListModel: saving tasks to:" << absolute_file_path;
}
