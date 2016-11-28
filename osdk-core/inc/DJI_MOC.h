#ifndef MOC_H
#define MOC_H

#include "DJI_API.h"

namespace DJI {
namespace onboardSDK {

/**
 * MOS Protocol parsing lirbary functions.
 */

class MOS {
  //! @note mobile control should not be a core library feature
  /**
   * Default MOS Protocol Parser. Calls other callback functions based on data
   */
 public:
  MOS(CoreAPI *API = 0) : api(API) {
    api->setFollowCallback(parseFromMobileCallback, this);
  }
  //! Mobile Data Transparent Transmission Input Servicing
  static void parseFromMobileCallback(CoreAPI *api, Header *protocolHeader,
                                      UserData userData);

  /**
   * Mobile Callback handler functions
   */
  void setObtainControlMobileCallback(CallBackHandler callback) {
    obtainControlMobileCallback = callback;
  }
  void setReleaseControlMobileCallback(CallBackHandler callback) {
    releaseControlMobileCallback = callback;
  }
  void setActivateMobileCallback(CallBackHandler callback) {
    activateMobileCallback = callback;
  }
  void setArmMobileCallback(CallBackHandler callback) {
    armMobileCallback = callback;
  }
  void setDisArmMobileCallback(CallBackHandler callback) {
    disArmMobileCallback = callback;
  }
  void setTakeOffMobileCallback(CallBackHandler callback) {
    takeOffMobileCallback = callback;
  }
  void setLandingMobileCallback(CallBackHandler callback) {
    landingMobileCallback = callback;
  }
  void setGoHomeMobileCallback(CallBackHandler callback) {
    goHomeMobileCallback = callback;
  }
  void setTakePhotoMobileCallback(CallBackHandler callback) {
    takePhotoMobileCallback = callback;
  }
  void setStartVideoMobileCallback(CallBackHandler callback) {
    startVideoMobileCallback = callback;
  }
  void setStopVideoMobileCallback(CallBackHandler callback) {
    stopVideoMobileCallback = callback;
  }

  /** Core functions - setters */
  void setObtainControlMobileCMD(bool userInput) {
    obtainControlMobileCMD = userInput;
  }
  void setReleaseControlMobileCMD(bool userInput) {
    releaseControlMobileCMD = userInput;
  }
  void setActivateMobileCMD(bool userInput) { activateMobileCMD = userInput; }
  void setArmMobileCMD(bool userInput) { armMobileCMD = userInput; }
  void setDisArmMobileCMD(bool userInput) { disArmMobileCMD = userInput; }
  void setTakeOffMobileCMD(bool userInput) { takeOffMobileCMD = userInput; }
  void setLandingMobileCMD(bool userInput) { landingMobileCMD = userInput; }
  void setGoHomeMobileCMD(bool userInput) { goHomeMobileCMD = userInput; }
  void setTakePhotoMobileCMD(bool userInput) { takePhotoMobileCMD = userInput; }
  void setStartVideoMobileCMD(bool userInput) {
    startVideoMobileCMD = userInput;
  }
  void setStopVideoMobileCMD(bool userInput) { stopVideoMobileCMD = userInput; }

  /** Custom missions - setters */
  void setDrawCirMobileCMD(bool userInput) { drawCirMobileCMD = userInput; }
  void setDrawSqrMobileCMD(bool userInput) { drawSqrMobileCMD = userInput; }
  void setAttiCtrlMobileCMD(bool userInput) { attiCtrlMobileCMD = userInput; }
  void setGimbalCtrlMobileCMD(bool userInput) {
    gimbalCtrlMobileCMD = userInput;
  }
  void setWayPointTestMobileCMD(bool userInput) {
    wayPointTestMobileCMD = userInput;
  }
  void setLocalNavTestMobileCMD(bool userInput) {
    localNavTestMobileCMD = userInput;
  }
  void setGlobalNavTestMobileCMD(bool userInput) {
    globalNavTestMobileCMD = userInput;
  }
  void setVRCTestMobileCMD(bool userInput) { VRCTestMobileCMD = userInput; }
  void setLocalMissionPlanCMD(bool userInput) {
    localMissionPlanCMD = userInput;
  }
  /** Core functions - getters */
  bool getObtainControlMobileCMD() { return obtainControlMobileCMD; }
  bool getReleaseControlMobileCMD() { return releaseControlMobileCMD; }
  bool getActivateMobileCMD() { return activateMobileCMD; }
  bool getArmMobileCMD() { return armMobileCMD; }
  bool getDisArmMobileCMD() { return disArmMobileCMD; }
  bool getTakeOffMobileCMD() { return takeOffMobileCMD; }
  bool getLandingMobileCMD() { return landingMobileCMD; }
  bool getGoHomeMobileCMD() { return goHomeMobileCMD; }
  bool getTakePhotoMobileCMD() { return takePhotoMobileCMD; }
  bool getStartVideoMobileCMD() { return startVideoMobileCMD; }

  bool getStopVideoMobileCMD() { return stopVideoMobileCMD; }

  /** Custom missions - getters */
  bool getDrawCirMobileCMD() { return drawCirMobileCMD; }
  bool getDrawSqrMobileCMD() { return drawSqrMobileCMD; }
  bool getAttiCtrlMobileCMD() { return attiCtrlMobileCMD; }
  bool getGimbalCtrlMobileCMD() { return gimbalCtrlMobileCMD; }
  bool getWayPointTestMobileCMD() { return wayPointTestMobileCMD; }
  bool getLocalNavTestMobileCMD() { return localNavTestMobileCMD; }
  bool getGlobalNavTestMobileCMD() { return globalNavTestMobileCMD; }
  bool getVRCTestMobileCMD() { return VRCTestMobileCMD; }
  bool getLocalMissionPlanCMD() { return localMissionPlanCMD; }

 private:
  CoreAPI *api;

  CallBackHandler obtainControlMobileCallback;
  CallBackHandler releaseControlMobileCallback;
  CallBackHandler activateMobileCallback;
  CallBackHandler armMobileCallback;
  CallBackHandler disArmMobileCallback;
  CallBackHandler takeOffMobileCallback;
  CallBackHandler landingMobileCallback;
  CallBackHandler goHomeMobileCallback;
  CallBackHandler takePhotoMobileCallback;
  CallBackHandler startVideoMobileCallback;
  CallBackHandler stopVideoMobileCallback;

  //! Mobile Data Transparent Transmission - flags

  bool obtainControlMobileCMD;
  bool releaseControlMobileCMD;
  bool activateMobileCMD;
  bool armMobileCMD;
  bool disArmMobileCMD;
  bool takeOffMobileCMD;
  bool landingMobileCMD;
  bool goHomeMobileCMD;
  bool takePhotoMobileCMD;
  bool startVideoMobileCMD;
  bool stopVideoMobileCMD;

  bool drawCirMobileCMD;
  bool drawSqrMobileCMD;
  bool attiCtrlMobileCMD;
  bool gimbalCtrlMobileCMD;
  bool wayPointTestMobileCMD;
  bool localNavTestMobileCMD;
  bool globalNavTestMobileCMD;
  bool VRCTestMobileCMD;
  bool localMissionPlanCMD;
};

}  // namespace onboarSDK
}  // namespace DJI

#endif  // MOC_H
