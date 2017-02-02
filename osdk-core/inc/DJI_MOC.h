#ifndef MOC_H
#define MOC_H

/*! @note Mobile SDK / Onboard SDK communication API
 *
 * */

#include "DJI_API.h"

namespace DJI {
namespace onboardSDK {

class MOC {
 public:
  MOC(CoreAPI* API = 0);

  CoreAPI* getAPI() const;
  void setAPI(CoreAPI* value);

  //! @todo from mobile

 public:
  void sendToMobile(uint8_t* data, uint8_t len, CallBack callback = 0,
                    UserData userData = 0);

 private:
  static void sendToMobileCallback(CoreAPI* api, Header* protocolHeader,
                                   UserData userData = 0);

 private:
  CoreAPI* api;
};

}  // onboardSDK
}  // DJI

#endif  // MOC_H
