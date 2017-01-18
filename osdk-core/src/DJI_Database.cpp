#include "DJI_Database.h"

using namespace DJI;
using namespace DJI::onboardSDK;
using namespace DJI::onboardSDK::Data;

// clang-format off
//DataClauseInfo DJI::onboardSDK::Data::HistoricalDataBase[] =
//{

//};

DataClauseInfo DJI::onboardSDK::Data::DataBase[] =
{
    {Data::UID_Quaternion              , sizeof(Structure<UID_Quaternion               >::type), Structure<UID_Quaternion              >::offset, 200, 0, 0, 0, 0, 0},
    {Data::UID_ACCELERATION_GROUND     , sizeof(Structure<UID_ACCELERATION_GROUND      >::type), Structure<UID_ACCELERATION_GROUND     >::offset, 200, 0, 0, 0, 0, 0},
    {Data::UID_ACCELERATION_BODY       , sizeof(Structure<UID_ACCELERATION_BODY        >::type), Structure<UID_ACCELERATION_BODY       >::offset, 200, 0, 0, 0, 0, 0},
    {Data::UID_ACCELERATION_RAW        , sizeof(Structure<UID_ACCELERATION_RAW         >::type), Structure<UID_ACCELERATION_RAW        >::offset, 400, 0, 0, 0, 0, 0},
    {Data::UID_VELOCITY                , sizeof(Structure<UID_VELOCITY                 >::type), Structure<UID_VELOCITY                >::offset, 200, 0, 0, 0, 0, 0},
    {Data::UID_PALSTANCE_FUSIONED      , sizeof(Structure<UID_PALSTANCE_FUSIONED       >::type), Structure<UID_PALSTANCE_FUSIONED      >::offset, 200, 0, 0, 0, 0, 0},
    {Data::UID_PALSTANCE_RAW           , sizeof(Structure<UID_PALSTANCE_RAW            >::type), Structure<UID_PALSTANCE_RAW           >::offset, 400, 0, 0, 0, 0, 0},
    {Data::UID_ALTITUDE_FUSIONED       , sizeof(Structure<UID_ALTITUDE_FUSIONED        >::type), Structure<UID_ALTITUDE_FUSIONED       >::offset, 200, 0, 0, 0, 0, 0},
    {Data::UID_ALTITUDE_BAROMETER      , sizeof(Structure<UID_ALTITUDE_BAROMETER       >::type), Structure<UID_ALTITUDE_BAROMETER      >::offset, 200, 0, 0, 0, 0, 0},
    {Data::UID_HEIGHT_HOMEPOOINT       , sizeof(Structure<UID_HEIGHT_HOMEPOOINT        >::type), Structure<UID_HEIGHT_HOMEPOOINT       >::offset, 1  , 0, 0, 0, 0, 0},
    {Data::UID_HEIGHT_FUSION           , sizeof(Structure<UID_HEIGHT_FUSION            >::type), Structure<UID_HEIGHT_FUSION           >::offset, 100, 0, 0, 0, 0, 0},
    {Data::UID_GPS_DATE                , sizeof(Structure<UID_GPS_DATE                 >::type), Structure<UID_GPS_DATE                >::offset, 50 , 0, 0, 0, 0, 0},
    {Data::UID_GPS_TIME                , sizeof(Structure<UID_GPS_TIME                 >::type), Structure<UID_GPS_TIME                >::offset, 50 , 0, 0, 0, 0, 0},
    {Data::UID_GPS_POSITION            , sizeof(Structure<UID_GPS_POSITION             >::type), Structure<UID_GPS_POSITION            >::offset, 50 , 0, 0, 0, 0, 0},
    {Data::UID_GPS_VELOCITY            , sizeof(Structure<UID_GPS_VELOCITY             >::type), Structure<UID_GPS_VELOCITY            >::offset, 50 , 0, 0, 0, 0, 0},
    {Data::UID_GPS_DETAILS             , sizeof(Structure<UID_GPS_DETAILS              >::type), Structure<UID_GPS_DETAILS             >::offset, 50 , 0, 0, 0, 0, 0},
    {Data::UID_RTK_POSITION            , sizeof(Structure<UID_RTK_POSITION             >::type), Structure<UID_RTK_POSITION            >::offset, 50 , 0, 0, 0, 0, 0},
    {Data::UID_RTK_VELOCITY            , sizeof(Structure<UID_RTK_VELOCITY             >::type), Structure<UID_RTK_VELOCITY            >::offset, 50 , 0, 0, 0, 0, 0},
    {Data::UID_RTK_YAW                 , sizeof(Structure<UID_RTK_YAW                  >::type), Structure<UID_RTK_YAW                 >::offset, 50 , 0, 0, 0, 0, 0},
    {Data::UID_RTK_POSITION_INFO       , sizeof(Structure<UID_RTK_POSITION_INFO        >::type), Structure<UID_RTK_POSITION_INFO       >::offset, 50 , 0, 0, 0, 0, 0},
    {Data::UID_RTK_YAW_INFO            , sizeof(Structure<UID_RTK_YAW_INFO             >::type), Structure<UID_RTK_YAW_INFO            >::offset, 50 , 0, 0, 0, 0, 0},
    {Data::UID_COMPASS                 , sizeof(Structure<UID_COMPASS                  >::type), Structure<UID_COMPASS                 >::offset, 100, 0, 0, 0, 0, 0},
    {Data::UID_RC                      , sizeof(Structure<UID_RC                       >::type), Structure<UID_RC                      >::offset, 50 , 0, 0, 0, 0, 0},
    {Data::UID_GIMBAL_ANGLES           , sizeof(Structure<UID_GIMBAL_ANGLES            >::type), Structure<UID_GIMBAL_ANGLES           >::offset, 50 , 0, 0, 0, 0, 0},
    {Data::UID_GIMBAL_STATUS           , sizeof(Structure<UID_GIMBAL_STATUS            >::type), Structure<UID_GIMBAL_STATUS           >::offset, 50 , 0, 0, 0, 0, 0},
    {Data::UID_STATUS_FLIGHT           , sizeof(Structure<UID_STATUS_FLIGHT            >::type), Structure<UID_STATUS_FLIGHT           >::offset, 50 , 0, 0, 0, 0, 0},
    {Data::UID_STATUS_DISPLAYMODE      , sizeof(Structure<UID_STATUS_DISPLAYMODE       >::type), Structure<UID_STATUS_DISPLAYMODE      >::offset, 50 , 0, 0, 0, 0, 0},
    {Data::UID_STATUS_LANDINGGEAR      , sizeof(Structure<UID_STATUS_LANDINGGEAR       >::type), Structure<UID_STATUS_LANDINGGEAR      >::offset, 50 , 0, 0, 0, 0, 0},
    {Data::UID_STATUS_MOTOR_START_ERROR, sizeof(Structure<UID_STATUS_MOTOR_START_ERROR >::type), Structure<UID_STATUS_MOTOR_START_ERROR>::offset, 50 , 0, 0, 0, 0, 0},
    {Data::UID_BATTERY_INFO            , sizeof(Structure<UID_BATTERY_INFO             >::type), Structure<UID_BATTERY_INFO            >::offset, 50 , 0, 0, 0, 0, 0},
    {Data::UID_CONTROL_DEVICE          , sizeof(Structure<UID_CONTROL_DEVICE           >::type), Structure<UID_CONTROL_DEVICE          >::offset, 50 , 0, 0, 0, 0, 0}
};
// clang-format on

const uint32_t DJI::onboardSDK::Data::DBVersion = 0x00000100;
const size_t DJI::onboardSDK::Data::toaltalClauseNumber =
    sizeof(DataBase) / sizeof(DataClauseInfo);
