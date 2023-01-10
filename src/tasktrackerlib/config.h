/*
    Copyright 2022 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QQmlEngine>

namespace tasktrackerlib {

class Config: public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(bool storeSecretsInKeychain READ storeSecretsInKeychain WRITE setStoreSecretsInKeychain NOTIFY storeSecretsInKeychainChanged)
    Q_PROPERTY(bool logsVisible READ logsVisible WRITE setLogsVisible NOTIFY logsVisibleChanged)
    Q_PROPERTY(QString dataFolderLocation READ dataFolderLocation WRITE setDataFolderLocation NOTIFY dataFolderLocationChanged)
    Q_PROPERTY(QString defaultDataFolderLocation READ defaultDataFolderLocation CONSTANT)

public:
    ~Config();

    static Config* get() {
        if (!m_instance) {
            m_instance = new Config();
        }
        return m_instance;
    }
    static Config *create(QQmlEngine *, QJSEngine *) { return get(); }

    void load();
    void save();

    bool storeSecretsInKeychain() const { return m_storeSecretsInKeychain; }
    void setStoreSecretsInKeychain(bool value);

    bool logsVisible() const { return m_logsVisible; }
    void setLogsVisible(bool newLogsVisible);

    QString dataFolderLocation() const { return m_dataFolderLocation; }
    void setDataFolderLocation(const QString &newDataFolderLocation);

    QString defaultDataFolderLocation() const { return m_defaultDataFolderLocation; }

signals:
    void storeSecretsInKeychainChanged();
    void logsVisibleChanged();
    void dataFolderLocationChanged();

private:
    Config();

    inline static Config* m_instance {nullptr};

    bool m_storeSecretsInKeychain = false;
    bool m_logsVisible = false;
    QString m_dataFolderLocation;
    QString m_defaultDataFolderLocation;
};

}
