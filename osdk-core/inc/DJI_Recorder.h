#ifndef RECORDER_H
#define RECORDER_H
#include "DJI_API.h"

namespace DJI {
namespace onboardSDK {
class Recorder {
 public:
#pragma pack(1)
  typedef struct Frame {
    uint16_t id;
    uint16_t len;
    uint8_t data[128];
  } Frame;
#pragma pack
 public:
  Recorder(CoreAPI* API = 0) : api(API) {}

  void record(uint16_t id, size8_t len_max128Byte, uint8_t* buffer);

 private:
  CoreAPI* api;
};

}  // onboardSDK
}  // DJI

#endif  // RECORDER_H
