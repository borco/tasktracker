/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QQmlEngine>

namespace tasktrackerlib {

class Task : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

public:
    explicit Task(QObject *parent = nullptr);

    QString name() const { return m_name; }
    void setName(const QString &newName);

signals:
    void nameChanged();

private:
    QString m_name;
};

}
