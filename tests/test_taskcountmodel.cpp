#include <QTest>

#include "tasktrackerlib/taskcount.h"
#include "tasktrackerlib/taskcountmodel.h"

using namespace tasktrackerlib;

struct Count {
    QDate date;
    int count;
};

typedef QList<Count> CountList;

class TestTaskCountModel: public QObject
{
    Q_OBJECT

private slots:
    void test_loadFromBinary_data() {
        QTest::addColumn<QString>("data");
        QTest::addColumn<CountList>("counts");

        QTest::newRow("Empty") << R"(
)" << CountList();

        QTest::newRow("Empty") << R"(
counts: []
)" << CountList();

        QTest::newRow("One Value") << R"(
counts:
- date: 2023-01-01T00:01:02Z
  count: 20
)" << (CountList() << Count { QDate(2023, 1, 1), 20 });

        QTest::newRow("Unordered") << R"(
counts:
- date: 2023-01-02
  count: 20
- date: 2023-01-01
  count: 10
- date: 2023-01-03
  count: 30
)" << (CountList()
        << Count { QDate(2023, 1, 1), 10 }
        << Count { QDate(2023, 1, 2), 20 }
        << Count { QDate(2023, 1, 3), 30 }
        );
    }

    void test_loadFromBinary() {
        QFETCH(QString, data);
        QFETCH(CountList, counts);

        TaskCountModel model;
        model.loadFromData(data.toUtf8());
        QCOMPARE(counts.size(), counts.size());
        for(int i = 0; i < counts.size(); ++i) {
            auto item = model.get(i);
            QCOMPARE(item->date(), counts[i].date);
            QCOMPARE(item->count(), counts[i].count);
        }
    }

};

QTEST_MAIN(TestTaskCountModel)
#include "test_taskcountmodel.moc"
