/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QAbstractListModel>
#include <QDateTime>
#include <QQmlEngine>

namespace YAML { class Node; }

namespace tasktrackerlib {

class TaskDurationModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("TaskDurationModel can be created only in C++")

    Q_PROPERTY(int size READ size NOTIFY sizeChanged)

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

signals:
    void sizeChanged();

private:
    struct Duration {
        QTime time;
        int seconds;
    };

    QList<Duration> m_durations;
};

} // namespace tasktrackerlib
