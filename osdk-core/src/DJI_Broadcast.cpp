#include "DJI_Broadcast.h"
#include "DJI_HardDriver.h"

using namespace DJI;
using namespace DJI::onboardSDK;

void DataBroadcast::callbackData(CoreAPI *api, Header *header, UserData data) {
  DataBroadcast *This = (DataBroadcast *)data;
  This->unpackData(header);
  if (This->handler.callback)
    This->handler.callback(api, header, This->handler.userData);
}

DataBroadcast::DataBroadcast(CoreAPI *API) {
  if (API) setAPI(API);
  handler.callback = 0;
  handler.userData = 0;
}

// clang-format off
Data::TimeStamp           DataBroadcast::getTimeStamp()          const {  api->getDriver()->lockMSG(); Data::TimeStamp           ans = timeStamp;  api->getDriver()->freeMSG();  return ans;}
Data::SyncStamp           DataBroadcast::getSyncStamp()          const {  api->getDriver()->lockMSG(); Data::SyncStamp           ans = syncStamp;  api->getDriver()->freeMSG();  return ans;}
Data::Quaternion          DataBroadcast::getQuaternion()         const {  api->getDriver()->lockMSG(); Data::Quaternion          ans = q;          api->getDriver()->freeMSG();  return ans;}
Data::Vector3f            DataBroadcast::getAcceleration()       const {  api->getDriver()->lockMSG(); Data::Vector3f            ans = a;          api->getDriver()->freeMSG();  return ans;}
Data::Vector3f            DataBroadcast::getVelocity()           const {  api->getDriver()->lockMSG(); Data::Vector3f            ans = v;          api->getDriver()->freeMSG();  return ans;}
Data::Vector3f            DataBroadcast::getPalstance()          const {  api->getDriver()->lockMSG(); Data::Vector3f            ans = w;          api->getDriver()->freeMSG();  return ans;}
Data::VelocityInfo        DataBroadcast::getVelocityInfo()       const {  api->getDriver()->lockMSG(); Data::VelocityInfo        ans = vi;         api->getDriver()->freeMSG();  return ans;}
Data::GlobalPosition      DataBroadcast::getGlobalPosition()     const {  api->getDriver()->lockMSG(); Data::GlobalPosition      ans = gp;         api->getDriver()->freeMSG();  return ans;}
Data::RelativePosition    DataBroadcast::getRelativePosition()   const {  api->getDriver()->lockMSG(); Data::RelativePosition    ans = rp;         api->getDriver()->freeMSG();  return ans;}
Data::GPSInfo             DataBroadcast::getGPSInfo()            const {  api->getDriver()->lockMSG(); Data::GPSInfo             ans = gps;        api->getDriver()->freeMSG();  return ans;}
Data::RTK                 DataBroadcast::getRTKInfo()            const {  api->getDriver()->lockMSG(); Data::RTK                 ans = rtk;        api->getDriver()->freeMSG();  return ans;}
Data::Mag                 DataBroadcast::getMag()                const {  api->getDriver()->lockMSG(); Data::Mag                 ans = mag;        api->getDriver()->freeMSG();  return ans;}
Data::RC                  DataBroadcast::getRC()                 const {  api->getDriver()->lockMSG(); Data::RC                  ans = rc;         api->getDriver()->freeMSG();  return ans;}
Data::Gimbal              DataBroadcast::getGimbal()             const {  api->getDriver()->lockMSG(); Data::Gimbal              ans = gimbal;     api->getDriver()->freeMSG();  return ans;}
Data::Status              DataBroadcast::getStaus()              const {  api->getDriver()->lockMSG(); Data::Status              ans = staus;      api->getDriver()->freeMSG();  return ans;}
Data::Battery             DataBroadcast::getBatteryInfo()        const {  api->getDriver()->lockMSG(); Data::Battery             ans = battery;    api->getDriver()->freeMSG();  return ans;}
Data::SDKInfo             DataBroadcast::getSDKInfo()            const {  api->getDriver()->lockMSG(); Data::SDKInfo             ans = info;       api->getDriver()->freeMSG();  return ans;}
// clang-format on

CoreAPI *DataBroadcast::getAPI() const { return api; }

void DataBroadcast::setAPI(CoreAPI *value) {
  api = value;
  api->setBroadcastCallback(callbackData, this);
}

void DataBroadcast::setBroadcastFreq(uint8_t *dataLenIs16, CallBack callback,
                                     UserData userData) {
  //! @note see also enum BROADCAST_FREQ in DJI_API.h
  for (int i = 0; i < 16; ++i) {
    dataLenIs16[i] = (dataLenIs16[i] > 7 ? 5 : dataLenIs16[i]);
  }
  api->send(2, 0, SET_ACTIVATION, CODE_FREQUENCY, dataLenIs16, 16, 100, 1,
            callback ? callback : DataBroadcast::setFrequencyCallback,
            userData);
}

