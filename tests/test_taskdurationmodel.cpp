#include <QTest>

#include "tasktrackerlib/taskdurationmodel.h"

using namespace tasktrackerlib;

struct Duration {
    QString dateTimeString;
    int seconds;

    QDateTime dateTime() { return QDateTime::fromString(dateTimeString, Qt::ISODate); }
};

typedef QList<Duration> DurationList;

class TestTaskDurationModel: public QObject
{
    Q_OBJECT

private slots:
    void test_loadFromBinary_data() {
        QTest::addColumn<QString>("data");
        QTest::addColumn<DurationList>("durations");

        QTest::newRow("Empty") << R"(
)" << DurationList();

        QTest::newRow("Empty") << R"(
durations: []
)" << DurationList();

        QTest::newRow("One Value") << R"(
durations:
- dateTime: 2023-01-01T00:01:02Z
  seconds: 20
)" << (DurationList() << Duration {"2023-01-01T00:01:02Z", 20});

        QTest::newRow("Unordered") << R"(
durations:
- dateTime: 2023-01-02T00:01:02Z
  seconds: 20
- dateTime: 2023-01-01T00:01:02Z
  seconds: 10
- dateTime: 2023-01-03T00:01:02Z
  seconds: 30
)" << (DurationList()
        << Duration {"2023-01-01T00:01:02Z", 10}
        << Duration {"2023-01-02T00:01:02Z", 20}
        << Duration {"2023-01-03T00:01:02Z", 30}
        );
    }

    void test_loadFromBinary() {
        QFETCH(QString, data);
        QFETCH(DurationList, durations);

        TaskDurationModel model;
        model.loadFromData(data.toUtf8());
        QCOMPARE(durations.size(), durations.size());
        for(int i = 0; i < durations.size(); ++i) {
            auto duration = model.get(i);
            QCOMPARE(duration->dateTime(), durations[i].dateTime());
            QCOMPARE(duration->seconds(), durations[i].seconds);
        }
    }

};

QTEST_MAIN(TestTaskDurationModel)
#include "test_taskdurationmodel.moc"
