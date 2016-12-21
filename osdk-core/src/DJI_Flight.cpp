/** @file DJI_Flight.cpp
 *  @version 3.1.7
 *  @date July 1st, 2016
 *
 *  @brief
 *  Flight Control API for DJI onboardSDK library
 *
 *  @copyright 2016 DJI. All rights reserved.
 *
 */

#include "DJI_Flight.h"
#include <math.h>
#include <string.h>
#include "DJI_HardDriver.h"

using namespace DJI;
using namespace DJI::onboardSDK;

Flight::Flight(DJI::onboardSDK::CoreAPI *ControlAPI) {
  api = ControlAPI;
#ifdef USE_SIMULATION  //! @note This functionality is not supported in this
                       //! release.
  simulating = 0;
#endif  // USE_SIMULATION
}

CoreAPI *Flight::getApi() const { return api; }

void Flight::setApi(CoreAPI *value) { api = value; }

#ifdef USE_SIMULATION  //! @note This functionality is not supported in this
                       //! release.
bool Flight::isSimulating() const { return simulating; }
void Flight::setSimulating(bool value) { simulating = value; }
#endif  // USE_SIMULATION

void Flight::task(TASK taskname, CallBack TaskCallback, UserData userData) {
  if (api->getSDKVersion() < MAKE_VERSION(3, 2, 20, 0)) {
    API_LOG(api->getDriver(), ERROR_LOG,
            "Flight class abandoned please port your code to class Control");
    return;
  }

  taskData.cmdData = taskname;
  taskData.cmdSequence++;

  api->send(2, encrypt, SET_CONTROL, CODE_TASK, (unsigned char *)&taskData,
            sizeof(taskData), 100, 3,
            TaskCallback ? TaskCallback : Flight::taskCallback, userData);
}

unsigned short Flight::task(TASK taskname, int timeout) {
  taskData.cmdData = taskname;
  taskData.cmdSequence++;

  api->send(2, encrypt, SET_CONTROL, CODE_TASK, (unsigned char *)&taskData,
            sizeof(taskData), 100, 3, 0, 0);

  api->getDriver()->lockACK();
  api->getDriver()->wait(timeout);
  api->getDriver()->freeACK();

  return api->missionACKUnion.simpleACK;
}

void Flight::setArm(bool enable, CallBack ArmCallback, UserData userData) {
  if (api->getSDKVersion() < MAKE_VERSION(3, 2, 20, 0)) {
    API_LOG(api->getDriver(), ERROR_LOG,
            "Flight class abandoned please port your code to class Control");
    return;
  }
  uint8_t data = enable ? 1 : 0;
  api->send(2, encrypt, SET_CONTROL, CODE_SETARM, &data, 1, 0, 1,
            ArmCallback ? ArmCallback : Flight::armCallback, userData);
}

unsigned short Flight::setArm(bool enable, int timeout) {
  if (api->getSDKVersion() < MAKE_VERSION(3, 2, 20, 0)) {
    API_LOG(api->getDriver(), ERROR_LOG,
            "Flight class abandoned please port your code to class Control");
    return 255;
  }
  uint8_t data = enable ? 1 : 0;
  api->send(2, encrypt, SET_CONTROL, CODE_SETARM, &data, 1, 0, 1, 0, 0);

  api->getDriver()->lockACK();
  api->getDriver()->wait(timeout);
  api->getDriver()->freeACK();

  return api->missionACKUnion.simpleACK;
}

void Flight::control(uint8_t flag, float32_t x, float32_t y, float32_t z,
                     float32_t yaw) {
  FlightData data;
  data.flag = flag;
  data.x    = x;
  data.y    = y;
  data.z    = z;
  data.yaw  = yaw;
  setFlight(&data);
}

void Flight::setMovementControl(uint8_t flag, float32_t x, float32_t y,
                                float32_t z, float32_t yaw) {
  FlightData data;
  data.flag = flag;
  data.x    = x;
  data.y    = y;
  data.z    = z;
  data.yaw  = yaw;
  api->send(0, encrypt, SET_CONTROL, CODE_CONTROL, &data, sizeof(FlightData));
}

void Flight::setFlight(FlightData *data) {
  api->send(0, encrypt, SET_CONTROL, CODE_CONTROL, (unsigned char *)data,
            sizeof(FlightData));
}

