/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include "tasktrack.h"

#include <QQmlEngine>
#include <QDateTime>

namespace YAML { class Node; }

namespace tasktrackerlib {

class TaskEvent : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(TaskTrack::Mode trackMode READ trackMode WRITE setTrackMode NOTIFY trackModeChanged)
    Q_PROPERTY(QDateTime dateTime READ dateTime WRITE setDateTime NOTIFY dateTimeChanged)
    Q_PROPERTY(int seconds READ seconds WRITE setSeconds NOTIFY secondsChanged)

public:
    explicit TaskEvent(QObject *parent = nullptr);

    TaskTrack::Mode trackMode() const;
    void setTrackMode(const TaskTrack::Mode &newTrackMode);

    QDateTime dateTime() const;
    void setDateTime(const QDateTime &newDateTime);

    int seconds() const;
    void setSeconds(int newSeconds);

    QDateTime now() const;
    int secondsElapsed() const;

    void loadFromData(const QByteArray& data);
    void loadFromYaml(const YAML::Node &node);

signals:
    void trackModeChanged();
    void dateTimeChanged();
    void secondsChanged();

private:
    TaskTrack::Mode m_trackMode = TaskTrack::DefaultMode;
    QDateTime m_dateTime;
    int m_seconds = 0;
};

} // namespace tasktrackerlib
