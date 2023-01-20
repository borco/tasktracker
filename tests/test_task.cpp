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

    void test_load_repeat_mode_data() {
        QTest::addColumn<QString>("data");
        QTest::addColumn<TaskRepeatMode::Mode>("repeatMode");

        QTest::newRow("No schedule mode") << R"(
)" << TaskRepeatMode::Daily;

        QTest::newRow("Unknown/invalid schedule mode") << R"(
repeat: xxx
)" << TaskRepeatMode::Daily;

        QTest::newRow("Daily") << R"(
repeat: Daily
)" << TaskRepeatMode::Daily;

        QTest::newRow("Weekly") << R"(
repeat: Weekly
)" << TaskRepeatMode::Weekly;
    }

    void test_load_repeat_mode() {
        QFETCH(QString, data);
        QFETCH(TaskRepeatMode::Mode, repeatMode);

        Task task;
        task.loadFromData(data.toUtf8());
        QCOMPARE(task.repeatMode(), repeatMode);
    }


    void test_load_track_mode_data() {
        QTest::addColumn<QString>("data");
        QTest::addColumn<TaskTrackMode::Mode>("trackMode");

        QTest::newRow("No track mode") << R"(
)" << TaskTrackMode::DefaultMode;

        QTest::newRow("Unknown/invalid track mode") << R"(
track: xxx
)" << TaskTrackMode::DefaultMode;

        QTest::newRow("Duration") << R"(
track: Duration
)" << TaskTrackMode::Duration;

        QTest::newRow("Count") << R"(
track: Count
)" << TaskTrackMode::Count;
    }

    void test_load_track_mode() {
        QFETCH(QString, data);
        QFETCH(TaskTrackMode::Mode, trackMode);

        Task task;
        task.loadFromData(data.toUtf8());
        QCOMPARE(task.trackMode(), trackMode);
    }
};

QTEST_MAIN(TestTask)
#include "test_task.moc"
