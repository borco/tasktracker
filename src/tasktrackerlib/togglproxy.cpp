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

    connect(m_webSocket, &QWebSocket::connected, this, [=]() {
       qDebug() << this << "web socket connected";
       m_webSocket->ping();
    });

    connect(m_webSocket, qOverload<QAbstractSocket::SocketError>(&QWebSocket::error), this, [=](QAbstractSocket::SocketError error) {
        qDebug() << this << "web socket error:" << error;
    });

    connect(m_webSocket, &QWebSocket::pong, this, [=](quint64 elapsedTime, const QByteArray &payload) {
        qDebug().nospace() << this << " pong: " << elapsedTime << "ms";
    });

    connect(m_webSocket, &QWebSocket::textMessageReceived, this, [=](QString message) {
        qDebug().noquote() << this << "text message received:" << message;
    });

    connect(m_networkAccessManager, &QNetworkAccessManager::sslErrors, this, [=](QNetworkReply *reply, const QList<QSslError> &errors){
        qDebug().noquote() << this
                           << "ssl errors when accessing:" << reply->url() << "\n"
                           << "errors:\n";
        for (const auto& error: errors) {
            qCritical().noquote() << "  " << error.errorString();
        }
    });

    m_networkAccessManager->setProxy(QNetworkProxy::applicationProxy());
    m_networkAccessManager->connectToHostEncrypted("toggl.com");
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
        qCritical().nospace().noquote() << this << "::login: error occured: " << code;
    });

    connect(reply, &QNetworkReply::finished, this, [=]() {
        auto response_data = reply->readAll();
        if (reply->error() == QNetworkReply::NoError) {
            auto doc = QJsonDocument::fromJson(response_data);
            auto json = doc.object();

            qDebug().nospace().noquote() << this << "::login: response: " << doc.toJson();

            if (json.contains("api_token")) {
                auto api_token = json["api_token"].toString();
                m_webSocket->open(QUrl(TogglWebSocketUrl));
                webSocketLogin(api_token);
            }
        } else {
            qDebug().nospace().noquote() << this << "::login: response: " << response_data;
        }
    });
}

void TogglProxy::webSocketLogin(QString token)
{
    QString message = QString(R"""(
{
    "type": "authenticate",
    "api_token": "%1"
}
)""").arg(token);
//    qDebug().nospace().noquote() << this << "::tokenLogin: message: " << message;

    m_webSocket->sendTextMessage(message);
}
