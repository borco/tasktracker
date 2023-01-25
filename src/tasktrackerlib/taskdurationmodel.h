/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QAbstractListModel>
#include <QDateTime>
#include <QQmlEngine>

namespace YAML { class Node; }

namespace tasktrackerlib {

class Task;

class TaskDurationModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(int size READ size NOTIFY sizeChanged)
    Q_PROPERTY(Task* task READ task WRITE setTask NOTIFY taskChanged)
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged)

public:
    typedef QMap<QTime, int> TimeDurations;

    explicit TaskDurationModel(QObject *parent = nullptr);
    ~TaskDurationModel() override;

    int size() const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    void clear();
    void setTimeDurations(const TimeDurations& timeDurations);

    Task *task() const;
    void setTask(Task *newTask);

    QDate date() const;
    void setDate(const QDate &newDate);

signals:
    void sizeChanged();
    void taskChanged();
    void dateChanged();

private:
    struct Duration {
        QTime time;
        int seconds;
    };

    QList<Duration> m_durations;
    Task *m_task = nullptr;
    QDate m_date;
};

} // namespace tasktrackerlib
