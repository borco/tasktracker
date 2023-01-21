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

QDate TaskCurrentDayHistory::selectedDate() const
{
    return m_selectedDate;
}

void TaskCurrentDayHistory::setSelectedDate(const QDate &newSelectedDate)
{
    if (m_selectedDate == newSelectedDate)
        return;
    m_selectedDate = newSelectedDate;
    invalidate();
    emit selectedDateChanged();
}

bool TaskCurrentDayHistory::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    auto history = qobject_cast<TaskHistory*>(sourceModel());
    if (!history)
        return false;

    auto duration = history->get(source_row);
    return duration->dateTime().date().daysTo(m_selectedDate) == 0;
}

} // namespace tasktrackerlib
