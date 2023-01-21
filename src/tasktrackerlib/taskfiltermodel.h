/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QQmlEngine>
#include <QSortFilterProxyModel>

namespace tasktrackerlib {

class TaskFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(bool isDoneVisible READ isDoneVisible WRITE setIsDoneVisible NOTIFY isDoneVisibleChanged)
    Q_PROPERTY(bool isArchivedVisible READ isArchivedVisible WRITE setIsArchivedVisible NOTIFY isArchivedVisibleChanged)

public:
    explicit TaskFilterModel(QObject* parent = nullptr);

    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

    bool isDoneVisible() const { return m_isDoneVisible; }
    void setIsDoneVisible(bool newIsDoneVisible);

    bool isArchivedVisible() const { return m_isArchivedVisible; }
    void setIsArchivedVisible(bool newIsArchivedVisible);

signals:
    void isDoneVisibleChanged();
    void isArchivedVisibleChanged();

private:
    bool m_isDoneVisible = false;
    bool m_isArchivedVisible = false;
};

}
