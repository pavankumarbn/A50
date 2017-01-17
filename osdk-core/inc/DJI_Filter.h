#ifndef FILTER_H
#define FILTER_H

#include "DJI_API.h"

namespace DJI {
namespace onboardSDK {

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
    typedef uint16_t ID;
    typedef STATUS (*Method)(Filter*, Header*, UserData);
    typedef ERROR (*Service)(Filter*, UserData);

   public:
    Poller(ID registerID = 0, Method userMethod = 0, Service userService = 0,
           UserData data);

   private:
    const ID id;
    Method method;
    Service thread;
  };

 public:
  Filter(CoreAPI* API = 0, ID registerID = 0);

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
