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
        TaskModel model;
        model.loadFromData(R"(tasks:
- name: Foo Bar
- name: foo bar
- name: Foo bar
- name: foo Bar
)");
        YAML::Emitter out;
        model.saveToYaml(out);
        QCOMPARE(QString(out.c_str()), R"(tasks:
  - name: Foo Bar
  - name: foo bar
  - name: Foo bar
  - name: foo Bar)");
    }
};

QTEST_MAIN(TestTaskModel)
#include "test_taskmodel.moc"
