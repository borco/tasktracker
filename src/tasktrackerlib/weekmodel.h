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

    Q_PROPERTY(QDate currentDate READ currentDate WRITE setCurrentDate NOTIFY currentDateChanged)

public:
    explicit WeekModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    QDate currentDate() const;
    void setCurrentDate(const QDate &newCurrentDate);

    Q_INVOKABLE void decrementCurrentDate();
    Q_INVOKABLE void incrementCurrentDate();

signals:
    void currentDateChanged();

private:
    enum Roles {
        Name = Qt::UserRole + 1,
        Date,
        IsCurrentDate,
    };

    struct Day {
        Day(const Qt::DayOfWeek dayOfWeek);

        Qt::DayOfWeek dayOfWeek;
        QString name;
        QDate date;
    };

    void updateDays();

    QDate m_currentDate;

    QList<Day> m_days;
};

} // namespace tasktrackerlib

