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

    Q_PROPERTY(bool isLoggedIn READ isLoggedIn WRITE setIsLoggedIn NOTIFY isLoggedInChanged)
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)

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

    void load();
    void save();

    bool isLoggedIn() const { return m_isLoggedIn; }
    void setIsLoggedIn(bool newIsLoggedIn);

    QString username() const { return m_username; }
    void setUsername(const QString &newUsername);

    QString password() const { return m_password; }
    void setPassword(const QString &newPassword);

signals:
    void isLoggedInChanged();
    void logInOk();
    void logInFailed();
    void usernameChanged();
    void passwordChanged();

public slots:
    void logIn();

private:
    explicit TogglProxy(QObject *parent = nullptr);

    QByteArray sessionFromCookieJar() const;
    void updateCookieJar();

    void getMe();
    void getOrganizations();

    inline static bool m_deleteInstanceOnCleanup = true;
    inline static TogglProxy* m_instance = nullptr;

    QNetworkAccessManager* m_networkAccessManager = nullptr;

    bool m_isLoggedIn = false;
    QByteArray m_session;
    QString m_username;
    QString m_password;
};

}
