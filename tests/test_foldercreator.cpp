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

    void test_existing_dir_is_invalid() {
        FolderCreator fc;
        fc.setPath(TEST_SOURCE_DIR);

        // verify existing path is not valid
        QCOMPARE(fc.isValidDir("data"), false);

        // verify check is done case insensitive
        // (actual path is "${TEST_SOURCE_DIR}/data")
        QCOMPARE(fc.isValidDir("Data"), false);
        QCOMPARE(fc.isValidDir("DATA"), false);
    }
};

QTEST_MAIN(TestFolderCreator)
#include "test_foldercreator.moc"
