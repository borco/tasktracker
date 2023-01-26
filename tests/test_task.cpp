#include <QTest>

#include "tasktrackerlib/task.h"

using namespace tasktrackerlib;

class TestTask: public QObject
{
    Q_OBJECT

private:
    struct Count {
        QDate date;
        int count;
    };

    struct Duration {
        QTime time() { return QTime::fromString(timeString, Qt::ISODate); }

        QString timeString;
        int seconds;
    };

    typedef QList<Count> CountList;
    typedef QList<Duration> DurationList;

private slots:
    void test_load_name_data() {
        QTest::addColumn<QString>("data");
        QTest::addColumn<QString>("name");

        QTest::newRow("No name value") << R"(
)" << "";

        QTest::newRow("Foo Bar") << R"(
name: Foo Bar
)" << "Foo Bar";

        QTest::newRow("foo bar") << R"(
name: foo bar
)" << "foo bar";
    }

    void test_load_name() {
        QFETCH(QString, data);
        QFETCH(QString, name);

        Task task;
        task.loadFromData(data.toUtf8());
        QCOMPARE(task.name(), name);
    }

    void test_load_isArchive_data() {
        QTest::addColumn<QString>("data");
        QTest::addColumn<bool>("isArchived");

        QTest::newRow("No archived value") << R"(
)" << false;

        QTest::newRow("false") << R"(
archived: false
)" << false;

        QTest::newRow("true") << R"(
archived: true
)" << true;
    }

    void test_load_isArchive() {
        QFETCH(QString, data);
        QFETCH(bool, isArchived);

        Task task;
        task.loadFromData(data.toUtf8());
        QCOMPARE(task.isArchived(), isArchived);
    }

    void test_load_repeat_mode_data() {
        QTest::addColumn<QString>("data");
        QTest::addColumn<TaskAggregate::Mode>("aggregateMode");

        QTest::newRow("No schedule mode") << R"(
)" << TaskAggregate::Daily;

        QTest::newRow("Unknown/invalid schedule mode") << R"(
aggregate: xxx
)" << TaskAggregate::Daily;

        QTest::newRow("Daily") << R"(
aggregate: Daily
)" << TaskAggregate::Daily;

        QTest::newRow("Weekly") << R"(
aggregate: Weekly
)" << TaskAggregate::Weekly;
    }

    void test_load_repeat_mode() {
        QFETCH(QString, data);
        QFETCH(TaskAggregate::Mode, aggregateMode);

        Task task;
        task.loadFromData(data.toUtf8());
        QCOMPARE(task.aggregateMode(), aggregateMode);
    }

    void test_load_track_mode_data() {
        QTest::addColumn<QString>("data");
        QTest::addColumn<TaskTrack::Mode>("trackMode");

        QTest::newRow("No track mode") << R"(
)" << TaskTrack::Count;

        QTest::newRow("Unknown/invalid track mode") << R"(
track: xxx
)" << TaskTrack::Count;

        QTest::newRow("Duration") << R"(
track: Duration
)" << TaskTrack::Duration;

        QTest::newRow("Count") << R"(
track: Count
)" << TaskTrack::Count;
    }

    void test_load_track_mode() {
        QFETCH(QString, data);
        QFETCH(TaskTrack::Mode, trackMode);

        Task task;
        task.loadFromData(data.toUtf8());
        QCOMPARE(task.trackMode(), trackMode);
    }

    void test_load_counts_data() {
        QTest::addColumn<QString>("data");
        QTest::addColumn<CountList>("counts");

        QTest::newRow("Empty") << R"(
)" << CountList();

        QTest::newRow("Empty") << R"(
counts: []
)" << CountList();

        QTest::newRow("One Value") << R"(
counts:
- date: 2023-01-01T00:01:02Z
  count: 20
)" << (CountList() << Count { QDate(2023, 1, 1), 20 });

        QTest::newRow("Unordered") << R"(
counts:
- date: 2023-01-02
  count: 20
- date: 2023-01-01
  count: 10
- date: 2023-01-03
  count: 30
)" << (CountList()
        << Count { QDate(2023, 1, 1), 10 }
        << Count { QDate(2023, 1, 2), 20 }
        << Count { QDate(2023, 1, 3), 30 }
        );
    }

    void test_load_counts() {
        QFETCH(QString, data);
        QFETCH(CountList, counts);

        Task task;
        task.loadFromData(data.toUtf8());
        for(int i = 0; i < counts.size(); ++i) {
            auto count = counts[i];
            QCOMPARE(task.count(count.date), count.count);
        }
    }
};

QTEST_MAIN(TestTask)
#include "test_task.moc"
