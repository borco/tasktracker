/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskdurationsortedlist.h"

#include "taskduration.h"

#include "yaml-cpp/yaml.h" // IWYU pragma: keep

namespace {
static const char* DurationsYamlName = "durations";
}

namespace tasktrackerlib {

TaskDurationSortedList::TaskDurationSortedList(QObject *parent)
    : QObject{parent}
{
}

TaskDurationSortedList::~TaskDurationSortedList()
{
    qDeleteAll(m_durations);
}

void TaskDurationSortedList::loadFromYaml(const YAML::Node &node)
{
    qDeleteAll(m_durations);
    m_durations.clear();

    if (node.IsNull()) {
        emit sizeChanged();
        return;
    }

    auto durations_node = node[DurationsYamlName];
    if (!durations_node) {
        emit sizeChanged();
        return;
    }

    if (!durations_node.IsSequence()) {
        qCritical().nospace() << DurationsYamlName << " is not a sequence";
        emit sizeChanged();
        return;
    }

    for (unsigned int i = 0; i < durations_node.size(); ++i) {
        auto duration_node = durations_node[i];
        if (!duration_node.IsMap()) {
            qCritical().nospace() << DurationsYamlName << "[" << i << "] is not a dictionary";
            continue;
        }
        auto duration = new TaskDuration();
        duration->loadFromYaml(duration_node);
        insert(duration);
    }

    emit sizeChanged();
}

void TaskDurationSortedList::insert(TaskDuration *duration)
{
    if (!duration->parent())
        duration->setParent(this);

    if (!duration->start().isValid()) {
        auto now = QDateTime::currentDateTimeUtc();

        duration->setStart(now);
        duration->setStop(now);
    }

    auto it = std::upper_bound(
                m_durations.begin(),
                m_durations.end(),
                duration->start(),
                [](const QDateTime& dateTime, const TaskDuration* duration) {
        return dateTime < duration->start();
    });
    m_durations.insert(it, duration);

    emit sizeChanged();
}

void TaskDurationSortedList::clear()
{
    qDeleteAll(m_durations);
    m_durations.clear();
    emit sizeChanged();
}

int TaskDurationSortedList::size() const
{
    return m_durations.size();
}

TaskDuration *TaskDurationSortedList::operator[](int i)
{
    return m_durations[i];
}

const TaskDuration *TaskDurationSortedList::operator[](int i) const
{
    return m_durations[i];
}

} // namespace tasktrackerlib
