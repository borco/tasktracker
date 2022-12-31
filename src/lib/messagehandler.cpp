/*
    Copyright 2022 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "messagehandler.h"

#include <QDebug>

void message_handler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";

    switch (type) {
    case QtDebugMsg:
        qDebug().noquote().nospace() << localMsg.constData() << " (file://" << file << ":" << context.line << ")";
        break;
    case QtInfoMsg:
        qInfo().noquote().nospace() << localMsg.constData() << " (file://" << file << ":" << context.line << ")";
        break;
    case QtWarningMsg:
        qWarning().noquote().nospace() << localMsg.constData() << " (file://" << file << ":" << context.line << ")";
        break;
    case QtCriticalMsg:
        qCritical().noquote().nospace() << localMsg.constData() << " (file://" << file << ":" << context.line << ")";
        break;
    case QtFatalMsg:
        qFatal("%s (file://%s:%i)", localMsg.constData(), file, context.line);
        break;
    }
}
