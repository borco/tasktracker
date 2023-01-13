/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "togglproxy.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QNetworkProxy>
#include <QNetworkReply>
#include <QSettings>
#include <QSslError>

namespace {
static const char* SettingsGroupKey = "TogglProxy";
static const char* SessionSettingsKey = "session";

static const char* TogglApiUrl = "https://api.track.toggl.com/";
static const char* SessionCookieName = "__Host-timer-session";
}

using namespace tasktrackerlib;

TogglProxy::TogglProxy(QObject *parent)
    : QObject{parent}
    , m_networkAccessManager(new QNetworkAccessManager(this))
{
//    qDebug().nospace() << "TogglProxy: instance created (" << static_cast<void*>(this) << ")";

    connect(m_networkAccessManager, &QNetworkAccessManager::sslErrors, this, [=](QNetworkReply *reply, const QList<QSslError> &errors){
        QStringList messages;
        for (const auto& error: errors) {
            messages << ("   " + error.errorString());
        }
        qWarning().noquote() << "TogglProxy: ssl errors when accessing:" << reply->url() << ":\n" << messages.join("\n");
    });

    m_networkAccessManager->setProxy(QNetworkProxy::applicationProxy());
    m_networkAccessManager->setCookieJar(new QNetworkCookieJar());
    m_networkAccessManager->connectToHostEncrypted("toggl.com");
}

TogglProxy::~TogglProxy()
{
    save();
//    qDebug().nospace() << "TogglProxy: instance deleted (" << static_cast<void*>(this) << ")";
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
    m_session = settings.value(SessionSettingsKey).toByteArray();
    settings.endGroup();

//    qDebug() << "TogglProxy: loaded";

    if (!m_session.isEmpty()) {
        updateCookieJar();
        getMe(true);
    } else {
        setLoggedStatus(LoggedOut);
    }
}

void TogglProxy::save()
{
    QSettings settings;
    settings.beginGroup(SettingsGroupKey);
    settings.setValue(SessionSettingsKey, m_session);
    settings.endGroup();

//    qDebug() << "TogglProxy: saved";
}

void TogglProxy::logIn()
{
    if (m_username.isEmpty() || m_password.isEmpty()) {
        qWarning() << "TogglProxy: can't login without an username and a password";
        setLoggedStatus(LoggedOut);
        return;
    }

    setLoggedStatus(LoggedUnknown);

    QString authorization = QString("%1:%2").arg(m_username, m_password);

    QNetworkRequest request;
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Authorization", QByteArray("Basic ") + authorization.toUtf8().toBase64());
    request.setUrl(QUrl("https://api.track.toggl.com/api/v9/me/sessions"));

    auto reply = m_networkAccessManager->post(request, QByteArray());

    connect(reply, &QNetworkReply::errorOccurred, this, [=](QNetworkReply::NetworkError code){
        qCritical().noquote() << "TogglProxy: error during login:" << code;
        setLoggedStatus(LoggedOut);
    });

    connect(reply, &QNetworkReply::finished, this, [=]() {
        auto response_data = reply->readAll();
        if (reply->error() == QNetworkReply::NoError) {
            auto doc = QJsonDocument::fromJson(response_data);
            auto json = doc.object();

            qDebug().noquote() << "TogglProxy: session login response:" << doc.toJson();

            m_session = sessionFromCookieJar();

            getMe(false);
            setLoggedStatus(LoggedIn);
            emit loggedWithUserAndPassword();
        } else {
            qDebug().noquote() << "TogglProxy: login failed:" << response_data;
            m_session.clear();
            updateCookieJar();
            setLoggedStatus(LoggedOut);
        }
    });
}

void TogglProxy::logOut()
{
    if (m_loggedStatus != LoggedIn) {
        return;
    }

    qDebug() << "TogglProxy: logged out";

    m_session.clear();
    updateCookieJar();
    setFullname("");
    setImageUrl("");
    setLoggedStatus(LoggedOut);
}

void TogglProxy::getMe(bool updateIsLoggedIn)
{
    if (m_session.isEmpty()) {
        qCritical() << "TogglProxy: can't get user info before logging in";
        if (updateIsLoggedIn) {
            setLoggedStatus(LoggedOut);
        }
        return;
    }

    auto url = QUrl("https://api.track.toggl.com/api/v9/me");
    QNetworkRequest request;
    request.setRawHeader("Content-Type", "application/json");
    request.setUrl(url);

    auto reply = m_networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        auto response_data = reply->readAll();
        if (reply->error() == QNetworkReply::NoError) {
            if (updateIsLoggedIn) {
                setLoggedStatus(LoggedIn);
                qDebug() << "TogglProxy: logged in using old session";
            }
            auto doc = QJsonDocument::fromJson(response_data);
            auto json = doc.object();

            static const char* FullnameKey = "fullname";
            static const char* ImageUrlKey = "image_url";

            if (json.contains(FullnameKey)) {
                setFullname(json[FullnameKey].toString());
            }

            if (json.contains(ImageUrlKey)) {
                setImageUrl(json[ImageUrlKey].toString());
            }

//            qDebug().noquote() << "TogglProxy: getMe response:" << doc.toJson();
        } else {
            setImageUrl("");
            setFullname("");
            if (updateIsLoggedIn) {
                setLoggedStatus(LoggedOut);
                qDebug() << "TogglProxy: failed to log in using old session";
            }
            qDebug().noquote() << "TogglProxy: failed to get user info:" << response_data;
        }
    });
}

void TogglProxy::getOrganizations()
{
    if (m_session.isEmpty()) {
        qCritical() << "TogglProxy: can't get organizations before logging in";
        return;
    }

    auto url = QUrl("https://api.track.toggl.com/api/v9/me/organizations");
    QNetworkRequest request;
    request.setRawHeader("Content-Type", "application/json");
    request.setUrl(url);

    auto reply = m_networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        auto response_data = reply->readAll();
        if (reply->error() == QNetworkReply::NoError) {
            auto doc = QJsonDocument::fromJson(response_data);
            auto json = doc.object();
            qDebug().noquote() << "TogglProxy: getClients response:" << doc.toJson();
        } else {
            qDebug().noquote() << "TogglProxy: getClients failed:" << response_data;
        }
    });
}

QByteArray TogglProxy::sessionFromCookieJar() const
{
    for(const auto& cookie: m_networkAccessManager->cookieJar()->cookiesForUrl(QUrl(TogglApiUrl))) {
        if (cookie.name() == SessionCookieName) {
            return cookie.value();
        }
    }

    return QByteArray();
}

void TogglProxy::updateCookieJar()
{
    auto cookie_jar = m_networkAccessManager->cookieJar();
    QList<QNetworkCookie> cookies;

    if (!m_session.isEmpty()) {
        cookies << QNetworkCookie(SessionCookieName, m_session);
    }
    cookie_jar->setCookiesFromUrl(cookies, QUrl(TogglApiUrl));
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

void TogglProxy::setLoggedStatus(const LoggedStatus &newLoggedStatus)
{
    if (m_loggedStatus == newLoggedStatus)
        return;
    m_loggedStatus = newLoggedStatus;
    emit loggedStatusChanged();
}

void TogglProxy::setFullname(const QString &newFullname)
{
    if (m_fullname == newFullname)
        return;
    m_fullname = newFullname;
    emit fullnameChanged();
}

void TogglProxy::setImageUrl(const QString &newImageUrl)
{
    if (m_imageUrl == newImageUrl)
        return;
    m_imageUrl = newImageUrl;
    emit imageUrlChanged();
}
