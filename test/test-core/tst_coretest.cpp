#include <QDebug>
#include <QString>
#include <QtTest>

#include "cmdline.h"

#include <QMap>
#include <QString>
class CoreTest : public QObject {
  Q_OBJECT

 public:
  CoreTest();

 private Q_SLOTS:
  void testCase1();

 private:
  QMap<QString, cmdline::parser *> parserMap;
};

CoreTest::CoreTest() {}

void CoreTest::testCase1() {
  qDebug() << "test";
  QVERIFY2(true, "Failure");
}

int main(int argc, char *argv[]) {
  CoreTest tc;
  QTEST_SET_MAIN_SOURCE_PATH
  int ans = QTest::qExec(&tc, argc, argv);
  while (1)
    ;
  return ans;
}

#include "tst_coretest.moc"
