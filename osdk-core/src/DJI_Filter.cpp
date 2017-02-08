#include "DJI_Filter.h"

using namespace DJI;
using namespace DJI::onboardSDK;

Filter::Filter(CoreAPI *API) : api(API) {}

CoreAPI *Filter::getAPI() const { return api; }

void Filter::setAPI(CoreAPI *value) { api = value; }

void Filter::servicesPoll() {
  for (int i = 0; i < pollerLength; ++i) {
    if (pollerlist[i]) pollerlist[i]->service(this);
  }
}

void Filter::callbackPoll() {
  for (int i = 0; i < callbackPollerLength; ++i) {
    if (callbackPoller[i]) callbackPoller[i]->service(this);
  }
}
