/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include "yamlbackingstore.h"

#include <QQmlEngine>

namespace tasktrackerlib {

class TaskDuration;

class TaskDurationSortedList : public QObject, public YamlBackingStore
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(int size READ size NOTIFY sizeChanged)

public:
    explicit TaskDurationSortedList(QObject *parent = nullptr);
    ~TaskDurationSortedList() override;

    void loadFromYaml(const YAML::Node &node) override;

    void insert(TaskDuration* duration);

    void clear();
    int size() const;
    TaskDuration* operator[](int i);
    const TaskDuration* operator[](int i) const;

signals:
    void sizeChanged();

private:
    std::vector<TaskDuration*> m_durations;
};

} // namespace tasktrackerlib

