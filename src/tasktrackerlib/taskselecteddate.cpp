/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskselecteddate.h"

#include "task.h"

namespace tasktrackerlib {

TaskSelectedDate::TaskSelectedDate(QObject *parent)
    : QObject{parent}
{
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
        connect(m_task, &Task::countChanged, this, [&](const QDate& date, int count){
            if (date == m_selectedDate) {
                setCount(count);
            }
        });
    }

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
    } else {
        setCount(0);
    }
}

} // namespace tasktrackerlib
