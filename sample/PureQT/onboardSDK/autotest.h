#ifndef AUTOTEST_H
#define AUTOTEST_H

#include <QWidget>
#include "DJI_API.h"
#include "DJI_Test.h"

namespace Ui {
class AutoTest;
}

class AutoTest : public QWidget {
  Q_OBJECT

 public:
  explicit AutoTest(QWidget *parent = 0);
  ~AutoTest();

  DJI::onboardSDK::CoreAPI *getAPI() const;
  void setAPI(DJI::onboardSDK::CoreAPI *value);

 private:
  Ui::AutoTest *ui;
  DJI::onboardSDK::CoreAPI *api;
  DJI::onboardSDK::Test *test;
};

#endif  // AUTOTEST_H
