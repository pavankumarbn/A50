#include "DJI_Database.h"

using namespace DJI;
using namespace DJI::onboardSDK;
using namespace DJI::onboardSDK::Data;

// clang-format off
DataClauseInfo DJI::onboardSDK::Data::DataBase[] =
{
    {Data::UID_Quaternion              , sizeof(Structure<UID_Quaternion               >::type), 200, 0, 0, 0, 0, 0},
    {Data::UID_ACCELERATION_GROUND     , sizeof(Structure<UID_ACCELERATION_GROUND      >::type), 200, 0, 0, 0, 0, 0},
    {Data::UID_ACCELERATION_BODY       , sizeof(Structure<UID_ACCELERATION_BODY        >::type), 200, 0, 0, 0, 0, 0},
    {Data::UID_ACCELERATION_RAW        , sizeof(Structure<UID_ACCELERATION_RAW         >::type), 400, 0, 0, 0, 0, 0},
    {Data::UID_VELOCITY                , sizeof(Structure<UID_VELOCITY                 >::type), 200, 0, 0, 0, 0, 0},
    {Data::UID_PALSTANCE_FUSIONED      , sizeof(Structure<UID_PALSTANCE_FUSIONED       >::type), 200, 0, 0, 0, 0, 0},
    {Data::UID_PALSTANCE_RAW           , sizeof(Structure<UID_PALSTANCE_RAW            >::type), 400, 0, 0, 0, 0, 0},
    {Data::UID_ALTITUDE_FUSIONED       , sizeof(Structure<UID_ALTITUDE_FUSIONED        >::type), 200, 0, 0, 0, 0, 0},
    {Data::UID_ALTITUDE_BAROMETER      , sizeof(Structure<UID_ALTITUDE_BAROMETER       >::type), 200, 0, 0, 0, 0, 0},
    {Data::UID_HEIGHT_HOMEPOOINT       , sizeof(Structure<UID_HEIGHT_HOMEPOOINT        >::type), 1  , 0, 0, 0, 0, 0},
    {Data::UID_HEIGHT_FUSION           , sizeof(Structure<UID_HEIGHT_FUSION            >::type), 100, 0, 0, 0, 0, 0},
    {Data::UID_GPS_DATE                , sizeof(Structure<UID_GPS_DATE                 >::type), 50 , 0, 0, 0, 0, 0},
    {Data::UID_GPS_TIME                , sizeof(Structure<UID_GPS_TIME                 >::type), 50 , 0, 0, 0, 0, 0},
    {Data::UID_GPS_POSITION            , sizeof(Structure<UID_GPS_POSITION             >::type), 50 , 0, 0, 0, 0, 0},
    {Data::UID_GPS_VELOCITY            , sizeof(Structure<UID_GPS_VELOCITY             >::type), 50 , 0, 0, 0, 0, 0},
    {Data::UID_GPS_DETAILS             , sizeof(Structure<UID_GPS_DETAILS              >::type), 50 , 0, 0, 0, 0, 0},
    {Data::UID_RTK_POSITION            , sizeof(Structure<UID_RTK_POSITION             >::type), 50 , 0, 0, 0, 0, 0},
    {Data::UID_RTK_VELOCITY            , sizeof(Structure<UID_RTK_VELOCITY             >::type), 50 , 0, 0, 0, 0, 0},
    {Data::UID_RTK_YAW                 , sizeof(Structure<UID_RTK_YAW                  >::type), 50 , 0, 0, 0, 0, 0},
    {Data::UID_RTK_POSITION_INFO       , sizeof(Structure<UID_RTK_POSITION_INFO        >::type), 50 , 0, 0, 0, 0, 0},
    {Data::UID_RTK_YAW_INFO            , sizeof(Structure<UID_RTK_YAW_INFO             >::type), 50 , 0, 0, 0, 0, 0},
    {Data::UID_COMPASS                 , sizeof(Structure<UID_COMPASS                  >::type), 100, 0, 0, 0, 0, 0},
    {Data::UID_RC                      , sizeof(Structure<UID_RC                       >::type), 50 , 0, 0, 0, 0, 0},
    {Data::UID_GIMBAL_ANGLES           , sizeof(Structure<UID_GIMBAL_ANGLES            >::type), 50 , 0, 0, 0, 0, 0},
    {Data::UID_GIMBAL_STATUS           , sizeof(Structure<UID_GIMBAL_STATUS            >::type), 50 , 0, 0, 0, 0, 0},
    {Data::UID_STATUS_FLIGHT           , sizeof(Structure<UID_STATUS_FLIGHT            >::type), 50 , 0, 0, 0, 0, 0},
    {Data::UID_STATUS_DISPLAYMODE      , sizeof(Structure<UID_STATUS_DISPLAYMODE       >::type), 50 , 0, 0, 0, 0, 0},
    {Data::UID_STATUS_LANDINGGEAR      , sizeof(Structure<UID_STATUS_LANDINGGEAR       >::type), 50 , 0, 0, 0, 0, 0},
    {Data::UID_STATUS_MOTOR_START_ERROR, sizeof(Structure<UID_STATUS_MOTOR_START_ERROR >::type), 50 , 0, 0, 0, 0, 0},
    {Data::UID_BATTERY_INFO            , sizeof(Structure<UID_BATTERY_INFO             >::type), 50 , 0, 0, 0, 0, 0},
    {Data::UID_CONTROL_DEVICE          , sizeof(Structure<UID_CONTROL_DEVICE           >::type), 50 , 0, 0, 0, 0, 0}
};
// clang-format on

const uint32_t DJI::onboardSDK::Data::DBVersion = 0x00000100;
const size_t DJI::onboardSDK::Data::toaltalClauseNumber =
    sizeof(DataBase) / sizeof(DataClauseInfo);
