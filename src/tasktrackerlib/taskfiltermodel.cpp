#include "taskfiltermodel.h"

#include "task.h"
#include "taskmodel.h"

namespace tasktrackerlib {

TaskFilterModel::TaskFilterModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

bool TaskFilterModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    auto task_list_model = qobject_cast<TaskModel*>(sourceModel());
    if (!task_list_model)
        return false;

    auto task = task_list_model->get(source_row);

    return (task->isEdited())
            || ((!task->isArchived() || m_archivedVisible)
                && (!task->isDone() || m_isDoneVisible));
}

void TaskFilterModel::setIsDoneVisible(bool newIsDoneVisible)
{
    if (m_isDoneVisible == newIsDoneVisible)
        return;
    m_isDoneVisible = newIsDoneVisible;
    invalidate();
    emit isDoneVisibleChanged();
}

void TaskFilterModel::setArchivedVisible(bool newArchivedVisible)
{
    if (m_archivedVisible == newArchivedVisible)
        return;
    m_archivedVisible = newArchivedVisible;
    invalidate();
    emit archivedVisibleChanged();
}

}