QuaternionData Flight::getQuaternion() const {
#ifdef USE_SIMULATION
  if (simulating) {
    QuaternionData ans;
    //! @todo better physical model

    return ans;
  } else
#endif  // USE_SIMULATION
    return api->getBroadcastData().q;
}

EulerAngle Flight::getEulerAngle() const {
  return Flight::toEulerAngle(api->getBroadcastData().q);
}

PositionData Flight::getPosition() const { return api->getBroadcastData().pos; }

VelocityData Flight::getVelocity() const { return api->getBroadcastData().v; }

//! @warning The return type for getAcceleration will change to Vector3fData in
//! a future release
CommonData Flight::getAcceleration() const { return api->getBroadcastData().a; }
//! @warning The return type for getYawRate will change to Vector3fData in a
//! future release
CommonData Flight::getYawRate() const { return api->getBroadcastData().w; }

//! @warning old interface. Will be replaced by MagData Flight::getMagData() in
//! the next release.
MagnetData Flight::getMagnet() const { return api->getBroadcastData().mag; }

Flight::Device Flight::getControlDevice() const {
  return (Flight::Device)api->getBroadcastData().ctrlInfo.deviceStatus;
}

Flight::Status Flight::getStatus() const {
  return (Flight::Status)api->getBroadcastData().status;
}

Flight::Mode Flight::getControlMode() const {
  if (api->getSDKVersion() != versionM100_23)
    return (Flight::Mode)api->getBroadcastData().ctrlInfo.mode;
  return MODE_NOT_SUPPORTED;
}

Angle Flight::getYaw() const {
#ifdef USE_SIMULATION
  if (simulating)
    return AngularSim.yaw;
  else
#endif  // USE_SIMULATION
    return toEulerAngle(api->getBroadcastData().q).yaw;
}

Angle Flight::getRoll() const {
#ifdef USE_SIMULATION
  if (simulating)
    return AngularSim.roll;
  else
#endif  // USE_SIMULATION
    return toEulerAngle(api->getBroadcastData().q).roll;
}

Angle Flight::getPitch() const {
#ifdef USE_SIMULATION
  if (simulating)
    return AngularSim.pitch;
  else
#endif  // USE_SIMULATION
    return toEulerAngle(api->getBroadcastData().q).pitch;
}

void Flight::armCallback(CoreAPI *api, Header *protocolHeader,
                         UserData userData __UNUSED) {
  unsigned short ack_data;
  if (protocolHeader->length - EXC_DATA_SIZE <= 2) {
    memcpy((unsigned char *)&ack_data,
           ((unsigned char *)protocolHeader) + sizeof(Header),
           (protocolHeader->length - EXC_DATA_SIZE));
    switch (ack_data) {
      case ACK_ARM_SUCCESS:
        API_LOG(api->getDriver(), STATUS_LOG, "Success,0x000%x\n", ack_data);
        break;
      case ACK_ARM_NEED_CONTROL:
        API_LOG(api->getDriver(), STATUS_LOG,
                "Need to obtain control first, 0x000%x\n", ack_data);
        break;
      case ACK_ARM_ALREADY_ARMED:
        API_LOG(api->getDriver(), STATUS_LOG, "Already done, 0x000%x\n",
                ack_data);
        break;
      case ACK_ARM_IN_AIR:
        API_LOG(api->getDriver(), STATUS_LOG,
                "Cannot execute while in air, 0x000%x\n", ack_data);
        break;
    }
  } else {
    API_LOG(api->getDriver(), ERROR_LOG,
            "ACK is exception,session id %d,sequence %d\n",
            protocolHeader->sessionID, protocolHeader->sequenceNumber);
  }
}

void Flight::taskCallback(CoreAPI *api, Header *protocolHeader,
                          UserData userData __UNUSED) {
  unsigned short ack_data;
  if (protocolHeader->length - EXC_DATA_SIZE <= 2) {
    memcpy((unsigned char *)&ack_data,
           ((unsigned char *)protocolHeader) + sizeof(Header),
           (protocolHeader->length - EXC_DATA_SIZE));
    API_LOG(api->getDriver(), STATUS_LOG, "Task running successfully,%d\n",
            ack_data);
  } else {
    API_LOG(api->getDriver(), ERROR_LOG,
            "ACK is exception,session id %d,sequence %d\n",
            protocolHeader->sessionID, protocolHeader->sequenceNumber);
  }
}

