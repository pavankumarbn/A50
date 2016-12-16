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
  typedef struct TimeStamp {
    uint32_t time_ms;
    uint32_t time_ns;
  } TimeStamp;

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
    uint8_t reserve : 7;
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
  typedef enum ERROR {
    ERROR_NONE                          = 0,
    ERROR_COMPASS_ABNORMAL              = 1,
    ERROR_ASSISTANT_LINK_SOFT_PROTECTED = 2,
    ERROR_DEVICE_LOCKED                 = 3,  //
    ERROR_TOO_FAR_FROM_HOMEPOINT        = 4,
    ERROR_IMU_NEED_CALIBRATION          = 5,
    ERROR_INTERNAL_6                    = 6,
    ERROR_IMU_PREHEATING                = 7,
    ERROR_COMPASS_CALIBRATING           = 8,
    ERROR_IMU_DAMAGED_9                 = 9,
    ERROR_NO_GPS_IN_BEGINNER_MODE       = 10,
    ERROR_BATTERY_INTERNAL_11           = 11,
    ERROR_BATTERY_INFO                  = 12,
    ERROR_BATTERY_LOWPOWER_SERIOUS      = 13,
    ERROR_BATTERY_CAPACITY_LOWLAND      = 14,
    ERROR_BATTERY_VOLTAGE_LOWLAND       = 15,
    ERROR_BATTERY_TEMPERATURE_LOWLAND   = 16,
    ERROR_BATTERY_INTERNAL_LOWLAND      = 17,  //
    ERROR_BATTERY_INTERNAL_18           = 18,  //
    ERROR_RUNNING_SIMULATOR             = 19,
    ERROR_PACKING                       = 20,
    ERROR_GROUND_NOT_HORI               = 21,  //
    ERROR_NOT_ACTIVATED                 = 22,  //
    ERROR_NFZ                           = 23,
    ERROR_IMU_NEED_CALIBRATION_2        = 24,
    ERROR_ESC_INTERNAL                  = 25,
    ERROR_IMU_INITING                   = 26,
    ERROR_UPGRADING                     = 27,
    ERROR_RUN_SIMULATOR_BEFORE          = 28,
    ERROR_IMU_CALIBRATING               = 29,
    ERROR_TAKEOFF_TILT_TOO_LARGE        = 30,  //
    ERROR_RESERVED_31                   = 31,
    ERROR_RESERVED_32                   = 32,
    ERROR_RESERVED_33                   = 33,
    ERROR_RESERVED_34                   = 34,
    ERROR_RESERVED_35                   = 35,
    ERROR_RESERVED_36                   = 36,
    ERROR_RESERVED_37                   = 37,
    ERROR_RESERVED_38                   = 38,
    ERROR_RESERVED_39                   = 39,
    ERROR_RESERVED_40                   = 40,
    ERROR_INTERNAL_41                   = 41,
    ERROR_BAROMETER_DAMAGED             = 42,  //
    ERROR_IMU_DAMAGED_43                = 43,  //
    ERROR_PREPAREING                    = 44,
    ERROR_GPS_OFFLINE                   = 45,
    ERROR_INTERNAL_46                   = 46,  //
    ERROR_INTERNAL_47                   = 47,
    ERROR_INTERNAL_48                   = 48,
    ERROR_RESERVED_49                   = 49,
    ERROR_RESERVED_50                   = 50,
    ERROR_RESERVED_51                   = 51,
    ERROR_RESERVED_52                   = 52,
    ERROR_RESERVED_53                   = 53,
    ERROR_RESERVED_54                   = 54,
    ERROR_RESERVED_55                   = 55,
    ERROR_RESERVED_56                   = 56,
    ERROR_RESERVED_57                   = 57,
    ERROR_RESERVED_58                   = 58,
    ERROR_RESERVED_59                   = 59,
    ERROR_RESERVED_60                   = 60,
    ERROR_IMU_OFFLINE                   = 61,
    ERROR_RC_CALIBRATING                = 62,
    ERROR_RC_CALI_ERROR                 = 63,
    ERROR_RC_NEED_CALI                  = 64,
    ERROR_RC_NEED_CALI_2                = 65,
    ERROR_RC_CHANNEL_MAPPING            = 66,
    ERROR_INTERNAL_67                   = 67,  //
    ERROR_CONFIG_NOT_FINISHED           = 68,
    ERROR_RESERVED_69                   = 69,
    ERROR_IMU_INTERNAL_DAMAGED          = 70,
    ERROR_BAROMETER_INTERNAL_DAMAGED    = 71,
    ERROR_COMPASS_INTERNAL_DAMAGED      = 72,
    ERROR_GPS_INTERNAL_DAMAGED          = 73,
    ERROR_INTERNAL_DAMAGED_74           = 74,  //
    ERROR_INTERNAL_DAMAGED_75           = 75,
    ERROR_RC_NEED_CALI_3                = 76,  //
    ERROR_INTERNAL_77                   = 77,
    ERROR_BATTERY_NOT_ENOUGH            = 78,
    ERROR_BATTERY_INTERNAL_79           = 79,
    ERROR_RESERVED_80                   = 80,
    ERROR_BATTERY_VOLTAGE_DIFF_81       = 81,
    ERROR_BATTERY_BOLTAHGE_DIFF_82      = 82,
    ERROR_NEED_NEW_FIRMWARE             = 83,
    ERROR_GIMBAL_IMU_DATA               = 84,
    ERROR_GIMBAL_ESC_PITCH              = 85,
    ERROR_GIMBAL_ESC_ROLL               = 86,
    ERROR_GIMBAL_ESC_YAW                = 87,
    ERROR_GIMBAL_UPGRADING              = 88,
    ERROR_GIMBAL_OFFLINE                = 89,
    ERROR_GIMBAL_PITCH_AUTO_OSCILLATION = 90,
    ERROR_GIMBAL_ROLL_AUTO_OSCILLATION  = 91,
    ERROR_GIMBAL_YAW_AUTO_OSCILLATION   = 92,
    ERROR_IMU_INTERNAL_NEED_REBOOT      = 93,
    ERROR_INTERNAL_94                   = 94,
    ERROR_MOTOR_LOCKED                  = 95,  //
    ERROR_MOTOR_UNBALANCE               = 96,
    ERROR_MOTOR_WITHOUT_BLADE           = 97,
    ERROR_MOTOR_INTERNAL                = 98,
    ERROR_INTERNAL_99                   = 99,  //
    ERROR_ROLL_OVER                     = 100,
    ERROR_BATTERY_INTERNAL_101          = 101,
    ERROR_RTK_INITING                   = 102,
    ERROR_RTK_FALL_TO_INIT              = 103,
    ERROR_RESERVED_104                  = 104,
    ERROR_RESERVED_105                  = 105,
    ERROR_RESERVED_106                  = 106,
    ERROR_RESERVED_107                  = 107,
    ERROR_RESERVED_108                  = 108,
    ERROR_RESERVED_109                  = 109,
    ERROR_ALREADY_DONE                  = 110,
    ERROR_INTERNAL_111                  = 111,
    ERROR_ESC_CALIBRATING               = 112,
    ERROR_GPS_INTERNAL                  = 113,
    ERROR_GIMBAL_CALIBRATING            = 114,
    ERROR_INTERNAL_115                  = 115,
    ERROR_INTERNAL_DAMAGED_116          = 116,
    ERROR_ESC_NEED_UPGRADE              = 117,
    ERROR_INTERNAL_118                  = 118,
    ERROR_INTERNAL_119                  = 119,
    ERROR_COMPASS_MOUNT_ERROR           = 120,
    ERROR_INTERNAL_121                  = 121
  } ERROR;

  typedef enum MODE {
    MODE_FREE_TO_SKY         = 0,
    MODE_A                   = 1,
    MODE_CURSELOCK           = 2,
    MODE_RESERVED_3          = 3,
    MODE_RESERVED_4          = 4,
    MODE_RESERVED_5          = 5,
    MODE_P_GPS               = 6,
    MODE_P_GPS_CURSELOCK     = 7,
    MODE_RESERVED_8          = 8,
    MODE_HOTPOINT            = 9,
    MODE_TAKING_OFF_STATUS_1 = 10,
    MODE_TAKING_OFF_STATUS_2 = 11,
    MODE_LANDING             = 12,
    MODE_RESERVED_13         = 13,
    MODE_WAYPOINTS           = 14,
    MODE_RETURN_HOME         = 15,
    MODE_RESERVED_16         = 16,
    MODE_SDK                 = 17,
    MODE_RESERVED_18         = 18,
    MODE_RESERVED_19         = 19,
    MODE_RESERVED_20         = 20,
    MODE_RESERVED_21         = 21,
    MODE_RESERVED_22         = 22,
    MODE_ERSERVED_23         = 23,
    MODE_RESERVED_24         = 24,
    MODE_FOLLOW              = 25,
    MODE_RESERVED_26         = 26,
    MODE_RESERVED_27         = 27,
    MODE_RESERVED_28         = 28,
    MODE_RESERVED_29         = 29,
    MODE_RESERVED_30         = 30,
    MODE_SPORT               = 31,
    MODE_BEGINNER            = 32,
    MODE_LOWLANDING          = 33,
    MODE_RESERVED_34         = 34,
    MODE_RESERVED_35         = 35,
    MODE_RESERVED_36         = 36,
    MODE_RESERVED_37         = 37,
    MODE_RESERVED_38         = 38,
    MODE_RESERVED_39         = 39,
    MODE_RESERVED_40         = 40,
    MODE_ENGINE_START        = 41,
    MODE_RESERVED_42         = 42
  } MODE;

  typedef enum LANDING_GEAR {
    GEAR_UNDEFINED  = 0,
    GEAR_DOWN       = 1,
    GEAR_UP_TO_DOWN = 2,
    GEAR_UP         = 3,
    GEAR_DOWN_TO_UP = 4,
    GEAR_HOLD       = 5,
    GEAR_PACKED     = 6,
    GEAR_PACKING    = 7,
    GEAR_UNPACKING  = 8
  } LANDING_GEAR;
};

class DataBroadcast {
 public:
  static void callbackData(DJI::onboardSDK::CoreAPI* api, Header* header,
                           UserData data);

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

  CoreAPI* getApi() const;

  void setAPI(CoreAPI* value);

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

  inline void unpackOne(FLAG flag, void* data, uint8_t* buf, size_t size);

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
  CallBackHandler handler;
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
