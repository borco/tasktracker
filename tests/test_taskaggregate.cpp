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

    void test_formatted_seconds_data() {
        QTest::addColumn<bool>("extended");
        QTest::addColumn<int>("seconds");
        QTest::addColumn<QString>("formattedSeconds");

        QTest::newRow("0") << false << 0 << "";
        QTest::newRow("0") << true << 0 << "";

        QTest::newRow("10") << false << 10 << "10s";
        QTest::newRow("10") << true << 10 << "10s";

        QTest::newRow("-10") << false << -10 << "-10s";
        QTest::newRow("-10") << true << -10 << "-10s";

        QTest::newRow("60") << false << 60 << "1m";
        QTest::newRow("60") << true << 60 << "1m 0s";

        QTest::newRow("-60") << false << -60 << "-1m";
        QTest::newRow("-60") << true << -60 << "-1m 0s";

        QTest::newRow("61") << false << 61 << "1m 1s";
        QTest::newRow("61") << true << 61 << "1m 1s";

        QTest::newRow("3600") << false << 3600 << "1h";
        QTest::newRow("3600") << true << 3600 << "1h 0m 0s";

        QTest::newRow("3601") << false << 3601 << "1h";
        QTest::newRow("3601") << true << 3601 << "1h 0m 1s";

        QTest::newRow("3661") << false << 3661 << "1h 1m";
        QTest::newRow("3661") << true << 3661 << "1h 1m 1s";

        QTest::newRow("3719") << false << 3719 << "1h 1m";
        QTest::newRow("3719") << true << 3719 << "1h 1m 59s";
    }

    void test_formatted_seconds() {
        QFETCH(bool, extended);
        QFETCH(int, seconds);
        QFETCH(QString, formattedSeconds);

        QCOMPARE(TaskAggregate::formattedSeconds(seconds, extended), formattedSeconds);
    }
};

QTEST_MAIN(TestAggregate)
#include "test_taskaggregate.moc"
