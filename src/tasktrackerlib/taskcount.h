/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QQmlEngine>
#include <QDate>

namespace YAML { class Node; }

namespace tasktrackerlib {

class TaskCount : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)

public:
    explicit TaskCount(QObject *parent = nullptr);

    QDate date() const;
    void setDate(const QDate &newDate);

    int count() const;
    void setCount(int newCount);

    void loadFromData(const QByteArray& data);
    void loadFromYaml(const YAML::Node &node);

signals:
    void dateChanged();
    void countChanged();

private:
    QDate m_date = QDate::currentDate();
    int m_count = 0;
};

} // namespace tasktrackerlib

