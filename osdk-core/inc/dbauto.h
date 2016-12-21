#ifndef DBAUTO_H
#define DBAUTO_H

//! @note auto generated header flie not need to modify

#include "stdint.h"

#define PACKED_STRUCT

typedef float fp32;
typedef double fp64;

/**************************************** SYS DATA
 * ***************************************/
typedef struct _sys_navi_data_q_cur { fp32 q[4]; } sys_navi_data_q_cur_t;

typedef struct _sys_navi_data_acc_ground {
  fp32 agx;
  fp32 agy;
  fp32 agz;
} sys_navi_data_acc_ground_t;

typedef struct _sys_navi_data_acc_body {
  fp32 abx;
  fp32 aby;
  fp32 abz;
} sys_navi_data_acc_body_t;

typedef PACKED_STRUCT _sys_navi_data_vel_with_status {
  fp32 vgx;
  fp32 vgy;
  fp32 vgz;
  PACKED_STRUCT _vgstatus {
    uint8_t health_flag : 1;
    uint8_t reserved : 7;
  }
  vgstatus;
}
sys_navi_data_vel_with_status_t;

typedef struct _sys_navi_data_ang_vel {
  fp32 wx;
  fp32 wy;
  fp32 wz;
} sys_navi_data_ang_vel_t;

typedef PACKED_STRUCT _sys_home_takeoff_alti { fp32 takeoff_alti; }
sys_home_takeoff_alti_t;

typedef PACKED_STRUCT _sys_fsm_flight_state_t { uint8_t flight_state; }
sys_fms_flight_state_t;

typedef PACKED_STRUCT _sys_mode_interface_display_mode_t {
  uint8_t display_mode;
}
sys_mode_interface_display_mode_t;

typedef PACKED_STRUCT _sys_gear_state_t { uint8_t gear_state; }
sys_gear_state_t;

typedef PACKED_STRUCT _sys_motor_start_error_code_t {
  uint16_t start_error_code;
}
sys_motor_start_error_code_t;

typedef PACKED_STRUCT _sys_navi_data_ctrl_dev_sdk {
  uint8_t cur_ctrl_mode;
  uint8_t cur_ctrl_dev_in_navi_mode : 3; /* !< 0 -> rc  1 -> app  2 -> serial */
  uint8_t serial_req_status : 1;         /* !< 1 -> opened  0 -> close */
  uint8_t reserved : 4;
}
sys_navi_data_ctrl_dev_sdk_t;

/***************************************** IMU
 * ******************************************/
typedef PACKED_STRUCT _imu_compass_data {
  int16_t mx;
  int16_t my;
  int16_t mz;
}
imu_compass_data_t;

typedef PACKED_STRUCT _imu_press_alti_high_freq { fp32 press_alti; }
imu_press_alti_high_freq_t;

typedef PACKED_STRUCT _imu_raw_alti_high_freq { fp32 raw_alti; }
imu_raw_alti_high_freq_t;

typedef PACKED_STRUCT _imu_us_height_high_freq { fp32 us_height; }
imu_us_height_high_freq_t;

/***************************************** GPS
 * ******************************************/
typedef struct _gps_raw_data_date_low_freq {
  uint32_t date;
} gps_raw_data_date_low_freq_t;

typedef struct _gps_raw_data_time_low_freq {
  uint32_t time;
} gps_raw_data_time_low_freq_t;

typedef struct _gps_raw_data_pos_low_freq {
  int32_t lon;
  int32_t lat;
  int32_t hmsl;
} gps_raw_data_pos_low_freq_t;

typedef struct _gps_raw_data_vel_low_freq {
  fp32 Vel_N;
  fp32 Vel_E;
  fp32 Vel_D;
} gps_raw_data_vel_low_freq_t;

typedef struct _gps_raw_data_details_low_freq {
  fp32 hdop;
  fp32 pdop;
  fp32 gps_fix;
  fp32 gnss_flag;
  fp32 hacc;
  fp32 sacc;
  uint32_t gps_used;
  uint32_t gln_used;
  uint16_t NumSV;
  uint16_t GpsState;
} gps_raw_data_details_low_freq_t;

/*************************************** GIMBAL
 * *****************************************/
