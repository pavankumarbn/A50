#include "subscribepannel.h"
#include "ui_subscribepannel.h"

#include <QDebug>
#include <QTableWidget>

#define INLINE_NAME(X) #X

using namespace DJI::onboardSDK;

SubscribePannel::SubscribePannel(QWidget *parent)
    : QWidget(parent), ui(new Ui::SubscribePannel) {
  ui->setupUi(this);
  subscribe = new DataSubscribe();
  ui->cb_version->addItem(QString("%1.%2.%3.%4")
                              .arg(Data::DBVersion >> 24, 0, 16)
                              .arg((Data::DBVersion >> 16) & 0xFF, 0, 16)
                              .arg((Data::DBVersion >> 8) & 0xFF, 0, 16)
                              .arg((Data::DBVersion)&0xFF, 0, 16));

  //! @note init table;
  ui->tableWidget->setColumnCount(subscribe->maxPakcageNumber + 2);
  ui->tableWidget->setRowCount(Data::toaltalClauseNumber + 2);

  for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
    for (int j = 0; j < ui->tableWidget->columnCount(); ++j) {
      QTableWidgetItem *t = new QTableWidgetItem();
      if (j == 0 && i == 0) t->setText("Name");
      if (j == 0 && i == 1) t->setText("Frequency");
      if (j == 0 && i > 1) {
        switch (i - 2) {
          // clang-format off
            case 0  :t->setText(INLINE_NAME(Quaternion                ));  break;
            case 1  :t->setText(INLINE_NAME(ACCELERATION_GROUND       ));  break;
            case 2  :t->setText(INLINE_NAME(ACCELERATION_BODY         ));  break;
            case 3  :t->setText(INLINE_NAME(ACCELERATION_RAW          ));  break;
            case 4  :t->setText(INLINE_NAME(VELOCITY                  ));  break;
            case 5  :t->setText(INLINE_NAME(PALSTANCE_FUSIONED        ));  break;
            case 6  :t->setText(INLINE_NAME(PALSTANCE_RAW             ));  break;
            case 7  :t->setText(INLINE_NAME(ALTITUDE_FUSIONED         ));  break;
            case 8  :t->setText(INLINE_NAME(ALTITUDE_BAROMETER        ));  break;
            case 9  :t->setText(INLINE_NAME(HEIGHT_HOMEPOOINT         ));  break;
            case 10 :t->setText(INLINE_NAME(HEIGHT_FUSION             ));  break;
            case 11 :t->setText(INLINE_NAME(GPS_DATE                  ));  break;
            case 12 :t->setText(INLINE_NAME(GPS_TIME                  ));  break;
            case 13 :t->setText(INLINE_NAME(GPS_POSITION              ));  break;
            case 14 :t->setText(INLINE_NAME(GPS_VELOCITY              ));  break;
            case 15 :t->setText(INLINE_NAME(GPS_DETAILS               ));  break;
            case 16 :t->setText(INLINE_NAME(RTK_POSITION              ));  break;
            case 17 :t->setText(INLINE_NAME(RTK_VELOCITY              ));  break;
            case 18 :t->setText(INLINE_NAME(RTK_YAW                   ));  break;
            case 19 :t->setText(INLINE_NAME(RTK_POSITION_INFO         ));  break;
            case 20 :t->setText(INLINE_NAME(RTK_YAW_INFO              ));  break;
            case 21 :t->setText(INLINE_NAME(COMPASS                   ));  break;
            case 22 :t->setText(INLINE_NAME(RC                        ));  break;
            case 23 :t->setText(INLINE_NAME(GIMBAL_ANGLES             ));  break;
            case 24 :t->setText(INLINE_NAME(GIMBAL_STATUS             ));  break;
            case 25 :t->setText(INLINE_NAME(STATUS_FLIGHT             ));  break;
            case 26 :t->setText(INLINE_NAME(STATUS_DISPLAYMODE        ));  break;
            case 27 :t->setText(INLINE_NAME(STATUS_LANDINGGEAR        ));  break;
            case 28 :t->setText(INLINE_NAME(STATUS_MOTOR_START_ERROR  ));  break;
            case 29 :t->setText(INLINE_NAME(BATTERY_INFO              ));  break;
            case 30 :t->setText(INLINE_NAME(CONTROL_DEVICE            ));  break;
            // clang-format on
        }
      }
      if (j == 1 && i == 0) t->setText(QString("Total"));
      if (j > 1 && i > 1) t->setCheckState(Qt::Unchecked);
      if (j > 1 && i == 0) t->setText(QString("Package%1").arg(j - 2));

      ui->tableWidget->setItem(i, j, t);
    }

  //! @note init package column
  for (int i = 0; i < subscribe->maxPakcageNumber; ++i) {
    ui->cb_pkg->addItem(QString::number(i));
  }
  //! @note init rows
  for (int i = 0; i < Data::toaltalClauseNumber; ++i)
    ;
}

SubscribePannel::~SubscribePannel() { delete ui; }

void SubscribePannel::on_btn_match_clicked() { subscribe->verify(); }

void SubscribePannel::on_btn_reset_clicked() { subscribe->reset(); }

void SubscribePannel::on_btn_subscribe_clicked() {
  uint8_t pkg = ui->cb_pkg->currentIndex() + 1;
  int size    = 0;
  uint32_t uidlst[40];
  DataSubscribe::Package *p = new DataSubscribe::Package(subscribe);
  p->setPackageID(ui->cb_pkg->currentIndex());
  subscribe->setPackage(p);
  p->setFreq(ui->le_freq->text().toInt());
  for (int i = 2; i < Data::toaltalClauseNumber + 2; ++i) {
    if (ui->tableWidget->item(i, pkg + 1)) {
      if (ui->tableWidget->item(i, pkg + 1)->checkState() == Qt::Checked) {
        uidlst[size++] = i - 2;
      }
    } else {
      qDebug() << "?" << i << pkg + 1;
      return;
    }
  }
  qDebug() << size;
  p->allocClauseOffset(size);
  for (int i = 0; i < size; ++i)
    if (!p->add(uidlst[i])) {
      API_LOG(subscribe->getAPI()->getDriver(), ERROR_LOG,
              "fail to add data %d", i);
      return;
    }
  p->start();
}

void SubscribePannel::on_btn_remove_clicked() {
  uint8_t pkg = ui->cb_pkg->currentIndex();
  subscribe->remove(pkg);
}
