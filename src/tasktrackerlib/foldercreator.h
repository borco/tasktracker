/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QQmlEngine>

namespace tasktrackerlib {

class FolderCreator : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QString error READ error WRITE setError NOTIFY errorChanged)

public:
    explicit FolderCreator(QObject *parent = nullptr);

    QString path() const { return m_path; }
    void setPath(const QString &newPath);

    QString error() const { return m_error; }
    void setError(const QString &newError);

    Q_INVOKABLE bool isValidDir(const QString& newDir);
    Q_INVOKABLE bool makeDir(const QString& newDir);

signals:
    void pathChanged();
    void errorChanged();

private:
    QString m_path;
    QString m_error;
};

}
