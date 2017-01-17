#ifndef ASSISTANT_H
#define ASSISTANT_H

#include "DJI_API.h"

namespace DJI {
namespace onboardSDK {

//! @todo implement
class Assistant {
 public:
  typedef enum DataType {
    TYPE_UINT8_T    = 0,
    TYPE_UINT16_T   = 1,
    TYPE_UINT32_T   = 2,
    TYPE_RESERVED_3 = 3,
    TYPE_INT8_T     = 4,
    TYPE_INT15_T    = 5,
    TYPE_INT32_T    = 6,
    TYPE_RESERVED_7 = 7,
    TYPE_FLOAT32_T  = 8
  } DataType;
#pragma pack(1)
  typedef uint32_t Hash;
  typedef struct ItemInfo {
    uint16_t dataType;
    uint16_t size;
    uint16_t attribute;
    uint32_t defaultValue;
    uint32_t min;
    uint32_t max;
  } ItemInfo;
  typedef struct ItemDetail {
    ItemInfo info;
    char name[160];
  } ItemDetail;
#pragma pack()
 public:
  Assistant();

 private:
  CoreAPI* api;
};

}  // onboardSDK
}  //  DJI

#endif  // ASSISTANT_H
