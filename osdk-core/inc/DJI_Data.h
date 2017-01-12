#ifndef DATASUBSCRIBE_H
#define DATASUBSCRIBE_H

#include <string.h>
#include "DJI_API.h"
#include "DJI_Database.h"
#include "DJI_HardDriver.h"
//! @warning This SDK structure only support SDK V3.2.20 or later

namespace DJI {
namespace onboardSDK {

class DataSubscribe {
 public:
  class Package;
  friend class Package;

 public:
  DataSubscribe(CoreAPI* API = 0);
  CoreAPI* getAPI() const;
  void setAPI(CoreAPI* value);

 public:
  template <uint32_t UID>
  typename Data::Structure<UID>::type getValue() {
    typename Data::Structure<UID>::type ans;
    api->getDriver()->lockMSG();
    if (Data::DataBase[Data::Structure<UID>::offset].latest != 0) {
      ans = Data::getData<UID>(
          api, Data::DataBase[Data::Structure<UID>::offset].latest);
      api->getDriver()->freeMSG();
      return ans;
    } else {
      API_LOG(api->getDriver(), ERROR_LOG,
              "0x%X offset %d Value memory not initialized, return default",
              UID, Data::Structure<UID>::offset);
    }
    api->getDriver()->freeMSG();
    memset(&ans, 0, sizeof(ans));
    return ans;
  }

 private:
  typedef enum SUBSCRIBE_CODE {
    CODE_SUBSCRIBE_VERSION_MATCH       = 0x00,
    CODE_SUBSCRIBE_ADD_PACKAGE         = 0x01,
    CODE_SUBSCRIBE_RESET               = 0x02,
    CODE_SUBSCRIBE_REMOVE_PACKAGE      = 0x03,
    CODE_SUBSCRIBE_UPDATE_PACKAGE_FREQ = 0X04,
    CODE_SUBSCRIBE_PAUSE_RESUME        = 0x05,
    CODE_SUBSCRIBE_GET_CONFIG          = 0x06
  } SUBSCRIBE_CODE;

  typedef enum RESULT_CODE {
    RESULT_SUCESS                   = 0x00,
    RESULT_INPUT_ILLEGAL            = 0x01,
    RESULT_NEED_VERSION_MATCH       = 0x02,
    RESULT_PACKAGE_OUT_OF_RANGE     = 0x03,
    RESULT_PACKAGE_ALREADY_EXIST    = 0x04,
    RESULT_PACKAGE_NOT_EXIST        = 0x05,
    RESULT_ILLEGAL_FREQUENCY        = 0x06,
    RESULT_PACKAGE_TOO_LARGE        = 0x07,
    RESULT_PIPELINE_OVERFLOW        = 0x08,
    RESULT_INTERNAL_ERROR_0X09      = 0x09,
    RESULT_EMPTY_PACKAGE            = 0x20,
    RESULT_INPUT_SEGMENTATION_FAULT = 0x21,
    RESULT_ILLEGAL_UID              = 0x22,
    RESULT_PERMISSION_DENY          = 0x23,
    RESULT_MULTIPLE_SUBSCRIBE       = 0x24,
    RESULT_SOUCE_DEVICE_OFFLINE     = 0x25,
    RESULT_PAUSED                   = 0x48,
    RESULT_RESUMED                  = 0x49,
    RESULT_INTERNAL_ERROR_0X4A      = 0x4A,
    RESULT_INTERNAL_ERROR_0X50      = 0x50,
    RESULT_VERSION_VERSION_TOO_FAR  = 0x51,
    RESULT_INTERNAL_ERROR_0XFF      = 0xFF
  } GENERAL_RESULT_CODE;

#pragma pack(1)
  typedef uint32_t VersionData;
  typedef struct SubscribeData {
    uint8_t packageID;
    uint16_t ferq;
    uint8_t config;
    uint8_t clauseNumber;
    //! @note variable data add through memcpy
    //! uint32_t* uidList;
  } SubscribeData;
#pragma pack()

 public:
  bool setPackage(Package* pkg, bool removeOld = true);
  Package* getPackage(size_t id);

 public:
  //! @note basic functions
  void verify(CallBack callback = 0, UserData userData = 0);
  void reset(CallBack callback = 0, UserData userData = 0);
  //! @todo implement  void getInfo();

 public:
  //! @note subscribe functions

 private:
  //! @note package management functions

 private:
  //! @note direct API portal to Flight controller
  void subscribe(uint8_t id, uint16_t freq, uint8_t flag, uint8_t clauseNumber,
                 uint32_t* uid);
  void remove(uint8_t packageID);
  void changeFreq(uint8_t packageID, uint16_t freq);
  void pause(uint8_t packageID);
  void resume(uint8_t packageID);

 private:
  static void verifyCallback(CoreAPI* API, Header* header, UserData THIS);
  static void addPackageCallback(CoreAPI* API, Header* header, UserData THIS);
  static void resetCallback(CoreAPI* API, Header* header, UserData THIS);
  static void removeCallback(CoreAPI* API, Header* header, UserData THIS);
  static void decodeCallback(CoreAPI* API, Header* header, UserData THIS);
  static void pauseCallback(CoreAPI* API, Header* header, UserData THIS);
  static void resumeCallback(CoreAPI* API, Header* header, UserData THIS);

  uint8_t decodeAck(Header* protocolHeader);
  uint8_t* decodeAckDetails(Header* protocolHeader);

 private:
  uint8_t getPackageNumber(Header* header);

 public:
  static const int maxPakcageNumber = 5;

 private:
  CoreAPI* api;
  Package* package[maxPakcageNumber];
};

class DataPublish {
  //! @todo mirror class with DataSubscribe
 public:
  DataPublish();

 private:
};

}  // onboardSDK
}  // DJI

#endif  // DATASUBSCRIBE_H
