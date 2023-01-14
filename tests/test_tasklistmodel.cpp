#include <QTest>

#include "tasktrackerlib/task.h"
#include "tasktrackerlib/tasklistmodel.h"

using namespace tasktrackerlib;

class TestTaskListModel: public QObject
{
    Q_OBJECT

private slots:
    void test_load_tasks_data() {
        QTest::addColumn<QString>("data");
        QTest::addColumn<QStringList>("taskNames");

        QTest::newRow("No tasks field") << R"(
)" << QStringList();

        QTest::newRow("Empty tasks list") << R"(
tasks: []
)" << QStringList();
    }

    void test_load_tasks() {
        QFETCH(QString, data);
        QFETCH(QStringList, taskNames);

        TaskListModel model;
        model.loadFromData(data.toUtf8());
        QCOMPARE(model.size(), taskNames.size());
        for(int i = 0; i < model.size(); ++i) {
            QCOMPARE(model.get(i)->name(), taskNames[i]);
        }
    }

};

QTEST_MAIN(TestTaskListModel)
#include "test_tasklistmodel.moc"