//! @ deprecated Use toEulerAngle instead.
EulerianAngle Flight::toEulerianAngle(QuaternionData data) {
  EulerianAngle ans;

  double q2sqr = data.q2 * data.q2;
  double t0    = -2.0 * (q2sqr + data.q3 * data.q3) + 1.0;
  double t1    = +2.0 * (data.q1 * data.q2 + data.q0 * data.q3);
  double t2    = -2.0 * (data.q1 * data.q3 - data.q0 * data.q2);
  double t3    = +2.0 * (data.q2 * data.q3 + data.q0 * data.q1);
  double t4    = -2.0 * (data.q1 * data.q1 + q2sqr) + 1.0;

  t2 = t2 > 1.0 ? 1.0 : t2;
  t2 = t2 < -1.0 ? -1.0 : t2;

  ans.pitch = asin(t2);
  ans.roll  = atan2(t3, t4);
  ans.yaw   = atan2(t1, t0);

  return ans;
}

EulerAngle Flight::toEulerAngle(QuaternionData quaternionData) {
  EulerAngle ans;

  double q2sqr = quaternionData.q2 * quaternionData.q2;
  double t0    = -2.0 * (q2sqr + quaternionData.q3 * quaternionData.q3) + 1.0;
  double t1    = +2.0 * (quaternionData.q1 * quaternionData.q2 +
                      quaternionData.q0 * quaternionData.q3);
  double t2 = -2.0 * (quaternionData.q1 * quaternionData.q3 -
                      quaternionData.q0 * quaternionData.q2);
  double t3 = +2.0 * (quaternionData.q2 * quaternionData.q3 +
                      quaternionData.q0 * quaternionData.q1);
  double t4 = -2.0 * (quaternionData.q1 * quaternionData.q1 + q2sqr) + 1.0;

  t2 = t2 > 1.0 ? 1.0 : t2;
  t2 = t2 < -1.0 ? -1.0 : t2;

  ans.pitch = asin(t2);
  ans.roll  = atan2(t3, t4);
  ans.yaw   = atan2(t1, t0);

  return ans;
}

QuaternionData Flight::toQuaternion(EulerianAngle eulerAngleData) {
  QuaternionData ans;
  double t0 = cos(eulerAngleData.yaw * 0.5);
  double t1 = sin(eulerAngleData.yaw * 0.5);
  double t2 = cos(eulerAngleData.roll * 0.5);
  double t3 = sin(eulerAngleData.roll * 0.5);
  double t4 = cos(eulerAngleData.pitch * 0.5);
  double t5 = sin(eulerAngleData.pitch * 0.5);

  ans.q0 = t2 * t4 * t0 + t3 * t5 * t1;
  ans.q1 = t3 * t4 * t0 - t2 * t5 * t1;
  ans.q2 = t2 * t5 * t0 + t3 * t4 * t1;
  ans.q3 = t2 * t4 * t1 - t3 * t5 * t0;
  return ans;
}

Control::Control(CoreAPI *API) : api(API) {}

void Control::obtain(CallBack callback, UserData userData) {
  unsigned char data = 1;
  api->send(2, DJI::onboardSDK::encrypt, SET_CONTROL, CODE_SETCONTROL, &data, 1,
            500, 2, callback ? callback : Control::setControlCallback,
            userData);
}

void Control::release(CallBack callback, UserData userData) {
  unsigned char data = 1;
  api->send(2, DJI::onboardSDK::encrypt, SET_CONTROL, CODE_SETCONTROL, &data, 1,
            500, 2, callback ? callback : Control::setControlCallback,
            userData);
}

void Control::command(Control::COMMAND cmd, CallBack callback,
                      UserData userData) {
  uint8_t data = cmd;
  api->send(2, DJI::onboardSDK::encrypt, SET_CONTROL, CODE_TASK, &data,
            sizeof(data), 500, 2, callback ? callback : commandCallback,
            userData);
}

