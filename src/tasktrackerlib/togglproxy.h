/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QQmlEngine>

class QNetworkAccessManager;

namespace tasktrackerlib {

class TogglProxy : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(LoggedStatus loggedStatus READ loggedStatus WRITE setLoggedStatus NOTIFY loggedStatusChanged)
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)

    Q_PROPERTY(QString fullname READ fullname NOTIFY fullnameChanged)
    Q_PROPERTY(QString imageUrl READ imageUrl NOTIFY imageUrlChanged)

public:
    enum LoggedStatus {
        LoggedUnknown = 0,
        LoggedIn,
        LoggedOut,
    };

    Q_ENUM(LoggedStatus);

    ~TogglProxy();

    static TogglProxy* get() {
        if (!m_instance) {
            m_instance = new TogglProxy();
        }
        return m_instance;
    }
    static TogglProxy *create(QQmlEngine *, QJSEngine *);
    static void cleanup();

    void load();
    void save();

    LoggedStatus loggedStatus() const { return m_loggedStatus; }
    void setLoggedStatus(const LoggedStatus &newLoggedStatus);

    QString username() const { return m_username; }
    void setUsername(const QString &newUsername);

    QString password() const { return m_password; }
    void setPassword(const QString &newPassword);

    QString fullname() const { return m_fullname; }

    QString imageUrl() const { return m_imageUrl; }

signals:
    void loggedStatusChanged();
    void loggedWithUserAndPassword();
    void usernameChanged();
    void passwordChanged();
    void fullnameChanged();
    void imageUrlChanged();

public slots:
    void logIn();
    void logOut();

private:
    explicit TogglProxy(QObject *parent = nullptr);

    void setFullname(const QString &newFullname);
    void setImageUrl(const QString &newImageUrl);

    QByteArray sessionFromCookieJar() const;
    void updateCookieJar();

    void getMe(bool updateIsLoggedIn=false);
    void getOrganizations();

    inline static bool m_deleteInstanceOnCleanup = true;
    inline static TogglProxy* m_instance = nullptr;

    QNetworkAccessManager* m_networkAccessManager = nullptr;

    LoggedStatus m_loggedStatus = LoggedUnknown;
    QByteArray m_session;
    QString m_username;
    QString m_password;
    QString m_fullname;
    QString m_imageUrl;
};

}
