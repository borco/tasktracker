/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskcountfiltermodel.h"

#include "taskcount.h"
#include "taskcountmodel.h"

namespace tasktrackerlib {

TaskCountFilterModel::TaskCountFilterModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
}

QDate TaskCountFilterModel::selectedDate() const
{
    return m_selectedDate;
}

void TaskCountFilterModel::setSelectedDate(const QDate &newSelectedDate)
{
    if (m_selectedDate == newSelectedDate)
        return;
    m_selectedDate = newSelectedDate;
    invalidate();
    emit selectedDateChanged();
}

bool TaskCountFilterModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    auto counts = qobject_cast<TaskCountModel*>(sourceModel());
    if (!counts)
        return false;

    auto count = counts->get(source_row);
    return count->date().daysTo(m_selectedDate) == 0;
}

} // namespace tasktrackerlib
