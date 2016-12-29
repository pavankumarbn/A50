#ifndef CONTROLPANNEL_H
#define CONTROLPANNEL_H

#include <QWidget>
#include "DJI_Control.h"

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
  void on_btn_control_clicked(bool checked);

 public:
  static void setControlCallback(DJI::onboardSDK::CoreAPI *This,
                                 DJI::onboardSDK::Header *header,
                                 DJI::UserData userData);

 private:
  Ui::ControlPannel *ui;
  DJI::onboardSDK::Control *controler;
};

#endif  // CONTROLPANNEL_H
