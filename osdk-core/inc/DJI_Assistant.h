#ifndef ASSISTANT_H
#define ASSISTANT_H

#include "DJI_API.h"

namespace DJI {
namespace onboardSDK {
class Assistant {
 public:
  Assistant();

 private:
  CoreAPI *api;
};

}  // onboardSDK
}  //  DJI

#endif  // ASSISTANT_H
