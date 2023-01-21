/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QDate>
#include <QQmlEngine>
#include <QSortFilterProxyModel>

namespace tasktrackerlib {

class TaskDurationFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QDate selectedDate READ selectedDate WRITE setSelectedDate NOTIFY selectedDateChanged)

public:
    explicit TaskDurationFilterModel(QObject *parent = nullptr);

    QDate selectedDate() const;
    void setSelectedDate(const QDate &newSelectedDate);

    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

signals:
    void selectedDateChanged();

private:
    QDate m_selectedDate;
};

} // namespace tasktrackerlib
