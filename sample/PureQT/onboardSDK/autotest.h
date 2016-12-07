#ifndef AUTOTEST_H
#define AUTOTEST_H

#include <QDebug>
#include <QString>
#include <QStringList>
#include <QWidget>
#include <Qmap>
#include "DJI_API.h"
#include "DJI_Test.h"
#include "cmdline.h"

namespace Ui {
class AutoTest;
}

class CoreTest;

class TestCase {
 public:
  TestCase(CoreTest *T) : test(T) { parser = new cmdline::parser(); }

 public:
  virtual QString init()    = 0;
  virtual QString calback() = 0;

  cmdline::parser *getParser() const;

 protected:
  cmdline::parser *parser;
  CoreTest *test;
};

class CoreTest : public DJI::onboardSDK::Test {
 public:
  CoreTest(DJI::onboardSDK::CoreAPI *API);
  void addTestCase(TestCase *c);
  virtual void enterence(std::string s);

 private:
  QMap<QString, TestCase *> parserMap;
};

class VersionTest : public TestCase {
 public:
  VersionTest(CoreTest *T) : TestCase(T) {}

 public:
  virtual QString init() { return "version"; }
  virtual QString calback() {
    test->getAPI()->getDroneVersion(handler, test);
    return "waiting";
  }

 public:
  static void handler(DJI::onboardSDK::CoreAPI *api,
                      DJI::onboardSDK::Header *protocolHeader,
                      DJI::UserData userData) {
    CoreTest *Test = (CoreTest *)userData;
    DJI::onboardSDK::CoreAPI::getDroneVersionCallback(api, protocolHeader,
                                                      userData);
    Test->injectFeedback(32, api->getVersionData().version_name);
  }
};

class ActivationTest : public TestCase {
 public:
  ActivationTest(CoreTest *T) : TestCase(T) {}

 public:
  virtual QString init();
  virtual QString calback();

  void activateCallback(DJI::onboardSDK::CoreAPI *api,
                        DJI::onboardSDK::Header *protocolHeader,
                        DJI::UserData userData);
};

class AutoTest : public QWidget {
  Q_OBJECT

 public:
  explicit AutoTest(QWidget *parent = 0);
  ~AutoTest();

  void init() {
    if (test) delete test;
    test = new CoreTest(api);
    test->addTestCase(new VersionTest(test));
    test->addTestCase(new ActivationTest(test));
  }

  DJI::onboardSDK::CoreAPI *getAPI() const;
  void setAPI(DJI::onboardSDK::CoreAPI *value);

 private slots:
  void on_btn_send_clicked();

 private:
  Ui::AutoTest *ui;
  DJI::onboardSDK::CoreAPI *api;
  CoreTest *test;
};

#endif  // AUTOTEST_H
