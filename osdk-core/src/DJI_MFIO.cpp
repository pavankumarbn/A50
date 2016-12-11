#include "DJI_MFIO.h"
#include "DJI_HardDriver.h"

using namespace DJI;
using namespace DJI::onboardSDK;

void MFIO::init(MFIO::MODE mode, CHANNEL channel, uint32_t defaultValue,
                uint16_t freq, CallBack fn, UserData userData) {
  InitData data;
  if ((channelUsage & (1 << channel)) == 0) {
    // channelUsage |= (1 << channel);
    data.port  = channel;
    data.mode  = mode;
    data.value = defaultValue;
    data.freq  = freq;
    API_LOG(api->getDriver(), STATUS_LOG, "sent");
    api->send(2, 0, SET_MFIO, 0x02, &data, sizeof(data), 500, 2,
              fn ? fn : initCallback, fn ? userData : this);
  } else {
    API_LOG(api->getDriver(), ERROR_LOG, "channel already used 0x%X,0x%X",
            channelUsage, 1 << channel);
  }
}

void MFIO::initCallback(CoreAPI *api, Header *header, UserData data) {
  API_LOG(api->getDriver(), STATUS_LOG, "callback");
}
