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
            *(uint32_t *)(buffer + sizeof(SubscribeData)));
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
  DataSubscribe *This = (DataSubscribe *)THIS;
  This->decodeAck(header);
  //  API->decodeAckDetails(pdata);
}

void DataSubscribe::addPackageCallback(CoreAPI *API, Header *header,
                                       UserData THIS) {
  DataSubscribe *This = (DataSubscribe *)THIS;
  This->decodeAck(header);
  //  API->decodeAckDetails(pdata);
}

void DataSubscribe::resetCallback(CoreAPI *API, Header *header, UserData THIS) {
  DataSubscribe *This = (DataSubscribe *)THIS;
  This->decodeAck(header);
  //  API->decodeAckDetails(pdata);
}

void DataSubscribe::removeCallback(CoreAPI *API, Header *header,
                                   UserData THIS) {
  DataSubscribe *This = (DataSubscribe *)THIS;
  This->decodeAck(header);
  //  API->decodeAckDetails(pdata);
}

void DataSubscribe::decodeCallback(CoreAPI *API, Header *header,
                                   UserData THIS) {
  //! @todo implement
  DataSubscribe *This = (DataSubscribe *)THIS;
  uint8_t pkg         = This->getPackageNumber(header);
  if (pkg < maxPakcageNumber) {
    API_LOG(API->getDriver(), STATUS_LOG, "Length %d %d %d", header->length,
            sizeof(Header), pkg);
    Package *p = This->package[pkg];
    if (p) p->unpack(header);
  } else {
    API_LOG(API->getDriver(), ERROR_LOG,
            "Segmentation fault, unexcepted package value %d", pkg);
  }
}

uint8_t DataSubscribe::decodeAck(Header *protocolHeader) {
  uint8_t *pdata = ((uint8_t *)protocolHeader) + sizeof(Header);
  API_LOG(api->getDriver(), STATUS_LOG, "entered %x %d", *pdata,
          protocolHeader->length - sizeof(Header));
  return *pdata;
}

uint8_t *DataSubscribe::decodeAckDetails(Header *protocolHeader) {
  uint8_t *pdata = ((uint8_t *)protocolHeader) + sizeof(Header);
  return pdata;
}

uint8_t DataSubscribe::getPackageNumber(Header *header) {
  uint8_t *pdata = ((uint8_t *)header) + sizeof(Header);
  return *(pdata + 2);
}

DataSubscribe::DataSubscribe(CoreAPI *API) {
  for (int i = 0; i < maxPakcageNumber; ++i) package[i] = 0;
  if (API) setAPI(API);
}

CoreAPI *DataSubscribe::getAPI() const { return api; }

void DataSubscribe::setAPI(CoreAPI *value) {
  api = value;
  api->setSubscribeCallback(decodeCallback, this);
}

bool DataSubscribe::setPackage(DataSubscribe::Package *pkg) {
  if (pkg->getPackageID() < maxPakcageNumber) {
    if (package[pkg->getPackageID()] != 0) {
      API_LOG(api->getDriver(), STATUS_LOG,
              "package already exist, remove the old one.")
      remove(pkg->getPackageID());
    }
    package[pkg->getPackageID()] = pkg;
    return true;
  } else {
    API_LOG(api->getDriver(), ERROR_LOG, "package out of range");
    return false;
  }
}

DataSubscribe::Package *DataSubscribe::getPackage(size_t id) {
  if (id < maxPakcageNumber)
    return package[id];
  else
    return 0;
}

DataSubscribe::Package::Package(DataSubscribe *API)
    : subscribe(API),
      freq(0),
      sendStamp(false),
      memoryPoll(0),
      size(0),
      packageID(0),
      clauseInited(0),
      clauseNumber(0),
      clauseOffset(0) {
  unpackHandler.callback = 0;
  unpackHandler.data     = 0;
}

bool DataSubscribe::Package::add(uint16_t offset) {
  if (offset < Data::toaltalClauseNumber) {
    if (clauseInited < clauseNumber) {
      size += Data::DataBase[offset].size;
      clauseOffset[clauseInited++] = offset;
      return true;
    }
    API_LOG(subscribe->getAPI()->getDriver(), ERROR_LOG,
            "too much data to subscribe.");
    return false;
  }
  API_LOG(subscribe->getAPI()->getDriver(), ERROR_LOG,
          "database offset overflow.");
  return false;
}

bool DataSubscribe::Package::add(Data::UID uid) {
  for (int i = 0; i < Data::toaltalClauseNumber; ++i)
    if (Data::DataBase[i].uid == uid) {
      return add(i);
    }
  API_LOG(subscribe->getAPI()->getDriver(), ERROR_LOG, "UID not found");
  return false;
}

bool DataSubscribe::Package::start() {
  if (clauseInited != clauseNumber) return false;
  uint32_t lst[40];
  for (int i = 0; i < clauseNumber; ++i)
    lst[i]   = Data::DataBase[clauseOffset[i]].uid;
  subscribe->subscribe(packageID, freq, sendStamp ? 1 : 0, clauseNumber, lst);
  return true;
}

void DataSubscribe::Package::stop() { subscribe->remove(packageID); }

void DataSubscribe::Package::unpack(Header *header) {
  //!@todo implement
  uint8_t *data = ((uint8_t *)header) + sizeof(Header) + 2;
  API_LOG(subscribe->getAPI()->getDriver(), STATUS_LOG,
          "%d unpacking %d %d 0x%x 0x%x.", size, header->length - 17,
          *((uint8_t *)data + 1), *((uint32_t *)data), *((uint32_t *)data + 1));
}

void DataSubscribe::Package::allocClauseOffset(size_t allocSize) {
  if (allocSize == 0) return;
  setClauseOffset(new uint32_t[allocSize]);
  setClauseNumber(allocSize);
}

size8_t DataSubscribe::Package::getPackageID() const { return packageID; }

void DataSubscribe::Package::setPackageID(const size8_t &value) {
  packageID = value;
}

bool DataSubscribe::Package::getSendStamp() const { return sendStamp; }

void DataSubscribe::Package::setSendStamp(bool value) { sendStamp = value; }

uint16_t DataSubscribe::Package::getFreq() const { return freq; }

void DataSubscribe::Package::setFreq(const uint16_t &value) { freq = value; }

uint32_t *DataSubscribe::Package::getClauseOffset() const {
  return clauseOffset;
}

void DataSubscribe::Package::setClauseOffset(uint32_t *value) {
  clauseOffset = value;
}

size_t DataSubscribe::Package::getClauseNumber() const { return clauseNumber; }

void DataSubscribe::Package::setClauseNumber(const size_t &value) {
  clauseNumber = value;
}
