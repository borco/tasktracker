/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "task.h"

#include "qtyamlcppadapter/yamlhelper.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"

using namespace tasktrackerlib;

namespace {
static const char* TaskYamlName = "name";
static const char* IsArchivedYamlName = "archived";
static const char* RepeatModeYamlName = "repeat";
static const char* TrackModeYamlName = "track";
static const char* CountsYamlName = "counts";
static const char* CountsDateYamlName = "date";
static const char* CountsCountYamlName = "count";

QMap<QDate, int> loadCounts(const YAML::Node &node) {
    QMap<QDate, int> counts;

    if (node.IsNull()) {
        return counts;
    }

    auto counts_node = node[CountsYamlName];
    if (!counts_node) {
        return counts;
    }

    if (!counts_node.IsSequence()) {
        qCritical().nospace() << CountsYamlName << " is not a sequence";
        return counts;
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
        counts[count_date] =
                (counts.contains(count_date) ? counts[count_date] : 0)
                + qtyamlcppadapter::intFromYaml(count, CountsCountYamlName, 0);
    }

    return counts;
}

}

Task::Task(QObject *parent)
    : QObject{parent}
    , m_durations(new TaskDurationModel(this))
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

void Task::setRepeatMode(TaskRepeat::Mode newRepeatMode)
{
    if (m_repeatMode == newRepeatMode)
        return;
    m_repeatMode = newRepeatMode;
    emit repeatModeChanged();
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
    setRepeatMode(enumFromYaml(node, RepeatModeYamlName, TaskRepeat::DefaultMode));
    setTrackMode(enumFromYaml(node, TrackModeYamlName, TaskTrack::DefaultMode));

    m_counts = loadCounts(node);
    m_durations->loadFromYaml(node);
}

int Task::count(const QDate &date) const
{
    return m_counts[date];
}

void Task::setCount(const QDate &date, int count)
{
    if (m_counts[date] == count && !date.isValid())
        return;
    m_counts[date] = count;
    emit countChanged(date, count);
}
