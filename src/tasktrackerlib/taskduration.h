/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QQmlEngine>
#include <QDateTime>

namespace YAML { class Node; }

namespace tasktrackerlib {

class TaskDuration : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QDateTime dateTime READ dateTime WRITE setDateTime NOTIFY dateTimeChanged)
    Q_PROPERTY(int seconds READ seconds WRITE setSeconds NOTIFY secondsChanged)

public:
    explicit TaskDuration(QObject *parent = nullptr);

    QDateTime dateTime() const;
    void setDateTime(const QDateTime &newDateTime);

    int seconds() const;
    void setSeconds(int newSeconds);

    QDateTime now() const;
    int secondsElapsed() const;

    void loadFromData(const QByteArray& data);
    void loadFromYaml(const YAML::Node &node);

signals:
    void dateTimeChanged();
    void secondsChanged();

private:
    QDateTime m_dateTime;
    int m_seconds = 0;
};

} // namespace tasktrackerlib
