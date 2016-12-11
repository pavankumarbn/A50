#include "DJI_Recorder.h"
#include <string.h>

using namespace DJI::onboardSDK;
using namespace DJI;

void Recorder::record(uint16_t id, size8_t len_max128Byte, uint8_t *buffer) {
  Frame data;
  data.id  = id;
  data.len = len_max128Byte;
  memcpy(&data.data, buffer, len_max128Byte);
  api->send(1, 0, SET_RECORDER, 0x05, &data, 4 + len_max128Byte);
}
