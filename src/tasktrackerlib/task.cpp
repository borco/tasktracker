/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "task.h"

#include "taskdurationsortedlist.h"

#include "qtyamlcppadapter/yamlhelper.h"
#include "yaml-cpp/yaml.h" // IWYU pragma: keep

namespace {

static const char* TaskYamlName = "name";
static const char* IsArchivedYamlName = "archived";
static const char* AggregateModeYamlName = "aggregate";
static const char* TrackModeYamlName = "track";
static const char* CountsYamlName = "counts";
static const char* CountsDateYamlName = "date";
static const char* CountsCountYamlName = "count";
static const char* DurationsYamlName = "durations";
static const char* DurationsDateTimeYamlName = "dateTime";
static const char* DurationsSecondsYamlName = "seconds";

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

void Task::loadFromData(const QByteArray &data)
{
    YAML::Node node = YAML::Load(data.toStdString());
    loadFromYaml(node);
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
    loadDurations(node);

    m_sortedDurations->loadFromYaml(node);
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

void Task::loadDurations(const YAML::Node &node)
{
    m_durations.clear();

    if (node.IsNull()) {
        return;
    }

    auto durations_node = node[DurationsYamlName];
    if (!durations_node) {
        return;
    }

    if (!durations_node.IsSequence()) {
        qCritical().nospace() << DurationsYamlName << " is not a sequence";
        return;
    }

    for (unsigned int i = 0; i < durations_node.size(); ++i) {
        auto duration = durations_node[i];
        if (!duration.IsMap()) {
            qCritical().nospace() << DurationsYamlName << "[" << i << "] is not a dictionary";
            continue;
        }
        auto duration_date_time = qtyamlcppadapter::dateTimeFromYaml(duration, DurationsDateTimeYamlName, QDateTime());
        if (!duration_date_time.isValid()) {
            qCritical().nospace() << DurationsYamlName << "[" << i << "]["<< DurationsDateTimeYamlName << "] is not a valid datetime";
            continue;
        }
        auto duration_date = duration_date_time.date();
        auto duration_time = duration_date_time.time();
        auto seconds = qtyamlcppadapter::intFromYaml(duration, DurationsSecondsYamlName, 0);
        m_durations[duration_date][duration_time] = seconds;
    }
}

void Task::setCount(const QDate &date, int count)
{
    if (m_counts[date] == count && !date.isValid())
        return;
    m_counts[date] = count;
    emit countChanged(date, count);
}

Task::TimeDurations Task::timeDurations(const QDate &date) const
{
    return m_durations[date];
}

} // tasktrackerlib
