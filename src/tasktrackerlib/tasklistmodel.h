/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QQmlEngine>
#include <QAbstractListModel>

namespace tasktrackerlib {

class Task;

class TaskListModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(int size READ size WRITE setSize NOTIFY sizeChanged)

public:
    explicit TaskListModel(QObject *parent = nullptr);
    ~TaskListModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QHash<int, QByteArray> roleNames() const override;

    int size() const { return m_size; }
    void setSize(int newSize);

signals:
    void sizeChanged();

public slots:
    void load(const QString& path, const QString& fileName = DefaultFileName);
    void save(const QString& path, const QString& fileName = DefaultFileName);

    tasktrackerlib::Task* prependTask();

private:
    enum Roles {
        NameRole = Qt::UserRole + 1,
    };

    inline static const QString DefaultFileName = "tasks.yaml";

    QList<Task*> m_tasks;
    int m_size = 0;
};

}