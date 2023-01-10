/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QQmlEngine>
#include <QAbstractListModel>

class FolderListModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString folder READ folder WRITE setFolder NOTIFY folderChanged)

public:
    explicit FolderListModel(QObject *parent = nullptr);
    ~FolderListModel();

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QString folder() const { return m_folder; }
    void setFolder(const QString &newFolder);

    Q_INVOKABLE void refresh();
    Q_INVOKABLE void cd(const QString& path);

signals:
    void folderChanged();

private:
    enum ColumnNames {
        FileName = Qt::UserRole + 1,
    };

    void updateModel();

    QString m_folder;
    QStringList m_files;
};
