#ifndef FILTER_H
#define FILTER_H

#include "DJI_API.h"

namespace DJI {
namespace onboardSDK {

//! @todo refactory funtionality part, used to replace appHandler's
//! implementation
class Poller;

class Filter {
 public:
  typedef uint8_t Order;
  typedef enum STATUS {
    STATUS_TAKE,
    STATUS_ACCEPT,
    STATUS_ERROR_INPUT,
    STATUS_ACCEPT_WITH_ERROR  // Accept with error
  } STATUS;

  typedef enum ERROR {
    ERROR_NONE,
    ERROR_INTERNAL,

  } ERROR;

 public:
  Filter(CoreAPI* API = 0);

  Order registerFilter(Poller* poller);

  CoreAPI* getAPI() const;
  void setAPI(CoreAPI* value);

 protected:
  CoreAPI* api;
  Poller*  pollerlist;
  size_t   pollerLength;
};

class Poller {
 public:
  friend class Filter;

  typedef uint16_t ID;

 public:
  Poller(ID registerID = 0, UserData userData = 0)
      : id(registerID), data(userData) {}

  template <typename T>
  T getData() const {
    return data;
  }

 private:
  virtual Filter::STATUS method(Filter* filter, Header* header);
  virtual Filter::ERROR service(Filter* filter);

 private:
  const ID id;
  UserData data;
};

}  // onboardSDK
}  // DJI
#endif  // FILTER_H
