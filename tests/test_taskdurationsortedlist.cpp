#include "tasktrackerlib/taskduration.h"
#include "tasktrackerlib/taskdurationsortedlist.h"

#include <QTest>

using namespace tasktrackerlib;

class TestTaskDurationSortedList: public QObject
{
    Q_OBJECT

    struct StartStop {
        QDateTime start;
        QDateTime stop;
    };

    typedef QList<StartStop> StartStopList;

private slots:
    void test_load_from_yaml_data() {
        QTest::addColumn<QString>("data");
        QTest::addColumn<StartStopList>("startStopList");

        QTest::newRow("empty") << "" << StartStopList();

        QTest::newRow("start == stop") << R"(
durations:
- start: 2023-01-02T01:10:01Z
  stop:  2023-01-02T01:10:01Z
)" << (StartStopList()
        << StartStop { QDateTime(QDate(2023, 1, 2), QTime(1, 10, 1), QTimeZone::UTC),
                       QDateTime(QDate(2023, 1, 2), QTime(1, 10, 1), QTimeZone::UTC) }
        );

        QTest::newRow("unordered") << R"(
durations:
- start: 2023-01-02T02:20:02Z
  stop:  2023-01-02T02:20:03Z
- start: 2023-01-02T01:10:01Z
  stop:  2023-01-02T01:10:02Z
- start: 2023-01-02T03:30:03Z
  stop:  2023-01-02T03:30:04Z
)" << (StartStopList()
        << StartStop { QDateTime(QDate(2023, 1, 2), QTime(1, 10, 1), QTimeZone::UTC),
                       QDateTime(QDate(2023, 1, 2), QTime(1, 10, 2), QTimeZone::UTC) }
        << StartStop { QDateTime(QDate(2023, 1, 2), QTime(2, 20, 2), QTimeZone::UTC),
                       QDateTime(QDate(2023, 1, 2), QTime(2, 20, 3), QTimeZone::UTC) }
        << StartStop { QDateTime(QDate(2023, 1, 2), QTime(3, 30, 3), QTimeZone::UTC),
                       QDateTime(QDate(2023, 1, 2), QTime(3, 30, 4), QTimeZone::UTC) }
        );
    }

    void test_load_from_yaml() {
        QFETCH(QString, data);
        QFETCH(StartStopList, startStopList);

        TaskDurationSortedList list;
        list.loadFromData(data.toUtf8());

        QCOMPARE(list.size(), startStopList.size());

        for (int i = 0; i < startStopList.size(); ++i) {
            const auto duration = list[i];
            QCOMPARE(duration->start(), startStopList[i].start);
            QCOMPARE(duration->stop(), startStopList[i].stop);
        }
    }
};

QTEST_MAIN(TestTaskDurationSortedList)
#include "test_taskdurationsortedlist.moc"
