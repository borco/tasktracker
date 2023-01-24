/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskduration.h"

namespace {

int seconds(const QTime& start, const QTime& stop) {
    return start.isValid() && stop.isValid() ? start.secsTo(stop) : 0;
}

}

namespace tasktrackerlib {

TaskDuration::TaskDuration(QObject *parent)
    : QObject(parent)
{
}

void TaskDuration::loadFromYaml(const YAML::Node &node)
{
}

QTime TaskDuration::start() const
{
    return m_start;
}

void TaskDuration::setStart(const QTime &time)
{
    if (m_start == time)
        return;
    m_start = time;
    setSeconds(::seconds(m_start, m_stop));
    emit startChanged();
}

QTime TaskDuration::stop() const
{
    return m_stop;
}

void TaskDuration::setStop(const QTime &time)
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
