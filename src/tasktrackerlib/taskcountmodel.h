/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QAbstractListModel>
#include <QQmlEngine>

namespace YAML { class Node; }

namespace tasktrackerlib {

class TaskCount;

class TaskCountModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("TaskCountModel can be created only in C++")

public:
    explicit TaskCountModel(QObject *parent = nullptr);
    ~TaskCountModel() override;

    int size() const;
    TaskCount* get(int index) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    void loadFromData(const QByteArray& data);
    void loadFromYaml(const YAML::Node &node);

private:
    void insertCount(int row, TaskCount* count);
    void clear();

    QList<TaskCount*> m_counts;
};

} // namespace tasktrackerlib
