#include "DJI_Data.h"

using namespace DJI;
using namespace DJI::onboardSDK;

// void *DataSubscribe::DataClause::getPtr() const { return ptr; }

// void DataSubscribe::DataClause::setPtr(void *value) { ptr = value; }

void DataSubscribe::verify(CallBack callback, UserData userData) {
  VersionData data = Data::DBVersion;
  api->send(2, DJI::onboardSDK::encrypt, SET_SUBSCRIBE,
            CODE_SUBSCRIBE_VERSION_MATCH, &data, sizeof(data), 500, 2,
            callback ? callback : verifyCallback, userData ? userData : this);
}

void DataSubscribe::subscribe(uint8_t id, uint16_t freq, uint8_t flag,
                              uint8_t clauseNumber, uint32_t *uid) {
  SubscribeData data;
  data.packageID    = id;
  data.ferq         = freq;
  data.config       = flag;
  data.clauseNumber = clauseNumber;
  //    data.uidList                  = uid;
  static const size_t bufferLen = 200;
  uint8_t buffer[bufferLen];
  size_t size = sizeof(SubscribeData) + sizeof(uint32_t) * clauseNumber;
  if (size > bufferLen) {
    API_LOG(api->getDriver(), ERROR_LOG,
            "subscribe segementation overflow size %d , max %d", size,
            bufferLen);
  } else {
    memcpy(buffer, (uint8_t *)&data, sizeof(data));
    memcpy(buffer + sizeof(SubscribeData), (uint8_t *)uid,
           sizeof(uint32_t) * clauseNumber);
    API_LOG(api->getDriver(), STATUS_LOG, "0x%x",
            (uint32_t)(buffer + sizeof(SubscribeData)));
    api->send(2, DJI::onboardSDK::encrypt, SET_SUBSCRIBE,
              CODE_SUBSCRIBE_ADD_PACKAGE, buffer, size, 500, 1,
              addPackageCallback, this);
  }
}

void DataSubscribe::reset(CallBack callback, UserData userData) {
  uint8_t data = 0;
  api->send(2, DJI::onboardSDK::encrypt, SET_SUBSCRIBE, CODE_SUBSCRIBE_RESET,
            &data, 0, 500, 1, callback ? callback : resetCallback,
            userData ? userData : this);
}

void DataSubscribe::remove(uint8_t packageID) {
  uint8_t data = packageID;
  api->send(2, DJI::onboardSDK::encrypt, SET_SUBSCRIBE,
            CODE_SUBSCRIBE_REMOVE_PACKAGE, &data, sizeof(data), 500, 1,
            removeCallback, this);
}

void DataSubscribe::verifyCallback(CoreAPI *API, Header *header,
                                   UserData THIS) {
  API_LOG(API->getDriver(), STATUS_LOG, "entered");
}

void DataSubscribe::addPackageCallback(CoreAPI *API, Header *header,
                                       UserData THIS) {
  API_LOG(API->getDriver(), STATUS_LOG, "entered");
}

void DataSubscribe::resetCallback(CoreAPI *API, Header *header, UserData THIS) {
  API_LOG(API->getDriver(), STATUS_LOG, "entered");
}

void DataSubscribe::removeCallback(CoreAPI *API, Header *header,
                                   UserData THIS) {
  API_LOG(API->getDriver(), STATUS_LOG, "entered");
}

void DataSubscribe::setAPI(CoreAPI *value) {
  api = value;
  //! @todo regist Callback
}
