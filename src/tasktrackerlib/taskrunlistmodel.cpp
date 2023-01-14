/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskrunlistmodel.h"

#include "taskrun.h"

namespace tasktrackerlib {

TaskRunListModel::TaskRunListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

TaskRunListModel::~TaskRunListModel()
{
    qDeleteAll(m_taskRuns);
}

int TaskRunListModel::rowCount(const QModelIndex &parent) const
{
    return m_taskRuns.count();
}

QVariant TaskRunListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role) {
    case Start:
        return m_taskRuns[index.row()]->start();
    case Stop:
        return m_taskRuns[index.row()]->stop();
    case Duration:
        return m_taskRuns[index.row()]->duration();
    }

    return QVariant();
}

bool TaskRunListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        bool changed = false;

        switch(role) {
        case Start:
            m_taskRuns[index.row()]->setStart(value.toDateTime());
            changed = true;
            break;
        case Stop:
            m_taskRuns[index.row()]->setStop(value.toDateTime());
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

QHash<int, QByteArray> TaskRunListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Start] = "start";
    roles[Stop] = "stop";
    roles[Duration] = "duration";
    return roles;
}

} // namespace tasktrackerlib

