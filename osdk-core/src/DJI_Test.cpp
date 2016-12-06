#include "DJI_Test.h"

using namespace DJI;
using namespace DJI::onboardSDK;

Test::Test(CoreAPI *API) : api(API) {
  CallBackHandler hdl;
  hdl.callback = testHook;
  hdl.userData = this;
  api->setTestCallback(hdl);
}

void Test::injectFeedback(size_t size, char *buf) {}

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
