#include <QTest>

#include "tasktrackerlib/foldercreator.h"

using namespace tasktrackerlib;

class TestFolderCreator: public QObject
{
    Q_OBJECT

private slots:
    void test_isValidDir_data() {
        QTest::addColumn<QString>("path");
        QTest::addColumn<bool>("is_valid");

        QTest::newRow("empty") << "" << false;
        QTest::newRow("max length") << QString("%1").arg("x", 128, QChar('x')) << true;
        QTest::newRow("too long") << QString("%1").arg("x", 129, QChar('x')) << false;
        QTest::newRow("space at start") << "  xxx" << false;
        QTest::newRow("space at end") << "xxx   " << false;
        QTest::newRow("only spaces") << "\n  \t" << false;
        QTest::newRow(".") << "." << false;
        QTest::newRow("..") << "." << false;
        QTest::newRow(".xxx") << ".xxx" << true;
        QTest::newRow("xxx.") << "xxx." << false;
        QTest::newRow("..xxx") << "..xxx" << false;
        QTest::newRow("xxx..") << "xxx.." << false;
        QTest::newRow(",xxx") << ",xxx" << false;
        QTest::newRow("xxx,") << "xxx," << false;
    }

    void test_isValidDir() {
        QFETCH(QString, path);
        QFETCH(bool, is_valid);

        FolderCreator fc;
        qDebug() << "test string:" << path.size() << path;
        QCOMPARE(fc.isValidDir(path), is_valid);
    }
};

QTEST_MAIN(TestFolderCreator)
#include "test_foldercreator.moc"
