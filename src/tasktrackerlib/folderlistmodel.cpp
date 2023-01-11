/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "folderlistmodel.h"

#include <QDir>

using namespace tasktrackerlib;

FolderListModel::FolderListModel(QObject *parent)
    : QAbstractListModel(parent)
{
//    qDebug().nospace() << "FolderListModel: instance created (" << static_cast<void*>(this) << ")";
}

FolderListModel::~FolderListModel()
{
//    qDebug().nospace() << "FolderListModel: instance deleted (" << static_cast<void*>(this) << ")";
}

QHash<int, QByteArray> FolderListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[FileName] = "fileName";
    return roles;
}

int FolderListModel::rowCount(const QModelIndex &parent) const
{
    return m_files.size();
}

QVariant FolderListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    return m_files[index.row()];
}

void FolderListModel::setFolder(const QString &newFolder)
{
    auto clean_path = QDir::cleanPath(newFolder);

    if (m_folder == clean_path)
        return;
    m_folder = clean_path;

    updateModel();

    emit folderChanged();
}

void FolderListModel::refresh()
{
//    qDebug() << "FolderListModel: refresh";
    updateModel();
}

void FolderListModel::cd(const QString &path)
{
    if (QDir(path).isAbsolute()) {
        setFolder(path);
    } else {
        setFolder(m_folder + "/" + path);
    }
}

void FolderListModel::updateModel()
{
    beginResetModel();
    QDir path(m_folder);
    m_files = path.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Drives);
    endResetModel();
}
