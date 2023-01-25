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

QDate TaskCount::selectedDate() const
{
    return m_selectedDate;
}

void TaskCount::setSelectedDate(const QDate &newSelectedDate)
{
    if (m_selectedDate == newSelectedDate)
        return;
    m_selectedDate = newSelectedDate;
    updateAggregateInterval();
    updateWrappedProperties();
    emit selectedDateChanged();
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
        m_task->setCount(m_selectedDate, m_count);
    }
    emit countChanged();
}

void TaskCount::updateWrappedProperties()
{
    if (m_task && m_selectedDate.isValid()) {
        setCount(m_task->count(m_selectedDate));
    } else {
        setCount(0);
    }
    updateAggregateCount();
}

void TaskCount::updateCount(const QDate &date, int count)
{
    if (date == m_selectedDate) {
        setCount(count);
        updateAggregateCount();
    } else if (date >= m_aggregateBegin && date <= m_aggregateEnd) {
        updateAggregateCount();
    }
}

void TaskCount::updateAggregateCount()
{
    if (!m_task || !m_selectedDate.isValid()) {
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
    if (m_task && m_selectedDate.isValid()) {
        auto week_start = Config::get()->weekStart();
        m_aggregateBegin = TaskAggregate::aggregateBegin(week_start, m_task->aggregateMode(), m_selectedDate);
        m_aggregateEnd = TaskAggregate::aggregateEnd(week_start, m_task->aggregateMode(), m_selectedDate);
    } else {
        m_aggregateBegin = m_selectedDate;
        m_aggregateEnd = m_selectedDate;
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
