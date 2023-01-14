/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QQmlEngine>
#include <QAbstractListModel>

namespace tasktrackerlib {

class TaskRun;

class TaskRunListModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(int size READ size NOTIFY sizeChanged)

public:
    explicit TaskRunListModel(QObject *parent = nullptr);
    ~TaskRunListModel();

    int size() const { return rowCount(); }
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QHash<int, QByteArray> roleNames() const override;

signals:
    void sizeChanged();

private:
    enum Roles {
        Start,
        Stop,
        Duration,
    };

    QList<TaskRun*> m_taskRuns;
};

} // namespace tasktrackerlib

