#include "tasktrackerlib/taskduration.h"

#include "yaml-cpp/yaml.h" // IWYU pragma: keep

#include <QTest>

using namespace tasktrackerlib;

class TestTaskDuration: public QObject
{
    Q_OBJECT

private slots:
    void test_seconds_data() {
        QTest::addColumn<QDateTime>("start");
        QTest::addColumn<QDateTime>("stop");
        QTest::addColumn<int>("seconds");

        auto date = QDate::currentDate();

        QTest::newRow("Invalid start & stop") << QDateTime() << QDateTime() << 0;
        QTest::newRow("Invalid start") << QDateTime() << QDateTime(date, QTime(1, 2, 3)) << 0;
        QTest::newRow("Invalid stop") << QDateTime(date, QTime(1, 2, 3)) << QDateTime() << 0;
        QTest::newRow("start = stop") << QDateTime(date, QTime(1, 2, 3)) << QDateTime(date, QTime(1, 2, 3)) << 0;
        QTest::newRow("start < stop") << QDateTime(date, QTime(1, 2, 3)) << QDateTime(date, QTime(1, 3, 3)) << 60;
        QTest::newRow("start > stop") << QDateTime(date, QTime(2, 2, 3)) << QDateTime(date, QTime(1, 2, 3)) << -3600;
    }

    void test_seconds() {
        QFETCH(QDateTime, start);
        QFETCH(QDateTime, stop);
        QFETCH(int, seconds);

        TaskDuration td;
        td.setStart(start);
        td.setStop(stop);
        QCOMPARE(td.seconds(), seconds);
    }

    void test_load_from_yaml_data() {
        QTest::addColumn<QString>("data");
        QTest::addColumn<QDateTime>("start");
        QTest::addColumn<QDateTime>("stop");

        QTest::newRow("empty") << "" << QDateTime() << QDateTime();
        QTest::newRow("valid start") << R"(
start: 2021-02-03T01:02:03.010Z
)" << QDateTime(QDate(2021, 2, 3), QTime(1, 2, 3, 10), QTimeZone::UTC) << QDateTime();

        QTest::newRow("valid stop") << R"(
stop: 2024-05-06T04:05:06.020Z
)" << QDateTime() << QDateTime(QDate(2024, 5, 6), QTime(4, 5, 6, 20), QTimeZone::UTC);

        QTest::newRow("valid start & stop") << R"(
start: 2021-02-03T01:02:03.000Z
stop: 2021-02-03T04:05:06.000Z
)" << QDateTime(QDate(2021, 2, 3), QTime(1, 2, 3), QTimeZone::UTC) << QDateTime(QDate(2021, 2, 3), QTime(4, 5, 6), QTimeZone::UTC);
    }

    void test_load_from_yaml() {
        QFETCH(QString, data);
        QFETCH(QDateTime, start);
        QFETCH(QDateTime, stop);

        TaskDuration td;
        td.loadFromData(data.toUtf8());
        QCOMPARE(td.start(), start);
        QCOMPARE(td.stop(), stop);
    }

    void test_save() {
        TaskDuration td;
        td.setStart(QDateTime(QDate(2021, 2, 3), QTime(1, 2, 3), QTimeZone::UTC));
        td.setStop(QDateTime(QDate(2021, 2, 3), QTime(1, 2, 4), QTimeZone::UTC));

        YAML::Emitter out;
        td.saveToYaml(out);
        QCOMPARE(QString(out.c_str()), R"(start: 2021-02-03T01:02:03Z
stop: 2021-02-03T01:02:04Z)");
    }
};

QTEST_MAIN(TestTaskDuration)
#include "test_taskduration.moc"
