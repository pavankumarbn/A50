#include "DJI_Sync.h"

using namespace DJI;
using namespace DJI::onboardSDK;

HardSync::HardSync(CoreAPI *API) : api(API) {}

void HardSync::serFreq(uint32_t freqInHz, uint16_t tag) {
  SyncCmdData data;
  data.freq = freqInHz;
  data.tag = tag;
  setFreq(data);
}

void HardSync::setFreq(SyncCmdData &data) {
  api->send(0, 1, SET_SYNC, CODE_SYNC_BROADCAST, &data, sizeof(data));
}
