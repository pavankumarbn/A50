#ifndef BROADCAST_H
#define BROADCAST_H

#include <QWidget>

#include "DJI_Data.h"
namespace Ui {
class Broadcast;
}

class Broadcast : public QWidget {
  Q_OBJECT

 public:
  explicit Broadcast(QWidget *parent = 0);
  ~Broadcast();

 public:
  void setAPI(DJI::onboardSDK::CoreAPI *api) { data.setAPI(api); }

 private:
  Ui::Broadcast *ui;
  DJI::onboardSDK::DataBroadcast data;
};

#endif  // BROADCAST_H
