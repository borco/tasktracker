/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include "taskdurationmodel.h"

#include <QDate>

namespace tasktrackerlib {

class Task;

class TaskSelectedDate : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(Task* task READ task WRITE setTask NOTIFY taskChanged)
    Q_PROPERTY(QDate selectedDate READ selectedDate WRITE setSelectedDate NOTIFY selectedDateChanged)
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
    Q_PROPERTY(TaskDurationModel* durations READ durations CONSTANT)

    Q_PROPERTY(int aggregateCount READ aggregateCount NOTIFY aggregateCountChanged)

    Q_PROPERTY(int seconds READ seconds WRITE setSeconds NOTIFY secondsChanged) // seconds tracked durint selectedDate, regardless of trackAggregate
    Q_PROPERTY(int aggregateSeconds READ aggregateSeconds WRITE setAggregateSeconds NOTIFY aggregateSecondsChanged)

public:
    explicit TaskSelectedDate(QObject *parent = nullptr);

    Task *task() const;
    void setTask(Task *newTask);

    QDate selectedDate() const;
    void setSelectedDate(const QDate &newSelectedDate);

    int count() const;
    void setCount(int newCount);

    TaskDurationModel *durations() const;

    int aggregateCount() const;

    int seconds() const;
    void setSeconds(int newSeconds);

    int aggregateSeconds() const;
    void setAggregateSeconds(int newAggregateSeconds);

    Q_INVOKABLE static QString formattedSeconds(int seconds);

signals:
    void taskChanged();
    void selectedDateChanged();
    void countChanged();

    void aggregateCountChanged();

    void secondsChanged();

    void aggregateSecondsChanged();

private:
    void setAggregateCount(int newAggregateCount);

    void updateWrappedProperties();
    void updateCount(const QDate& date, int count);
    void updateAggregateCount();
    void updateAggregateInterval();

    Task *m_task = nullptr;
    QDate m_selectedDate;
    QDate m_aggregateBegin;
    QDate m_aggregateEnd;
    int m_count = 0;
    int m_aggregateCount = 0;
    TaskDurationModel *m_durations = nullptr;
    int m_seconds = 0;
    int m_aggregateSeconds = 0;
};

} // namespace tasktrackerlib
