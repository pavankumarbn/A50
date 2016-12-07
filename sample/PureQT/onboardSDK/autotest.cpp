#include "autotest.h"
#include "DJI_HardDriver.h"
#include "ui_autotest.h"

using namespace DJI;
using namespace DJI::onboardSDK;

AutoTest::AutoTest(QWidget *parent)
    : QWidget(parent), ui(new Ui::AutoTest), test(0) {
  ui->setupUi(this);
}

AutoTest::~AutoTest() { delete ui; }

DJI::onboardSDK::CoreAPI *AutoTest::getAPI() const { return api; }

void AutoTest::setAPI(DJI::onboardSDK::CoreAPI *value) { api = value; }

CoreTest::CoreTest(DJI::onboardSDK::CoreAPI *API) : Test(API) {}

void CoreTest::addTestCase(TestCase *c) { parserMap.insert(c->init(), c); }

void CoreTest::enterence(std::string s) {
  QString str     = QString::fromStdString(s);
  QStringList lst = str.split(" ");
  qDebug() << lst;
  QMap<QString, TestCase *>::const_iterator i = parserMap.find(lst[0]);

  while (i != parserMap.end() && i.key() == lst[0]) {
    qDebug() << i.value() << "Parse" << str << endl;
    if (str.isEmpty() || (*i)->getParser()->parse(str.toStdString())) {
      QString fb = (*i)->calback();
      injectFeedback(fb.length(), fb.toLatin1().data());
    } else {
      injectFeedback(13, "fail to parse");
      qDebug() << (*i)->getParser()->usage().c_str();
    }
    ++i;
  }
}

void AutoTest::on_btn_send_clicked() {
  QString str = ui->le_inject->text();
  test->injectFeedback(str.length(), str.toLocal8Bit().data());
}

cmdline::parser *TestCase::getParser() const { return parser; }

QString ActivationTest::init() {
  parser->add<uint32_t>("id", 'i', "active ID for activation", true, 10086);
  parser->add<std::string>("key", 'k', "Encripy key", true,
                           "DJI-demo aes256 lalahaha-ma");
  parser->add("help", 0, "Help message");
  parser->set_program_name("activation");
  return "activation";
}

QString ActivationTest::calback() {
  DJI::onboardSDK::ActivateData data;
  data.ID     = parser->get<uint32_t>("id");
  data.encKey = const_cast<char *>(parser->get<std::string>("key").c_str());
  test->getAPI()->activate(&data, 0, test);
  return "waiting activation";
}

QString VersionTest::calback() {
  test->getAPI()->getDroneVersion(handler, test);
  return "waiting version";
}

void VersionTest::handler(CoreAPI *api, Header *protocolHeader,
                          UserData userData) {
  CoreTest *Test = (CoreTest *)userData;
  DJI::onboardSDK::CoreAPI::getDroneVersionCallback(api, protocolHeader,
                                                    userData);
  Test->injectFeedback(32, api->getVersionData().version_name);
}
