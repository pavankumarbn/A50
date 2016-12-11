#ifndef MFIOPANNEL_H
#define MFIOPANNEL_H

#include <QWidget>
#include "DJI_MFIO.h"

namespace Ui {
class MFIOPannel;
}

class MFIOPannel : public QWidget {
  Q_OBJECT

 public:
  explicit MFIOPannel(QWidget *parent = 0);
  ~MFIOPannel();

  void setMfio(DJI::onboardSDK::MFIO *value);

 private slots:
  void on_btn_init_clicked();

 private:
  Ui::MFIOPannel *ui;
  DJI::onboardSDK::MFIO *mfio;
};

#endif  // MFIOPANNEL_H
