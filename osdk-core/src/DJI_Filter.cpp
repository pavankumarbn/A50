#include "DJI_Filter.h"

using namespace DJI;
using namespace DJI::onboardSDK;

Filter::Filter(CoreAPI *API) : api(API) {}

CoreAPI *Filter::getAPI() const { return api; }

void Filter::setAPI(CoreAPI *value) { api = value; }
