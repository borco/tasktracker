#include "togglproxy.h"

#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSslError>
#include <QWebSocket>

namespace {
static const char* TogglWebSocketOrigin = "https://toggl.com";
static const char* TogglWebSocketUrl = "wss://stream.toggl.com/ws";
}

TogglProxy::TogglProxy(QObject *parent)
    : QObject{parent}
    , m_webSocket(new QWebSocket(TogglWebSocketOrigin, QWebSocketProtocol::VersionLatest, this))
    , m_networkAccessManager(new QNetworkAccessManager(this))
{
    qDebug().nospace() << this;
    connect(m_webSocket, &QWebSocket::connected, this, [=]() {
       qDebug() << this << "web socket connected";
       m_webSocket->ping();
    });

    connect(m_webSocket, qOverload<QAbstractSocket::SocketError>(&QWebSocket::error), this, [=](QAbstractSocket::SocketError error) {
        qDebug() << this << "web socket error:" << error;
    });

    connect(m_webSocket, &QWebSocket::pong, this, [=](quint64 elapsedTime, const QByteArray &payload) {
        qDebug() << this << "pong:" << elapsedTime << payload;
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

//    m_webSocket->open(QUrl(TogglWebSocketUrl));
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
    QString authorization = QString("%1:xxx").arg(username, password);

    QNetworkRequest request;
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Authorization", QByteArray("Basic ") + authorization.toUtf8().toBase64());
    request.setUrl(QUrl("https://api.track.toggl.com/api/v9/me"));

    qDebug() << request.rawHeaderList();

    auto reply = m_networkAccessManager->get(request);

    connect(reply, &QNetworkReply::errorOccurred, this, [=](QNetworkReply::NetworkError code){
        qCritical().nospace().noquote() << this << "::login: error occured: " << code;
    });

    connect(reply, &QNetworkReply::finished, this, [=]() {
        qDebug().nospace().noquote() << this << "::login: response: " << reply->readAll() << ", error: " << reply->errorString();
    });
}

void TogglProxy::tokenLogin(QString token)
{
    QString message = QString(R"""(
{
    "type": "authenticate",
    "api_token": "%1"
}
)""").arg(token);
    qDebug().nospace().noquote() << this << "::tokenLogin: message: " << message;

    m_webSocket->sendTextMessage(message);
}

void TogglProxy::sessionLogin(QString session)
{
    QString message = QString(R"""(
{
    "type": "authenticate",
    "session": "%1"
}
)""").arg(session);
    qDebug().nospace().noquote() << this << "::sessionLogin: message: " << message;

    m_webSocket->sendTextMessage(message);
}
