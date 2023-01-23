#include <QTest>

#include "tasktrackerlib/config.h"
#include "tasktrackerlib/task.h"
#include "tasktrackerlib/taskselecteddate.h"

using namespace tasktrackerlib;

class TestTaskSelectedDate: public QObject
{
    Q_OBJECT

private slots:
    void test_seconds_and_aggregate_seconds_data() {
        QTest::addColumn<QString>("data");
        QTest::addColumn<Qt::DayOfWeek>("weekStart");
        QTest::addColumn<TaskAggregate::Mode>("aggregateMode");
        QTest::addColumn<QDate>("selectedDate");
        QTest::addColumn<int>("seconds");
        QTest::addColumn<int>("aggregateSeconds");

        QString duration_tracking_data = R"(
track: Duration
durations:
- dateTime: "2023-01-21T00:00.000Z"
  seconds: 1
- dateTime: "2023-01-22T00:01.000Z"
  seconds: 2
- dateTime: "2023-01-22T00:02.000Z"
  seconds: 4
- dateTime: "2023-01-22T00:03.000Z"
  seconds: 8
- dateTime: "2023-01-23T00:00.000Z"
  seconds: 16
)";

        QString count_tracking_data = R"(
track: Count
counts:
- date: "2023-01-21"
  count: 2
)";

        QTest::newRow("Empty")
                << ""
                << Qt::Sunday
                << TaskAggregate::Daily
                << QDate()
                << 0
                << 0;

        QTest::newRow("Tracking Counts")
                << count_tracking_data
                << Qt::Sunday
                << TaskAggregate::Daily
                << QDate(2023, 1, 21)
                << 0
                << 0;

        QTest::newRow("Daily, 2023/1/21")
                << duration_tracking_data
                << Qt::Sunday
                << TaskAggregate::Daily
                << QDate(2023, 1, 21)
                << 1
                << 1;

        QTest::newRow("Daily, 2023/1/22")
                << duration_tracking_data
                << Qt::Sunday
                << TaskAggregate::Daily
                << QDate(2023, 1, 22)
                << 14
                << 14;
    }

    void test_seconds_and_aggregate_seconds() {
        QFETCH(QString, data);
        QFETCH(Qt::DayOfWeek, weekStart);
        QFETCH(TaskAggregate::Mode, aggregateMode);
        QFETCH(QDate, selectedDate);
        QFETCH(int, seconds);
        QFETCH(int, aggregateSeconds);

        Config::get()->setWeekStart(weekStart);

        Task task;
        task.loadFromData(data.toUtf8());
        task.setAggregateMode(aggregateMode);

        TaskSelectedDate task_selected_date;
        task_selected_date.setTask(&task);
        task_selected_date.setSelectedDate(selectedDate);
        QCOMPARE(task_selected_date.seconds(), seconds);
        QCOMPARE(task_selected_date.aggregateSeconds(), aggregateSeconds);
    }
};

QTEST_MAIN(TestTaskSelectedDate)
#include "test_taskselecteddate.moc"
