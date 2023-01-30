/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskduration.h"

#include "qtyamlcppadapter/yamlhelper.h"
#include "yaml-cpp/yaml.h" // IWYU pragma: keep

namespace {

static const char* StartTimeYamlName = "start";
static const char* StopTimeYamlName = "stop";

int seconds(const QDateTime& start, const QDateTime& stop) {
    return start.isValid() && stop.isValid() ? start.secsTo(stop) : 0;
}

}

namespace tasktrackerlib {

TaskDuration::TaskDuration(const QDateTime &start, const QDateTime &stop, QObject *parent)
    : QObject(parent)
    , m_start(start)
    , m_stop(stop)
{
}

TaskDuration::TaskDuration(QObject *parent)
    : QObject(parent)
{
}

void TaskDuration::loadFromYaml(const YAML::Node &node)
{
    using namespace qtyamlcppadapter;

    if (!node.IsMap() && !node.IsNull()) {
        qCritical() << "TaskDuration: yaml node is not a map";
        return;
    }

    setStart(dateTimeFromYaml(node, StartTimeYamlName));
    setStop(dateTimeFromYaml(node, StopTimeYamlName));
}

void TaskDuration::saveToYaml(YAML::Emitter &out) const
{

}

QDateTime TaskDuration::start() const
{
    return m_start;
}

void TaskDuration::setStart(const QDateTime &time)
{
    if (m_start == time)
        return;
    m_start = time;
    setSeconds(::seconds(m_start, m_stop));
    emit startChanged();
}

QDateTime TaskDuration::stop() const
{
    return m_stop;
}

void TaskDuration::setStop(const QDateTime &time)
{
    if (m_stop == time)
        return;
    m_stop = time;
    setSeconds(::seconds(m_start, m_stop));
    emit stopChanged();
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

} // namespace tasktrackerlib
