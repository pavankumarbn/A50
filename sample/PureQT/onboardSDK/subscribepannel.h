#ifndef SUBSCRIBEPANNEL_H
#define SUBSCRIBEPANNEL_H

#include <QWidget>
#include "DJI_Database.h"
#include "DJI_Package.h"

namespace Ui {
class SubscribePannel;
}

class SubscribePannel : public QWidget {
  Q_OBJECT

 public:
  explicit SubscribePannel(QWidget *parent = 0);
  ~SubscribePannel();

  void setAPI(DJI::onboardSDK::CoreAPI *API);
  void display(uint32_t offset, uint32_t id);

 private slots:
  void on_btn_match_clicked();
  void on_btn_reset_clicked();
  void on_btn_subscribe_clicked();
  void on_btn_remove_clicked();
  void on_btn_pause_clicked();
  void on_btn_resume_clicked();

  static void packageUnpackCallback(
      DJI::onboardSDK::DataSubscribe::Package *pkg,
      DJI::onboardSDK::Data::TimeStamp time, DJI::UserData THIS);

 private:
  Ui::SubscribePannel *ui;

  DJI::onboardSDK::DataSubscribe *subscribe;
};

#endif  // SUBSCRIBEPANNEL_H
