#ifndef FILTER_H
#define FILTER_H

#include "DJI_API.h"

namespace DJI {
namespace onboardSDK {

//! @todo refactor functionality part, used to replace appHandler's
//! implementation
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

  class Poller {
   public:
    friend class Filter;

    typedef uint16_t ID;
    typedef STATUS (*Method)(Filter*, Header*, UserData);
    typedef ERROR (*Service)(Filter*, UserData);

   public:
    Poller(ID registerID = 0, Method userMethod = 0, Service userService = 0,
           UserData userData = 0)
        : id(registerID),
          method(userMethod),
          service(userService),
          data(userData) {}

    template <typename T>
    T getData() const {
      return data;
    }

   private:
    const ID id;
    Method method;
    Service service;
    UserData data;
  };

 public:
  Filter(CoreAPI* API = 0);

  Order registerFilter(Poller* poller);

  CoreAPI* getAPI() const;
  void setAPI(CoreAPI* value);

 protected:
  CoreAPI* api;
  Poller* pollerlist;
  size_t pollerLength;
};

}  // onboardSDK
}  // DJI
#endif  // FILTER_H
