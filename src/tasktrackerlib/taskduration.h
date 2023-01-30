/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include "yamlbackingstore.h"

#include <QQmlEngine>
#include <QTime>

namespace tasktrackerlib {

class TaskDuration : public QObject, public YamlBackingStore
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QDateTime start READ start WRITE setStart NOTIFY startChanged)
    Q_PROPERTY(QDateTime stop READ stop WRITE setStop NOTIFY stopChanged)
    Q_PROPERTY(int seconds READ seconds NOTIFY secondsChanged)

public:
    explicit TaskDuration(const QDateTime& start, const QDateTime& stop, QObject *parent = nullptr);
    explicit TaskDuration(QObject *parent = nullptr);

    void loadFromYaml(const YAML::Node &node) override;
    void saveToYaml(YAML::Emitter& out) const override;

    QDateTime start() const;
    void setStart(const QDateTime& time);

    QDateTime stop() const;
    void setStop(const QDateTime& time);

    int seconds() const;

signals:
    void startChanged();
    void stopChanged();
    void secondsChanged();

private:
    void setSeconds(int newSeconds);

    QDateTime m_start;
    QDateTime m_stop;
    int m_seconds = 0;
};

} // namespace tasktrackerlib
