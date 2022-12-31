/*
    Copyright 2022 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "config.h"

#include <QDebug>

Config::Config()
{
    qDebug() << this;
}

Config::~Config()
{
    qDebug().nospace() << "~" << this;
}

void Config::setUseKeyChain(bool newUseKeyChain)
{
    if (m_useKeyChain == newUseKeyChain)
        return;
    m_useKeyChain = newUseKeyChain;
    emit useKeyChainChanged();
}
