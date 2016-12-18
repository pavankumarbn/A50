#ifndef DJI_DATABASE_H
#define DJI_DATABASE_H

#include "DJI_Status.h"
#include "DJI_Type.h"

namespace DJI {
namespace onboardSDK {
namespace Data {

typedef struct DataClauseInfo {
  uint32_t uid;
  uint16_t freq;  //! @note max freq in Hz
  size8_t size;
  UserData userMethod;
  // char brief[64];
} DataClauseInfo;

extern const DataClauseInfo DataBase[];

typedef enum UID {
  UID_Quaternion               = 0xa493281f,
  UID_ACCELERATION_GROUND      = 0x8696c85b,
  UID_ACCELERATION_BODY        = 0xbb17d5fe,
  UID_ACCELERATION_RAW         = 0x00,
  UID_VELOCITY                 = 0x00,
  UID_PALSTANCE_FUSIONED       = 0x00,
  UID_PALSTANCE_RAW            = 0x00,
  UID_ALTITUDE_FUSIONED        = 0x00,
  UID_ALTITUDE_BAROMETER       = 0x00,
  UID_HEIGHT_HOMEPOOINT        = 0x00,
  UID_HEIGHT_ULTRASONIC        = 0x00,
  UID_GPS_DATE                 = 0x00,
  UID_GPS_TIME                 = 0x00,
  UID_GPS_POSITION             = 0x00,
  UID_GPS_VELOCITY             = 0x00,
  UID_GPS_DETAILS              = 0x00,
  UID_RTK_POSITION             = 0x00,
  UID_RTK_VELOCITY             = 0x00,
  UID_RTK_YAW                  = 0x00,
  UID_RTK_POSITION_INFO        = 0x00,
  UID_RTK_YAW_INFO             = 0x00,
  UID_COMPASS                  = 0x00,
  UID_RC                       = 0x00,
  UID_GIMBAL_ANGLES            = 0x00,
  UID_GIMBAL_STATUS            = 0x00,
  UID_STATUS_FLIGHT            = 0x00,
  UID_STATUS_DISPLAYMODE       = 0x00,
  UID_STATUS_LANDINGGEAR       = 0x00,
  UID_STATUS_MOTOR_START_ERROR = 0x00,
  UID_BATTERY_INFO             = 0x00,
  UID_CONTROL_DEVICE           = 0x00
} UID;

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
}  // namespace Data
}  // onboardSDK
}  // DJI

#endif  // DJI_DATABASE_H
