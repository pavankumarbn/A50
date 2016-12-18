#include "DJI_Database.h"

using namespace DJI;
using namespace DJI::onboardSDK;
using namespace DJI::onboardSDK::Data;

// clang-format off
const DJI::onboardSDK::Data::DataClauseInfo
DJI::onboardSDK::Data::DataBase[] =
{
    {Data::UID_Quaternion              , sizeof(DataClauseInfo), 200, 0},
    {Data::UID_ACCELERATION_GROUND     , sizeof(DataClauseInfo), 200, 0},
    {Data::UID_ACCELERATION_BODY       , sizeof(DataClauseInfo), 200, 0},
    {Data::UID_ACCELERATION_RAW        , sizeof(DataClauseInfo), 400, 0},
    {Data::UID_VELOCITY                , sizeof(DataClauseInfo), 200, 0},
    {Data::UID_PALSTANCE_FUSIONED      , sizeof(DataClauseInfo), 200, 0},
    {Data::UID_PALSTANCE_RAW           , sizeof(DataClauseInfo), 400, 0},
    {Data::UID_ALTITUDE_FUSIONED       , sizeof(DataClauseInfo), 200, 0},
    {Data::UID_ALTITUDE_BAROMETER      , sizeof(DataClauseInfo), 200, 0},
    {Data::UID_HEIGHT_HOMEPOOINT       , sizeof(DataClauseInfo), 1  , 0},
    {Data::UID_HEIGHT_ULTRASONIC       , sizeof(DataClauseInfo), 100, 0},
    {Data::UID_GPS_DATE                , sizeof(DataClauseInfo), 50 , 0},
    {Data::UID_GPS_TIME                , sizeof(DataClauseInfo), 50 , 0},
    {Data::UID_GPS_POSITION            , sizeof(DataClauseInfo), 50 , 0},
    {Data::UID_GPS_VELOCITY            , sizeof(DataClauseInfo), 50 , 0},
    {Data::UID_GPS_DETAILS             , sizeof(DataClauseInfo), 50 , 0},
    {Data::UID_RTK_POSITION            , sizeof(DataClauseInfo), 50 , 0},
    {Data::UID_RTK_VELOCITY            , sizeof(DataClauseInfo), 50 , 0},
    {Data::UID_RTK_YAW                 , sizeof(DataClauseInfo), 50 , 0},
    {Data::UID_RTK_POSITION_INFO       , sizeof(DataClauseInfo), 50 , 0},
    {Data::UID_RTK_YAW_INFO            , sizeof(DataClauseInfo), 50 , 0},
    {Data::UID_COMPASS                 , sizeof(DataClauseInfo), 100, 0},
    {Data::UID_RC                      , sizeof(DataClauseInfo), 50 , 0},
    {Data::UID_GIMBAL_ANGLES           , sizeof(DataClauseInfo), 50 , 0},
    {Data::UID_GIMBAL_STATUS           , sizeof(DataClauseInfo), 50 , 0},
    {Data::UID_STATUS_FLIGHT           , sizeof(DataClauseInfo), 50 , 0},
    {Data::UID_STATUS_DISPLAYMODE      , sizeof(DataClauseInfo), 50 , 0},
    {Data::UID_STATUS_LANDINGGEAR      , sizeof(DataClauseInfo), 50 , 0},
    {Data::UID_STATUS_MOTOR_START_ERROR, sizeof(DataClauseInfo), 50 , 0},
    {Data::UID_BATTERY_INFO            , sizeof(DataClauseInfo), 50 , 0},
    {Data::UID_CONTROL_DEVICE          , sizeof(DataClauseInfo), 50 , 0}
};
//clang-format on