void Control::input(uint8_t flag, float32_t x, float32_t y, float32_t z,
                    float32_t yaw, float32_t xFeedforward,
                    float32_t yFeedforward) {
  if (xFeedforward == 0 && yFeedforward == 0) {
    FlightData data;
    data.flag = flag;
    data.x    = x;
    data.y    = y;
    data.z    = z;
    data.yaw  = yaw;
    basic(&data);
  } else {
    AdvancedFlightData data;
    data.flag         = flag;
    data.advFlag      = 0x01;
    data.x            = x;
    data.y            = y;
    data.z            = z;
    data.yaw          = yaw;
    data.xFeedforward = xFeedforward;
    data.yFeedforward = yFeedforward;
    advanced(&data);
  }
}

void Control::emergencyBrake() {
  AdvancedFlightData data;
  data.flag         = 0x4B;
  data.advFlag      = 0x02;
  data.x            = 0;
  data.y            = 0;
  data.z            = 0;
  data.yaw          = 0;
  data.xFeedforward = 0;
  data.yFeedforward = 0;
  advanced(&data);
}

void Control::setControlCallback(CoreAPI *api, Header *protocolHeader,
                                 UserData userData __UNUSED) {
  unsigned short ack_data = ACK_COMMON_NO_RESPONSE;
  unsigned char data      = 0x1;

  if (protocolHeader->length - EXC_DATA_SIZE <= sizeof(ack_data)) {
    memcpy((unsigned char *)&ack_data,
           ((unsigned char *)protocolHeader) + sizeof(Header),
           (protocolHeader->length - EXC_DATA_SIZE));
  } else {
    API_LOG(api->getDriver(), ERROR_LOG,
            "ACK is exception, session id %d,sequence %d\n",
            protocolHeader->sessionID, protocolHeader->sequenceNumber);
  }

  switch (ack_data) {
    case ACK_SETCONTROL_ERROR_MODE:
      if (api->getSDKVersion() != versionA3_32) {
        API_LOG(api->getDriver(), STATUS_LOG,
                "Obtain control failed: switch to F mode\n");
      } else {
        API_LOG(api->getDriver(), STATUS_LOG,
                "Obtain control failed: switch to P mode\n");
      }
      break;
    case ACK_SETCONTROL_RELEASE_SUCCESS:
      API_LOG(api->getDriver(), STATUS_LOG, "Released control successfully\n");
      break;
    case ACK_SETCONTROL_OBTAIN_SUCCESS:
      API_LOG(api->getDriver(), STATUS_LOG, "Obtained control successfully\n");
      break;
    case ACK_SETCONTROL_OBTAIN_RUNNING:
      API_LOG(api->getDriver(), STATUS_LOG, "Obtain control running\n");
      api->send(2, DJI::onboardSDK::encrypt, SET_CONTROL, CODE_SETCONTROL,
                &data, sizeof(data), 500, 2, CoreAPI::setControlCallback);
      break;
    case ACK_SETCONTROL_RELEASE_RUNNING:
      API_LOG(api->getDriver(), STATUS_LOG, "Release control running\n");
      data = 0;
      api->send(2, DJI::onboardSDK::encrypt, SET_CONTROL, CODE_SETCONTROL,
                &data, sizeof(data), 500, 2, CoreAPI::setControlCallback);
      break;
    case ACK_SETCONTROL_IOC:
      API_LOG(api->getDriver(), STATUS_LOG,
              "IOC mode opening can not obtain control\n");
      break;
    default:
      if (!api->decodeACKStatus(ack_data)) {
        API_LOG(api->getDriver(), ERROR_LOG, "While calling this function");
      }
      break;
  }
}

