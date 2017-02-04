#ifndef PACKAGE_H
#define PACKAGE_H

#include "DJI_Data.h"

namespace DJI {
namespace onboardSDK {

class DataSubscribe::Package {
 public:
  typedef uint8_t* PackageBuffer;
  typedef void (*Callback)(Package*, Data::TimeStamp, UserData);
  typedef struct CallbackHandler {
    Callback callback;
    UserData data;
  } CallbackHandler;

 public:
  Package(DataSubscribe* API = 0);

 public:
  bool addByUID(Data::UID uid);
  virtual bool addByOffset(uint16_t offset);
  bool addArrayOfUID(Data::UID uidArray[], size_t numberOfClause, size8_t id, uint16_t freq, bool flagSendTimeStamp=true, Package::Callback packageUnpackCallback=0);
  //! @todo virtual bool remove(uint16_t offset);
  virtual bool start();
  virtual void stop();
  virtual void pause();
  virtual void resume();

 private:
  void unpack(Header* header);

 public:
  void allocClauseOffset(size_t allocSize);

  bool            getSendStamp() const;
  size_t          getClauseNumber() const;
  size8_t         getPackageID() const;
  uint16_t        getFreq() const;
  uint32_t*       getClauseOffset() const;
  uint32_t*       getMemoryOffset() const;
  DataSubscribe*  getSubscribe() const;
  PackageBuffer   getMemoryPool() const;
  Data::TimeStamp getTimeStamp() const;

  void setSendStamp(bool value);
  void setPackageID(const size8_t& value);
  void setFreq(const uint16_t& value);
  void setClauseNumber(const size_t& value);
  void setClauseOffset(uint32_t* value);
  void setMemoryOffset(uint32_t* value);
  void setUnpackHandler(const Callback& cb, const UserData& data);
  void setUnpackHandler(const CallbackHandler& value);

 private:
  //! @todo implement and init
  bool isUsingAPI;

  uint16_t freq;
  bool     sendStamp;

  DataSubscribe*  subscribe;
  PackageBuffer   memoryPool;
  CallbackHandler unpackHandler;
  size16_t        size;
  size8_t         packageID;
  size_t          clauseInited;
  size_t          clauseNumber;
  uint32_t*       clauseOffset;
  uint32_t*       memoryOffset;

  friend class DataSubscribe;
};

}  // onboardSDK
}  // DJI

#endif  // P_H
