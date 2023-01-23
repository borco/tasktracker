/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QDate>
#include <QQmlEngine>

namespace tasktrackerlib {

class Task;

class TaskSelectedDate : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(Task* task READ task WRITE setTask NOTIFY taskChanged)
    Q_PROPERTY(QDate selectedDate READ selectedDate WRITE setSelectedDate NOTIFY selectedDateChanged)
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)

public:
    explicit TaskSelectedDate(QObject *parent = nullptr);

    Task *task() const;
    void setTask(Task *newTask);

    QDate selectedDate() const;
    void setSelectedDate(const QDate &newSelectedDate);

    int count() const;
    void setCount(int newCount);

signals:
    void taskChanged();
    void selectedDateChanged();
    void countChanged();

private:
    void updateWrappedProperties();

    Task *m_task = nullptr;
    QDate m_selectedDate;
    int m_count = 0;
};

} // namespace tasktrackerlib
