/*
    Copyright 2022 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include <QQmlEngine>

class Config: public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(bool storePasswordInKeyChain READ storePasswordInKeyChain WRITE setStorePasswordInKeyChain NOTIFY storePasswordInKeyChainChanged)

public:
    ~Config();

    static Config* get() {
        if (!m_instance) {
            m_instance = new Config();
        }
        return m_instance;
    }
    static Config *create(QQmlEngine *, QJSEngine *) { return get(); }

    void load();
    void save();

    bool storePasswordInKeyChain() const { return m_storePasswordInKeyChain; }
    void setStorePasswordInKeyChain(bool value);

    Q_INVOKABLE void login(QString username, QString password);

signals:
    void storePasswordInKeyChainChanged();

private:
    Config();

    inline static Config* m_instance {nullptr};

    bool m_storePasswordInKeyChain {false};
};
