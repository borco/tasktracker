/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "task.h"

#include "taskdurationsortedlist.h"

#include "qtyamlcppadapter/yamlhelper.h"
#include "yaml-cpp/yaml.h" // IWYU pragma: keep

#include <QIODevice>

namespace {

static const char* TaskYamlName = "name";
static const char* IsArchivedYamlName = "archived";
static const char* AggregateModeYamlName = "aggregate";
static const char* TrackModeYamlName = "track";
static const char* CountsYamlName = "counts";
static const char* CountsDateYamlName = "date";
static const char* CountsCountYamlName = "count";

}

namespace tasktrackerlib {

Task::Task(QObject *parent)
    : QObject{parent}
    , m_sortedDurations(new TaskDurationSortedList(this))
{
}

Task::~Task()
{
}

void Task::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

void Task::setIsEdited(bool newIsEdited)
{
    if (m_isEdited == newIsEdited)
        return;
    m_isEdited = newIsEdited;
    emit isEditedChanged();
}

void Task::setIsDone(bool newIsDone)
{
    if (m_isDone == newIsDone)
        return;
    m_isDone = newIsDone;
    emit isDoneChanged();
}

void Task::setIsArchived(bool newIsArchived)
{
    if (m_isArchived == newIsArchived)
        return;
    m_isArchived = newIsArchived;
    emit isArchivedChanged();
}

void Task::setAggregateMode(TaskAggregate::Mode newAggregateMode)
{
    if (m_aggregateMode == newAggregateMode)
        return;
    m_aggregateMode = newAggregateMode;
    emit aggregateModeChanged();
}

void Task::setTrackMode(TaskTrack::Mode newTrackMode)
{
    if (m_trackMode == newTrackMode)
        return;
    m_trackMode = newTrackMode;
    emit trackModeChanged();
}

void Task::loadFromYaml(const YAML::Node &node)
{
    using namespace qtyamlcppadapter;

    if (!node.IsMap() && !node.IsNull()) {
        qCritical() << "Task: yaml node is not a map";
        return;
    }

    setName(stringFromYaml(node, TaskYamlName));
    setIsArchived(boolFromYaml(node, IsArchivedYamlName, false));
    setAggregateMode(enumFromYaml(node, AggregateModeYamlName, TaskAggregate::DefaultMode));
    setTrackMode(enumFromYaml(node, TrackModeYamlName, TaskTrack::DefaultMode));

    loadCounts(node);

    m_sortedDurations->loadFromYaml(node);
}

void Task::saveToYaml(YAML::Emitter &out) const
{
    using namespace qtyamlcppadapter;

    out << YAML::BeginMap;

    emitYaml(out, TaskYamlName, m_name);

    if (m_isArchived)
        emitYaml(out, IsArchivedYamlName, m_isArchived);

    if (m_aggregateMode != TaskAggregate::DefaultMode)
        emitYaml(out, AggregateModeYamlName, m_aggregateMode);

    if (m_trackMode != TaskTrack::DefaultMode)
        emitYaml(out, TrackModeYamlName, m_trackMode);

    saveCounts(out);

    out << YAML::EndMap;
}

int Task::count(const QDate &date) const
{
    return m_counts[date];
}

void Task::loadCounts(const YAML::Node &node)
{
    m_counts.clear();

    if (node.IsNull()) {
        return;
    }

    auto counts_node = node[CountsYamlName];
    if (!counts_node) {
        return;
    }

    if (!counts_node.IsSequence()) {
        qCritical().nospace() << CountsYamlName << " is not a sequence";
        return;
    }

    for (unsigned int i = 0; i < counts_node.size(); ++i) {
        auto count = counts_node[i];
        if (!count.IsMap()) {
            qCritical().nospace() << CountsYamlName << "[" << i << "] is not a dictionary";
            continue;
        }
        auto count_date = qtyamlcppadapter::dateFromYaml(count, CountsDateYamlName, QDate());
        if (!count_date.isValid()) {
            qCritical().nospace() << CountsYamlName << "[" << i << "]["<< CountsDateYamlName << "] is not a valid date";
            continue;
        }
        m_counts[count_date] =
                (m_counts.contains(count_date) ? m_counts[count_date] : 0)
                + qtyamlcppadapter::intFromYaml(count, CountsCountYamlName, 0);
    }
}

void Task::saveCounts(YAML::Emitter &out) const
{
    using namespace qtyamlcppadapter;

    if (m_counts.size() == 0)
        return;

    out << YAML::Key << CountsYamlName;
    out << YAML::Value << YAML::BeginSeq;
    for (auto it = m_counts.constBegin(); it != m_counts.constEnd(); ++it) {
        out << YAML::Value << YAML::BeginMap;
        emitYaml(out, CountsDateYamlName, it.key());
        emitYaml(out, CountsCountYamlName, it.value());
        out << YAML::EndMap;
    }
    out << YAML::EndSeq;
}

void Task::setCount(const QDate &date, int count)
{
    if (m_counts[date] == count && !date.isValid())
        return;
    m_counts[date] = count;
    emit countChanged(date, count);
}

} // tasktrackerlib
