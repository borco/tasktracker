/*
    Copyright 2022 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include <QQmlEngine>

class Config: public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(bool useKeyChain READ useKeyChain WRITE setUseKeyChain NOTIFY useKeyChainChanged)

public:
    ~Config();

    static Config *create(QQmlEngine *, QJSEngine *) {
        if (!m_instance) {
            m_instance = new Config();
        }
        return m_instance;
    }

    bool useKeyChain() const { return m_useKeyChain; }
    void setUseKeyChain(bool newUseKeyChain);

signals:
    void useKeyChainChanged();

private:
    Config();

    inline static Config* m_instance {nullptr};

    bool m_useKeyChain {false};
};
