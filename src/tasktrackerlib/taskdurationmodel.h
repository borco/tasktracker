/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QAbstractListModel>
#include <QQmlEngine>

namespace YAML { class Node; }

namespace tasktrackerlib {

class TaskDuration;

class TaskDurationModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("TaskDurationModel can be created only in C++")

    Q_PROPERTY(int size READ size NOTIFY sizeChanged)

public:
    explicit TaskDurationModel(QObject *parent = nullptr);
    ~TaskDurationModel() override;

    int size() const;
    TaskDuration* get(int index) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    void loadFromData(const QByteArray& data);
    void loadFromYaml(const YAML::Node &node);

signals:
    void sizeChanged();

private:
    void insertDuration(int row, TaskDuration* duration);
    void clear();

    QList<TaskDuration*> m_durations;
};

} // namespace tasktrackerlib
