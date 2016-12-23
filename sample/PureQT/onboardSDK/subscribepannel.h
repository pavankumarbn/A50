#ifndef SUBSCRIBEPANNEL_H
#define SUBSCRIBEPANNEL_H

#include <QWidget>
#include "DJI_Data.h"
#include "DJI_Database.h"

namespace Ui {
class SubscribePannel;
}

class SubscribePannel : public QWidget {
  Q_OBJECT

 public:
  explicit SubscribePannel(QWidget *parent = 0);
  ~SubscribePannel();

  void setAPI(DJI::onboardSDK::CoreAPI *API) { subscribe->setAPI(API); }

 private slots:
  void on_btn_match_clicked();
  void on_btn_reset_clicked();
  void on_btn_subscribe_clicked();
  void on_btn_remove_clicked();

 private:
  Ui::SubscribePannel *ui;

  DJI::onboardSDK::DataSubscribe *subscribe;
};

#endif  // SUBSCRIBEPANNEL_H
