#include "DJI_Control.h"
#include "DJI_HardDriver.h"

#include <string.h>

using namespace DJI;
using namespace DJI::onboardSDK;

Control::Control(CoreAPI *API) : api(API) {}

CoreAPI *Control::getAPI() const { return api; }

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
                                 UserData userData) {
  unsigned short ack_data = ACK_COMMON_NO_RESPONSE;
  unsigned char data      = 0x1;

  if (protocolHeader->length - CoreAPI::PackageMin <= sizeof(ack_data)) {
    memcpy((unsigned char *)&ack_data,
           ((unsigned char *)protocolHeader) + sizeof(Header),
           (protocolHeader->length - CoreAPI::PackageMin));
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
                &data, sizeof(data), 500, 2, Control::setControlCallback);
      break;
    case ACK_SETCONTROL_RELEASE_RUNNING:
      API_LOG(api->getDriver(), STATUS_LOG, "Release control running\n");
      data = 0;
      api->send(2, DJI::onboardSDK::encrypt, SET_CONTROL, CODE_SETCONTROL,
                &data, sizeof(data), 500, 2, Control::setControlCallback);
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
                              UserData userData) {
  unsigned short ack_data;
  if (protocolHeader->length - CoreAPI::PackageMin <= 2) {
    memcpy((unsigned char *)&ack_data,
           ((unsigned char *)protocolHeader) + sizeof(Header),
           (protocolHeader->length - CoreAPI::PackageMin));
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
        API_LOG(api->getDriver(), STATUS_LOG,
                "fail to run command "
                "ERROR_COMMAND_PACKED_MODE_NOT_SUPPORTED,%d\n",
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
