/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QDateTime>

namespace tasktrackerlib {

template <typename T>
concept ObjectWithStart = requires (T a) {
    [](T a) -> QObject* { return a.parent(); };
    [](T a, QObject* o) { a.setParent(o); };
    [](T a) -> QDateTime { return a.start(); };
};

template <ObjectWithStart T>
class DateSortedList
{
public:
    DateSortedList(QObject* itemsOwner) : m_itemsOwner{itemsOwner} {}
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
            item->setParent(m_itemsOwner);

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
            if (item->parent() == m_itemsOwner)
                delete item;
        }
        m_items.clear();
        setSize(0);
    }

    T* operator[](int i) { return m_items[i]; }
    const T* operator[](int i) const { return m_items[i]; }

    virtual int size() const { return m_size; }
    virtual void setSize(int newSize) { m_size = newSize; }

protected:
    QObject* m_itemsOwner = nullptr;
    int m_size = 0;
    std::vector<T*> m_items;
};

} // tasktrackerlib
