/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskdurationsortedlist.h"

#include "yaml-cpp/yaml.h" // IWYU pragma: keep

namespace tasktrackerlib {

TaskDurationSortedList::TaskDurationSortedList(QObject *parent)
    : QObject{parent}
    , DateSortedList<TaskDuration>(this)
{
}

void TaskDurationSortedList::loadFromYaml(const YAML::Node &node)
{
    clear();

    if (node.IsNull()) {
        return;
    }

    if (!node.IsSequence()) {
        qCritical() << "Node is not a sequence";
        return;
    }

    for (unsigned int i = 0; i < node.size(); ++i) {
        auto duration_node = node[i];
        if (!duration_node.IsMap()) {
            qCritical() << "Node is not a dictionary";
            continue;
        }
        auto duration = new TaskDuration(this);
        duration->loadFromYaml(duration_node);
        insert(duration);
    }
}

void TaskDurationSortedList::saveToYaml(YAML::Emitter &out) const
{
    if (m_items.empty())
        return;

    out << YAML::BeginSeq;

    for (auto it = m_items.cbegin(); it != m_items.cend(); ++it) {
        const auto& duration = **it;
        duration.saveToYaml(out);
    }

    out << YAML::EndSeq;
}

void TaskDurationSortedList::setSize(int newSize)
{
    if (m_size == newSize)
        return;
    m_size = newSize;
    emit sizeChanged();
}

TaskDurationSortedList *TaskDurationSortedList::forDate(const QDate &date)
{
    auto list = new TaskDurationSortedList(nullptr);
    list->m_source = this;
    list->m_date = date;
    list->m_items = Items(localTimeBegin(date), localTimeEnd(date));
    list->setSize(list->m_items.size());
    connect(this,
            qOverload<TaskDurationSortedList *, const QDate &, QPrivateSignal>(&TaskDurationSortedList::sorted),
            list,
            &TaskDurationSortedList::onOtherSorted);
    return list;
}

void TaskDurationSortedList::sort()
{
    DateSortedList<TaskDuration>::sort(m_items.begin(), m_items.end());

    if (m_source) {
        m_source->sort(this, m_date);
    } else {
        emit sorted();
    }
}

void TaskDurationSortedList::sort(TaskDurationSortedList * source, const QDate &date)
{
    DateSortedList<TaskDuration>::sort(localTimeBegin(date), localTimeEnd(date));
    emit sorted(source, date, QPrivateSignal());
}

void TaskDurationSortedList::onOtherSorted(TaskDurationSortedList *source, const QDate &date, QPrivateSignal)
{
    if (this == source || !date.isValid() || date != m_date)
        return;

    DateSortedList<TaskDuration>::sort(m_items.begin(), m_items.end());
    emit sorted();
}

} // namespace tasktrackerlib
