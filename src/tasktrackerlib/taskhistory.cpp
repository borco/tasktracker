/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskhistory.h"

namespace tasktrackerlib {

TaskHistory::TaskHistory(QObject *parent)
    : QAbstractTableModel(parent)
{
}

TaskHistory::~TaskHistory()
{
    qDeleteAll(m_events);
}

QHash<int, QByteArray> TaskHistory::roleNames() const
{
    return {
        { DateTime, "dateTime" },
        { TrackMode, "trackMode" },
        { Seconds, "seconds" },
    };
}

int TaskHistory::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_events.size();
}

int TaskHistory::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 3;
}

QVariant TaskHistory::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
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

//Qt::ItemFlags TaskHistory::flags(const QModelIndex &index) const
//{
//    if (!index.isValid())
//        return Qt::NoItemFlags;

//    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
//}

bool TaskHistory::insertEvent(int row)
{
    beginInsertRows(QModelIndex(), row, row);
    auto event = new TaskEvent(this);
    m_events.insert(row, event);
    endInsertRows();
    return true;
}

bool TaskHistory::removeEvent(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    auto event = m_events.takeAt(row);
    delete event;
    endRemoveRows();
    return true;
}

bool TaskHistory::appendEvent()
{
    return insertEvent(m_events.size());
}

bool TaskHistory::removeLastEvent()
{
    return removeEvent(m_events.size() - 1);
}

} // namespace tasktrackerlib

