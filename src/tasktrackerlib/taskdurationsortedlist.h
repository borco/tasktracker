/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include "datesortedlist.h"
#include "taskduration.h"
#include "yamlbackingstore.h"

#include <QQmlEngine>

namespace tasktrackerlib {

class TaskDurationSortedList : public QObject, public DateSortedList<TaskDuration>, public YamlBackingStore
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(int size READ size WRITE setSize NOTIFY sizeChanged)

public:
    explicit TaskDurationSortedList(QObject *parent = nullptr);

    void loadFromYaml(const YAML::Node &node) override;

    void setSize(int newSize) override;

signals:
    void sizeChanged();
};

} // namespace tasktrackerlib

