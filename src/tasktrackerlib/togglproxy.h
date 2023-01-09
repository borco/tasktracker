/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QQmlEngine>

class QWebSocket;
class QNetworkAccessManager;

namespace tasktrackerlib {

class TogglProxy : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    ~TogglProxy();

    static TogglProxy* get() {
        if (!m_instance) {
            m_instance = new TogglProxy();
        }
        return m_instance;
    }
    static TogglProxy *create(QQmlEngine *, QJSEngine *);
    static void cleanup();

signals:

public slots:
    void login(QString username, QString password);

private:
    explicit TogglProxy(QObject *parent = nullptr);

    void webSocketReconnect();
    void webSocketLogin(QString token);

    inline static bool m_deleteInstanceOnCleanup = true;
    inline static TogglProxy* m_instance = nullptr;

    QWebSocket* m_webSocket = nullptr;
    QNetworkAccessManager* m_networkAccessManager = nullptr;
    QString m_apiToken;
};

}
