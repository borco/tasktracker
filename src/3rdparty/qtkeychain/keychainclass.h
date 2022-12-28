#pragma once

#include <QObject>

namespace QKeychain {
class Job;
}

class KeyChainClass: public QObject
{
    Q_OBJECT
public:
    explicit KeyChainClass(const QString& service, QObject* parent = nullptr);

    Q_INVOKABLE void readKey(const QString& key);
    Q_INVOKABLE void writeKey(const QString& key, const QString& value);
    Q_INVOKABLE void deleteKey(const QString& key);

Q_SIGNALS:
    void keyStored(const QString& key);
    void keyRestored(const QString& key, const QString& value);
    void keyDeleted(const QString& key);
    void error(const QString& errorText);

private:
    QString m_service;
};
