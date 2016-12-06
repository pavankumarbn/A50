#ifndef HARDSYNC_H
#define HARDSYNC_H

#include "DJI_API.h"

namespace DJI {
namespace onboardSDK {

class HardSync {
 public:
  HardSync(CoreAPI* API = 0);

  void serFreq(uint32_t freqInHz, uint16_t tag = 0);
  void setFreq(SyncCmdData& data);

 private:
  CoreAPI* api;
};
}  // onboardSDK
}  // DJI

#endif  // HARDSYNC_H
