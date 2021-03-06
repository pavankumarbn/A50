#include "DJI_Data.h"
#include "DJI_Package.h"

using namespace DJI;
using namespace DJI::onboardSDK;

// void *DataSubscribe::DataClause::getPtr() const { return ptr; }

// void DataSubscribe::DataClause::setPtr(void *value) { ptr = value; }

bool DataSubscribe::codeCheck = false;

void DataSubscribe::verify(CallBack callback, UserData userData) {
  VersionData data = Data::DBVersion;
  while (lock)
    ;
  lock = true;
  api->send(2, DJI::onboardSDK::encrypt, SET_SUBSCRIBE,
            CODE_SUBSCRIBE_VERSION_MATCH, &data, sizeof(data), 500, 2,
            callback ? callback : verifyCallback, userData ? userData : this);
}

void DataSubscribe::subscribe(uint8_t id, uint16_t freq, uint8_t flag,
                              uint8_t clauseNumber, uint32_t *uid) {
  SubscribeData data;
  data.packageID    = id;
  data.freq         = freq;
  data.config       = flag;
  data.clauseNumber = clauseNumber;
  //    data.uidList                  = uid;
  static const size_t bufferLen = 200;
  uint8_t buffer[bufferLen];
  size_t size = sizeof(SubscribeData) + sizeof(uint32_t) * clauseNumber;
  if (size > bufferLen) {
    API_LOG(api->getDriver(), ERROR_LOG,
            "Too many clauses subscribed %d , max %d\n", size, bufferLen);
  } else {
    memcpy(buffer, (uint8_t *)&data, sizeof(data));
    memcpy(buffer + sizeof(SubscribeData), (uint8_t *)uid,
           sizeof(uint32_t) * clauseNumber);
    API_LOG(api->getDriver(), DEBUG_LOG, "0x%x",
            *(uint32_t *)(buffer + sizeof(SubscribeData)));
    api->send(2, DJI::onboardSDK::encrypt, SET_SUBSCRIBE,
              CODE_SUBSCRIBE_ADD_PACKAGE, buffer, size, 500, 1,
              addPackageCallback, package[id]);
  }
}

void DataSubscribe::reset(CallBack callback, UserData userData) {
  uint8_t data = 0;
  while (lock)
    ;
  lock = true;
  api->send(2, DJI::onboardSDK::encrypt, SET_SUBSCRIBE, CODE_SUBSCRIBE_RESET,
            &data, 0, 500, 1, callback ? callback : resetCallback,
            userData ? userData : this);
}

void DataSubscribe::remove(uint8_t packageID) {
  uint8_t data = packageID;
  api->send(2, DJI::onboardSDK::encrypt, SET_SUBSCRIBE,
            CODE_SUBSCRIBE_REMOVE_PACKAGE, &data, sizeof(data), 500, 1,
            removeCallback, package[packageID]);
}

void DataSubscribe::pause(uint8_t packageID) {
  uint16_t data = packageID;
  api->send(2, DJI::onboardSDK::encrypt, SET_SUBSCRIBE,
            CODE_SUBSCRIBE_PAUSE_RESUME, &data, sizeof(data), 500, 1,
            pauseCallback, package[packageID]);
}

void DataSubscribe::resume(uint8_t packageID) {
  uint16_t data = packageID | 0x0100;
  api->send(2, DJI::onboardSDK::encrypt, SET_SUBSCRIBE,
            CODE_SUBSCRIBE_PAUSE_RESUME, &data, sizeof(data), 500, 1,
            resumeCallback, package[packageID]);
}

void DataSubscribe::verifyCallback(CoreAPI *API, Header *header,
                                   UserData THIS) {
  //! @todo implement
  API_LOG(API->getDriver(),STATUS_LOG,"finishing verify");
  DataSubscribe *This = (DataSubscribe *)THIS;
  This->lock          = false;
  This->decodeAck(header);
  //  API->decodeAckDetails(pdata);
}

void DataSubscribe::addPackageCallback(CoreAPI *API, Header *header,
                                       UserData THIS) {

  DataSubscribe::Package *This = (DataSubscribe::Package *)THIS;
  if (This->getSubscribe()->decodeAck(header) == RESULT_SUCESS) {
    API_LOG(API->getDriver(),STATUS_LOG,"finishing adding package %d",This->getPackageID());
    size_t tmp    = This->getClauseNumber();
    uint16_t freq = This->getFreq();
    for (size_t i = 0; i < tmp; ++i) {
      Data::DataBase[This->getClauseOffset()[i]].pkg  = This;
      Data::DataBase[This->getClauseOffset()[i]].freq = freq;
      Data::DataBase[This->getClauseOffset()[i]].latest =
          This->memoryPool + (This->sendStamp ? 8 : 0) +
          This->getMemoryOffset()[i];
    }
  }else if(This->getSubscribe()->decodeAck(header) == RESULT_PACKAGE_ALREADY_EXIST){
    API_LOG(API->getDriver(),STATUS_LOG,"package already exists %d",This->getPackageID());
  }else if(This->getSubscribe()->decodeAck(header) == RESULT_MULTIPLE_SUBSCRIBE){
    API_LOG(API->getDriver(),STATUS_LOG,"package %d, multiple subscribe",This->getPackageID());
  }
  else {
    API_LOG(API->getDriver(),STATUS_LOG,"fail to subscribe package %d",This->getPackageID());
    //! @todo error management
    //  API->decodeAckDetails(pdata);
  }
}

