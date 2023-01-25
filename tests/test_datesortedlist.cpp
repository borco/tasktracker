#include "tasktrackerlib/datesortedlist.h"

#include <QTest>

using namespace tasktrackerlib;

class Event : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QDateTime start READ start WRITE setStart NOTIFY startChanged)
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)

public:
    explicit Event(QObject* parent = nullptr): QObject(parent) {}

    QDateTime start() const { return m_start; }

    void setStart(const QDateTime &newStart) {
        if (m_start == newStart)
            return;
        m_start = newStart;
        emit startChanged();
    }

    int value() const { return m_value; }

    void setValue(int newValue) {
        if (m_value == newValue)
            return;
        m_value = newValue;
        emit valueChanged();
    }

signals:
    void startChanged();
    void valueChanged();

private:
    QDateTime m_start;
    int m_value = 0;
};

struct EventData {
    QDateTime start;
    int value;
};

typedef QList<EventData> EventDataList;

class TestDateSortedList: public QObject
{
    Q_OBJECT

private slots:
    void test_insert_data() {
        QTest::addColumn<EventDataList>("inputData");
        QTest::addColumn<EventDataList>("sortedData");

        QTest::newRow("1 value")
                << (EventDataList() << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 3), QTimeZone::UTC), 100 })
                << (EventDataList() << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 3), QTimeZone::UTC), 100 })
                   ;

        QTest::newRow("ordered values (same day)")
                << (EventDataList()
                    << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 3), QTimeZone::UTC), 100 }
                    << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 4), QTimeZone::UTC), 200 }
                    )
                << (EventDataList()
                    << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 3), QTimeZone::UTC), 100 }
                    << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 4), QTimeZone::UTC), 200 }
                    )
                   ;

        QTest::newRow("ordered values (different days)")
                << (EventDataList()
                    << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 3), QTimeZone::UTC), 100 }
                    << EventData { QDateTime(QDate(2023, 1, 2), QTime(1, 1, 1), QTimeZone::UTC), 200 }
                    )
                << (EventDataList()
                    << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 3), QTimeZone::UTC), 100 }
                    << EventData { QDateTime(QDate(2023, 1, 2), QTime(1, 1, 1), QTimeZone::UTC), 200 }
                    )
                   ;

        QTest::newRow("unordered values (same day)")
                << (EventDataList()
                    << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 4), QTimeZone::UTC), 200 }
                    << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 3), QTimeZone::UTC), 100 }
                    )
                << (EventDataList()
                    << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 3), QTimeZone::UTC), 100 }
                    << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 4), QTimeZone::UTC), 200 }
                    )
                   ;

        QTest::newRow("unordered values (different days)")
                << (EventDataList()
                    << EventData { QDateTime(QDate(2023, 1, 2), QTime(1, 1, 1), QTimeZone::UTC), 200 }
                    << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 3), QTimeZone::UTC), 100 }
                    )
                << (EventDataList()
                    << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 3), QTimeZone::UTC), 100 }
                    << EventData { QDateTime(QDate(2023, 1, 2), QTime(1, 1, 1), QTimeZone::UTC), 200 }
                    )
                   ;
    }

    void test_insert() {
        QFETCH(EventDataList, inputData);
        QFETCH(EventDataList, sortedData);

        DateSortedList<Event> sortedEvents;
        for (const auto &data: inputData) {
            auto event = new Event();
            event->setStart(data.start);
            event->setValue(data.value);
            sortedEvents.insert(event);
        };

        QCOMPARE(sortedEvents.size(), sortedData.size());

        for (int i = 0; i < sortedEvents.size(); ++i) {
            auto event = sortedEvents[i];
            auto data = sortedData[i];
            QCOMPARE(event->start(), data.start);
            QCOMPARE(event->value(), data.value);
        }
    }
};

QTEST_MAIN(TestDateSortedList)
#include "test_datesortedlist.moc"
