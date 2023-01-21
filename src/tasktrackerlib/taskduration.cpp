/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskduration.h"

#include "qtyamlcppadapter/yamlhelper.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"

namespace {
static const char* DateTimeYamlName = "dateTime";
static const char* SecondsYamlName = "seconds";
}

namespace tasktrackerlib {

TaskDuration::TaskDuration(QObject *parent)
    : QObject{parent}
{
}

QDateTime TaskDuration::dateTime() const
{
    return m_dateTime;
}

void TaskDuration::setDateTime(const QDateTime &newDateTime)
{
    if (m_dateTime == newDateTime)
        return;
    m_dateTime = newDateTime;
    emit dateTimeChanged();
}

int TaskDuration::seconds() const
{
    return m_seconds;
}

void TaskDuration::setSeconds(int newSeconds)
{
    if (m_seconds == newSeconds)
        return;
    m_seconds = newSeconds;
    emit secondsChanged();
}

QDateTime TaskDuration::now() const
{
    return QDateTime::currentDateTimeUtc();
}

int TaskDuration::secondsElapsed() const
{
    if (!m_dateTime.isValid()) {
        qCritical() << "TaskDuration: dateTime not set";
        return -1;
    }

    return now().secsTo(m_dateTime);
}

void TaskDuration::loadFromData(const QByteArray &data)
{
    YAML::Node node = YAML::Load(data.toStdString());
    loadFromYaml(node);
}

void TaskDuration::loadFromYaml(const YAML::Node &node)
{
    using namespace qtyamlcppadapter;

    if (!node.IsMap() && !node.IsNull()) {
        qCritical() << "Task: yaml node is not a map";
        return;
    }

    setDateTime(dateTimeFromYaml(node, DateTimeYamlName, QDateTime()));
    setSeconds(intFromYaml(node, SecondsYamlName, 0));
}

} // namespace tasktrackerlib
