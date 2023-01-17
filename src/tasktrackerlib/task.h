/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QQmlEngine>

#include "taskschedulemode.h"
#include "tasktrackmode.h"

namespace YAML { class Node; }

namespace tasktrackerlib {

class Task : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(bool isEdited READ isEdited WRITE setIsEdited NOTIFY isEditedChanged)
    Q_PROPERTY(bool isDone READ isDone WRITE setIsDone NOTIFY isDoneChanged)
    Q_PROPERTY(bool isArchived READ isArchived WRITE setIsArchived NOTIFY isArchivedChanged)
    Q_PROPERTY(TaskScheduleMode::Mode scheduleMode READ scheduleMode WRITE setScheduleMode NOTIFY scheduleModeChanged)
    Q_PROPERTY(TaskTrackMode::Mode trackMode READ trackMode WRITE setTrackMode NOTIFY trackModeChanged)

public:
    explicit Task(QObject *parent = nullptr);

    QString name() const { return m_name; }
    void setName(const QString &newName);

    bool isEdited() const { return m_isEdited; }
    void setIsEdited(bool newIsEdited);

    bool isDone() const { return m_isDone; }
    void setIsDone(bool newIsDone);

    bool isArchived() const { return m_isArchived; }
    void setIsArchived(bool newIsArchived);

    TaskScheduleMode::Mode scheduleMode() const { return m_scheduleMode; }
    void setScheduleMode(TaskScheduleMode::Mode newScheduleMode);

    TaskTrackMode::Mode trackMode() const { return m_trackMode; }
    void setTrackMode(TaskTrackMode::Mode newTrackMode);

    void loadFromData(const QByteArray& data);
    void loadFromYaml(const YAML::Node &node);

signals:
    void nameChanged();
    void isEditedChanged();
    void isDoneChanged();
    void isArchivedChanged();
    void scheduleModeChanged();
    void trackModeChanged();

private:
    QString m_name;
    bool m_isEdited = false;
    bool m_isDone = false;
    bool m_isArchived = false;
    TaskScheduleMode::Mode m_scheduleMode = TaskScheduleMode::Daily;
    TaskTrackMode::Mode m_trackMode = TaskTrackMode::NoTracking;
};

}
