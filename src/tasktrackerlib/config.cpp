/*
    Copyright 2022 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "config.h"

#include <QDebug>
#include <QSettings>

namespace {
static const char* SettingsGroupKey = "Config";
static const char* StorePasswordInKeyChainSettingsKey = "storeSecretsInKeychain";
static const char* LogsVisibleSettingsKey = "logsVisible";
}

using namespace tasktrackerlib;

Config::Config()
{
    qDebug().nospace() << "Config: instance created (" << static_cast<void*>(this) << ")";
}

Config::~Config()
{
    save();
    qDebug().nospace() << "Config: instance deleted (" << static_cast<void*>(this) << ")";
}

void Config::load()
{
    QSettings settings;
    settings.beginGroup(SettingsGroupKey);
    setStoreSecretsInKeychain(settings.value(StorePasswordInKeyChainSettingsKey, false).toBool());
    setLogsVisible(settings.value(LogsVisibleSettingsKey, false).toBool());
    settings.endGroup();

    qDebug() << "Config: loaded";
}

void Config::save()
{
    QSettings settings;
    settings.beginGroup(SettingsGroupKey);
    settings.setValue(StorePasswordInKeyChainSettingsKey, m_storeSecretsInKeychain);
    settings.setValue(LogsVisibleSettingsKey, m_logsVisible);
    settings.endGroup();

    qDebug() << "Config: saved";
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
