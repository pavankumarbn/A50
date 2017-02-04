#ifndef DATABROADCAST_H
#define DATABROADCAST_H

#include "DJI_Data.h"
#include "DJI_Filter.h"

namespace DJI {
namespace onboardSDK {

class DataBroadcast {
 public:
  enum FREQ {
    FREQ_0HZ   = 0,
    FREQ_1HZ   = 1,
    FREQ_10HZ  = 2,
    FREQ_50HZ  = 3,
    FREQ_100HZ = 4,
    FREQ_HOLD  = 5,
    FREQ_200HZ = 6,
    FREQ_400HZ = 7,
  };

 public:
  DataBroadcast(CoreAPI* API = 0);

  // clang-format off
  Data::TimeStamp           getTimeStamp()          const;
  Data::SyncStamp           getSyncStamp()          const;
  Data::Quaternion          getQuaternion()         const;
  Data::Vector3f            getAcceleration()       const;
  Data::Vector3f            getVelocity()           const;
  Data::Vector3f            getPalstance()          const;
  Data::VelocityInfo        getVelocityInfo()       const;
  Data::GlobalPosition      getGlobalPosition()     const;
  Data::RelativePosition    getRelativePosition()   const;
  Data::GPSInfo             getGPSInfo()            const;
  Data::RTK                 getRTKInfo()            const;
  Data::Mag                 getMag()                const;
  Data::RC                  getRC()                 const;
  Data::Gimbal              getGimbal()             const;
  Data::Status              getStaus()              const;
  Data::Battery             getBatteryInfo()        const;
  Data::SDKInfo             getSDKInfo()            const;
  // clang-format on

  CoreAPI* getAPI() const;
  void setAPI(CoreAPI* value);

  void setBroadcastFreq(uint8_t* dataLenIs16, CallBack callback = 0,
                        UserData userData = 0);

  void setBroadcastFreqDefaults();
  void setBroadcastFreqToZero();

  void setBroadcastCallback(CallBackHandler callback);
  void setBroadcastCallback(CallBack userCallback, UserData userData = 0);

 public:
  static void callbackData(DJI::onboardSDK::CoreAPI* api, Header* header,
                           UserData data);
  static void setFrequencyCallback(CoreAPI* api, Header* protocolHeader,
                                   UserData userData = 0);

 private:
  // clang-format off
  typedef enum FLAG {
    FLAG_TIME           = 0X0001,
    FLAG_QUATERNION     = 0X0002,
    FLAG_ACCELERATION   = 0X0004,
    FLAG_VELOCITY       = 0X0008,
    FLAG_PALSTANCE      = 0X0010,
    FLAG_POSITION       = 0X0020,
    FLAG_GPSINFO        = 0X0040,
    FLAG_RTKINFO        = 0X0080,
    FLAG_MAG            = 0X0100,
    FLAG_RC             = 0X0200,
    FLAG_GIMBAL         = 0X0400,
    FLAG_STATUS         = 0X0800,
    FLAG_BATTERY        = 0X1000,
    FLAG_DEVICE         = 0X2000,
    FLAG_END            = 0X4000
  } FLAG;
  // clang-format on

 private:
  void unpackData(Header* protocolHeader);

  inline void unpackOne(FLAG flag, void* data, uint8_t*& buf, size_t size);

 private:
  // clang-format off
  Data::TimeStamp           timeStamp   ;
  Data::SyncStamp           syncStamp   ;
  Data::Quaternion          q           ;
  Data::Vector3f            a           ;
  Data::Vector3f            v           ;
  Data::VelocityInfo        vi          ;
  Data::Vector3f            w           ;
  Data::GlobalPosition      gp          ;
  Data::RelativePosition    rp          ;
  Data::GPSInfo             gps         ;
  Data::RTK                 rtk         ;
  Data::Mag                 mag         ;
  Data::RC                  rc          ;
  Data::Gimbal              gimbal      ;
  Data::Status              staus       ;
  Data::Battery             battery     ;
  Data::SDKInfo             info        ;
  // clang-format on

 private:
  CoreAPI*        api;
  uint16_t        passFlag;
  CallBackHandler handler;
};

}  // onboardSDK
}  // DJI
#endif  // DATABROADCAST_H
