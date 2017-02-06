#include "broadcast.h"
#include <QDebug>
#include "ui_broadcast.h"

using namespace DJI;
using namespace DJI::onboardSDK;

Broadcast::Broadcast(QWidget *parent) : QWidget(parent), ui(new Ui::Broadcast) {
  ui->setupUi(this);
}

Broadcast::~Broadcast() { delete ui; }

void Broadcast::displayData(CoreAPI *api, Header *header, UserData data) {
  Broadcast *This  = (Broadcast *)data;
  uint8_t *  pdata = ((uint8_t *)header) + sizeof(Header);
  pdata += 2;
  uint16_t passFlag = *(uint16_t *)pdata;
  This->displayGlobalStamp(passFlag);
  This->displaySyncStamp(passFlag);
  This->displayQuaternion(passFlag);
  This->displayAcceleration(passFlag);
  This->displayVelocity(passFlag);
  This->displayPalstance(passFlag);
  This->displayGlobalPosition(passFlag);
  This->displayRelativePosition(passFlag);
  This->displayGPS(passFlag);
  This->displayRTK(passFlag);
  This->displayMag(passFlag);
  This->displayRC(passFlag);
  This->displayGimbal(passFlag);
  This->displayBattery(passFlag);
  This->displaySDKInfo(passFlag);
}
