#include "tasktrackerlib/task.h"
#include "tasktrackerlib/taskmodel.h"

#include "yaml-cpp/yaml.h" // IWYU pragma: keep

#include <QTest>

using namespace tasktrackerlib;

class TestTaskModel: public QObject
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

        TaskModel model;
        model.loadFromData(data.toUtf8());
        QCOMPARE(model.size(), taskNames.size());
        for(int i = 0; i < model.size(); ++i) {
            QCOMPARE(model.get(i)->name(), taskNames[i]);
        }
    }

    void test_save_to_yaml_no_tasks() {
        TaskModel model;
        YAML::Emitter out;
        model.saveToYaml(out);
        QCOMPARE(QString(out.c_str()), R"(tasks:
  [])");
    }

    void test_save_to_yaml_some_task() {
        QString data = R"(tasks:
  - name: Foo Bar
    durations:
      - start: 2021-02-03T01:02:03Z
        stop: 2021-02-03T01:02:04Z
  - name: foo bar
    counts:
      - date: 2023-01-01
        count: 10
      - date: 2023-01-02
        count: 1
  - name: Foo bar
  - name: foo Bar)";

        TaskModel model;
        model.loadFromData(data.toUtf8());
        YAML::Emitter out;
        model.saveToYaml(out);
        QCOMPARE(QString(out.c_str()), data);
    }
};

QTEST_MAIN(TestTaskModel)
#include "test_taskmodel.moc"
