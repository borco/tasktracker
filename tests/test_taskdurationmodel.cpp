#include "tasktrackerlib/task.h"
#include "tasktrackerlib/taskduration.h"
#include "tasktrackerlib/taskdurationmodel.h"
#include "tasktrackerlib/taskdurationsortedlist.h"

#include <QTest>

using namespace tasktrackerlib;

class TestTaskDurationModel: public QObject
{
    Q_OBJECT

private slots:
    void test_order_updated_when_changing_task_stop() {
        auto data = R"(
track: Duration
durations:
- start: 2023-01-02T12:00:00Z
  stop:  2023-01-02T12:10:00Z
- start: 2023-01-02T13:00:00Z
  stop:  2023-01-02T13:10:00Z
- start: 2023-01-02T14:00:00Z
  stop:  2023-01-02T14:10:00Z
)";
        Task task;
        task.loadFromData(data);

        TaskDurationModel model;
        model.setTask(&task);
        model.setDate(QDate(2023, 1, 2));

        assert(model.size() == 3);

        auto start = QDateTime(QDate(2023, 1, 2), QTime(13, 0, 0), QTimeZone::UTC);
        auto stop = QDateTime(QDate(2023, 1, 2), QTime(13, 20, 0), QTimeZone::UTC);

        TaskDuration new_duration(start, stop);
        model.setDuration(1, &new_duration);

        QCOMPARE(model.duration(1)->start(), start);
        QCOMPARE(model.duration(1)->stop(), stop);
    }

    void test_order_updated_when_changing_task_start() {
        auto data = R"(
track: Duration
durations:
- start: 2023-01-02T12:00:00Z
  stop:  2023-01-02T12:10:00Z
- start: 2023-01-02T13:00:00Z
  stop:  2023-01-02T13:10:00Z
- start: 2023-01-02T14:00:00Z
  stop:  2023-01-02T14:10:00Z
)";
        Task task;
        task.loadFromData(data);

        TaskDurationModel model;
        model.setTask(&task);
        model.setDate(QDate(2023, 1, 2));

        assert(model.size() == 3);

        auto start = QDateTime(QDate(2023, 1, 2), QTime(11, 0, 0), QTimeZone::UTC);
        auto stop = QDateTime(QDate(2023, 1, 2), QTime(11, 10, 0), QTimeZone::UTC);

        TaskDuration new_duration(start, stop);
        model.setDuration(1, &new_duration);

        QCOMPARE(model.duration(0)->start(), start);
        QCOMPARE(model.duration(0)->stop(), stop);
    }

    void test_order_updated_when_changing_task_start_in_other_model() {
        auto data = R"(
track: Duration
durations:
- start: 2023-01-02T12:00:00Z
  stop:  2023-01-02T12:10:00Z
- start: 2023-01-02T13:00:00Z
  stop:  2023-01-02T13:10:00Z
- start: 2023-01-02T14:00:00Z
  stop:  2023-01-02T14:10:00Z
)";
        Task task;
        task.loadFromData(data);

        TaskDurationModel model1;
        model1.setTask(&task);
        model1.setDate(QDate(2023, 1, 2));

        TaskDurationModel model2;
        model2.setTask(&task);
        model2.setDate(QDate(2023, 1, 2));

        assert(model1.size() == 3);
        assert(model2.size() == 3);

        auto start = QDateTime(QDate(2023, 1, 2), QTime(11, 0, 0), QTimeZone::UTC);
        auto stop = QDateTime(QDate(2023, 1, 2), QTime(11, 10, 0), QTimeZone::UTC);

        TaskDuration new_duration(start, stop);
        model1.setDuration(1, &new_duration);

        QCOMPARE(model2.duration(0)->start(), start);
        QCOMPARE(model2.duration(0)->stop(), stop);
    }
};

QTEST_MAIN(TestTaskDurationModel)
#include "test_taskdurationmodel.moc"
