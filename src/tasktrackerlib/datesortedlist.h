/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QDateTime>

namespace tasktrackerlib {

class ObjectWithSize : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int size READ size WRITE setSize NOTIFY sizeChanged)

public:
    explicit ObjectWithSize(QObject* parent = nullptr) : QObject(parent) {}

    int size() const { return m_size; }
    void setSize(int newSize) {
        if (m_size == newSize)
            return;
        m_size = newSize;
        emit sizeChanged();
    }

signals:
    void sizeChanged();

protected:
    int m_size = 0;
};

template <typename T> requires
requires (T a) {
    [](T a) -> QObject* { return a.parent(); };
    [](T a, QObject* o) { a.setParent(o); };
    [](T a) -> QDateTime { return a.start(); };
}
class DateSortedList: public ObjectWithSize
{
public:
    DateSortedList(QObject* parent = nullptr) : ObjectWithSize(parent) {}
    ~DateSortedList() { clear(); }

    bool insert(T* item) {
        if (!item->start().isValid()) {
            qDebug() << "Date is not valid";
            return false;
        }

        if (std::find(m_items.cbegin(), m_items.cend(), item) != m_items.cend()) {
            qDebug() << "The list already contains" << item;
            return false;
        }

        if (!item->parent())
            item->setParent(this);

        auto it = std::upper_bound(
                    m_items.begin(),
                    m_items.end(),
                    item->start(),
                    [](const QDateTime& dateTime, const T* duration) {
            return dateTime < duration->start();
        });
        m_items.insert(it, item);

        setSize(m_items.size());

        return true;
    }

    void clear() {
        for (auto item: m_items) {
            if (item->parent() == this)
                delete item;
        }
        m_items.clear();
        setSize(0);
    }

    T* operator[](int i) { return m_items[i]; }
    const T* operator[](int i) const { return m_items[i]; }

protected:
    std::vector<T*> m_items;
};

} // tasktrackerlib
