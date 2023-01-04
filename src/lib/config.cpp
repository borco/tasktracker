/*
    Copyright 2022 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "config.h"

#include <QDebug>
#include <QSettings>

namespace {
static const char* DefaultSettingsGroupKey {"Config"};
static const char* StorePasswordInKeyChainKey {"storePasswordInKeyChain"};
}

Config::Config()
{
    qDebug() << this;
}

Config::~Config()
{
    save();
    qDebug().nospace() << "~" << this;
}

void Config::load()
{
    QSettings settings;
    qDebug().nospace() << this << "::load";
}

void Config::save()
{
    qDebug().nospace() << this << "::save";
}

void Config::setStorePasswordInKeyChain(bool value)
{
    if (m_storePasswordInKeyChain == value)
        return;
    m_storePasswordInKeyChain = value;
    emit storePasswordInKeyChainChanged();
}
