/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include "taskaggregate.h"
#include "tasktrack.h"

#include <QDateTime>

namespace YAML {
class Emitter;
class Node;
}

namespace tasktrackerlib {

class TaskDurationSortedList;

class Task : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(bool isEdited READ isEdited WRITE setIsEdited NOTIFY isEditedChanged)
    Q_PROPERTY(bool isDone READ isDone WRITE setIsDone NOTIFY isDoneChanged)
    Q_PROPERTY(bool isArchived READ isArchived WRITE setIsArchived NOTIFY isArchivedChanged)
    Q_PROPERTY(TaskAggregate::Mode aggregateMode READ aggregateMode WRITE setAggregateMode NOTIFY aggregateModeChanged)
    Q_PROPERTY(TaskTrack::Mode trackMode READ trackMode WRITE setTrackMode NOTIFY trackModeChanged)

public:
    explicit Task(QObject *parent = nullptr);
    ~Task() override;

    QString name() const { return m_name; }
    void setName(const QString &newName);

    bool isEdited() const { return m_isEdited; }
    void setIsEdited(bool newIsEdited);

    bool isDone() const { return m_isDone; }
    void setIsDone(bool newIsDone);

    bool isArchived() const { return m_isArchived; }
    void setIsArchived(bool newIsArchived);

    TaskAggregate::Mode aggregateMode() const { return m_aggregateMode; }
    void setAggregateMode(TaskAggregate::Mode newAggregateMode);

    TaskTrack::Mode trackMode() const { return m_trackMode; }
    void setTrackMode(TaskTrack::Mode newTrackMode);

    void loadFromData(const QByteArray& data);
    void loadFromYaml(const YAML::Node &node);
    void saveToYaml(YAML::Emitter& out) const;

    int count(const QDate& date) const;
    void setCount(const QDate& date, int count);
    TaskDurationSortedList* sortedDurations() const { return m_sortedDurations; }

signals:
    void nameChanged();
    void isEditedChanged();
    void isDoneChanged();
    void isArchivedChanged();
    void aggregateModeChanged();
    void trackModeChanged();
    void countChanged(const QDate& date, int count);

private:
    void loadCounts(const YAML::Node &node);
    void saveCounts(YAML::Emitter& out) const;

    QString m_name;
    bool m_isEdited = false;
    bool m_isDone = false;
    bool m_isArchived = false;
    TaskAggregate::Mode m_aggregateMode = TaskAggregate::DefaultMode;
    TaskTrack::Mode m_trackMode = TaskTrack::DefaultMode;

    QMap<QDate, int> m_counts;
    TaskDurationSortedList* m_sortedDurations = nullptr;
};

}
