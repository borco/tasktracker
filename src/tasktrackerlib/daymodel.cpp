/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "daymodel.h"

namespace {

inline static const int DaysInThePast = 365 * 10; // 10 years
inline static const int TodayIndex = DaysInThePast + 1;

enum Roles {
    Date = Qt::UserRole + 1,
};
}

namespace tasktrackerlib {

DayModel::DayModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int DayModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return TodayIndex + DaysInThePast;
}

QHash<int, QByteArray> DayModel::roleNames() const
{
    return {
        { Date, "date" },
    };
}

QVariant DayModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role) {
    case Date:
        return dateForIndex(index.row());
    }

    return QVariant();
}

QDate DayModel::dateForIndex(int index) {
    auto date = QDate::currentDate();
    date = date.addDays(index - TodayIndex);
    return date;
}

int DayModel::indexForDate(const QDate &date) {
    auto today = QDate::currentDate();
    return date.daysTo(today) + TodayIndex;
}

} // namespace tasktrackerlib
