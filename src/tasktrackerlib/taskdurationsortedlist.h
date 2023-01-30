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
    void saveToYaml(YAML::Emitter& out) const override;

    void setSize(int newSize) override;

    void sort();

    TaskDurationSortedList* forDate(const QDate& date);

signals:
    void sizeChanged();
    void sorted();
    void sorted(tasktrackerlib::TaskDurationSortedList* source, const QDate& date, QPrivateSignal);

private:
    void sort(TaskDurationSortedList* source, const QDate& date);
    void onOtherSorted(TaskDurationSortedList* source, const QDate& date, QPrivateSignal);

    TaskDurationSortedList* m_source = nullptr;
    QDate m_date;
};

} // namespace tasktrackerlib

