#ifndef GIMBAL_H
#define GIMBAL_H

#include "DJI_API.h"
#include "DJI_Data.h"

namespace DJI {
namespace onboardSDK {

//! @todo test
class Gimbal {
 public:
  Gimbal(DataSubscribe* subscribe = 0) : data(subscribe) {}

  void moveToAngle(int16_t yaw, int16_t roll, int16_t pitch, uint8_t mode,
                   uint8_t duration);
  void moveToCenter();

  void moveWithPalstance(int16_t yaw, int16_t roll, int16_t pitch);

  /*! @todo refactory
  void Camera::setGimbalAngle(GimbalAngleData *data) {
    api->send(0, encrypt, SET_CONTROL, Camera::CODE_GIMBAL_ANGLE,
              (unsigned char *)data, sizeof(GimbalAngleData));
  }

  void Camera::setGimbalSpeed(GimbalSpeedData *data) {
    data->reserved = 0x80;
    api->send(0, encrypt, SET_CONTROL, Camera::CODE_GIMBAL_SPEED,
              (unsigned char *)data, sizeof(GimbalSpeedData));
  }
*/

 public:
  //! @note data accessing
  bool isMount();
  bool isIdle();
  bool hasFault();

  Data::Vector3f getAngles() const;
  float32_t      getYaw() const;
  float32_t      getRoll() const;
  float32_t      getPitch() const;
  bool           isYawLimit() const;
  bool           isRollLimit() const;
  bool           isPitchLimit() const;

 private:
  typedef enum ANGLES { ANGLE_ROLL = 0, ANGLE_PITCH = 1, ANGLE_YAW = 2 } ANGLES;

#pragma pack(1)
  typedef struct AngleData {
    int16_t yaw;
    int16_t roll;
    int16_t pitch;
    uint8_t mode;
    uint8_t duration;
  } AngleData;

  typedef struct PalstanceData {
    int16_t yaw;
    int16_t roll;
    int16_t pitch;
    uint8_t reserved;  // always 0x80;
  } PalstanceData;
#pragma pack()

 private:
  DataSubscribe* data;  //! @note introducing evil coupling
};

}  // namespace onboardSDK
}  // namespace DJI
#endif  // GIMBAL_H
