#include <QTest>

#include "tasktrackerlib/taskhistory.h"

using namespace tasktrackerlib;

struct Event {
    TaskTrack::Mode trackMode;
    QString dateTimeString;
    int seconds;

    QDateTime dateTime() { return QDateTime::fromString(dateTimeString, Qt::ISODate); }
};

typedef QList<Event> EventList;

class TestTaskHistory: public QObject
{
    Q_OBJECT

private slots:
    void test_loadFromBinary_data() {
        QTest::addColumn<QString>("data");
        QTest::addColumn<EventList>("events");

        QTest::newRow("Empty") << R"(
)" << EventList();

        QTest::newRow("Empty") << R"(
history: []
)" << EventList();

        QTest::newRow("One Value") << R"(
history:
- track: Duration
  dateTime: 2023-01-01T00:01:02Z
  seconds: 20
)" << (EventList() << Event {TaskTrack::Duration, "2023-01-01T00:01:02Z", 20});

        QTest::newRow("Unordered") << R"(
history:
- track: Duration
  dateTime: 2023-01-02T00:01:02Z
  seconds: 20
- track: Duration
  dateTime: 2023-01-01T00:01:02Z
  seconds: 10
- track: Duration
  dateTime: 2023-01-03T00:01:02Z
  seconds: 30
)" << (EventList()
        << Event {TaskTrack::Duration, "2023-01-01T00:01:02Z", 10}
        << Event {TaskTrack::Duration, "2023-01-02T00:01:02Z", 20}
        << Event {TaskTrack::Duration, "2023-01-03T00:01:02Z", 30}
        );
    }

    void test_loadFromBinary() {
        QFETCH(QString, data);
        QFETCH(EventList, events);

        TaskHistory history;
        history.loadFromData(data.toUtf8());
        QCOMPARE(history.size(), events.size());
        for(int i = 0; i < history.size(); ++i) {
            auto event = history.get(i);
            QCOMPARE(event->trackMode(), events[i].trackMode);
            QCOMPARE(event->dateTime(), events[i].dateTime());
            QCOMPARE(event->seconds(), events[i].seconds);
        }
    }

};

QTEST_MAIN(TestTaskHistory)
#include "test_taskhistory.moc"
