/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QDate>
#include <QQmlEngine>

namespace tasktrackerlib {

class Task;

class TaskCount : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(Task* task READ task WRITE setTask NOTIFY taskChanged)
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
    Q_PROPERTY(int aggregateCount READ aggregateCount NOTIFY aggregateCountChanged)

public:
    explicit TaskCount(QObject *parent = nullptr);

    Task *task() const;
    void setTask(Task *newTask);

    QDate date() const;
    void setDate(const QDate &newDate);

    int count() const;
    void setCount(int newCount);

    int aggregateCount() const;

signals:
    void taskChanged();
    void dateChanged();
    void countChanged();
    void aggregateCountChanged();

private:
    void setAggregateCount(int newAggregateCount);

    void updateWrappedProperties();
    void updateCount(const QDate& date, int count);
    void updateAggregateCount();
    void updateAggregateInterval();

    Task *m_task = nullptr;
    QDate m_date;
    QDate m_aggregateBegin;
    QDate m_aggregateEnd;
    int m_count = 0;
    int m_aggregateCount = 0;
};

} // namespace tasktrackerlib
