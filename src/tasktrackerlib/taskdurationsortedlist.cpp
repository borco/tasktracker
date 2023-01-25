/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskdurationsortedlist.h"

#include "yaml-cpp/yaml.h" // IWYU pragma: keep

namespace {
static const char* DurationsYamlName = "durations";
}

namespace tasktrackerlib {

TaskDurationSortedList::TaskDurationSortedList(QObject *parent)
    : DateSortedList<TaskDuration>{parent}
{
}

void TaskDurationSortedList::loadFromYaml(const YAML::Node &node)
{
    clear();

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
        auto duration = new TaskDuration(this);
        duration->loadFromYaml(duration_node);
        insert(duration);
    }

    emit sizeChanged();
}

} // namespace tasktrackerlib
