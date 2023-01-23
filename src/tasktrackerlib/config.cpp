/*
    Copyright 2022 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "config.h"

#include <QDebug>
#include <QSettings>
#include <QStandardPaths>

namespace {
static const char* SettingsGroupKey = "Config";
static const char* StorePasswordInKeyChainSettingsKey = "storeSecretsInKeychain";
static const char* LogsVisibleSettingsKey = "logsVisible";
static const char* DataFolderLocationSettingsKey = "dataFolderLocation";
}

using namespace tasktrackerlib;

Config::Config()
{
//    qDebug().nospace() << "Config: instance created (" << static_cast<void*>(this) << ")";
    m_defaultDataFolderLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    m_dataFolderLocation = m_defaultDataFolderLocation;
}

Config::~Config()
{
    save();
//    qDebug().nospace() << "Config: instance deleted (" << static_cast<void*>(this) << ")";
}

void Config::load()
{
    QSettings settings;
    settings.beginGroup(SettingsGroupKey);
    setStoreSecretsInKeychain(settings.value(StorePasswordInKeyChainSettingsKey, false).toBool());
    setLogsVisible(settings.value(LogsVisibleSettingsKey, false).toBool());
    setDataFolderLocation(settings.value(DataFolderLocationSettingsKey, m_defaultDataFolderLocation).toString());
    settings.endGroup();

//    qDebug() << "Config: loaded";
}

void Config::save()
{
    QSettings settings;
    settings.beginGroup(SettingsGroupKey);
    settings.setValue(StorePasswordInKeyChainSettingsKey, m_storeSecretsInKeychain);
    settings.setValue(LogsVisibleSettingsKey, m_logsVisible);
    settings.setValue(DataFolderLocationSettingsKey, m_dataFolderLocation);
    settings.endGroup();

//    qDebug() << "Config: saved";
}

void Config::setStoreSecretsInKeychain(bool value)
{
    if (m_storeSecretsInKeychain == value)
        return;
    m_storeSecretsInKeychain = value;
    emit storeSecretsInKeychainChanged();
}

void Config::setLogsVisible(bool newLogsVisible)
{
    if (m_logsVisible == newLogsVisible)
        return;
    m_logsVisible = newLogsVisible;
    emit logsVisibleChanged();
}

void Config::setDataFolderLocation(const QString &newDataFolderLocation)
{
    if (m_dataFolderLocation == newDataFolderLocation)
        return;
    m_dataFolderLocation = newDataFolderLocation;
    emit dataFolderLocationChanged();
}

Qt::DayOfWeek Config::weekStart() const
{
    return m_weekStart;
}

void Config::setWeekStart(Qt::DayOfWeek newWeekStart)
{
    if (m_weekStart == newWeekStart)
        return;
    m_weekStart = newWeekStart;
    emit weekStartChanged();
}
