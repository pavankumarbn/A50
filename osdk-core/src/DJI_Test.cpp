#include "DJI_Test.h"
#include "DJI_HardDriver.h"

using namespace DJI;
using namespace DJI::onboardSDK;

Test::Test(CoreAPI *API) : api(API) {
  CallBackHandler hdl;
  hdl.callback = testHook;
  hdl.userData = this;
  api->setTestCallback(hdl);
}

void Test::injectFeedback(size8_t size, char *buf) {
  uint8_t buffer[256];
  buffer[0] = size;
  memcpy(&buffer[1], buf, size);
  API_LOG(api->getDriver(), STATUS_LOG, "send test inject data %d %.*s",
          size + 1, size, &buffer[1]);
  api->send(2, 0, SET_ACTIVATION, 0xFD, &buffer, size + 1, 500, 2, 0, 0);
}

void Test::injectFeedback(uint32_t data) {
  injectFeedback(sizeof(data), (char *)&data);
}

void Test::testHook(CoreAPI *api, Header *header, UserData data) {
  Test *This = (Test *)data;

  char *pdata = ((char *)header) + sizeof(Header) + 2;

  std::string s(pdata + 1, (*(uint8_t *)pdata));

  This->enterence(s);
}

void Test::selfTest() {
  injectFeedback(0);
  injectFeedback(11, "Hello world");
}

CoreAPI *Test::getAPI() const { return api; }
