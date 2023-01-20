/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include "taskhistory.h"
#include "taskrepeatmode.h"
#include "tasktrackmode.h"

namespace YAML { class Node; }

namespace tasktrackerlib {

class TaskHistory;

class Task : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(bool isEdited READ isEdited WRITE setIsEdited NOTIFY isEditedChanged)
    Q_PROPERTY(bool isDone READ isDone WRITE setIsDone NOTIFY isDoneChanged)
    Q_PROPERTY(bool isArchived READ isArchived WRITE setIsArchived NOTIFY isArchivedChanged)
    Q_PROPERTY(TaskRepeatMode::Mode repeatMode READ repeatMode WRITE setRepeatMode NOTIFY repeatModeChanged)
    Q_PROPERTY(TaskTrackMode::Mode trackMode READ trackMode WRITE setTrackMode NOTIFY trackModeChanged)
    Q_PROPERTY(TaskHistory* history READ history CONSTANT)

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

    TaskRepeatMode::Mode repeatMode() const { return m_repeatMode; }
    void setRepeatMode(TaskRepeatMode::Mode newRepeatMode);

    TaskTrackMode::Mode trackMode() const { return m_trackMode; }
    void setTrackMode(TaskTrackMode::Mode newTrackMode);

    void loadFromData(const QByteArray& data);
    void loadFromYaml(const YAML::Node &node);

    TaskHistory *history() const { return m_history; }

signals:
    void nameChanged();
    void isEditedChanged();
    void isDoneChanged();
    void isArchivedChanged();
    void repeatModeChanged();
    void trackModeChanged();

private:
    QString m_name;
    bool m_isEdited = false;
    bool m_isDone = false;
    bool m_isArchived = false;
    TaskRepeatMode::Mode m_repeatMode = TaskRepeatMode::Daily;
    TaskTrackMode::Mode m_trackMode = TaskTrackMode::NoTracking;
    TaskHistory *m_history = nullptr;
};

}
