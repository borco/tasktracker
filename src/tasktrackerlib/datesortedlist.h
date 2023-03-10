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
    typedef std::vector<T*> Items;
    typedef typename Items::iterator iterator;

    DateSortedList(QObject* itemsOwner) : m_itemsOwner{itemsOwner} {}
    ~DateSortedList() { clear(); }

    bool empty() const { return m_items.empty(); }

    bool insert(T* item) {
        if (!item->start().isValid()) {
            qCritical() << "Can't store an item with invalid start";
            return false;
        }

        if (std::find(m_items.cbegin(), m_items.cend(), item) != m_items.cend()) {
            qCritical() << "The list already contains" << item;
            return false;
        }

        auto it = std::upper_bound(
                    m_items.begin(),
                    m_items.end(),
                    item->start(),
                    [](const QDateTime& dateTime, const T* item) {
            return dateTime < item->start();
        });
        m_items.insert(it, item);

        setSize(m_items.size());

        return true;
    }

    void clear() {
        if (!m_itemsOwner) {
            for (auto item: m_items) {
                if (item->parent() == m_itemsOwner)
                    delete item;
            }
        }
        m_items.clear();
        setSize(0);
    }

    T* operator[](int i) { return m_items[i]; }
    const T* operator[](int i) const { return m_items[i]; }

    T* last() { return m_items.size() > 0 ? m_items[m_items.size() - 1] : nullptr; }
    const T* last() const { return m_items.size() > 0 ? m_items[m_items.size() - 1] : nullptr; }

    virtual int size() const { return m_size; }
    virtual void setSize(int newSize) { m_size = newSize; }

    iterator begin() { return m_items.begin(); }

    iterator localTimeBegin(const QDate& date) {
        if (date.isValid()) {
            return std::lower_bound(m_items.begin(), m_items.end(), date, [](const T* item, const QDate& date) { return item->start().toLocalTime().date() < date; });
        } else {
            return m_items.begin();
        }
    }

    iterator end() { return m_items.end(); }

    iterator localTimeEnd(const QDate& date) {
        if (date.isValid()) {
            return std::upper_bound(m_items.begin(), m_items.end(), date, [](const QDate& date, const T* item) { return date < item->start().toLocalTime().date(); });
        } else {
            return m_items.end();
        }
    }

    void sort(iterator first, iterator last) {
        std::sort(first, last, [](const T* item1, const T* item2) { return item1->start() < item2->start(); });
    }

protected:
    QObject* m_itemsOwner = nullptr;
    int m_size = 0;
    Items m_items;
};

} // tasktrackerlib
