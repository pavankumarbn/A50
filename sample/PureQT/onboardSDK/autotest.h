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

class CoreTest : public DJI::onboardSDK::Test {
 public:
  CoreTest(DJI::onboardSDK::CoreAPI *API);
  virtual void enterence(std::string s);

 public:
  typedef QString ParserCallback(cmdline::parser *);
  typedef struct ParserHandler {
    ParserCallback init;
    ParserCallback callback;
    cmdline::parser *parser;
  } ParserHandler;

 private:
  QMap<QString, cmdline::parser *> parserMap;
};

class AutoTest : public QWidget {
  Q_OBJECT

 public:
  explicit AutoTest(QWidget *parent = 0);
  ~AutoTest();

  void init() {
    if (test) delete test;
    test = new CoreTest(api);
  }

  DJI::onboardSDK::CoreAPI *getAPI() const;
  void setAPI(DJI::onboardSDK::CoreAPI *value);

 private slots:
  void on_btn_send_clicked();

 private:
  Ui::AutoTest *ui;
  DJI::onboardSDK::CoreAPI *api;
  DJI::onboardSDK::Test *test;
};

#endif  // AUTOTEST_H
