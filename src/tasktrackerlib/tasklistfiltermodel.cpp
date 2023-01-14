#include "tasklistfiltermodel.h"

#include "task.h"
#include "tasklistmodel.h"

namespace tasktrackerlib {

TaskListFilterModel::TaskListFilterModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

bool TaskListFilterModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    auto task_list_model = qobject_cast<TaskListModel*>(sourceModel());
    if (!task_list_model)
        return false;

    auto task = task_list_model->get(source_row);

    return !task->isArchived() || m_showArchived;
}

void TaskListFilterModel::setShowArchived(bool newShowArchived)
{
    if (m_showArchived == newShowArchived)
        return;
    m_showArchived = newShowArchived;
    emit showArchivedChanged();
    invalidate();
}

}