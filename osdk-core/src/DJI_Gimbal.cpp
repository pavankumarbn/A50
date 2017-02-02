#include "DJI_Gimbal.h"

using namespace DJI;
using namespace DJI::onboardSDK;

bool Gimbal::isMount() {
  return data->getValue<Data::UID_GIMBAL_STATUS>().mountStatus ? true : false;
}

bool Gimbal::isIdle() {
  return data->getValue<Data::UID_GIMBAL_STATUS>().isIdle ? true : false;
}

bool Gimbal::hasFault() {
  //! @todo
}

Data::Vector3f Gimbal::getAngles() const {
  return data->getValue<Data::UID_GIMBAL_ANGLES>();
}

float32_t Gimbal::getYaw() const { return getAngles()[ANGLE_YAW]; }

float32_t Gimbal::getRoll() const { return getAngles()[ANGLE_ROLL]; }

float32_t Gimbal::getPitch() const { return getAngles()[ANGLE_PITCH]; }

bool Gimbal::isYawLimit() const {
  return data->getValue<Data::UID_GIMBAL_STATUS>().yawLimited ? true : false;
}

bool Gimbal::isRollLimit() const {
  return data->getValue<Data::UID_GIMBAL_STATUS>().rollLimited ? true : false;
}

bool Gimbal::isPitchLimit() const {
  return data->getValue<Data::UID_GIMBAL_STATUS>().pitchLimited ? true : false;
}