void Control::commandCallback(CoreAPI *api, Header *protocolHeader,
                              UserData userData __UNUSED) {
  unsigned short ack_data;
  if (protocolHeader->length - EXC_DATA_SIZE <= 2) {
    memcpy((unsigned char *)&ack_data,
           ((unsigned char *)protocolHeader) + sizeof(Header),
           (protocolHeader->length - EXC_DATA_SIZE));
    switch (ack_data) {
      case ERROR_COMMAND_NONE:
        API_LOG(api->getDriver(), STATUS_LOG, "successful,%d\n", ack_data);
        break;
      case ERROR_COMMAND_MOTOR_ON:
        API_LOG(api->getDriver(), STATUS_LOG,
                "fail to run command ERROR_COMMAND_MOTOR_ON,%d\n", ack_data);
        break;
      case ERROR_COMMAND_MOTOR_OFF:
        API_LOG(api->getDriver(), STATUS_LOG,
                "fail to run command ERROR_COMMAND_MOTOR_OFF,%d\n", ack_data);
        break;
      case ERROR_COMMAND_IN_AIR:
        API_LOG(api->getDriver(), STATUS_LOG,
                "fail to run command ERROR_COMMAND_IN_AIR,%d\n", ack_data);
        break;
      case ERROR_COMMAND_NOT_IN_AIR:
        API_LOG(api->getDriver(), STATUS_LOG,
                "fail to run command ERROR_COMMAND_NOT_IN_AIR,%d\n", ack_data);
        break;
      case ERROR_COMMAND_NO_HOMEPOINT:
        API_LOG(api->getDriver(), STATUS_LOG,
                "fail to run command ERROR_COMMAND_NO_HOMEPOINT,%d\n",
                ack_data);
        break;
      case ERROR_COMMAND_BAD_GPS:
        API_LOG(api->getDriver(), STATUS_LOG,
                "fail to run command ERROR_COMMAND_BAD_GPS,%d\n", ack_data);
        break;
      case ERROR_COMMAND_IN_SIMULATOR:
        API_LOG(api->getDriver(), STATUS_LOG,
                "fail to run command ERROR_COMMAND_IN_SIMULATOR,%d\n",
                ack_data);
        break;
      case ERROR_COMMAND_ALREADY_RUNNING:
        API_LOG(api->getDriver(), STATUS_LOG,
                "fail to run command ERROR_COMMAND_ALREADY_RUNNING,%d\n",
                ack_data);
        break;
      case ERROR_COMMAND_NOT_RUNNING:
        API_LOG(api->getDriver(), STATUS_LOG,
                "fail to run command ERROR_COMMAND_NOT_RUNNING,%d\n", ack_data);
        break;
      case ERROR_COMMAND_INVAILD:
        API_LOG(api->getDriver(), STATUS_LOG,
                "fail to run command ERROR_COMMAND_INVAILD,%d\n", ack_data);
        break;
      case ERROR_COMMAND_NO_LANDING_GEAR:
        API_LOG(api->getDriver(), STATUS_LOG,
                "fail to run command ERROR_COMMAND_NO_LANDING_GEAR,%d\n",
                ack_data);
        break;
      case ERROR_COMMAND_GIMBAL_MOUNTED:
        API_LOG(api->getDriver(), STATUS_LOG,
                "fail to run command ERROR_COMMAND_GIMBAL_MOUNTED,%d\n",
                ack_data);
        break;
      case ERROR_COMMAND_BAD_SENSOR:
        API_LOG(api->getDriver(), STATUS_LOG,
                "fail to run command ERROR_COMMAND_BAD_SENSOR,%d\n", ack_data);
        break;
      case ERROR_COMMAND_ALREADY_PACKED:
        API_LOG(api->getDriver(), STATUS_LOG,
                "fail to run command ERROR_COMMAND_ALREADY_PACKED,%d\n",
                ack_data);
        break;
      case ERROR_COMMAND_NO_PACKED:
        API_LOG(api->getDriver(), STATUS_LOG,
                "fail to run command ERROR_COMMAND_NO_PACKED,%d\n", ack_data);
        break;
      case ERROR_COMMAND_PACKED_MODE_NOT_SUPPORTED:
        API_LOG(
            api->getDriver(), STATUS_LOG,
            "fail to run command ERROR_COMMAND_PACKED_MODE_NOT_SUPPORTED,%d\n",
            ack_data);
        break;
      default:
        API_LOG(api->getDriver(), STATUS_LOG,
                "fail to run command Unknown Error,%d\n", ack_data);
    }
  } else {
    API_LOG(api->getDriver(), ERROR_LOG,
            "ACK is exception,session id %d,sequence %d\n",
            protocolHeader->sessionID, protocolHeader->sequenceNumber);
  }
}

void Control::basic(Control::FlightData *data) {
  api->send(0, DJI::onboardSDK::encrypt, SET_CONTROL, CODE_CONTROL, &data,
            sizeof(FlightData));
}

void Control::advanced(Control::AdvancedFlightData *data) {
  api->send(0, DJI::onboardSDK::encrypt, SET_CONTROL, CODE_CONTROL, &data,
            sizeof(AdvancedFlightData));
}

void Control::setAPI(CoreAPI *value) { api = value; }

CoreAPI *Control::getApi() const { return api; }
