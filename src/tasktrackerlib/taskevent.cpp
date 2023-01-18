/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskevent.h"

#include "qtyamlcppadapter/yamlhelper.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"

namespace {
static const char* TrackModeYamlName = "track";
static const char* DateTimeYamlName = "dateTime";
static const char* SecondsYamlName = "seconds";
}

namespace tasktrackerlib {

TaskEvent::TaskEvent(QObject *parent)
    : QObject{parent}
{
}

TaskTrackMode::Mode TaskEvent::trackMode() const
{
    return m_trackMode;
}

void TaskEvent::setTrackMode(const TaskTrackMode::Mode &newTrackMode)
{
    if (m_trackMode == newTrackMode)
        return;
    m_trackMode = newTrackMode;
    emit trackModeChanged();
}

QDateTime TaskEvent::dateTime() const
{
    return m_dateTime;
}

void TaskEvent::setDateTime(const QDateTime &newDateTime)
{
    if (m_dateTime == newDateTime)
        return;
    m_dateTime = newDateTime;
    emit dateTimeChanged();
}

int TaskEvent::seconds() const
{
    return m_seconds;
}

void TaskEvent::setSeconds(int newSeconds)
{
    if (m_seconds == newSeconds)
        return;
    m_seconds = newSeconds;
    emit secondsChanged();
}

QDateTime TaskEvent::now() const
{
    return QDateTime::currentDateTimeUtc();
}

int TaskEvent::secondsElapsed() const
{
    if (!m_dateTime.isValid()) {
        qCritical() << "TaskEvent: dateTime not set";
        return -1;
    }

    return now().secsTo(m_dateTime);
}

void TaskEvent::loadFromData(const QByteArray &data)
{
    YAML::Node node = YAML::Load(data.toStdString());
    loadFromYaml(node);
}

void TaskEvent::loadFromYaml(const YAML::Node &node)
{
    using namespace qtyamlcppadapter;

    if (!node.IsMap() && !node.IsNull()) {
        qCritical() << "Task: yaml node is not a map";
        return;
    }

    setTrackMode(enumFromYaml(node, TrackModeYamlName, TaskTrackMode::NoTracking));
    setDateTime(dateTimeFromYaml(node, DateTimeYamlName, QDateTime()));
    setSeconds(intFromYaml(node, SecondsYamlName, 0));
}

} // namespace tasktrackerlib
