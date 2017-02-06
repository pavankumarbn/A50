#ifndef BROADCAST_H
#define BROADCAST_H

#include <QWidget>

#include "DJI_Broadcast.h"

namespace Ui {
class Broadcast;
}

class Broadcast : public QWidget {
  Q_OBJECT

 public:
  explicit Broadcast(QWidget *parent = 0);
  ~Broadcast();

 public:
  void setAPI(DJI::onboardSDK::CoreAPI *api) {
    data.setAPI(api);
    data.setBroadcastCallback(displayData, this);
  }

 public:
  static void displayData(DJI::onboardSDK::CoreAPI *api,
                          DJI::onboardSDK::Header *header, DJI::UserData data);

 private:
  void displayGlobalStamp(uint16_t flag) {}
  void displaySyncStamp(uint16_t flag) {}
  void displayQuaternion(uint16_t flag) {}
  void displayAcceleration(uint16_t flag) {}
  void displayVelocity(uint16_t flag) {}
  void displayPalstance(uint16_t flag) {}
  void displayGlobalPosition(uint16_t flag) {}
  void displayRelativePosition(uint16_t flag) {}
  void displayGPS(uint16_t flag) {}
  void displayRTK(uint16_t flag) {}
  void displayMag(uint16_t flag) {}
  void displayRC(uint16_t flag) {}
  void displayGimbal(uint16_t flag) {}
  void displayBattery(uint16_t flag) {}
  void displaySDKInfo(uint16_t flag) {}

 private:
  Ui::Broadcast *                ui;
  DJI::onboardSDK::DataBroadcast data;
};

#endif  // BROADCAST_H
