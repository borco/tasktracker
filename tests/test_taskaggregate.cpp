#include <QTest>

#include "tasktrackerlib/taskaggregate.h"

using namespace tasktrackerlib;

class TestAggregate: public QObject
{
    Q_OBJECT

private slots:
    void test_aggregate_dates_data() {
        QTest::addColumn<Qt::DayOfWeek>("weekStart");
        QTest::addColumn<TaskAggregate::Mode>("aggregateMode");
        QTest::addColumn<QDate>("date");
        QTest::addColumn<QDate>("aggregateBegin");
        QTest::addColumn<QDate>("aggregateEnd");

        QTest::newRow("Invalid Date")
                << Qt::Sunday
                << TaskAggregate::Daily
                << QDate()
                << QDate()
                << QDate();

        QTest::newRow("Daily Aggregate")
                << Qt::Monday
                << TaskAggregate::Daily
                << QDate(2023, 1, 1)
                << QDate(2023, 1, 1)
                << QDate(2023, 1, 1);

        QTest::newRow("Monthly Aggregate, Week Starts Sunday")
                << Qt::Sunday
                << TaskAggregate::Monthly
                << QDate(2023, 1, 22)
                << QDate(2023, 1, 1)
                << QDate(2023, 1, 31);

        QTest::newRow("Monthly Aggregate, Week Starts Monday")
                << Qt::Monday
                << TaskAggregate::Monthly
                << QDate(2023, 1, 22)
                << QDate(2023, 1, 1)
                << QDate(2023, 1, 31);

        QTest::newRow("Weekly Aggregate, Week Starts Sunday")
                << Qt::Sunday
                << TaskAggregate::Weekly
                << QDate(2023, 1, 22) // is a Sunday
                << QDate(2023, 1, 22)
                << QDate(2023, 1, 28);

        QTest::newRow("Weekly Aggregate, Week Starts Monday")
                << Qt::Monday
                << TaskAggregate::Weekly
                << QDate(2023, 1, 22) // is a Sunday
                << QDate(2023, 1, 16)
                << QDate(2023, 1, 22);

        QTest::newRow("Weekly Aggregate, Week Starts Tuesday")
                << Qt::Tuesday
                << TaskAggregate::Weekly
                << QDate(2023, 1, 22) // is a Sunday
                << QDate(2023, 1, 17)
                << QDate(2023, 1, 23);
    }

    void test_aggregate_dates() {
        QFETCH(Qt::DayOfWeek, weekStart);
        QFETCH(TaskAggregate::Mode, aggregateMode);
        QFETCH(QDate, date);
        QFETCH(QDate, aggregateBegin);
        QFETCH(QDate, aggregateEnd);

        QCOMPARE(TaskAggregate::aggregateBegin(weekStart, aggregateMode, date), aggregateBegin);
        QCOMPARE(TaskAggregate::aggregateEnd(weekStart, aggregateMode, date), aggregateEnd);
    }
};

QTEST_MAIN(TestAggregate)
#include "test_taskaggregate.moc"
