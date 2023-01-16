/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "task.h"

#include "qtyamlcppadapter/yamlhelper.h"
#include "taskrunlistmodel.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"

using namespace tasktrackerlib;

namespace {
static const char* TaskYamlName = "name";
static const char* IsArchivedYamlName = "archived";
static const char* ScheduleModeYamlName = "schedule";
static const char* TrackModeYamlName = "track";
}

Task::Task(QObject *parent)
    : QObject{parent}
    , m_runs(new TaskRunListModel(this))
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

void Task::setScheduleMode(ScheduleMode newScheduleMode)
{
    if (m_scheduleMode == newScheduleMode)
        return;
    m_scheduleMode = newScheduleMode;
    emit scheduleModeChanged();
}

void Task::setTrackMode(TrackMode newTrackMode)
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
    if (!node.IsMap() && !node.IsNull()) {
        qCritical() << "Task: yaml node is not a map";
        return;
    }
    using namespace qtyamlcppadapter;
    setName(stringFromYaml(node, TaskYamlName));
    setIsArchived(boolFromYaml(node, IsArchivedYamlName, false));
    setScheduleMode(enumFromYaml(node, ScheduleModeYamlName, Task::Daily));
    setTrackMode(enumFromYaml(node, TrackModeYamlName, Task::NoTracking));
}
