/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QQmlEngine>
#include <QSortFilterProxyModel>

namespace tasktrackerlib {

class TaskListFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(bool doneVisible READ doneVisible WRITE setDoneVisible NOTIFY doneVisibleChanged)
    Q_PROPERTY(bool showArchived READ showArchived WRITE setShowArchived NOTIFY showArchivedChanged)

public:
    explicit TaskListFilterModel(QObject* parent = nullptr);

    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

    bool doneVisible() const { return m_doneVisible; }
    void setDoneVisible(bool newDoneVisible);

    bool showArchived() const { return m_showArchived; }
    void setShowArchived(bool newShowArchived);

signals:
    void doneVisibleChanged();
    void showArchivedChanged();

private:
    bool m_doneVisible = false;
    bool m_showArchived = false;
};

}
