#include "DJI_Data.h"

using namespace DJI;
using namespace DJI::onboardSDK;

void *DataSubscribe::DataClause::getPtr() const { return ptr; }

void DataSubscribe::DataClause::setPtr(void *value) { ptr = value; }
