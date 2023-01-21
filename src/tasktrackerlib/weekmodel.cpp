#include "weekmodel.h"

namespace {
enum Roles {
    Name = Qt::UserRole + 1,
    Date,
    IsSelectedDate,
};
}

namespace tasktrackerlib {

WeekModel::WeekModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_days << Qt::Sunday
           << Qt::Monday
           << Qt::Tuesday
           << Qt::Wednesday
           << Qt::Thursday
           << Qt::Friday
           << Qt::Saturday
              ;
}

int WeekModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_days.size();
}

QHash<int, QByteArray> WeekModel::roleNames() const
{
    return {
        { Name, "name" },
        { Date, "date" },
        { IsSelectedDate, "isSelectedDate" },
    };
}

QVariant WeekModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto day = m_days[index.row()];

    switch(role) {
    case Name:
        return day.name;
    case Date:
        return day.date;
    case IsSelectedDate:
        return day.date.daysTo(m_selectedDate) == 0;
    }

    return QVariant();
}

bool WeekModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        QList<int> roles = {};

        switch(role) {
        }

        if (!roles.isEmpty()) {
            emit dataChanged(index, index, roles);
            return true;
        } else {
            return false;
        }
    }
    return false;
}

QDate WeekModel::selectedDate() const
{
    return m_selectedDate;
}

void WeekModel::setSelectedDate(const QDate &newSelectedDate)
{
    if (m_selectedDate == newSelectedDate)
        return;
    m_selectedDate = newSelectedDate;

    updateDays();
    emit selectedDateChanged();
}

void WeekModel::addDays(int days)
{
    setSelectedDate(m_selectedDate.addDays(days));
}

void WeekModel::updateDays()
{
    beginResetModel();
    auto day_of_week = m_selectedDate.dayOfWeek();
    auto it = std::find_if(m_days.begin(), m_days.end(), [&](const Day& d) { return d.dayOfWeek == day_of_week; });
    auto index = it - m_days.begin();

    for (int i = 0; i < m_days.size(); ++i) {
        m_days[i].date = m_selectedDate.addDays(i - index);
    }

    endResetModel();
}

WeekModel::Day::Day(const Qt::DayOfWeek dayOfWeek)
    : dayOfWeek(dayOfWeek)
{
    switch (dayOfWeek) {
    case Qt::Monday:
        name = tr("Monday");
        break;
    case Qt::Tuesday:
        name = tr("Tuesday");
        break;
    case Qt::Wednesday:
        name = tr("Wednesday");
        break;
    case Qt::Thursday:
        name = tr("Thursday");
        break;
    case Qt::Friday:
        name = tr("Friday");
        break;
    case Qt::Saturday:
        name = tr("Saturday");
        break;
    case Qt::Sunday:
        name = tr("Sunday");
        break;
    }
}

} // namespace tasktrackerlib
