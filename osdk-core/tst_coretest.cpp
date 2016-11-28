#include <QString>
#include <QtTest>

class CoreTest : public QObject
{
    Q_OBJECT

public:
    CoreTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void osdk_core_test_data();
    void osdk_core_test();
};

CoreTest::CoreTest()
{
}

void CoreTest::initTestCase()
{
}

void CoreTest::cleanupTestCase()
{
}

void CoreTest::osdk_core_test_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

void CoreTest::osdk_core_test()
{
    QFETCH(QString, data);
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(CoreTest)

#include "tst_coretest.moc"
