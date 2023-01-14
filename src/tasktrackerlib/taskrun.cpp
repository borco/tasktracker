/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskrun.h"

namespace tasktrackerlib {

TaskRun::TaskRun(QObject *parent)
    : QObject{parent}
{

}

QDateTime TaskRun::start() const
{
    return m_start;
}

void TaskRun::setStart(const QDateTime &newStart)
{
    if (m_start == newStart)
        return;
    m_start = newStart;
    emit durationChanged();
    emit startChanged();
}

QDateTime TaskRun::stop() const
{
    return m_stop;
}

void TaskRun::setStop(const QDateTime &newStop)
{
    if (m_stop == newStop)
        return;
    m_stop = newStop;

    if (m_start.isValid()) {
        emit durationChanged();
    }

    emit stopChanged();
}

int TaskRun::duration() const
{
    if (m_start.isValid()) {
        return - m_start.secsTo(m_stop.isValid() ? m_stop : QDateTime::currentDateTime());
    }

    return -1;
}

void TaskRun::clear()
{
    setStart(QDateTime());
    setStop(QDateTime());
}

} // namespace tasktrackerlib
