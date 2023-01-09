/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "togglproxy.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSslError>
#include <QWebSocket>

namespace {
static const char* TogglWebSocketOrigin = "https://toggl.com";
static const char* TogglWebSocketUrl = "wss://stream.toggl.com/ws";
}

using namespace tasktrackerlib;

TogglProxy::TogglProxy(QObject *parent)
    : QObject{parent}
    , m_webSocket(new QWebSocket(TogglWebSocketOrigin, QWebSocketProtocol::VersionLatest, this))
    , m_networkAccessManager(new QNetworkAccessManager(this))
{
    qDebug() << this;

    connect(m_webSocket, qOverload<QAbstractSocket::SocketError>(&QWebSocket::error), this, [=](QAbstractSocket::SocketError error) {
        if (error == QAbstractSocket::RemoteHostClosedError) {
            qDebug() << "TogglProxy: remote host closed connection; reconecting...";
            webSocketReconnect();
        } else {
            qWarning() << "TogglProxy: web socket error:" << error;
        }
    });

    connect(m_webSocket, &QWebSocket::sslErrors, this, [=](const QList<QSslError> &errors) {
        QStringList messages;
        for (const auto& error: errors) {
            messages << ("   " + error.errorString());
        }
        qWarning().noquote() << "TogglProxy: websocket ssl errors:\n" << messages.join("\n");
    });

    connect(m_networkAccessManager, &QNetworkAccessManager::sslErrors, this, [=](QNetworkReply *reply, const QList<QSslError> &errors){
        QStringList messages;
        for (const auto& error: errors) {
            messages << ("   " + error.errorString());
        }
        qWarning().noquote() << "TogglProxy: ssl errors when accessing:" << reply->url() << ":\n" << messages.join("\n");
    });

    connect(m_webSocket, &QWebSocket::textMessageReceived, this, [=](QString message) {
        qDebug().noquote() << "TogglProxy: text message received:" << message;
    });

    m_networkAccessManager->setProxy(QNetworkProxy::applicationProxy());
    //    m_networkAccessManager->connectToHostEncrypted("toggl.com");
}

TogglProxy::~TogglProxy()
{
    qDebug().nospace() << "~" << this;
}

TogglProxy *TogglProxy::create(QQmlEngine *, QJSEngine *)
{
    m_deleteInstanceOnCleanup = false;
    return get();
}

void TogglProxy::cleanup()
{
    if (m_deleteInstanceOnCleanup && m_instance) {
        delete m_instance;
        m_instance = nullptr;
    }
}

void TogglProxy::login(QString username, QString password)
{
    QString authorization = QString("%1:%2").arg(username, password);

    QNetworkRequest request;
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Authorization", QByteArray("Basic ") + authorization.toUtf8().toBase64());
    request.setUrl(QUrl("https://api.track.toggl.com/api/v9/me"));

    auto reply = m_networkAccessManager->get(request);

    connect(reply, &QNetworkReply::errorOccurred, this, [=](QNetworkReply::NetworkError code){
        qCritical().nospace().noquote() << "TogglProxy: error during login: " << code;
    });

    connect(reply, &QNetworkReply::finished, this, [=]() {
        auto response_data = reply->readAll();
        if (reply->error() == QNetworkReply::NoError) {
            auto doc = QJsonDocument::fromJson(response_data);
            auto json = doc.object();

            qDebug().nospace().noquote() << "TogglProxy: login response: " << doc.toJson();

            if (json.contains("api_token")) {
                webSocketLogin(json["api_token"].toString());
            }
        } else {
            qDebug().nospace().noquote() << "TogglProxy: login failed: " << response_data;
        }
    });
}

void TogglProxy::webSocketReconnect()
{
    if (m_apiToken.isEmpty()) {
        qWarning() << "TogglProxy: can't reconnect (no api token)";
        return;
    }

    if (m_webSocket->isValid()) {
        qWarning() << "TogglProxy: no need to reconnect (web socket is valid)";
        return;
    }

    webSocketLogin(m_apiToken);
}

void TogglProxy::webSocketLogin(QString token)
{
    m_apiToken = token;
    QString message = QString(R"""(
{
    "type": "authenticate",
    "api_token": "%1"
}
)""").arg(token);

    m_webSocket->open(QUrl(TogglWebSocketUrl));
    m_webSocket->sendTextMessage(message);
}
