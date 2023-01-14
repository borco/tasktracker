#include <QTest>

#include "tasktrackerlib/task.h"
#include "tasktrackerlib/tasklistmodel.h"

using namespace tasktrackerlib;

class TestTaskListModel: public QObject
{
    Q_OBJECT

private slots:
};

QTEST_MAIN(TestTaskListModel)
#include "test_tasklistmodel.moc"
