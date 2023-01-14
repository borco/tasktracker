/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QQmlEngine>
#include <QDateTime>

namespace tasktrackerlib {

class TaskRun : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QDateTime start READ start WRITE setStart NOTIFY startChanged)
    Q_PROPERTY(QDateTime stop READ stop WRITE setStop NOTIFY stopChanged)
    Q_PROPERTY(int duration READ duration NOTIFY durationChanged)

public:
    explicit TaskRun(QObject *parent = nullptr);

    QDateTime start() const;
    void setStart(const QDateTime &newStart);

    QDateTime stop() const;
    void setStop(const QDateTime &newStop);

    int duration() const;

signals:
    void startChanged();
    void stopChanged();
    void durationChanged();

public slots:
    void clear();

private:
    QDateTime m_start;
    QDateTime m_stop;
};

} // namespace tasktrackerlib

