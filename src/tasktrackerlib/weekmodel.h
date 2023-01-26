/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QAbstractListModel>
#include <QDate>
#include <QQmlEngine>

namespace tasktrackerlib {

class WeekModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(Qt::DayOfWeek weekStart READ weekStart WRITE setWeekStart NOTIFY weekStartChanged)
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged)

public:
    explicit WeekModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    Qt::DayOfWeek weekStart() const;
    void setWeekStart(Qt::DayOfWeek newWeekStart);

    QDate date() const;
    void setDate(const QDate &newDate);

    Q_INVOKABLE void addDays(int days);

signals:
    void dateChanged();

    void weekStartChanged();

private:
    struct Day {
        Day(const Qt::DayOfWeek dayOfWeek);

        Qt::DayOfWeek dayOfWeek;
        QString name;
        QDate date;
    };

    void updateDays();

    Qt::DayOfWeek m_weekStart = Qt::Sunday;
    QDate m_date;

    QList<Day> m_days;
};

} // namespace tasktrackerlib
