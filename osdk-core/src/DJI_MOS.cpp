#include "DJI_MOS.h"

using namespace DJI;
using namespace DJI::onboardSDK;

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
