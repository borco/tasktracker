/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QQmlEngine>

#include "taskrunlistmodel.h"

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
    Q_PROPERTY(Task::ScheduleMode scheduleMode READ scheduleMode WRITE setScheduleMode NOTIFY scheduleModeChanged)
    Q_PROPERTY(Task::TrackMode trackMode READ trackMode WRITE setTrackMode NOTIFY trackModeChanged)
    Q_PROPERTY(TaskRunListModel* runs READ runs CONSTANT)

public:
    enum ScheduleMode {
        Daily = 0,
        Weekly,
        Monthly,
        Once, // do it once, without a specific time limit
        Before, // before a set date; shown as "Overdue" after end date
        After,  // after a set date; not shown by default before start date
        Between, // between 2 date; not shown by default before start date; shown as"Overdue" after end date
    };
    Q_ENUM(ScheduleMode)

    enum TrackMode {
        NoTracking = 0, // needs to be done once; marked as done after doing it
        Repeats,
        MinimumRepeats,
        MaximumRepeats,
        Duration,
        MinimumDuration,
        MaximumDuration,
    };
    Q_ENUM(TrackMode)

    explicit Task(QObject *parent = nullptr);

    QString name() const { return m_name; }
    void setName(const QString &newName);

    bool isEdited() const { return m_isEdited; }
    void setIsEdited(bool newIsEdited);

    bool isDone() const { return m_isDone; }
    void setIsDone(bool newIsDone);

    bool isArchived() const { return m_isArchived; }
    void setIsArchived(bool newIsArchived);

    ScheduleMode scheduleMode() const { return m_scheduleMode; }
    void setScheduleMode(ScheduleMode newScheduleMode);

    TrackMode trackMode() const { return m_trackMode; }
    void setTrackMode(TrackMode newTrackMode);

    TaskRunListModel* runs() const { return m_runs; }

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
    ScheduleMode m_scheduleMode = Daily;
    TrackMode m_trackMode = NoTracking;
    TaskRunListModel* m_runs = nullptr;
};

}