// moved from fmu_device_gimbal.h
typedef struct _gimbal_status {
  uint32_t mount_status : 1;
  uint32_t is_busy : 1;

  uint32_t is_pitch_limit : 1;
  uint32_t is_roll_limit : 1;
  uint32_t is_yaw_limit : 1;

  uint32_t is_auto_calib : 1;
  uint32_t prev_calib_result : 1;
  uint32_t install_dir : 1;
  uint32_t disable_mvo : 1;

  uint32_t gear_show_unable : 1;

  uint32_t gyro_status : 1;
  uint32_t esc_pitch_status : 1;
  uint32_t esc_roll_status : 1;
  uint32_t esc_yaw_status : 1;
  uint32_t drone_data_recv : 1;
  uint32_t limit_find_status : 1;
  uint32_t firm_updating : 1;
  uint32_t pitch_motor_choked : 1;
  uint32_t roll_motor_choked : 1;
  uint32_t yaw_motor_choked : 1;
  uint32_t pitch_motor_temp_protected : 1;
  uint32_t roll_motor_temp_protected : 1;
  uint32_t yaw_motor_temp_protected : 1;
  uint32_t gimbal_base_inversion : 1;
  uint32_t gimbal_disorder : 1;
  uint32_t gimbal_pitch_shock : 1;
  uint32_t gimbal_roll_shock : 1;
  uint32_t gimbal_yaw_shock : 1;
  uint32_t is_aircraft_follow_gimbal : 1;

  uint32_t reserved : 3;
} gimbal_status_bits;
// moved from fmu_device_gimbal.h
typedef union {
  gimbal_status_bits bit;
  uint32_t all;
} gimbal_status;

// moved from fmu_device_gimbal.h
typedef struct _gimbal_angles {
  fp32 pitch;
  fp32 roll;
  fp32 yaw;
} gimbal_angles;

/************************************** GYRO ACC
 * ****************************************/
typedef struct _gyro_acc_calied_acc {
  fp32 gyro_acc_x;
  fp32 gyro_acc_y;
  fp32 gyro_acc_z;
} gyro_acc_calied_acc_t;

typedef struct _gyro_acc_calied_gyro {
  fp32 gyro_x;
  fp32 gyro_y;
  fp32 gyro_z;
} gyro_acc_calied_gyro_t;

/************************************* RC
 * **********************************************/
typedef PACKED_STRUCT _rc_func_data_sdk {
  int16_t roll;
  int16_t pitch;
  int16_t yaw;
  int16_t throttle;
  int16_t mode;
  int16_t gear;
}
rc_func_data_sdk_t;

/*********************************** BATTERY
 * ********************************************/
typedef PACKED_STRUCT _bat_raw_data_sdk {
  uint32_t remaining_capacity; /* !< capacity MAh */
  int32_t pack_voltage;        /* !< battery voltage */
  int32_t current;             /* !< battery current */
  uint8_t capacity_percentage; /* !< battery capacity percentage 100% */
}
bat_raw_data_sdk_t;

/************************************* RTK
 * *********************************************/
typedef PACKED_STRUCT _rtk_raw_data_pos_low_freq {
  fp64 Lon_P;
  fp64 Lat_P;
  fp32 Hmsl_P;
}
rtk_raw_data_pos_low_freq_t;

typedef struct _rtk_raw_data_vel_low_freq {
  fp32 Vel_N;
  fp32 Vel_E;
  fp32 Vel_D;
} rtk_raw_data_vel_low_freq_t;

typedef PACKED_STRUCT _rtk_raw_data_yaw_low_freq { int16_t YAW; }
rtk_raw_data_yaw_low_freq_t;

typedef PACKED_STRUCT _rtk_raw_data_pos_health_low_freq {
  uint8_t pos_health; /* !< 0:not ready 16:single point 17:rtd 34:float solution
                         50:fixed solution */
}
rtk_raw_data_pos_health_low_freq_t;

typedef PACKED_STRUCT _rtk_raw_data_yaw_health_low_freq {
  uint8_t yaw_health; /* !< 0:not ready 34:float solution 50:fixed solution */
}
rtk_raw_data_yaw_health_low_freq_t;

#endif  // DBAUTO_H
