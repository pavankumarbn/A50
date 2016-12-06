#include "autotest.h"
#include "ui_autotest.h"

AutoTest::AutoTest(QWidget *parent) : QWidget(parent), ui(new Ui::AutoTest) {
  ui->setupUi(this);
}

AutoTest::~AutoTest() { delete ui; }

DJI::onboardSDK::CoreAPI *AutoTest::getAPI() const { return api; }

void AutoTest::setAPI(DJI::onboardSDK::CoreAPI *value) { api = value; }
