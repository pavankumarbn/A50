#ifndef DJI_ENUMS_H
#define DJI_ENUMS_H

namespace DJI {
namespace onboardSDK {
namespace Data {

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

enum CTRL_MODE {
  ATTI_STOP                   = 0,
  HORIZ_ANG_VERT_VEL_YAW_ANG  = 1,
  HORIZ_ANG_VERT_VEL_YAW_RATE = 2,
  HORIZ_VEL_VERT_VEL_YAW_ANG  = 3,
  HORIZ_VEL_VERT_VEL_YAW_RATE = 4,
  HORIZ_POS_VERT_VEL_YAW_ANG  = 5,
  HORIZ_POS_VERT_VEL_YAW_RATE = 6,
  HORIZ_ANG_VERT_POS_YAW_ANG  = 7,
  HORIZ_ANG_VERT_POS_YAW_RATE = 8,
  HORIZ_VEL_VERT_POS_YAW_ANG  = 9,
  HORIZ_VEL_VERT_POS_YAW_RATE = 10,
  HORIZ_POS_VERT_POS_YAW_ANG  = 11,
  HORIZ_POS_VERT_POS_YAW_RATE = 12,
  HORIZ_ANG_VERT_THR_YAW_ANG  = 13,
  HORIZ_ANG_VERT_THR_YAW_RATE = 14,
  HORIZ_VEL_VERT_THR_YAW_ANG  = 15,
  HORIZ_VEL_VERT_THR_YAW_RATE = 16,
  HORIZ_POS_VERT_THR_YAW_ANG  = 17,
  HORIZ_POS_VERT_THR_YAW_RATE = 18,
  HORIZ_PAL_VERT_VEL_YAW_RATE = 19,
  HORIZ_PAL_VERT_POS_YAW_RATE = 20,
  HORIZ_PAL_VERT_THR_YAW_RATE = 21,
  GPS_ATII_CTRL_CL_YAW_RATE   = 97,  //! @note unused
  GPS_ATTI_CTRL_YAW_RATE      = 98,  //! @note unused
  ATTI_CTRL_YAW_RATE          = 99,  //! @note unused
  ATTI_CTRL_STOP              = 100,
  MODE_NOT_SUPPORTED          = 0xFF  //! @note unused
};

enum STATUS {
  STATUS_STOPED = 0,
  STATUS_ON_GND = 1,
  STATUS_IN_AIR = 2,
};

}  // namespace Data
}  // onboardSDK
}  // DJI
#endif  // DJI_ENUMS_H
