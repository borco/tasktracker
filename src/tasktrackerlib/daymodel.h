/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QAbstractListModel>
#include <QDate>
#include <QQmlEngine>

namespace tasktrackerlib {

class DayModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit DayModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE static QDate dateForIndex(int index);
    Q_INVOKABLE static int indexForDate(const QDate& date);
};

} // namespace tasktrackerlib
