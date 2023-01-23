/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskselecteddate.h"

#include "config.h"
#include "task.h"

namespace tasktrackerlib {

TaskSelectedDate::TaskSelectedDate(QObject *parent)
    : QObject{parent}
    , m_durations(new TaskDurationModel(this))
{
    connect(Config::get(), &Config::weekStartChanged, this, &TaskSelectedDate::updateAggregateInterval);
}

Task *TaskSelectedDate::task() const
{
    return m_task;
}

void TaskSelectedDate::setTask(Task *newTask)
{
    if (m_task == newTask)
        return;

    if (m_task)
        m_task->disconnect(this);

    m_task = newTask;

    if (m_task) {
        connect(m_task, &Task::countChanged, this, &TaskSelectedDate::updateCount);
        connect(m_task, &Task::aggregateModeChanged, this, &TaskSelectedDate::updateAggregateInterval);
    }

    updateAggregateInterval();
    updateWrappedProperties();
    emit taskChanged();
}

QDate TaskSelectedDate::selectedDate() const
{
    return m_selectedDate;
}

void TaskSelectedDate::setSelectedDate(const QDate &newSelectedDate)
{
    if (m_selectedDate == newSelectedDate)
        return;
    m_selectedDate = newSelectedDate;
    updateAggregateInterval();
    updateWrappedProperties();
    emit selectedDateChanged();
}

int TaskSelectedDate::count() const
{
    return m_count;
}

void TaskSelectedDate::setCount(int newCount)
{
    if (m_count == newCount)
        return;
    m_count = newCount;
    if (m_task) {
        m_task->setCount(m_selectedDate, m_count);
    }
    emit countChanged();
}

void TaskSelectedDate::updateWrappedProperties()
{
    if (m_task && m_selectedDate.isValid()) {
        setCount(m_task->count(m_selectedDate));
        m_durations->setTimeDurations(m_task->timeDurations(m_selectedDate));
        updateAggregateCount();
    } else {
        setCount(0);
        m_durations->clear();
        updateAggregateCount();
    }
}

void TaskSelectedDate::updateCount(const QDate &date, int count)
{
    if (date == m_selectedDate) {
        setCount(count);
        updateAggregateCount();
    } else if (date >= m_aggregateBegin && date <= m_aggregateEnd) {
        updateAggregateCount();
    }

}

void TaskSelectedDate::updateAggregateCount()
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

void TaskSelectedDate::updateAggregateInterval()
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

TaskDurationModel *TaskSelectedDate::durations() const
{
    return m_durations;
}

int TaskSelectedDate::aggregateCount() const
{
    return m_aggregateCount;
}

void TaskSelectedDate::setAggregateCount(int newAggregateCount)
{
    if (m_aggregateCount == newAggregateCount)
        return;
    m_aggregateCount = newAggregateCount;
    emit aggregateCountChanged();
}

} // namespace tasktrackerlib
