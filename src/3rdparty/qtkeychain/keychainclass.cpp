#include "keychainclass.h"

#include "keychain.h"

#include <QDebug>

KeyChainClass::KeyChainClass(const QString &service, QObject* parent)
    : QObject(parent)
    , m_service(service)
{
}

void KeyChainClass::readKey(const QString &key)
{
    auto read_job = new QKeychain::ReadPasswordJob(m_service);
    read_job->setKey(key);

    connect(read_job, &QKeychain::ReadPasswordJob::finished, this, [=]() {
        if (read_job->error()) {
            emit error(tr("Read key failed: %1").arg(qPrintable(read_job->errorString())));
            return;
        }
        emit keyRestored(key, read_job->textData());
    });

    read_job->start();
}

void KeyChainClass::writeKey(const QString &key, const QString &value)
{
    auto write_job = new QKeychain::WritePasswordJob(m_service);
    write_job->setKey(key);

    connect(write_job, &QKeychain::WritePasswordJob::finished, this, [=](){
        if (write_job->error()) {
            emit error(tr("Write key failed: %1").arg(qPrintable(write_job->errorString())));
            return;
        }
        emit keyStored(key);
    });

    write_job->setTextData(value);
    write_job->start();
}

void KeyChainClass::deleteKey(const QString &key)
{
    auto delete_job = new QKeychain::DeletePasswordJob(m_service);
    delete_job->setKey(key);

    connect(delete_job, &QKeychain::DeletePasswordJob::finished, this, [=]() {
        if (delete_job->error()) {
            emit error(tr("Delete key failed: %1").arg(qPrintable(delete_job->errorString())));
            return;
        }
        emit keyDeleted(key);
    });

    delete_job->start();
}
