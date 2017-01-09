#include "DJI_MOC.h"

#include <string.h>

#include "DJI_HardDriver.h"

using namespace DJI;
using namespace DJI::onboardSDK;

MOC::MOC(CoreAPI *API) : api(API) {}

CoreAPI *MOC::getAPI() const { return api; }

void MOC::setAPI(CoreAPI *value) { api = value; }

void MOC::sendToMobile(uint8_t *data, uint8_t len, CallBack callback,
                       UserData userData) {
  if (len > 100) {
    API_LOG(api->getDriver(), ERROR_LOG, "Too much data to send");
    return;
  }
  api->send(0, 0, SET_ACTIVATION, CODE_TOMOBILE, data, len, 500, 1,
            callback ? callback : MOC::sendToMobileCallback, userData);
}

void MOC::sendToMobileCallback(CoreAPI *api, Header *protocolHeader,
                               UserData userData) {
  unsigned short ack_data = ACK_COMMON_NO_RESPONSE;
  if (protocolHeader->length - CoreAPI::PackageMin <= 2) {
    memcpy((unsigned char *)&ack_data,
           ((unsigned char *)protocolHeader) + sizeof(Header),
           (protocolHeader->length - CoreAPI::PackageMin));
    if (!api->decodeACKStatus(ack_data)) {
      API_LOG(api->getDriver(), ERROR_LOG, "While calling this function");
    }
  } else {
    API_LOG(api->getDriver(), ERROR_LOG,
            "ACK is exception, session id %d,sequence %d\n",
            protocolHeader->sessionID, protocolHeader->sequenceNumber);
  }
}
