/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include "taskevent.h"

#include <QAbstractTableModel>

namespace tasktrackerlib {

class TaskHistory : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("History can be created only in C++")

public:
    explicit TaskHistory(QObject *parent = nullptr);
    ~TaskHistory() override;

    QHash<int, QByteArray> roleNames() const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

//    Qt::ItemFlags flags(const QModelIndex& index) const override;

    Q_INVOKABLE bool insertEvent(int row);
    Q_INVOKABLE bool removeEvent(int row);
    Q_INVOKABLE bool appendEvent();
    Q_INVOKABLE bool removeLastEvent();

private:
    enum Roles {
        DateTime = Qt::UserRole + 1,
        TrackMode,
        Seconds
    };

    QList<TaskEvent*> m_events;
};

} // namespace tasktrackerlib

