/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskhistory.h"
#include "taskcurrentdayhistory.h"

namespace tasktrackerlib {

TaskCurrentDayHistory::TaskCurrentDayHistory(QObject *parent)
    : QSortFilterProxyModel{parent}
{

}

QDate TaskCurrentDayHistory::currentDate() const
{
    return m_currentDate;
}

void TaskCurrentDayHistory::setCurrentDate(const QDate &newCurrentDate)
{
    if (m_currentDate == newCurrentDate)
        return;
    m_currentDate = newCurrentDate;
    invalidate();
    emit currentDateChanged();
}

bool TaskCurrentDayHistory::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    auto history = qobject_cast<TaskHistory*>(sourceModel());
    if (!history)
        return false;

    auto event = history->get(source_row);
    return event->dateTime().date().daysTo(m_currentDate) == 0;
}

} // namespace tasktrackerlib
