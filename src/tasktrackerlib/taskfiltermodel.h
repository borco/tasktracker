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
    Q_PROPERTY(bool archivedVisible READ archivedVisible WRITE setArchivedVisible NOTIFY archivedVisibleChanged)

public:
    explicit TaskFilterModel(QObject* parent = nullptr);

    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

    bool isDoneVisible() const { return m_isDoneVisible; }
    void setIsDoneVisible(bool newIsDoneVisible);

    bool archivedVisible() const { return m_archivedVisible; }
    void setArchivedVisible(bool newArchivedVisible);

signals:
    void isDoneVisibleChanged();
    void archivedVisibleChanged();

private:
    bool m_isDoneVisible = false;
    bool m_archivedVisible = false;
};

}
