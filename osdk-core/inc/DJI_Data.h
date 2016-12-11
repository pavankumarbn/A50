#ifndef DATASUBSCRIBE_H
#define DATASUBSCRIBE_H

#include <string.h>
#include "DJI_API.h"
#include "DJI_HardDriver.h"
//! @warning This SDK structure only support SDK V3.2.20 or later

namespace DJI {
namespace onboardSDK {

class Data {
 public:
  struct TimeStamp {
    uint32_t time_ms;
    uint32_t time_ns;
  };

  typedef struct TimeStamp TimeStamp;

  typedef struct SyncStamp {
    uint32_t time;  //! @note relative sync time
    uint16_t tag;
    uint8_t flag;
  } SyncStamp;

  typedef struct Quaternion {
    float32_t q0;
    float32_t q1;
    float32_t q2;
    float32_t q3;
  } Quaternion;

  typedef struct Vector3f {
    float32_t x;
    float32_t y;
    float32_t z;
  } Vector3f;
  typedef struct VelocityInfo {
    uint8_t health : 1;
    uint8_t sensorID : 4;
    uint8_t reserve : 3;
  } VelocityInfo;

  typedef struct GlobalPosition {
    float64_t latitude;
    float64_t longitude;
    float32_t altitude;
    float32_t height;
    uint8_t health;
  } GlobalPosition;

  typedef struct RelativePosition {
    float32_t down;
    float32_t front;
    float32_t right;
    float32_t back;
    float32_t left;
    float32_t up;
    uint8_t downHealth : 1;
    uint8_t frontHealth : 1;
    uint8_t rightHealth : 1;
    uint8_t backHealth : 1;
    uint8_t leftHealth : 1;
    uint8_t upHealth : 1;
    uint8_t reserved : 2;
  } RelativePosition;

  typedef struct PositionFrame {
    uint32_t date;
    uint32_t time;
    float64_t longitude;
    float64_t latitude;
    float32_t HFSL;
  } PositionFrame;

  typedef struct GPSInfo {
    PositionFrame pos;
    Vector3f velocityNED;

    float32_t hdop;
    float32_t pdop;
    float32_t fix;
    float32_t gnssStatus;
    float32_t hacc;
    float32_t sacc;
    uint32_t usedGPS;
    uint32_t usedGLN;
    uint16_t NSV;
    uint16_t GPScounter;

  } GPSInfo;

  typedef struct RTK {
    PositionFrame pos;
    Vector3f velocityNED;

    int16_t yaw;
    uint8_t posFlag;
    uint8_t yawFlag;

  } RTK;

  typedef struct Mag {
    int16_t x;
    int16_t y;
    int16_t z;
  } Mag;

  typedef struct RC {
    int16_t roll;
    int16_t pitch;
    int16_t yaw;
    int16_t throttle;
    int16_t mode;
    int16_t gear;
  } RC;

  typedef struct Gimbal {
    float32_t roll;
    float32_t pitch;
    float32_t yaw;
    uint8_t pitchLimit : 1;
    uint8_t rollLimit : 1;
    uint8_t yawLimit : 1;
    uint8_t reserved : 5;
  } Gimbal;

  typedef struct Status {
    uint8_t flight;
    uint8_t mode;
    uint8_t gear;
    uint8_t error;
  } Status;

  typedef struct Battery {
    uint32_t capacity;
    int32_t voltage;
    int32_t current;
    uint8_t percentage;
  } Battery;

  typedef struct SDKInfo {
    uint8_t mode;
    uint8_t deviceStatus : 3; /*0->rc  1->app  2->serial*/
    uint8_t flightStatus : 1; /*1->opensd  0->close*/
    uint8_t vrcStatus : 1;
    uint8_t reserved : 3;
  } SDKInfo;

 public:
};

class DataBroadcast {
 public:
  DataBroadcast(CoreAPI* API) : api(API) {}

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

 private:
  // clang-format off
  typedef enum FLAG {
    FLAG_TIME           = 0X0001,
    FLAG_QUATERNION     = 0X0002,
    FLAG_ACCELERATION   = 0X0004,
    FLAG_VELOCITY       = 0X0008,
    FLAG_PALSTANCE      = 0X010,
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
  void unpackData(Header* protocolHeader) {
    uint8_t* pdata = ((uint8_t*)protocolHeader) + sizeof(Header);
    pdata += 2;
    passFlag = *(uint16_t*)pdata;
    pdata += sizeof(uint16_t);
    api->getDriver()->lockMSG();
    // clang-format off
    unpackOne(FLAG_TIME        ,&timeStamp ,pdata,sizeof(timeStamp ));
    unpackOne(FLAG_TIME        ,&syncStamp ,pdata,sizeof(syncStamp ));
    unpackOne(FLAG_QUATERNION  ,&q         ,pdata,sizeof(q         ));
    unpackOne(FLAG_ACCELERATION,&a         ,pdata,sizeof(a         ));
    unpackOne(FLAG_VELOCITY    ,&v         ,pdata,sizeof(v         ));
    unpackOne(FLAG_PALSTANCE   ,&w         ,pdata,sizeof(w         ));
    unpackOne(FLAG_VELOCITY    ,&vi        ,pdata,sizeof(vi        ));
    unpackOne(FLAG_POSITION    ,&gp        ,pdata,sizeof(gp        ));
    unpackOne(FLAG_POSITION    ,&rp        ,pdata,sizeof(rp        ));
    unpackOne(FLAG_GPSINFO     ,&gps       ,pdata,sizeof(gps       ));
    unpackOne(FLAG_RTKINFO     ,&rtk       ,pdata,sizeof(rtk       ));
    unpackOne(FLAG_MAG         ,&mag       ,pdata,sizeof(mag       ));
    unpackOne(FLAG_RC          ,&rc        ,pdata,sizeof(rc        ));
    unpackOne(FLAG_GIMBAL      ,&gimbal    ,pdata,sizeof(gimbal    ));
    unpackOne(FLAG_STATUS      ,&staus     ,pdata,sizeof(staus     ));
    unpackOne(FLAG_BATTERY     ,&battery   ,pdata,sizeof(battery   ));
    unpackOne(FLAG_DEVICE      ,&info      ,pdata,sizeof(info      ));
     // clang format on
    api->getDriver()->freeMSG();
  }

  inline void unpackOne(FLAG flag, void* data, uint8_t* buf, size_t size) {
    if (flag & passFlag) memcpy((uint8_t*)data, (uint8_t*)buf, size);
  }

 private:
  // clang-format off
  Data::TimeStamp           timeStamp   ;
  Data::SyncStamp           syncStamp   ;
  Data::Quaternion          q           ;
  Data::Vector3f            a           ;
  Data::Vector3f            v           ;
  Data::Vector3f            w           ;
  Data::VelocityInfo        vi          ;
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
  CoreAPI* api;
  uint16_t passFlag;
};

class DataSubscribe {
 public:
  DataSubscribe(CoreAPI* API) : api(API) {}

  void verify();
  void subscribe();
  void add();
  void remove();
  void updateFreq();
  void pause();
  void info();
  void packageInfo();

 private:
  void verifyAuthorty();
  void verifyVersion();

 private:
  CoreAPI* api;
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
