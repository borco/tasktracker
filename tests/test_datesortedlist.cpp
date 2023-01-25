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
    ~Event() {
        qDebug() << "~Event:" << m_start.toString(Qt::ISODate) << m_value;
    }

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

class EventDateSortedList: public QObject, public DateSortedList<Event>
{
public:
    explicit EventDateSortedList() : DateSortedList<Event>(this) {}
    ~EventDateSortedList() { qDebug() << "~EventDateSortedList"; }
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
                << (EventDataList() << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 3), QTimeZone::UTC), 1 })
                << (EventDataList() << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 3), QTimeZone::UTC), 1 })
                   ;

        QTest::newRow("ordered values (same day)")
                << (EventDataList()
                    << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 3), QTimeZone::UTC), 1 }
                    << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 4), QTimeZone::UTC), 2 }
                    )
                << (EventDataList()
                    << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 3), QTimeZone::UTC), 1 }
                    << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 4), QTimeZone::UTC), 2 }
                    )
                   ;

        QTest::newRow("ordered values (different days)")
                << (EventDataList()
                    << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 3), QTimeZone::UTC), 1 }
                    << EventData { QDateTime(QDate(2023, 1, 2), QTime(1, 1, 1), QTimeZone::UTC), 2 }
                    )
                << (EventDataList()
                    << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 3), QTimeZone::UTC), 1 }
                    << EventData { QDateTime(QDate(2023, 1, 2), QTime(1, 1, 1), QTimeZone::UTC), 2 }
                    )
                   ;

        QTest::newRow("unordered values (same day)")
                << (EventDataList()
                    << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 4), QTimeZone::UTC), 2 }
                    << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 3), QTimeZone::UTC), 1 }
                    )
                << (EventDataList()
                    << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 3), QTimeZone::UTC), 1 }
                    << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 4), QTimeZone::UTC), 2 }
                    )
                   ;

        QTest::newRow("unordered values (different days)")
                << (EventDataList()
                    << EventData { QDateTime(QDate(2023, 1, 2), QTime(1, 1, 1), QTimeZone::UTC), 2 }
                    << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 3), QTimeZone::UTC), 1 }
                    )
                << (EventDataList()
                    << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 3), QTimeZone::UTC), 1 }
                    << EventData { QDateTime(QDate(2023, 1, 2), QTime(1, 1, 1), QTimeZone::UTC), 2 }
                    )
                   ;
    }

    void test_insert() {
        QFETCH(EventDataList, inputData);
        QFETCH(EventDataList, sortedData);

        EventDateSortedList sortedEvents;
        for (const auto &data: inputData) {
            auto event = new Event(&sortedEvents);
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

    void test_slice_data() {
        QTest::addColumn<EventDataList>("inputData");
        QTest::addColumn<QDate>("date");
        QTest::addColumn<int>("sliceBeginDistance");
        QTest::addColumn<int>("sliceEndDistance");

        QTest::newRow("1 value")
                << (EventDataList() << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 3), QTimeZone::UTC), 1 })
                << QDate(2023, 1, 1)
                << 0
                << 1
                   ;

        QTest::newRow("one value per day")
                << (EventDataList()
                    << EventData { QDateTime(QDate(2023, 1, 1), QTime(1, 2, 3), QTimeZone::UTC), 1 }
                    << EventData { QDateTime(QDate(2023, 1, 2), QTime(1, 2, 3), QTimeZone::UTC), 2 }
                    << EventData { QDateTime(QDate(2023, 1, 3), QTime(1, 2, 3), QTimeZone::UTC), 3 }
                    )
                << QDate(2023, 1, 2)
                << 1
                << 2
                   ;

        QTest::newRow("multiple values in a day")
                << (EventDataList()
                    << EventData { QDateTime(QDate(2023, 1, 1), QTime(0, 0, 1), QTimeZone::UTC), 1 }
                    << EventData { QDateTime(QDate(2023, 1, 2), QTime(0, 0, 2), QTimeZone::UTC), 2 }
                    << EventData { QDateTime(QDate(2023, 1, 2), QTime(0, 0, 3), QTimeZone::UTC), 3 }
                    << EventData { QDateTime(QDate(2023, 1, 3), QTime(0, 0, 4), QTimeZone::UTC), 4 }
                    )
                << QDate(2023, 1, 2)
                << 1
                << 3
                   ;
    }

    void test_slice() {
        QFETCH(EventDataList, inputData);
        QFETCH(QDate, date);
        QFETCH(int, sliceBeginDistance);
        QFETCH(int, sliceEndDistance);

        EventDateSortedList sortedEvents;
        for (const auto &data: inputData) {
            auto event = new Event(&sortedEvents);
            event->setStart(data.start);
            event->setValue(data.value);
            sortedEvents.insert(event);
        };

        auto slice_begin = sortedEvents.begin(date);
        auto slice_end = sortedEvents.end(date);

        QCOMPARE(sortedEvents.begin(date) - sortedEvents.begin(), sliceBeginDistance);
        QCOMPARE(sortedEvents.end(date) - sortedEvents.begin(), sliceEndDistance);
    }
};

QTEST_MAIN(TestDateSortedList)
#include "test_datesortedlist.moc"
