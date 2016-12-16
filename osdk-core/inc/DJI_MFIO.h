#ifndef MFIO_H
#define MFIO_H

#include "DJI_API.h"

namespace DJI {
namespace onboardSDK {

class MFIO {
 public:
  typedef enum MODE {
    MODE_PWM_OUT  = 0,  // PWMO
    MODE_PWM_IN   = 1,  // PWMI
    MODE_GPIO_OUT = 2,  // GPO
    MODE_GPIO_IN  = 3,  // GPI
    MODE_ADC      = 4   // ADC
  } MODE;

  typedef enum CHANNEL {
    CHANNEL_0 = 0,  //
    CHANNEL_1 = 1,
    CHANNEL_2 = 2,
    CHANNEL_3 = 3,
    CHANNEL_4 = 4,
    CHANNEL_5 = 5,
    CHANNEL_6 = 6,
    CHANNEL_7 = 7,
  } CHANNEL;

  typedef enum INIT_ERROR {
    ERROR_INIT_NONE        = 0,
    ERROR_INIT_UNKNOWN     = 1,
    ERROR_INIT_PORT_NUMBER = 2,
    ERROR_INIT_PORT_MODE   = 3,
    ERROR_INIT_PORT_DATA   = 4
  } INIT_ERROR;

  typedef enum SET_ERROR {
    ERROR_SET_NONT = 0,
    ERROR_SET_PROT = 1,  //! @note port not exit or not an output config
    ERROR_SET_MAP  = 2   //! @note port not map to f channle
  } SET_ERROR;

  MFIO(CoreAPI* API) : api(API) { channelUsage = 0; }

  void init(MODE mode, CHANNEL channel, uint32_t defaultValue, uint16_t freq,
            CallBack fn = 0, UserData userData = 0);
  void setValue(CHANNEL channel, uint32_t value, CallBack fn = 0,
                UserData data = 0);
  void getValue(CHANNEL channel, uint32_t value, CallBack fn = 0,
                UserData data = 0);

 private:
  static void initCallback(CoreAPI* api, Header* header, UserData data);
  static void setValueCallback(CoreAPI* api, Header* header, UserData data);
  static void getValueCallback(CoreAPI* api, Header* header, UserData data);

 private:
  CoreAPI* api;

  uint8_t channelUsage;

 private:
#pragma pack(1)
  typedef struct InitData {
    uint8_t port;
    uint8_t mode;
    uint32_t value;
    uint16_t freq;
  } InitData;

  typedef struct SetData {
    uint8_t port;
    uint32_t data;
  } SetData;

  typedef uint32_t GetData;

  typedef struct GetResult {
    uint8_t reserved;
    uint32_t value;
  } GetResult;

#pragma pack()
};

//! @note not decided how to use
/*class GPI {
 public:
  GPI(MFIO* io) : mfio(io) {}
  void reinit();
  void updateValue();

 private:
  MFIO* mfio;
  time_ms time;
  uint32_t value;
};

class GPO {
 public:
  GPO(MFIO* io) : mfio(io) {}
  void reinit();
  void uploadValue();

 private:
  MFIO* mfio;
};

class PWMI {
 public:
  PWMI(MFIO* io) : mfio(io) {}
  void reinit();
  void updateValue();

 private:
  MFIO* mfio;
  time_ms time;
  uint32_t value;
};

class PWMO {
 public:
  PWMO(MFIO* io) : mfio(io) {}
  void reinit();
  void uploadValue();

 private:
  MFIO* mfio;
};

class ADC {
 public:
  ADC(MFIO* io) : mfio(io) {}
  void reinit();
  void updateValue();

 private:
  MFIO* mfio;
  time_ms time;
  uint32_t value;
};*/

}  // onboardSDK
}  // DJI

#endif  // MFIO_H
