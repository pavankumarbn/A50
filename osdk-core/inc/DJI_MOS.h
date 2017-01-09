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
  MOS(CoreAPI *API = 0);
  //! Mobile Data Transparent Transmission Input Servicing
  static void parseFromMobileCallback(CoreAPI *api, Header *protocolHeader,
                                      UserData userData);

  /**
   * Mobile Callback handler functions
   */
  void setObtainControlMobileCallback(CallBackHandler callback);
  void setReleaseControlMobileCallback(CallBackHandler callback);
  void setActivateMobileCallback(CallBackHandler callback);
  void setArmMobileCallback(CallBackHandler callback);
  void setDisArmMobileCallback(CallBackHandler callback);
  void setTakeOffMobileCallback(CallBackHandler callback);
  void setLandingMobileCallback(CallBackHandler callback);
  void setGoHomeMobileCallback(CallBackHandler callback);
  void setTakePhotoMobileCallback(CallBackHandler callback);
  void setStartVideoMobileCallback(CallBackHandler callback);
  void setStopVideoMobileCallback(CallBackHandler callback);

  /** Core functions - setters */
  void setObtainControlMobileCMD(bool userInput);
  void setReleaseControlMobileCMD(bool userInput);
  void setActivateMobileCMD(bool userInput);
  void setArmMobileCMD(bool userInput);
  void setDisArmMobileCMD(bool userInput);
  void setTakeOffMobileCMD(bool userInput);
  void setLandingMobileCMD(bool userInput);
  void setGoHomeMobileCMD(bool userInput);
  void setTakePhotoMobileCMD(bool userInput);
  void setStartVideoMobileCMD(bool userInput);
  void setStopVideoMobileCMD(bool userInput);

  /** Custom missions - setters */
  void setDrawCirMobileCMD(bool userInput);
  void setDrawSqrMobileCMD(bool userInput);
  void setAttiCtrlMobileCMD(bool userInput);
  void setGimbalCtrlMobileCMD(bool userInput);
  void setWayPointTestMobileCMD(bool userInput);
  void setLocalNavTestMobileCMD(bool userInput);
  void setGlobalNavTestMobileCMD(bool userInput);
  void setVRCTestMobileCMD(bool userInput);
  void setLocalMissionPlanCMD(bool userInput);
  /** Core functions - getters */
  bool getObtainControlMobileCMD();
  bool getReleaseControlMobileCMD();
  bool getActivateMobileCMD();
  bool getArmMobileCMD();
  bool getDisArmMobileCMD();
  bool getTakeOffMobileCMD();
  bool getLandingMobileCMD();
  bool getGoHomeMobileCMD();
  bool getTakePhotoMobileCMD();
  bool getStartVideoMobileCMD();

  bool getStopVideoMobileCMD();

  /** Custom missions - getters */
  bool getDrawCirMobileCMD();
  bool getDrawSqrMobileCMD();
  bool getAttiCtrlMobileCMD();
  bool getGimbalCtrlMobileCMD();
  bool getWayPointTestMobileCMD();
  bool getLocalNavTestMobileCMD();
  bool getGlobalNavTestMobileCMD();
  bool getVRCTestMobileCMD();
  bool getLocalMissionPlanCMD();

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
