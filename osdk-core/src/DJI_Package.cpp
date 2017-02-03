#include "DJI_Package.h"

using namespace DJI;
using namespace DJI::onboardSDK;

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
      memoryPool(0),
      size(0),
      packageID(0),
      clauseInited(0),
      clauseNumber(0),
      clauseOffset(0) {
  unpackHandler.callback = 0;
  unpackHandler.data     = 0;
  //! @todo check initailization
}

bool DataSubscribe::Package::addByUID(Data::UID uid){
  for(int i = 0 ; i < Data::toaltalClauseNumber;i++)
    if(Data::DataBase[i].uid == uid){
      addByOffset(i);
      return true;
    }
  API_LOG(subscribe->getAPI()->getDriver(), ERROR_LOG,
          "UID %x not found\n",uid);
  return false;
}

bool DataSubscribe::Package::addArrayOfUID(Data::UID  uidArray[],
                                        size_t     numberOfClause,
                                        size8_t    id,
                                        uint16_t   freq,
                                        bool       flagSendTimeStamp,
                                        DataSubscribe::Package::Callback packageUnpackCallback)
{
  if(!uidArray)
    return false;

  setPackageID(id);
  setFreq(freq);
  setSendStamp(flagSendTimeStamp);
  allocClauseOffset(numberOfClause);


  for(int i=0; i<numberOfClause; i++)
  {
    if(!addByUID(uidArray[i]))
      return false;
  }

  setUnpackHandler(packageUnpackCallback, NULL);

  getSubscribe()->setPackage(this);

  return true;
}

bool DataSubscribe::Package::addByOffset(uint16_t offset) {
  if (offset < Data::toaltalClauseNumber) {
    if (clauseInited < clauseNumber) {
      memoryOffset[clauseInited]   = size;
      clauseOffset[clauseInited++] = offset;
      size += Data::DataBase[offset].size;
      return true;
    }
    API_LOG(subscribe->getAPI()->getDriver(), ERROR_LOG,
            "too much data to subscribe, please relloc.");
    return false;
  }
  API_LOG(subscribe->getAPI()->getDriver(), ERROR_LOG,
          "database offset overflow. %d", offset);
  return false;
}

bool DataSubscribe::Package::start() {
  if (clauseInited != clauseNumber) return false;
  uint32_t lst[40];
  for (int i = 0; i < clauseNumber; i++) {
    lst[i] = Data::DataBase[clauseOffset[i]].uid;
    if (Data::DataBase[clauseOffset[i]].maxfreq < freq) {
      API_LOG(subscribe->getAPI()->getDriver(), STATUS_LOG,
              "Package clause 0x%X offset %d required a publishing frequency "
              "upper than the sampling frequency \n",
              Data::DataBase[clauseOffset[i]].uid, clauseOffset[i]);
    }
  }
  subscribe->subscribe(packageID, freq, sendStamp ? 1 : 0, clauseNumber, lst);
  if (memoryPool) {
    API_LOG(subscribe->getAPI()->getDriver(), STATUS_LOG,
            "Warning! dirty memory layout.");
    delete memoryPool;
  }
  memoryPool = new uint8_t[size + (sendStamp ? 8 : 0)];
  return true;
}

void DataSubscribe::Package::stop() { subscribe->remove(packageID); }

void DataSubscribe::Package::pause() { subscribe->pause(packageID); }

void DataSubscribe::Package::resume() { subscribe->resume(packageID); }

void DataSubscribe::Package::unpack(Header *header) {
  uint8_t *data = ((uint8_t *)header) + sizeof(Header) + 2;
  API_LOG(subscribe->getAPI()->getDriver(), DEBUG_LOG,
          "%d unpacking %d %d 0x%x 0x%x.", size,
          header->length - CoreAPI::PackageMin - 3, *((uint8_t *)data + 1),
          *((uint32_t *)data), *((uint32_t *)data + 1));
  data++;
  subscribe->getAPI()->getDriver()->lockMSG();
  if (memoryPool)
    memcpy(memoryPool, data, header->length - CoreAPI::PackageMin - 3);
  else
    API_LOG(subscribe->getAPI()->getDriver(), ERROR_LOG,
            "Package do not have a vaild memory pool");
  subscribe->getAPI()->getDriver()->freeMSG();

  if (unpackHandler.callback)
    unpackHandler.callback(
        this, sendStamp ? *reinterpret_cast<Data::TimeStamp *>(data)
                        : Data::TimeStamp(),
        unpackHandler.data);
}

void DataSubscribe::Package::allocClauseOffset(size_t allocSize) {
  if (allocSize == 0) return;
  setClauseOffset(new uint32_t[allocSize]);
  setMemoryOffset(new uint32_t[allocSize]);
  setClauseNumber(allocSize);
}

size8_t DataSubscribe::Package::getPackageID() const { return packageID; }

void DataSubscribe::Package::setPackageID(const size8_t &value) {
  packageID = value;
}

bool DataSubscribe::Package::getSendStamp() const { return sendStamp; }

void DataSubscribe::Package::setSendStamp(bool value) { sendStamp = value; }

DataSubscribe *DataSubscribe::Package::getSubscribe() const {
  return subscribe;
}

uint32_t *DataSubscribe::Package::getMemoryOffset() const {
  return memoryOffset;
}

void DataSubscribe::Package::setMemoryOffset(uint32_t *value) {
  memoryOffset = value;
}

void DataSubscribe::Package::setUnpackHandler(const Callback &cb,
                                              const UserData &data) {
  Package::CallbackHandler hdl;
  hdl.callback = cb;
  hdl.data     = data;
  setUnpackHandler(hdl);
}

void DataSubscribe::Package::setUnpackHandler(const CallbackHandler &value) {
  unpackHandler = value;
}

DataSubscribe::Package::PackageBuffer DataSubscribe::Package::getMemoryPool()
    const {
  return memoryPool;
}

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
