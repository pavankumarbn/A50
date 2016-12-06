#ifndef TEST_H
#define TEST_H

#include "DJI_API.h"

namespace DJI {
namespace onboardSDK {
class Test {
 public:
  Test(CoreAPI* API = 0);

  virtual void enterence(std::string s) = 0;

  void injectFeedback(size8_t size, char* buf);
  void injectFeedback(uint32_t data);

 public:
  static void testHook(CoreAPI* api, Header* header, UserData data);

  CoreAPI* getAPI() const;

 private:
  //! @note test setps
  void selfTest();
  void activation();

 private:
  //! @note test cases;

 private:
  CoreAPI* api;
};

}  // onboardSDK
}  // DJI

#endif  // TEST_H
