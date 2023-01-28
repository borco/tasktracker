/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QAbstractListModel>
#include <QDateTime>
#include <QQmlEngine>

namespace YAML { class Node; }

namespace tasktrackerlib {

class Task;
class TaskDuration;
class TaskDurationSortedList;

class TaskDurationModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(int size READ size NOTIFY sizeChanged)
    Q_PROPERTY(Task* task READ task WRITE setTask NOTIFY taskChanged)
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged)

    Q_PROPERTY(int seconds READ seconds WRITE setSeconds NOTIFY secondsChanged)
    Q_PROPERTY(int aggregateSeconds READ aggregateSeconds WRITE setAggregateSeconds NOTIFY aggregateSecondsChanged)

public:
    explicit TaskDurationModel(QObject *parent = nullptr);
    ~TaskDurationModel() override;

    int size() const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Task *task() const;
    void setTask(Task *newTask);

    QDate date() const;
    void setDate(const QDate &newDate);

    int seconds() const;
    void setSeconds(int newSeconds);

    int aggregateSeconds() const;
    void setAggregateSeconds(int newAggregateSeconds);

    const TaskDuration* duration(int row) const;
    void setDuration(int row, const TaskDuration* newDuration);

    Q_INVOKABLE void addDuration(const QVariant& value);
    Q_INVOKABLE QDateTime nextFreeLocalTime() const;

signals:
    void sizeChanged();
    void taskChanged();
    void dateChanged();
    void secondsChanged();
    void aggregateSecondsChanged();

private:
    void updateDurations();
    void onSorted();

    Task *m_task = nullptr;
    QDate m_date;
    TaskDurationSortedList* m_durations = nullptr;
    int m_seconds = 0;
    int m_aggregateSeconds = 0;
};

} // namespace tasktrackerlib
