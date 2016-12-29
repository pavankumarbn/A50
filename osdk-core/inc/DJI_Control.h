#ifndef C_H
#define C_H

#include "DJI_API.h"

namespace DJI {
namespace onboardSDK {

//! @todo move to DJI_Control.h
class Control {
 public:
  typedef enum COMMAND {
    COMMAND_TAKEOFF = 1,
    COMMAND_LANDING = 2,
    //! @note independent mode COMMAND_CURSELOCK, cannot contorl through SDK
    COMMAND_CURSELOCK              = 5,
    COMMAND_GOHOME                 = 6,
    COMMAND_STARTMOTOR             = 7,
    COMMAND_STOPMOTOR              = 8,
    COMMAND_CALIBRATE_COMPASS      = 9,
    COMMAND_EXIT_GOHOME            = 12,
    COMMAND_EXIT_TAKEOFF           = 13,
    COMMAND_EXIT_LANDING           = 14,
    COMMADN_EXIT_CALIBRATE_COMPASS = 21,
    COMMAND_EXIT_PACK_MODE         = 22,
    COMMAND_LANGDING_GEAR_UP       = 28,
    COMMAND_LANDING_GEAR_DOWN      = 29
  } COMMAND;

  typedef enum COMMAND_ERROR {
    ERROR_COMMAND_NONE                      = 0,
    ERROR_COMMAND_MOTOR_ON                  = 1,
    ERROR_COMMAND_MOTOR_OFF                 = 2,
    ERROR_COMMAND_IN_AIR                    = 3,
    ERROR_COMMAND_NOT_IN_AIR                = 4,
    ERROR_COMMAND_NO_HOMEPOINT              = 5,
    ERROR_COMMAND_BAD_GPS                   = 6,
    ERROR_COMMAND_IN_SIMULATOR              = 7,
    ERROR_COMMAND_ALREADY_RUNNING           = 8,
    ERROR_COMMAND_NOT_RUNNING               = 9,
    ERROR_COMMAND_INVAILD                   = 10,
    ERROR_COMMAND_NO_LANDING_GEAR           = 11,
    ERROR_COMMAND_GIMBAL_MOUNTED            = 12,
    ERROR_COMMAND_BAD_SENSOR                = 13,
    ERROR_COMMAND_ALREADY_PACKED            = 14,
    ERROR_COMMAND_NO_PACKED                 = 15,
    ERROR_COMMAND_PACKED_MODE_NOT_SUPPORTED = 16
  } COMMAND_ERROR;

  enum VerticalLogic {
    VERTICAL_VELOCITY = 0x00,
    VERTICAL_POSITION = 0x10,
    VERTICAL_THRUST   = 0x20,
  };

  enum HorizontalLogic {
    HORIZONTAL_ANGLE     = 0x00,
    HORIZONTAL_VELOCITY  = 0x40,
    HORIZONTAL_POSITION  = 0x80,
    HORIZONTAL_PALSTANCE = 0xC0
  };

  enum YawLogic { YAW_ANGLE = 0x00, YAW_RATE = 0x08 };

  enum HorizontalCoordinate {
    HORIZONTAL_GROUND = 0x00,
    HORIZONTAL_BODY   = 0x02
  };

  enum SmoothMode { SMOOTH_DISABLE = 0x00, SMOOTH_ENABLE = 0x01 };

#pragma pack(1)
  typedef struct FlightData {
    uint8_t flag;
    float32_t x;
    float32_t y;
    float32_t z;
    float32_t yaw;
  } FlightData;

  typedef struct AdvancedFlightData {
    uint8_t flag;
    uint8_t advFlag;
    float32_t x;
    float32_t y;
    float32_t z;
    float32_t yaw;
    float32_t xFeedforward;
    float32_t yFeedforward;
  } AdvancedFlightData;
#pragma pack()

 public:
  Control(CoreAPI *API = 0);
  CoreAPI *getApi() const;
  void setAPI(CoreAPI *value) { api = value; }

  void obtain(CallBack callback = 0, UserData userData = 0);
  void release(CallBack callback = 0, UserData userData = 0);
  void command(COMMAND cmd, CallBack callback = 0, UserData userData = 0);
  void input(uint8_t flag, float32_t x, float32_t y, float32_t z, float32_t yaw,
             float32_t xFeedforward = 0, float32_t yFeedforward = 0);
  void emergencyBrake();

 public:
  static void setControlCallback(CoreAPI *api, Header *protocolHeader,
                                 UserData userData);
  static void commandCallback(CoreAPI *api, Header *protocolHeader,
                              UserData userData);

 private:
  void basic(FlightData *data);
  void advanced(AdvancedFlightData *data);

 private:
  CoreAPI *api;
};

}  // onboardSDK
}  // DJI

#endif  // C_H
