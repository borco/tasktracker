/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "foldermodel.h"

#include <QDir>

using namespace tasktrackerlib;

FolderModel::FolderModel(QObject *parent)
    : QAbstractListModel(parent)
{
//    qDebug().nospace() << "FolderModel: instance created (" << static_cast<void*>(this) << ")";
}

FolderModel::~FolderModel()
{
//    qDebug().nospace() << "FolderModel: instance deleted (" << static_cast<void*>(this) << ")";
}

QHash<int, QByteArray> FolderModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[FileName] = "fileName";
    return roles;
}

int FolderModel::rowCount(const QModelIndex &parent) const
{
    return m_files.size();
}

QVariant FolderModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    return m_files[index.row()];
}

void FolderModel::setFolder(const QString &newFolder)
{
    auto clean_path = QDir::cleanPath(newFolder);

    if (m_folder == clean_path)
        return;
    m_folder = clean_path;

    updateModel();

    emit folderChanged();
}

void FolderModel::refresh()
{
//    qDebug() << "FolderModel: refresh";
    updateModel();
}

void FolderModel::cd(const QString &path)
{
    if (QDir(path).isAbsolute()) {
        setFolder(path);
    } else {
        setFolder(m_folder + "/" + path);
    }
}

void FolderModel::updateModel()
{
    beginResetModel();
    QDir path(m_folder);
    m_files = path.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Drives);
    endResetModel();
}
