/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "foldercreator.h"

#include <QRegularExpression>

using namespace tasktrackerlib;

namespace {

static const int MaximumPathLength = 128;

static const char* WindowsDevicePattern = R"((CON|AUX|PRN|NUL|COM[1-9]|LPT[1-9])(\..*)?)";

// not all charactes from InvalidCharacters are invalid, but we better to avoid them
static const char* InvalidCharacters = "\t\n`~!@#$%^&*()=[]{}\\|/<>?:;\"'";

}

FolderCreator::FolderCreator(QObject *parent)
    : QObject{parent}
{
}

bool FolderCreator::isValidDir(const QString &newDir)
{
    if (newDir.isEmpty()) {
        setError(tr("Path is empty"));
        return false;
    }

    if (newDir.size() > MaximumPathLength) {
        setError(tr("Path is too long"));
        return false;
    }

    if (newDir == ".") {
        setError(tr("'.' is not a valid path"));
        return false;
    }

    if (newDir.startsWith("..")) {
        setError(tr("Path can't start with '..'"));
        return false;
    }

    if (newDir.endsWith(".")) {
        setError(tr("Path can't end with '.'"));
        return false;
    }

    if (newDir.startsWith(",") or newDir.endsWith(",")) {
        setError(tr("Path can't start or end with ','"));
        return false;
    }

    if (newDir.endsWith(".")) {
        setError(tr("Path can't end with '.'"));
        return false;
    }

    if (newDir[0].isSpace() || newDir[newDir.size() - 1].isSpace()) {
        setError(tr("Path can't start or end with spaces"));
        return false;
    }

    if (newDir[0].isSpace() || newDir[newDir.size() - 1].isSpace()) {
        setError(tr("Path can't start or end with spaces"));
        return false;
    }

    for (const auto& c: newDir) {
        if (QString(InvalidCharacters).contains(c)) {
            setError(tr("Path can't use '%1' character").arg(c));
            return false;
        }
    }

    QRegularExpression re(WindowsDevicePattern);
    auto match = re.match(newDir);
    if (match.hasMatch()) {
        setError(tr("'%1' is not valid").arg(newDir));
        return false;
    }

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
