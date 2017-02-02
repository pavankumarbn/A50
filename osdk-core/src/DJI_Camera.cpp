/** @file DJI_Camera.cpp
 *  @version 3.1.7
 *  @date July 1st, 2016
 *
 *  @brief
 *  Camera/Gimbal API for DJI onboardSDK library
 *
 *  @copyright 2016 DJI. All rights reserved.
 *
 */

#include "DJI_Camera.h"

using namespace DJI::onboardSDK;

Camera::Camera(CoreAPI *ControlAPI) { api = ControlAPI; }

void Camera::setCamera(Camera::CAMERA_CODE camera_cmd) {
  unsigned char send_data = 0;
  api->send(0, encrypt, SET_CONTROL, camera_cmd, &send_data, 1);
}

CoreAPI *Camera::getAPI() const { return api; }

void Camera::setAPI(CoreAPI *value) { api = value; }
