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

    Q_PROPERTY(bool showDone READ showDone WRITE setShowDone NOTIFY showDoneChanged)
    Q_PROPERTY(bool showArchived READ showArchived WRITE setShowArchived NOTIFY showArchivedChanged)

public:
    explicit TaskListFilterModel(QObject* parent = nullptr);

    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

    bool showDone() const { return m_showDone; }
    void setShowDone(bool newShowDone);

    bool showArchived() const { return m_showArchived; }
    void setShowArchived(bool newShowArchived);

signals:
    void showDoneChanged();
    void showArchivedChanged();

private:
    bool m_showDone = false;
    bool m_showArchived = false;
};

}