void DataSubscribe::resetCallback(CoreAPI *API, Header *header, UserData THIS) {
  API_LOG(API->getDriver(),STATUS_LOG,"finishing reset");

  DataSubscribe *This = (DataSubscribe *)THIS;
  This->lock          = false;
  This->decodeAck(header);
  //  API->decodeAckDetails(pdata);
}

void DataSubscribe::removeCallback(CoreAPI *API, Header *header,
                                   UserData THIS) {
  API_LOG(API->getDriver(),STATUS_LOG,"finishing remove");
  if (THIS) {
    DataSubscribe::Package *This = (DataSubscribe::Package *)THIS;
    This->getSubscribe()->decodeAck(header);
    //  API->decodeAckDetails(pdata);
    for (int i = 0; i < This->clauseNumber; ++i) {
      Data::DataBase[This->clauseOffset[i]].freq = 0;
    }
  } else {
    API_LOG(API->getDriver(), STATUS_LOG,
            "unknown package removed successfully.");
  }
}

void DataSubscribe::decodeCallback(CoreAPI *API, Header *header,
                                   UserData THIS) {
  DataSubscribe *This = (DataSubscribe *)THIS;
  uint8_t pkg         = This->getPackageNumber(header);
  if (pkg < maxPakcageNumber) {
    API_LOG(API->getDriver(), DEBUG_LOG, "Length %d %d %d %d", header->length,
            sizeof(Header), pkg, API->getDriver()->getTimeStamp());
    Package *p = This->package[pkg];
    if (p)
      p->unpack(header);
    else {
      API_LOG(API->getDriver(), ERROR_LOG,
              "Unknown subsciption package %d, removing...", pkg);
      if (DEBUG_LOG) {  //! @note used for package decode time varing debug
        uint8_t *data = ((uint8_t *)header) + sizeof(Header) + 2;
        data++;

        API_LOG(This->getAPI()->getDriver(), STATUS_LOG, "Time: %d %d",
                *((uint32_t *)data), *((uint32_t *)data + 1));
      }
      This->remove(pkg);
    }
  } else {
    API_LOG(API->getDriver(), ERROR_LOG,
            "Segmentation fault, unexcepted package value %d", pkg);
  }
}

void DataSubscribe::pauseCallback(CoreAPI *API, Header *header, UserData THIS) {
  //! @todo implement
  DataSubscribe::Package *This = (DataSubscribe::Package *)THIS;
  This->getSubscribe()->decodeAck(header);
}

void DataSubscribe::resumeCallback(CoreAPI *API, Header *header,
                                   UserData THIS) {
  //! @todo implement
  DataSubscribe::Package *This = (DataSubscribe::Package *)THIS;
  This->getSubscribe()->decodeAck(header);
}

uint8_t DataSubscribe::decodeAck(Header *protocolHeader) {
  uint8_t *pdata = ((uint8_t *)protocolHeader) + sizeof(Header);
  API_LOG(api->getDriver(), STATUS_LOG, "ACK: %x, length: %d", *pdata,
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

void DataSubscribe::checkDataBase()
{
  if(!codeCheck){
    for(int i = 0 ; i < Data::toaltalClauseNumber; ++i)
      if(Data::DataBase[i].offset_check != i){
        API_LOG(api->getDriver(),ERROR_LOG,"DataBase Internal Error\n");
      }
    API_LOG(api->getDriver(),STATUS_LOG,"Finish checking data base's accessibility\n");
    codeCheck = true;
  }
}

DataSubscribe::DataSubscribe(CoreAPI *API) {
  for (int i = 0; i < maxPakcageNumber; ++i) package[i] = 0;
  if (API){
    setAPI(API);
    checkDataBase();
  }
  lock = false;
}

CoreAPI *DataSubscribe::getAPI() const { return api; }

void DataSubscribe::setAPI(CoreAPI *value) {
  api = value;
  checkDataBase();
  api->setSubscribeCallback(decodeCallback, this);
}

bool DataSubscribe::setPackage(DataSubscribe::Package *pkg, bool removeOld) {
  if (pkg->getPackageID() < maxPakcageNumber) {
    if (package[pkg->getPackageID()] != 0) {
      if (removeOld) {
        API_LOG(api->getDriver(), STATUS_LOG,
                "package already exist, remove the old one.")
            remove(pkg->getPackageID());
      } else {
        API_LOG(api->getDriver(), DEBUG_LOG, "package %d, already used",
                pkg->getPackageID());
        return false;
      }
    }
    package[pkg->getPackageID()] = pkg;
    return true;
  } else {
    API_LOG(api->getDriver(), ERROR_LOG, "package out of range");
    return false;
  }
}
