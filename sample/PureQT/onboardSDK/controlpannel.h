#ifndef CONTROLPANNEL_H
#define CONTROLPANNEL_H

#include <QWidget>
#include "DJI_Flight.h"

namespace Ui {
class ControlPannel;
}

class ControlPannel : public QWidget {
  Q_OBJECT

 public:
  explicit ControlPannel(QWidget *parent = 0);
  ~ControlPannel();

  void setAPI(DJI::onboardSDK::CoreAPI *api);

 private slots:
  void on_btn_flight_runCommand_clicked();

 private:
  Ui::ControlPannel *ui;
  DJI::onboardSDK::Control *controler;
};

#endif  // CONTROLPANNEL_H
