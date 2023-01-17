/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include "tasktrackmode.h"

#include <QQmlEngine>
#include <QDateTime>

namespace tasktrackerlib {

class TaskEvent : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(TaskTrackMode::Mode trackMode READ trackMode WRITE setTrackMode NOTIFY trackModeChanged)
    Q_PROPERTY(QDateTime dateTime READ dateTime WRITE setDateTime NOTIFY dateTimeChanged)
    Q_PROPERTY(int seconds READ seconds WRITE setSeconds NOTIFY secondsChanged)

public:
    explicit TaskEvent(QObject *parent = nullptr);

    TaskTrackMode::Mode trackMode() const;
    void setTrackMode(const TaskTrackMode::Mode &newTrackMode);

    QDateTime dateTime() const;
    void setDateTime(const QDateTime &newDateTime);

    int seconds() const;
    void setSeconds(int newSeconds);

    Q_INVOKABLE QDateTime now() const;
    Q_INVOKABLE int secondsElapsed() const;

signals:
    void trackModeChanged();
    void dateTimeChanged();
    void secondsChanged();

private:
    TaskTrackMode::Mode m_trackMode = TaskTrackMode::NoTracking;
    QDateTime m_dateTime;
    int m_seconds = 0;
};

} // namespace tasktrackerlib

