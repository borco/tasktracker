/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "tasklistmodel.h"

#include "task.h"

using namespace tasktrackerlib;

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

QVariant TaskListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role) {
    case NameRole:
        return m_tasks[index.row()]->name();
    }

    return QVariant();
}

bool TaskListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        bool changed = false;

        switch(role) {
        case NameRole:
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

QHash<int, QByteArray> TaskListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    return roles;
}

Task* TaskListModel::prependTask()
{
    auto task = new Task(this);
    beginInsertRows(QModelIndex(), 0, 0);
    m_tasks.prepend(task);
    setSize(m_tasks.size());
    endInsertRows();
    return task;
}

void TaskListModel::setSize(int newSize)
{
    if (m_size == newSize)
        return;
    m_size = newSize;
    emit sizeChanged();
}
