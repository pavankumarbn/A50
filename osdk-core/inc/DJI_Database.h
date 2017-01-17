#ifndef DJI_DATABASE_H
#define DJI_DATABASE_H

#include "DJI_Status.h"
#include "DJI_Type.h"

namespace DJI {
namespace onboardSDK {
namespace Data {

typedef enum HistoricalUID {
  UID_INVAILD = 0xFFFFFFFF  //
} HistoricalUID;

typedef enum UID {
  UID_Quaternion               = 0xa493281f,
  UID_ACCELERATION_GROUND      = 0x8696c85b,
  UID_ACCELERATION_BODY        = 0xbb17d5fe,
  UID_ACCELERATION_RAW         = 0xc3503a6e,
  UID_VELOCITY                 = 0x18fb271d,
  UID_PALSTANCE_FUSIONED       = 0x3599c4be,
  UID_PALSTANCE_RAW            = 0x700389ee,
  UID_ALTITUDE_FUSIONED        = 0x11e9c81a,
  UID_ALTITUDE_BAROMETER       = 0x27396a39,
  UID_HEIGHT_HOMEPOOINT        = 0x252c164b,
  UID_HEIGHT_FUSION            = 0x87cf419d,
  UID_GPS_DATE                 = 0x598f79bc,
  UID_GPS_TIME                 = 0xd48912c9,
  UID_GPS_POSITION             = 0x0c949e94,
  UID_GPS_VELOCITY             = 0x7ac7eb80,
  UID_GPS_DETAILS              = 0x81fed54e,
  UID_RTK_POSITION             = 0x1df9a6b6,
  UID_RTK_VELOCITY             = 0x763d13c3,
  UID_RTK_YAW                  = 0xf45d73fd,
  UID_RTK_POSITION_INFO        = 0xda4a57b5,
  UID_RTK_YAW_INFO             = 0xcb72b9e3,
  UID_COMPASS                  = 0xdf3d72b7,
  UID_RC                       = 0x739f7fe4,
  UID_GIMBAL_ANGLES            = 0x01f71678,
  UID_GIMBAL_STATUS            = 0x8b6cd45c,
  UID_STATUS_FLIGHT            = 0x20cfb02a,
  UID_STATUS_DISPLAYMODE       = 0x1a67d6a1,
  UID_STATUS_LANDINGGEAR       = 0x772d6e22,
  UID_STATUS_MOTOR_START_ERROR = 0x3a41e909,
  UID_BATTERY_INFO             = 0x69779dd9,
  UID_CONTROL_DEVICE           = 0x667ba86a
} UID;

#pragma pack(1)

typedef struct TimeStamp {
  uint32_t time_2p5ms;
  uint32_t time_ns;
} TimeStamp;

typedef struct SyncStamp {
  uint32_t time_2p5ms;  //! @note relative sync time
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

typedef struct Vector3d {
  int32_t x;
  int32_t y;
  int32_t z;
} Vector3d;

typedef struct VelocityInfo {
  uint8_t health : 1;
  uint8_t reserve : 7;
} VelocityInfo;

typedef struct Velocity {
  Vector3f data;
  VelocityInfo info;
} Velocity;

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

typedef struct PositionTimeStamp {
  uint32_t date;
  uint32_t time;
} PositionTimeStamp;

typedef struct PositionData {
  float64_t longitude;
  float64_t latitude;
  float32_t HFSL;
} PositionData;

typedef struct PositionFrame {
  PositionTimeStamp time;
  PositionData data;
} PositionFrame;

typedef struct GPSDetail {
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
} GPSDetail;

typedef struct GPSInfo {
  PositionFrame pos;
  Vector3f velocityNED;
  GPSDetail detail;
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

typedef struct GimbalStatus {
  uint32_t mountStatus : 1;
  uint32_t isIdle : 1;

  uint32_t pitchLimited : 1;
  uint32_t rollLimited : 1;
  uint32_t yawLimited : 1;

  uint32_t calibrating : 1;
  uint32_t calibrationgResult : 1;
  uint32_t installDirection : 1;  // 0 -> normal 1 -> inversed for osmo
  uint32_t reserved : 2;

  uint32_t gyroFalut : 1;
  uint32_t escPitchFault : 1;
  uint32_t escRollFault : 1;
  uint32_t escYawFault : 1;
  uint32_t internalFault : 1;
  uint32_t initUnfinished : 1;
  uint32_t updating : 1;
  uint32_t reserved2 : 15;
} gimbal_status_bits;

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
  uint8_t flight;  //! @note enum STATUS
  uint8_t mode;    //! @note enum MODE
  uint8_t gear;    //! @note enum LANDING_GEAR
  uint8_t error;   //! @note enum ERROR
} Status;

typedef struct Battery {
  uint32_t capacity;
  int32_t voltage;
  int32_t current;
  uint8_t percentage;
} Battery;

typedef struct SDKInfo {
  uint8_t controlMode;      //! @note enum CTRL_MODE
  uint8_t deviceStatus : 3; /*0->rc  1->app  2->serial*/
  uint8_t flightStatus : 1; /*1->opensd  0->close*/
  uint8_t vrcStatus : 1;
  uint8_t reserved : 3;
} SDKInfo;

#pragma pack()

//! @todo unpacka callback redefine, not start to use yet, maybe remove later
typedef void (*UnpackedCallback)(CoreAPI*, uint8_t*, UserData);

typedef struct DataClauseInfo {
  const uint32_t uid;
  const size_t size;
  const uint16_t maxfreq;  //! @note max freq in Hz
  uint16_t freq;
  void* pkg;
  uint8_t*
      latest;  //! @note this pointer save the latest data's memory pool pointer
  UnpackedCallback
      callback;  //! @note called while received a package contained this clause
  UserData userData;  //! @note callback's userData
  //  char brief[64];
} DataClauseInfo;

//! @note dynamic linkage
//! @note cpp03 standard not support
//! static constant vector annouced in
//! a class
extern DataClauseInfo DataBase[];
extern const uint32_t DBVersion;
extern const size_t toaltalClauseNumber;

template <uint32_t UID>
struct Structure {
  typedef void type;
  static const uint32_t offset = 0xFFFFFFFF;
};

template <uint32_t UID>
typename Structure<UID>::type getData(CoreAPI* api, uint8_t* buffer) {
  if (Structure<UID>::offset < toaltalClauseNumber) {
    if (DataBase[Structure<UID>::offset].callback)  //! @todo remove this design
      DataBase[Structure<UID>::offset].callback(
          api, buffer, DataBase[Structure<UID>::offset].userData);
  }
  return *reinterpret_cast<typename Structure<UID>::type*>(buffer);
}

//! @note static linkage
// clang-format off
template <> struct Structure<UID_Quaternion               > {  typedef Quaternion      type; static const uint32_t offset = 0 ;};
template <> struct Structure<UID_ACCELERATION_GROUND      > {  typedef Vector3f        type; static const uint32_t offset = 1 ;};
template <> struct Structure<UID_ACCELERATION_BODY        > {  typedef Vector3f        type; static const uint32_t offset = 2 ;};
template <> struct Structure<UID_ACCELERATION_RAW         > {  typedef Vector3f        type; static const uint32_t offset = 3 ;};
template <> struct Structure<UID_VELOCITY                 > {  typedef Velocity        type; static const uint32_t offset = 4 ;};
template <> struct Structure<UID_PALSTANCE_FUSIONED       > {  typedef Vector3f        type; static const uint32_t offset = 5 ;};
template <> struct Structure<UID_PALSTANCE_RAW            > {  typedef Vector3f        type; static const uint32_t offset = 6 ;};
template <> struct Structure<UID_ALTITUDE_FUSIONED        > {  typedef float32_t       type; static const uint32_t offset = 7 ;};
template <> struct Structure<UID_ALTITUDE_BAROMETER       > {  typedef float32_t       type; static const uint32_t offset = 8 ;};
template <> struct Structure<UID_HEIGHT_HOMEPOOINT        > {  typedef float32_t       type; static const uint32_t offset = 9 ;};
template <> struct Structure<UID_HEIGHT_FUSION            > {  typedef float32_t       type; static const uint32_t offset = 10;};
template <> struct Structure<UID_GPS_DATE                 > {  typedef uint32_t        type; static const uint32_t offset = 11;};
template <> struct Structure<UID_GPS_TIME                 > {  typedef uint32_t        type; static const uint32_t offset = 12;};
template <> struct Structure<UID_GPS_POSITION             > {  typedef Vector3d        type; static const uint32_t offset = 13;};
template <> struct Structure<UID_GPS_VELOCITY             > {  typedef Vector3f        type; static const uint32_t offset = 14;};
template <> struct Structure<UID_GPS_DETAILS              > {  typedef GPSDetail       type; static const uint32_t offset = 15;};
template <> struct Structure<UID_RTK_POSITION             > {  typedef PositionData    type; static const uint32_t offset = 16;};
template <> struct Structure<UID_RTK_VELOCITY             > {  typedef Vector3f        type; static const uint32_t offset = 17;};
template <> struct Structure<UID_RTK_YAW                  > {  typedef int16_t         type; static const uint32_t offset = 18;};
template <> struct Structure<UID_RTK_POSITION_INFO        > {  typedef uint8_t         type; static const uint32_t offset = 19;};
template <> struct Structure<UID_RTK_YAW_INFO             > {  typedef uint8_t         type; static const uint32_t offset = 20;};
template <> struct Structure<UID_COMPASS                  > {  typedef Mag             type; static const uint32_t offset = 21;};
template <> struct Structure<UID_RC                       > {  typedef RC              type; static const uint32_t offset = 22;};
template <> struct Structure<UID_GIMBAL_ANGLES            > {  typedef Vector3f        type; static const uint32_t offset = 23;};
template <> struct Structure<UID_GIMBAL_STATUS            > {  typedef GimbalStatus    type; static const uint32_t offset = 24;};
template <> struct Structure<UID_STATUS_FLIGHT            > {  typedef uint8_t         type; static const uint32_t offset = 25;};
template <> struct Structure<UID_STATUS_DISPLAYMODE       > {  typedef uint8_t         type; static const uint32_t offset = 26;};
template <> struct Structure<UID_STATUS_LANDINGGEAR       > {  typedef uint8_t         type; static const uint32_t offset = 27;};
template <> struct Structure<UID_STATUS_MOTOR_START_ERROR > {  typedef uint16_t        type; static const uint32_t offset = 28;};
template <> struct Structure<UID_BATTERY_INFO             > {  typedef Battery         type; static const uint32_t offset = 29;};
template <> struct Structure<UID_CONTROL_DEVICE           > {  typedef SDKInfo         type; static const uint32_t offset = 30;};
// clang-format on

}  // namespace Data
}  // onboardSDK
}  // DJI

#endif  // DJI_DATABASE_H
