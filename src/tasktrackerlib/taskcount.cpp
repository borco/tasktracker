/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskcount.h"

#include "config.h"
#include "task.h"

namespace tasktrackerlib {

TaskCount::TaskCount(QObject *parent)
    : QObject{parent}
{
    connect(Config::get(), &Config::weekStartChanged, this, &TaskCount::updateAggregateInterval);
}

Task *TaskCount::task() const
{
    return m_task;
}

void TaskCount::setTask(Task *newTask)
{
    if (m_task == newTask)
        return;

    if (m_task)
        m_task->disconnect(this);

    m_task = newTask;

    if (m_task) {
        connect(m_task, &Task::countChanged, this, &TaskCount::updateCount);
        connect(m_task, &Task::aggregateModeChanged, this, &TaskCount::updateAggregateInterval);
    }

    updateAggregateInterval();
    updateWrappedProperties();
    emit taskChanged();
}

QDate TaskCount::date() const
{
    return m_date;
}

void TaskCount::setDate(const QDate &newDate)
{
    if (m_date == newDate)
        return;
    m_date = newDate;
    updateAggregateInterval();
    updateWrappedProperties();
    emit dateChanged();
}

int TaskCount::count() const
{
    return m_count;
}

void TaskCount::setCount(int newCount)
{
    if (m_count == newCount)
        return;
    m_count = newCount;
    if (m_task) {
        m_task->setCount(m_date, m_count);
    }
    emit countChanged();
}

void TaskCount::updateWrappedProperties()
{
    if (m_task && m_date.isValid()) {
        setCount(m_task->count(m_date));
    } else {
        setCount(0);
    }
    updateAggregateCount();
}

void TaskCount::updateCount(const QDate &date, int count)
{
    if (date == m_date) {
        setCount(count);
        updateAggregateCount();
    } else if (date >= m_aggregateBegin && date <= m_aggregateEnd) {
        updateAggregateCount();
    }
}

void TaskCount::updateAggregateCount()
{
    if (!m_task || !m_date.isValid()) {
        setAggregateCount(0);
        return;
    }

    int aggregate_count = 0;
    for (auto date = m_aggregateBegin; date <= m_aggregateEnd; date = date.addDays(1)) {
        aggregate_count += m_task->count(date);
    }
    setAggregateCount(aggregate_count);
}

void TaskCount::updateAggregateInterval()
{
    if (m_task && m_date.isValid()) {
        auto week_start = Config::get()->weekStart();
        m_aggregateBegin = TaskAggregate::aggregateBegin(week_start, m_task->aggregateMode(), m_date);
        m_aggregateEnd = TaskAggregate::aggregateEnd(week_start, m_task->aggregateMode(), m_date);
    } else {
        m_aggregateBegin = m_date;
        m_aggregateEnd = m_date;
    }

    updateAggregateCount();
}

int TaskCount::aggregateCount() const
{
    return m_aggregateCount;
}

void TaskCount::setAggregateCount(int newAggregateCount)
{
    if (m_aggregateCount == newAggregateCount)
        return;
    m_aggregateCount = newAggregateCount;
    emit aggregateCountChanged();
}

} // namespace tasktrackerlib
