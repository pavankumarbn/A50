#include <QDebug>
#include <QString>
#include <QTimer>
#include <QtTest>

#include "DJI_HardDriver_Qt.h"
#include "DJI_Test.h"

#include "cmdline.h"

#include <QMap>
#include <QSerialPort>
#include <QString>
#include <QThread>

namespace DJI {
namespace onboardSDK {

class TestCore : public Test, public QThread {
 public:
  TestCore(CoreAPI* API = 0) : Test(API) {}

  virtual void enterence(std::string s) {}

 protected:
  virtual void run() {
    while (1) {
      Test::getAPI()->sendPoll();
      Test::getAPI()->readPoll();
    }
  }

 private:
  QMap<QString, cmdline::parser*> parserMap;
};

}  // onboardSDK
}  // DJI

class CoreTest : public QObject {
  Q_OBJECT

 public:
  CoreTest() {
    port   = new QSerialPort(this);
    driver = new QHardDriver(port);
    api    = new CoreAPI(driver);
    test   = new TestCore(api);

    QList<QSerialPortInfo> info = QSerialPortInfo::availablePorts();
    for (int i = 0; i < info.length(); ++i) qDebug() << info[i].portName();
    port->setPortName("COM3");
    driver->setBaudrate(921600);
    driver->init();

    test->start();
  }

 private Q_SLOTS:
  void testDriver();
  void testVersion();
  void testCase1();
  void testAll();

 private:
  QSerialPort* port;
  QHardDriver* driver;
  CoreAPI* api;
  TestCore* test;
};

void CoreTest::testDriver() {
  QVERIFY2(port->isOpen(),
           port->portName().append(" not exit").toStdString().c_str());
  API_LOG(api->getDriver(), STATUS_LOG, "Testing");
}

void CoreTest::testVersion() { api->getDroneVersion(); }

void CoreTest::testCase1() {
  qDebug() << "test";
  QVERIFY2(true, "Failure");
}

void CoreTest::testAll() {
  while (1) {
    QTest::qSleep(1);
  }
}

int main(int argc, char* argv[]) {
  CoreTest tc;
  QTEST_SET_MAIN_SOURCE_PATH
  int ans = QTest::qExec(&tc, argc, argv);
  return ans;
}

#include "tst_coretest.moc"
