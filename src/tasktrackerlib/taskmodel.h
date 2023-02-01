/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include "yamlbackingstore.h"

#include <QQmlEngine>
#include <QAbstractListModel>

namespace tasktrackerlib {

class Task;

class TaskModel : public QAbstractListModel, public YamlBackingStore
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(int size READ size WRITE setSize NOTIFY sizeChanged)

public:
    explicit TaskModel(QObject *parent = nullptr);
    ~TaskModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    int size() const { return m_size; }
    void setSize(int newSize);

    void loadFromYaml(const YAML::Node &node) override;
    void saveToYaml(YAML::Emitter& out) const override;

    const Task* get(int row) const { return m_tasks[row]; }

    void moveTask(const QModelIndex &oldIndex, const QModelIndex &newIndex);

    Q_INVOKABLE void load(const QString& path, const QString& fileName = DefaultFileName);
    Q_INVOKABLE void save(const QString& path, const QString& fileName = DefaultFileName);

    Q_INVOKABLE tasktrackerlib::Task* prependTask();
    Q_INVOKABLE void deleteTask(tasktrackerlib::Task* task);

signals:
    void sizeChanged();

private:
    void loadTasks(const YAML::Node& node);
    tasktrackerlib::Task* insertTask(int row, Task* task);

    inline static const QString DefaultFileName = "tasks.yaml";

    QList<Task*> m_tasks;
    int m_size = 0;
};

}
