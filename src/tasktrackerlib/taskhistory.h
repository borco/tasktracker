/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include "taskevent.h"

#include <QAbstractListModel>

namespace YAML { class Node; }

namespace tasktrackerlib {

class TaskHistory : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("History can be created only in C++")

public:
    explicit TaskHistory(QObject *parent = nullptr);
    ~TaskHistory() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    void loadFromData(const QByteArray& data);
    void loadFromYaml(const YAML::Node &node);

private:
    enum Roles {
        TrackMode = Qt::UserRole + 1,
        DateTime,
        Seconds,
        Date,
        Time,
    };

    tasktrackerlib::TaskEvent* insertEvent(int row, TaskEvent* event);

    QList<TaskEvent*> m_events;
};

} // namespace tasktrackerlib

