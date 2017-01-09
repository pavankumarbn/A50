#include "DJI_MOS.h"

using namespace DJI;
using namespace DJI::onboardSDK;

MOS::MOS(CoreAPI *API) : api(API) {
  api->setFollowCallback(parseFromMobileCallback, this);
}

void MOS::parseFromMobileCallback(CoreAPI *api, Header *protocolHeader,
                                  UserData userData) {
  MOS *This = (MOS *)userData;
  uint16_t mobile_data_id;

  if (protocolHeader->length - CoreAPI::PackageMin <= 4) {
    mobile_data_id = *((unsigned char *)protocolHeader + sizeof(Header) + 2);

    switch (mobile_data_id) {
      case 2:
        if (This->obtainControlMobileCallback.callback) {
          This->obtainControlMobileCallback.callback(
              api, protocolHeader, This->obtainControlMobileCallback.userData);
        } else {
          This->obtainControlMobileCMD = true;
        }
        break;

      case 3:
        if (This->releaseControlMobileCallback.callback) {
          This->releaseControlMobileCallback.callback(
              api, protocolHeader, This->releaseControlMobileCallback.userData);
        } else {
          This->releaseControlMobileCMD = true;
        }
        break;

      case 4:
        if (This->activateMobileCallback.callback) {
          This->activateMobileCallback.callback(
              api, protocolHeader, This->activateMobileCallback.userData);
        } else {
          This->activateMobileCMD = true;
        }
        break;

      case 5:
        if (This->armMobileCallback.callback) {
          This->armMobileCallback.callback(api, protocolHeader,
                                           This->armMobileCallback.userData);
        } else {
          This->armMobileCMD = true;
        }
        break;

      case 6:
        if (This->disArmMobileCallback.callback) {
          This->disArmMobileCallback.callback(
              api, protocolHeader, This->disArmMobileCallback.userData);
        } else {
          This->disArmMobileCMD = true;
        }
        break;

      case 7:
        if (This->takeOffMobileCallback.callback) {
          This->takeOffMobileCallback.callback(
              api, protocolHeader, This->takeOffMobileCallback.userData);
        } else {
          This->takeOffMobileCMD = true;
        }
        break;

      case 8:
        if (This->landingMobileCallback.callback) {
          This->landingMobileCallback.callback(
              api, protocolHeader, This->landingMobileCallback.userData);
        } else {
          This->landingMobileCMD = true;
        }
        break;

      case 9:
        if (This->goHomeMobileCallback.callback) {
          This->goHomeMobileCallback.callback(
              api, protocolHeader, This->goHomeMobileCallback.userData);
        } else {
          This->goHomeMobileCMD = true;
        }
        break;

      case 10:
        if (This->takePhotoMobileCallback.callback) {
          This->takePhotoMobileCallback.callback(
              api, protocolHeader, This->takePhotoMobileCallback.userData);
        } else {
          This->takePhotoMobileCMD = true;
        }
        break;

      case 11:
        if (This->startVideoMobileCallback.callback) {
          This->startVideoMobileCallback.callback(
              api, protocolHeader, This->startVideoMobileCallback.userData);
        } else {
          This->startVideoMobileCMD = true;
        }
        break;

      case 13:
        if (This->stopVideoMobileCallback.callback) {
          This->stopVideoMobileCallback.callback(
              api, protocolHeader, This->stopVideoMobileCallback.userData);
        } else {
          This->stopVideoMobileCMD = true;
        }
        break;
      //! The next few are only polling based and do not use callbacks. See
      //! usage in Linux Sample.
      case 61:
        This->drawCirMobileCMD = true;
        break;
      case 62:
        This->drawSqrMobileCMD = true;
        break;
      case 63:
        This->attiCtrlMobileCMD = true;
        break;
      case 64:
        This->gimbalCtrlMobileCMD = true;
        break;
      case 65:
        This->wayPointTestMobileCMD = true;
        break;
      case 66:
        This->localNavTestMobileCMD = true;
        break;
      case 67:
        This->globalNavTestMobileCMD = true;
        break;
      case 68:
        This->VRCTestMobileCMD = true;
        break;
      case 69:
        This->localMissionPlanCMD = true;
        break;
    }
  }
}

void MOS::setObtainControlMobileCallback(CallBackHandler callback) {
  obtainControlMobileCallback = callback;
}

void MOS::setReleaseControlMobileCallback(CallBackHandler callback) {
  releaseControlMobileCallback = callback;
}

void MOS::setActivateMobileCallback(CallBackHandler callback) {
  activateMobileCallback = callback;
}

void MOS::setArmMobileCallback(CallBackHandler callback) {
  armMobileCallback = callback;
}

void MOS::setDisArmMobileCallback(CallBackHandler callback) {
  disArmMobileCallback = callback;
}

