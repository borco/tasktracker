/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include "yamlbackingstore.h"

#include <QQmlEngine>
#include <QTime>

namespace YAML { class Node; }

namespace tasktrackerlib {

class TaskDuration : public QObject, public YamlBackingStore
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QTime start READ start WRITE setStart NOTIFY startChanged)
    Q_PROPERTY(QTime stop READ stop WRITE setStop NOTIFY stopChanged)
    Q_PROPERTY(int seconds READ seconds NOTIFY secondsChanged)

public:
    explicit TaskDuration(QObject *parent = nullptr);

    void loadFromYaml(const YAML::Node &node) override;

    QTime start() const;
    void setStart(const QTime& time);

    QTime stop() const;
    void setStop(const QTime& time);

    int seconds() const;

signals:
    void startChanged();
    void stopChanged();
    void secondsChanged();

private:
    void setSeconds(int newSeconds);

    QTime m_start;
    QTime m_stop;
    int m_seconds = 0;
};

} // namespace tasktrackerlib
