/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include "taskdurationmodel.h"
#include "taskrepeat.h"
#include "tasktrack.h"

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
    Q_PROPERTY(TaskRepeat::Mode repeatMode READ repeatMode WRITE setRepeatMode NOTIFY repeatModeChanged)
    Q_PROPERTY(TaskTrack::Mode trackMode READ trackMode WRITE setTrackMode NOTIFY trackModeChanged)
    Q_PROPERTY(TaskDurationModel* durations READ durations CONSTANT)

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

    TaskRepeat::Mode repeatMode() const { return m_repeatMode; }
    void setRepeatMode(TaskRepeat::Mode newRepeatMode);

    TaskTrack::Mode trackMode() const { return m_trackMode; }
    void setTrackMode(TaskTrack::Mode newTrackMode);

    void loadFromData(const QByteArray& data);
    void loadFromYaml(const YAML::Node &node);

    TaskDurationModel *durations() const { return m_durations; }

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
    TaskRepeat::Mode m_repeatMode = TaskRepeat::DefaultMode;
    TaskTrack::Mode m_trackMode = TaskTrack::DefaultMode;
    TaskDurationModel *m_durations = nullptr;
};

}
