#include "DJI_Data.h"

using namespace DJI;
using namespace DJI::onboardSDK;
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
 Data::RTK                 DataBroadcast::getRTKInof()            const {  api->getDriver()->lockMSG(); Data::RTK                 ans = rtk;        api->getDriver()->freeMSG();  return ans;}
 Data::Mag                 DataBroadcast::getMag()                const {  api->getDriver()->lockMSG(); Data::Mag                 ans = mag;        api->getDriver()->freeMSG();  return ans;}
 Data::RC                  DataBroadcast::getRC()                 const {  api->getDriver()->lockMSG(); Data::RC                  ans = rc;         api->getDriver()->freeMSG();  return ans;}
 Data::Gimbal              DataBroadcast::getGimbal()             const {  api->getDriver()->lockMSG(); Data::Gimbal              ans = gimbal;     api->getDriver()->freeMSG();  return ans;}
 Data::Status              DataBroadcast::getStaus()              const {  api->getDriver()->lockMSG(); Data::Status              ans = staus;      api->getDriver()->freeMSG();  return ans;}
 Data::Battery             DataBroadcast::getBatteryInfo()        const {  api->getDriver()->lockMSG(); Data::Battery             ans = battery;    api->getDriver()->freeMSG();  return ans;}
 Data::SDKInfo             DataBroadcast::getSDKInfo()            const {  api->getDriver()->lockMSG(); Data::SDKInfo             ans = info;       api->getDriver()->freeMSG();  return ans;}
// clang-format on
