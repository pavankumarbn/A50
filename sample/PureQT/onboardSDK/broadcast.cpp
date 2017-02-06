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
  qDebug() << "start display";
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
  qDebug() << "finish display";
}

void Broadcast::displayGlobalStamp(uint16_t flag) {
  if (flag & DataBroadcast::FLAG_TIME) {
    Data::TimeStamp t = data.getTimeStamp();
    ui->le_gt_2p5ms->setText(QString("%1").arg(t.time_2p5ms));
    ui->le_gt_ns->setText(QString("%1").arg(t.time_ns));
  }
}

void Broadcast::displaySyncStamp(uint16_t flag) {
  if (flag & DataBroadcast::FLAG_TIME) {
    Data::SyncStamp t = data.getSyncStamp();
    ui->le_st_2p5ms->setText(QString("%1").arg(t.time_2p5ms));
    ui->le_st_tag->setText(QString("%1").arg(t.tag));
    ui->le_st_flag->setText(QString("%1").arg(t.flag));
  }
}
