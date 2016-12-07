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

void activateCallback(DJI::onboardSDK::CoreAPI *api,
                      DJI::onboardSDK::Header *protocolHeader,
                      DJI::UserData userData) {
  unsigned short ack_data;
  if (protocolHeader->length - EXC_DATA_SIZE <= 2) {
    memcpy((unsigned char *)&ack_data,
           ((unsigned char *)protocolHeader) + sizeof(Header),
           (protocolHeader->length - EXC_DATA_SIZE));
    switch (ack_data) {
      case ACK_ACTIVE_SUCCESS:
        API_LOG(api->serialDevice, STATUS_LOG, "Activated successfully\n");

        //        if (api->accountData.encKey)
        //        api->setKey(api->accountData.encKey);

        return;
      case ACK_ACTIVE_NEW_DEVICE:
        API_LOG(api->serialDevice, STATUS_LOG,
                "New device, please link DJIGO to your "
                "remote controller and try again\n");
        break;
      case ACK_ACTIVE_PARAMETER_ERROR:
        API_LOG(api->serialDevice, ERROR_LOG, "Wrong parameter\n");
        break;
      case ACK_ACTIVE_ENCODE_ERROR:
        API_LOG(api->serialDevice, ERROR_LOG, "Encode error\n");
        break;
      case ACK_ACTIVE_APP_NOT_CONNECTED:
        API_LOG(api->serialDevice, ERROR_LOG, "DJIGO not connected\n");
        break;
      case ACK_ACTIVE_NO_INTERNET:
        API_LOG(api->serialDevice, ERROR_LOG,
                "DJIGO not "
                "connected to the internet\n");
        break;
      case ACK_ACTIVE_SERVER_REFUSED:
        API_LOG(api->serialDevice, ERROR_LOG,
                "DJI server rejected "
                "your request, please use your SDK ID\n");
        break;
      case ACK_ACTIVE_ACCESS_LEVEL_ERROR:
        API_LOG(api->serialDevice, ERROR_LOG, "Wrong SDK permission\n");
        break;
      case ACK_ACTIVE_VERSION_ERROR:
        API_LOG(api->serialDevice, ERROR_LOG, "SDK version did not match\n");
        api->getDroneVersion();
        break;
      default:
        if (!api->decodeACKStatus(ack_data)) {
          API_LOG(api->serialDevice, ERROR_LOG, "While calling this function");
        }
        break;
    }
  } else {
    API_LOG(api->serialDevice, ERROR_LOG,
            "ACK is exception, session id %d,sequence %d\n",
            protocolHeader->sessionID, protocolHeader->sequenceNumber);
  }
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
  return "waiting";
}