void DataBroadcast::unpackData(Header *protocolHeader) {
  uint8_t *pdata = ((uint8_t *)protocolHeader) + sizeof(Header);
  pdata += 2;
  api->getDriver()->lockMSG();
  passFlag = *(uint16_t *)pdata;
  pdata += sizeof(uint16_t);
  // clang-format off
  unpackOne(FLAG_TIME        ,&timeStamp ,pdata,sizeof(timeStamp ));
  unpackOne(FLAG_TIME        ,&syncStamp ,pdata,sizeof(syncStamp ));
  unpackOne(FLAG_QUATERNION  ,&q         ,pdata,sizeof(q         ));
  unpackOne(FLAG_ACCELERATION,&a         ,pdata,sizeof(a         ));
  unpackOne(FLAG_VELOCITY    ,&v         ,pdata,sizeof(v         ));
  unpackOne(FLAG_PALSTANCE   ,&w         ,pdata,sizeof(w         ));
  unpackOne(FLAG_VELOCITY    ,&vi        ,pdata,sizeof(vi        ));
  unpackOne(FLAG_POSITION    ,&gp        ,pdata,sizeof(gp        ));
  unpackOne(FLAG_POSITION    ,&rp        ,pdata,sizeof(rp        ));
  unpackOne(FLAG_GPSINFO     ,&gps       ,pdata,sizeof(gps       ));
  unpackOne(FLAG_RTKINFO     ,&rtk       ,pdata,sizeof(rtk       ));
  unpackOne(FLAG_MAG         ,&mag       ,pdata,sizeof(mag       ));
  unpackOne(FLAG_RC          ,&rc        ,pdata,sizeof(rc        ));
  unpackOne(FLAG_GIMBAL      ,&gimbal    ,pdata,sizeof(gimbal    ));
  unpackOne(FLAG_STATUS      ,&staus     ,pdata,sizeof(staus     ));
  unpackOne(FLAG_BATTERY     ,&battery   ,pdata,sizeof(battery   ));
  unpackOne(FLAG_DEVICE      ,&info      ,pdata,sizeof(info      ));
  // clang-format on
  api->getDriver()->freeMSG();
}

void DataBroadcast::unpackOne(DataBroadcast::FLAG flag, void *data,
                              uint8_t *&buf, size_t size) {
  if (flag & passFlag) {
    memcpy((uint8_t *)data, (uint8_t *)buf, size);
    buf += size;
  }
}

void DataBroadcast::setBroadcastFreqDefaults() {
  uint8_t freq[16];
  freq[0]  = FREQ_1HZ;
  freq[1]  = FREQ_10HZ;
  freq[2]  = FREQ_50HZ;
  freq[3]  = FREQ_100HZ;
  freq[4]  = FREQ_50HZ;
  freq[5]  = FREQ_10HZ;
  freq[6]  = FREQ_0HZ;
  freq[7]  = FREQ_0HZ;
  freq[8]  = FREQ_1HZ;
  freq[9]  = FREQ_10HZ;
  freq[10] = FREQ_50HZ;
  freq[11] = FREQ_100HZ;
  freq[12] = FREQ_50HZ;
  freq[13] = FREQ_10HZ;
  setBroadcastFreq(freq);
}

void DataBroadcast::setBroadcastFreqToZero() {
  uint8_t freq[16];

  freq[0]  = FREQ_0HZ;
  freq[1]  = FREQ_0HZ;
  freq[2]  = FREQ_0HZ;
  freq[3]  = FREQ_0HZ;
  freq[4]  = FREQ_0HZ;
  freq[5]  = FREQ_0HZ;
  freq[6]  = FREQ_0HZ;
  freq[7]  = FREQ_0HZ;
  freq[8]  = FREQ_0HZ;
  freq[9]  = FREQ_0HZ;
  freq[10] = FREQ_0HZ;
  freq[11] = FREQ_0HZ;
  freq[12] = FREQ_0HZ;
  freq[13] = FREQ_0HZ;
  setBroadcastFreq(freq);
}

void DataBroadcast::setFrequencyCallback(CoreAPI *api, Header *protocolHeader,
                                         UserData userData) {
  unsigned short ack_data = ACK_COMMON_NO_RESPONSE;

  if (protocolHeader->length - CoreAPI::PackageMin <= 2) {
    memcpy((unsigned char *)&ack_data,
           ((unsigned char *)protocolHeader) + sizeof(Header),
           (protocolHeader->length - CoreAPI::PackageMin));
  }
  switch (ack_data) {
    case 0x0000:
      API_LOG(api->getDriver(), STATUS_LOG, "Frequency set successfully\n");
      break;
    case 0x0001:
      API_LOG(api->getDriver(), ERROR_LOG, "Frequency parameter error\n");
      break;
    default:
      if (!api->decodeACKStatus(ack_data)) {
        API_LOG(api->getDriver(), ERROR_LOG, "While calling this function\n");
      }
      break;
  }
}
