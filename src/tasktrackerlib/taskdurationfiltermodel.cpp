/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskdurationmodel.h"
#include "taskdurationfiltermodel.h"

namespace tasktrackerlib {

TaskDurationFilterModel::TaskDurationFilterModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{

}

QDate TaskDurationFilterModel::selectedDate() const
{
    return m_selectedDate;
}

void TaskDurationFilterModel::setSelectedDate(const QDate &newSelectedDate)
{
    if (m_selectedDate == newSelectedDate)
        return;
    m_selectedDate = newSelectedDate;
    invalidate();
    emit selectedDateChanged();
}

bool TaskDurationFilterModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    auto durations = qobject_cast<TaskDurationModel*>(sourceModel());
    if (!durations)
        return false;

    auto duration = durations->get(source_row);
    return duration->dateTime().date().daysTo(m_selectedDate) == 0;
}

} // namespace tasktrackerlib
