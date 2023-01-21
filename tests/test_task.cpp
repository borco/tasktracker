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
        QTest::addColumn<TaskRepeat::Mode>("repeatMode");

        QTest::newRow("No schedule mode") << R"(
)" << TaskRepeat::Once;

        QTest::newRow("Unknown/invalid schedule mode") << R"(
repeat: xxx
)" << TaskRepeat::Once;

        QTest::newRow("Daily") << R"(
repeat: Daily
)" << TaskRepeat::Daily;

        QTest::newRow("Weekly") << R"(
repeat: Weekly
)" << TaskRepeat::Weekly;
    }

    void test_load_repeat_mode() {
        QFETCH(QString, data);
        QFETCH(TaskRepeat::Mode, repeatMode);

        Task task;
        task.loadFromData(data.toUtf8());
        QCOMPARE(task.repeatMode(), repeatMode);
    }


    void test_load_track_mode_data() {
        QTest::addColumn<QString>("data");
        QTest::addColumn<TaskTrack::Mode>("trackMode");

        QTest::newRow("No track mode") << R"(
)" << TaskTrack::Duration;

        QTest::newRow("Unknown/invalid track mode") << R"(
track: xxx
)" << TaskTrack::Duration;

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
};

QTEST_MAIN(TestTask)
#include "test_task.moc"
