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
    } else {
        setCount(0);
        m_durations->clear();
    }
    updateAggregateCount();
    updateSeconds();
    updateAggregateSeconds();
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
    updateAggregateSeconds();
}

void TaskSelectedDate::updateSeconds()
{
    setSeconds(seconds(m_selectedDate, m_selectedDate));
}

void TaskSelectedDate::updateAggregateSeconds()
{
    setAggregateSeconds(seconds(m_aggregateBegin, m_aggregateEnd));
}

int TaskSelectedDate::seconds(const QDate &start, const QDate &end) const
{
    if (!m_task || m_task->trackMode() != TaskTrack::Duration || !start.isValid() || !end.isValid())
        return 0;

    int seconds = 0;
    for (auto date = start; date <= end; date = date.addDays(1)) {
        auto time_durations = m_task->timeDurations(date);
        for (auto it = time_durations.cbegin(); it != time_durations.cend(); ++it) {
            seconds += it.value();
        }
    }
    return seconds;
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

int TaskSelectedDate::seconds() const
{
    return m_seconds;
}

void TaskSelectedDate::setSeconds(int newSeconds)
{
    if (m_seconds == newSeconds)
        return;
    m_seconds = newSeconds;
    emit secondsChanged();
}

int TaskSelectedDate::aggregateSeconds() const
{
    return m_aggregateSeconds;
}

void TaskSelectedDate::setAggregateSeconds(int newAggregateSeconds)
{
    if (m_aggregateSeconds == newAggregateSeconds)
        return;
    m_aggregateSeconds = newAggregateSeconds;
    emit aggregateSecondsChanged();
}

QString TaskSelectedDate::formattedSeconds(int seconds)
{
    if (seconds == 0)
        return tr("-");

    int hours = seconds / 3600;
    int mins = (seconds / 60) % 60;
    seconds = seconds % 60;
    if (hours > 0) {
        return tr("%1h %2m").arg(hours).arg(mins);
    } else if (mins > 0) {
        return tr("%1m %2s").arg(mins).arg(seconds);
    } else {
        return tr("%1s").arg(seconds);
    }
}

} // namespace tasktrackerlib
