#include <QTest>

#include "tasktrackerlib/taskhistory.h"

using namespace tasktrackerlib;

struct Duration {
    TaskTrack::Mode trackMode;
    QString dateTimeString;
    int seconds;

    QDateTime dateTime() { return QDateTime::fromString(dateTimeString, Qt::ISODate); }
};

typedef QList<Duration> DurationList;

class TestTaskHistory: public QObject
{
    Q_OBJECT

private slots:
    void test_loadFromBinary_data() {
        QTest::addColumn<QString>("data");
        QTest::addColumn<DurationList>("durations");

        QTest::newRow("Empty") << R"(
)" << DurationList();

        QTest::newRow("Empty") << R"(
history: []
)" << DurationList();

        QTest::newRow("One Value") << R"(
history:
- track: Duration
  dateTime: 2023-01-01T00:01:02Z
  seconds: 20
)" << (DurationList() << Duration {TaskTrack::Duration, "2023-01-01T00:01:02Z", 20});

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
)" << (DurationList()
        << Duration {TaskTrack::Duration, "2023-01-01T00:01:02Z", 10}
        << Duration {TaskTrack::Duration, "2023-01-02T00:01:02Z", 20}
        << Duration {TaskTrack::Duration, "2023-01-03T00:01:02Z", 30}
        );
    }

    void test_loadFromBinary() {
        QFETCH(QString, data);
        QFETCH(DurationList, durations);

        TaskHistory history;
        history.loadFromData(data.toUtf8());
        QCOMPARE(history.size(), durations.size());
        for(int i = 0; i < history.size(); ++i) {
            auto duration = history.get(i);
            QCOMPARE(duration->trackMode(), durations[i].trackMode);
            QCOMPARE(duration->dateTime(), durations[i].dateTime());
            QCOMPARE(duration->seconds(), durations[i].seconds);
        }
    }

};

QTEST_MAIN(TestTaskHistory)
#include "test_taskhistory.moc"
