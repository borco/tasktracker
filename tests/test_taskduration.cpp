#include "tasktrackerlib/taskduration.h"

#include <QTest>

using namespace tasktrackerlib;

class TestTaskDuration: public QObject
{
    Q_OBJECT

private slots:
    void test_seconds_data() {
        QTest::addColumn<QTime>("start");
        QTest::addColumn<QTime>("stop");
        QTest::addColumn<int>("seconds");

        QTest::newRow("Invalid start & stop") << QTime() << QTime() << 0;
        QTest::newRow("Invalid start") << QTime() << QTime(1, 2, 3) << 0;
        QTest::newRow("Invalid stop") << QTime(1, 2, 3) << QTime() << 0;
        QTest::newRow("start = stop") << QTime(1, 2, 3) << QTime(1, 2, 3) << 0;
        QTest::newRow("start < stop") << QTime(1, 2, 3) << QTime(1, 3, 3) << 60;
        QTest::newRow("start > stop") << QTime(2, 2, 3) << QTime(1, 2, 3) << -3600;
    }

    void test_seconds() {
        QFETCH(QTime, start);
        QFETCH(QTime, stop);
        QFETCH(int, seconds);

        TaskDuration td;
        td.setStart(start);
        td.setStop(stop);
        QCOMPARE(td.seconds(), seconds);
    }
};

QTEST_MAIN(TestTaskDuration)
#include "test_taskduration.moc"
