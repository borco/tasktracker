/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "foldercreator.h"

using namespace tasktrackerlib;

namespace {

static const char* WindowsDevicePattern = "(CON|AUX|PRN|NUL|COM[1-9]|LPT[1-9])(\\..*)?";

// not all charactes from InvalidCharacters are invalid, but we better to avoid them
static const char* InvalidCharacters = "`~!@#$%^&*()=[]{}\\|/<>?:;\"'";

}

FolderCreator::FolderCreator(QObject *parent)
    : QObject{parent}
{
}

bool FolderCreator::isValidDir(const QString &newDir)
{
    static const int maximum_length = 128;

    if (newDir.isEmpty()) {
        setError(tr("Path is empty"));
        return false;
    }

    if (newDir.size() > maximum_length) {
        setError(tr("Path is too long"));
        return false;
    }

    // TODO: finish isValidDir
    // * check no invalid characters: /\\|`'"
    // * check not composed only from spaces
    // * check no spaces at start or end
    // * check no dots at start or end
    // * check not a windows device name
    // * check no invalid character present
    setError("");
    return true;
}

bool FolderCreator::makeDir(const QString &newDir)
{
    // TODO: implement makeDir
    return false;
}

void FolderCreator::setPath(const QString &newPath)
{
    if (m_path == newPath)
        return;
    m_path = newPath;
    emit pathChanged();
}

void FolderCreator::setError(const QString &newError)
{
    if (m_error == newError)
        return;
    m_error = newError;
    emit errorChanged();
}
