/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "togglproxy.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkProxy>
#include <QNetworkReply>
#include <QSettings>
#include <QSslError>

namespace {
static const char* SettingsGroupKey = "TogglProxy";
static const char* SessionSettingsKey = "session";
}

using namespace tasktrackerlib;

TogglProxy::TogglProxy(QObject *parent)
    : QObject{parent}
    , m_networkAccessManager(new QNetworkAccessManager(this))
{
    qDebug().nospace() << "TogglProxy: instance created (" << static_cast<void*>(this) << ")";

    connect(m_networkAccessManager, &QNetworkAccessManager::sslErrors, this, [=](QNetworkReply *reply, const QList<QSslError> &errors){
        QStringList messages;
        for (const auto& error: errors) {
            messages << ("   " + error.errorString());
        }
        qWarning().noquote() << "TogglProxy: ssl errors when accessing:" << reply->url() << ":\n" << messages.join("\n");
    });

    m_networkAccessManager->setProxy(QNetworkProxy::applicationProxy());
    m_networkAccessManager->connectToHostEncrypted("toggl.com");
}

TogglProxy::~TogglProxy()
{
    save();
    qDebug().nospace() << "TogglProxy: instance deleted (" << static_cast<void*>(this) << ")";
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

void TogglProxy::load()
{
    QSettings settings;
    settings.beginGroup(SettingsGroupKey);
    m_session = settings.value(SessionSettingsKey).toString();
    settings.endGroup();

    qDebug() << "TogglProxy: loaded";
}

void TogglProxy::save()
{
    QSettings settings;
    settings.beginGroup(SettingsGroupKey);
    settings.setValue(SessionSettingsKey, m_session);
    settings.endGroup();

    qDebug() << "TogglProxy: saved";
}

void TogglProxy::onLogInNetworkError(QNetworkReply::NetworkError code)
{
    qCritical().nospace().noquote() << "TogglProxy: error during login: " << code;
    setIsLoggedIn(false);
    m_apiToken.clear();
}

void TogglProxy::onLogInNetworkFinished(QNetworkReply *reply)
{
    auto response_data = reply->readAll();
    if (reply->error() == QNetworkReply::NoError) {
        auto doc = QJsonDocument::fromJson(response_data);
        auto json = doc.object();

        qDebug().nospace().noquote() << "TogglProxy: login response: " << doc.toJson();

        if (json.contains("api_token")) {
            m_apiToken = json["api_token"].toString();
        }

        finishOkLogIn();
    } else {
        qDebug().nospace().noquote() << "TogglProxy: login failed: " << response_data;
        finishFailedLogIn();
    }
}

void TogglProxy::logIn(const QString &username, const QString &password)
{
    if (username.isEmpty() || password.isEmpty()) {
        qWarning() << "TogglProxy: can't login because user or password is empty";
        emit logInFailed();
        return;
    }

    QString authorization = QString("%1:%2").arg(username, password);

    QNetworkRequest request;
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Authorization", QByteArray("Basic ") + authorization.toUtf8().toBase64());
    request.setUrl(QUrl("https://api.track.toggl.com/api/v9/me"));

    auto reply = m_networkAccessManager->get(request);

    connect(reply, &QNetworkReply::errorOccurred, this, &TogglProxy::onLogInNetworkError);
    connect(reply, &QNetworkReply::finished, this, [=]() { onLogInNetworkFinished(reply); });
}

void TogglProxy::finishOkLogIn()
{
    setIsLoggedIn(true);
    emit logInOk();
}

void TogglProxy::finishFailedLogIn()
{
    setIsLoggedIn(false);
    m_session.clear();
    m_apiToken.clear();
    emit logInFailed();
}

void TogglProxy::apiTokenLogIn()
{
    if (m_apiToken.isEmpty()) {
        qDebug() << "TogglProxy: api token not available";
        return;
    }

    logIn(m_apiToken, "api_token");
}

void TogglProxy::logIn()
{
    logIn(m_username, m_password);
}

void TogglProxy::setUsername(const QString &newUsername)
{
    if (m_username == newUsername)
        return;
    m_username = newUsername;
    emit usernameChanged();
}

void TogglProxy::setPassword(const QString &newPassword)
{
    if (m_password == newPassword)
        return;
    m_password = newPassword;
    emit passwordChanged();
}

void TogglProxy::setIsLoggedIn(bool newIsLoggedIn)
{
    if (m_isLoggedIn == newIsLoggedIn)
        return;
    m_isLoggedIn = newIsLoggedIn;
    emit isLoggedInChanged();
}
