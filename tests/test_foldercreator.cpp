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
        QTest::newRow("CON") << "CON" << false;
        QTest::newRow("AUX") << "AUX" << false;
        QTest::newRow("PRN") << "PRN" << false;
        QTest::newRow("NUL") << "NUL" << false;
        QTest::newRow("COM1") << "COM1" << false;
        QTest::newRow("LPT2") << "LPT2" << false;
        QTest::newRow("CON.abc") << "CON.abc" << false;
        QTest::newRow("xxx xxx") << "xxx xxx" << true;
        QTest::newRow("xxx\txxx") << "xxx\txxx" << false;
        QTest::newRow("xxx\nxxx") << "xxx\nxxx" << false;
        QTest::newRow("xxx!xxx") << "xxx!xxx" << false;
        QTest::newRow("xxx@xxx") << "xxx@xxx" << false;
        QTest::newRow("xxx#xxx") << "xxx#xxx" << false;
        QTest::newRow("xxx%xxx") << "xxx%xxx" << false;
        QTest::newRow("xxx$xxx") << "xxx$xxx" << false;
        QTest::newRow("xxx`xxx") << "xxx`xxx" << false;
        QTest::newRow("xxx\\xxx") << "xxx\\xxx" << false;
        QTest::newRow("xxx/xxx") << "xxx/xxx" << false;
        QTest::newRow("xxx|xxx") << "xxx|xxx" << false;
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
