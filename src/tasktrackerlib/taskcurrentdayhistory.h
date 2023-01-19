/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QDate>
#include <QQmlEngine>
#include <QSortFilterProxyModel>

namespace tasktrackerlib {

class TaskCurrentDayHistory : public QSortFilterProxyModel
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QDate currentDate READ currentDate WRITE setCurrentDate NOTIFY currentDateChanged)

public:
    explicit TaskCurrentDayHistory(QObject *parent = nullptr);

    QDate currentDate() const;
    void setCurrentDate(const QDate &newCurrentDate);

    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

signals:
    void currentDateChanged();

private:
    QDate m_currentDate;
};

} // namespace tasktrackerlib

