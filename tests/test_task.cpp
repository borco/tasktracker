#include <QTest>

#include "tasktrackerlib/task.h"

using namespace tasktrackerlib;

class TestTask: public QObject
{
    Q_OBJECT

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

    void test_load_schedule_mode_data() {
        QTest::addColumn<QString>("data");
        QTest::addColumn<Task::ScheduleMode>("scheduleMode");

        QTest::newRow("No schedule mode") << R"(
)" << Task::Daily;

        QTest::newRow("Unknown/invalid schedule mode") << R"(
schedule: xxx
)" << Task::Daily;

        QTest::newRow("Daily") << R"(
schedule: Daily
)" << Task::Daily;

        QTest::newRow("Weekly") << R"(
schedule: Weekly
)" << Task::Weekly;
    }

    void test_load_schedule_mode() {
        QFETCH(QString, data);
        QFETCH(Task::ScheduleMode, scheduleMode);

        Task task;
        task.loadFromData(data.toUtf8());
        QCOMPARE(task.scheduleMode(), scheduleMode);
    }


    void test_load_track_mode_data() {
        QTest::addColumn<QString>("data");
        QTest::addColumn<Task::TrackMode>("trackMode");

        QTest::newRow("No track mode") << R"(
)" << Task::NoTracking;

        QTest::newRow("Unknown/invalid track mode") << R"(
track: xxx
)" << Task::NoTracking;

        QTest::newRow("NoTracking") << R"(
track: NoTracking
)" << Task::NoTracking;

        QTest::newRow("MinimumRepeats") << R"(
track: MinimumRepeats
)" << Task::MinimumRepeats;
    }

    void test_load_track_mode() {
        QFETCH(QString, data);
        QFETCH(Task::TrackMode, trackMode);

        Task task;
        task.loadFromData(data.toUtf8());
        QCOMPARE(task.trackMode(), trackMode);
    }
};

QTEST_MAIN(TestTask)
#include "test_task.moc"