void MOS::setTakeOffMobileCallback(CallBackHandler callback) {
  takeOffMobileCallback = callback;
}

void MOS::setLandingMobileCallback(CallBackHandler callback) {
  landingMobileCallback = callback;
}

void MOS::setGoHomeMobileCallback(CallBackHandler callback) {
  goHomeMobileCallback = callback;
}

void MOS::setTakePhotoMobileCallback(CallBackHandler callback) {
  takePhotoMobileCallback = callback;
}

void MOS::setStartVideoMobileCallback(CallBackHandler callback) {
  startVideoMobileCallback = callback;
}

void MOS::setStopVideoMobileCallback(CallBackHandler callback) {
  stopVideoMobileCallback = callback;
}

void MOS::setObtainControlMobileCMD(bool userInput) {
  obtainControlMobileCMD = userInput;
}

void MOS::setReleaseControlMobileCMD(bool userInput) {
  releaseControlMobileCMD = userInput;
}

void MOS::setActivateMobileCMD(bool userInput) {
  activateMobileCMD = userInput;
}

void MOS::setArmMobileCMD(bool userInput) { armMobileCMD = userInput; }

void MOS::setDisArmMobileCMD(bool userInput) { disArmMobileCMD = userInput; }

void MOS::setTakeOffMobileCMD(bool userInput) { takeOffMobileCMD = userInput; }

void MOS::setLandingMobileCMD(bool userInput) { landingMobileCMD = userInput; }

void MOS::setGoHomeMobileCMD(bool userInput) { goHomeMobileCMD = userInput; }

void MOS::setTakePhotoMobileCMD(bool userInput) {
  takePhotoMobileCMD = userInput;
}

void MOS::setStartVideoMobileCMD(bool userInput) {
  startVideoMobileCMD = userInput;
}

void MOS::setStopVideoMobileCMD(bool userInput) {
  stopVideoMobileCMD = userInput;
}

void MOS::setDrawCirMobileCMD(bool userInput) { drawCirMobileCMD = userInput; }

void MOS::setDrawSqrMobileCMD(bool userInput) { drawSqrMobileCMD = userInput; }

void MOS::setAttiCtrlMobileCMD(bool userInput) {
  attiCtrlMobileCMD = userInput;
}

void MOS::setGimbalCtrlMobileCMD(bool userInput) {
  gimbalCtrlMobileCMD = userInput;
}

void MOS::setWayPointTestMobileCMD(bool userInput) {
  wayPointTestMobileCMD = userInput;
}

void MOS::setLocalNavTestMobileCMD(bool userInput) {
  localNavTestMobileCMD = userInput;
}

void MOS::setGlobalNavTestMobileCMD(bool userInput) {
  globalNavTestMobileCMD = userInput;
}

void MOS::setVRCTestMobileCMD(bool userInput) { VRCTestMobileCMD = userInput; }

void MOS::setLocalMissionPlanCMD(bool userInput) {
  localMissionPlanCMD = userInput;
}

bool MOS::getObtainControlMobileCMD() { return obtainControlMobileCMD; }

bool MOS::getReleaseControlMobileCMD() { return releaseControlMobileCMD; }

bool MOS::getActivateMobileCMD() { return activateMobileCMD; }

bool MOS::getArmMobileCMD() { return armMobileCMD; }

bool MOS::getDisArmMobileCMD() { return disArmMobileCMD; }

bool MOS::getTakeOffMobileCMD() { return takeOffMobileCMD; }

bool MOS::getLandingMobileCMD() { return landingMobileCMD; }

bool MOS::getGoHomeMobileCMD() { return goHomeMobileCMD; }

bool MOS::getTakePhotoMobileCMD() { return takePhotoMobileCMD; }

bool MOS::getStartVideoMobileCMD() { return startVideoMobileCMD; }

bool MOS::getStopVideoMobileCMD() { return stopVideoMobileCMD; }

bool MOS::getDrawCirMobileCMD() { return drawCirMobileCMD; }

bool MOS::getDrawSqrMobileCMD() { return drawSqrMobileCMD; }

bool MOS::getAttiCtrlMobileCMD() { return attiCtrlMobileCMD; }

bool MOS::getGimbalCtrlMobileCMD() { return gimbalCtrlMobileCMD; }

bool MOS::getWayPointTestMobileCMD() { return wayPointTestMobileCMD; }

bool MOS::getLocalNavTestMobileCMD() { return localNavTestMobileCMD; }

bool MOS::getGlobalNavTestMobileCMD() { return globalNavTestMobileCMD; }

bool MOS::getVRCTestMobileCMD() { return VRCTestMobileCMD; }

bool MOS::getLocalMissionPlanCMD() { return localMissionPlanCMD; }
