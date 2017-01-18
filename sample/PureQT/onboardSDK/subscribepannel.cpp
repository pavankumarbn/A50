#include "subscribepannel.h"
#include "DJI_HardDriver.h"
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
      if (j == 0 && i == 1) t->setText("TimeStamp");
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
      if (j == 1 && i == 0) t->setText(QString("Value"));
      if (j > 1 && i > 0) t->setCheckState(Qt::Unchecked);
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

void SubscribePannel::setAPI(CoreAPI *API) { subscribe->setAPI(API); }
void SubscribePannel::display(uint32_t offset, uint32_t id) {
  switch (offset) {
    case Data::Structure<Data::UID_Quaternion>::offset: {
      Data::Quaternion q = subscribe->getValue<Data::UID_Quaternion>();
      ui->tableWidget->item(2 + offset, 2 + id)
          ->setText(QString("q0: %1\nq1: %2\nq2: %3\nq3: %4")
                        .arg(q.q0, 0, 'f', 3)
                        .arg(q.q1, 0, 'f', 3)
                        .arg(q.q2, 0, 'f', 3)
                        .arg(q.q3, 0, 'f', 3));
    } break;
    case Data::Structure<Data::UID_ACCELERATION_GROUND>::offset: {
      Data::Vector3f ag = subscribe->getValue<Data::UID_ACCELERATION_GROUND>();
      ui->tableWidget->item(2 + offset, 2 + id)
          ->setText(QString("x: %1\ny: %2\nz: %3")
                        .arg(ag.x, 0, 'f', 3)
                        .arg(ag.y, 0, 'f', 3)
                        .arg(ag.z, 0, 'f', 3));
    } break;
    case Data::Structure<Data::UID_ACCELERATION_BODY>::offset: {
      Data::Vector3f ab = subscribe->getValue<Data::UID_ACCELERATION_BODY>();
      ui->tableWidget->item(2 + offset, 2 + id)
          ->setText(QString("x: %1\ny: %2\nz: %3")
                        .arg(ab.x, 0, 'f', 3)
                        .arg(ab.y, 0, 'f', 3)
                        .arg(ab.z, 0, 'f', 3));
    } break;
    case Data::Structure<Data::UID_ACCELERATION_RAW>::offset: {
      Data::Vector3f ar = subscribe->getValue<Data::UID_ACCELERATION_RAW>();
      ui->tableWidget->item(2 + offset, 2 + id)
          ->setText(QString("x: %1\ny: %2\nz: %3")
                        .arg(ar.x, 0, 'f', 3)
                        .arg(ar.y, 0, 'f', 3)
                        .arg(ar.z, 0, 'f', 3));
    } break;
    case Data::Structure<Data::UID_VELOCITY>::offset: {
      Data::Velocity v = subscribe->getValue<Data::UID_VELOCITY>();
      ui->tableWidget->item(2 + offset, 2 + id)
          ->setText(QString("x: %1\ny: %2\nz: %3\nhealth: %4")
                        .arg(v.data.x, 0, 'f', 3)
                        .arg(v.data.y, 0, 'f', 3)
                        .arg(v.data.z, 0, 'f', 3)
                        .arg(v.info.health));
    } break;
    case Data::Structure<Data::UID_PALSTANCE_FUSIONED>::offset: {
      Data::Vector3f pf = subscribe->getValue<Data::UID_PALSTANCE_FUSIONED>();
      ui->tableWidget->item(2 + offset, 2 + id)
          ->setText(QString("x: %1\ny: %2\nz: %3")
                        .arg(pf.x, 0, 'f', 3)
                        .arg(pf.y, 0, 'f', 3)
                        .arg(pf.z, 0, 'f', 3));
    } break;
    case Data::Structure<Data::UID_PALSTANCE_RAW>::offset: {
      Data::Vector3f pr = subscribe->getValue<Data::UID_PALSTANCE_RAW>();
      ui->tableWidget->item(2 + offset, 2 + id)
          ->setText(QString("x: %1\ny: %2\nz: %3")
                        .arg(pr.x, 0, 'f', 3)
                        .arg(pr.y, 0, 'f', 3)
                        .arg(pr.z, 0, 'f', 3));
    } break;
    case Data::Structure<Data::UID_ALTITUDE_FUSIONED>::offset: {
      float32_t d = subscribe->getValue<Data::UID_ALTITUDE_FUSIONED>();
      ui->tableWidget->item(2 + offset, 2 + id)
          ->setText(QString("%1").arg(d, 0, 'f', 3));
    } break;
    case Data::Structure<Data::UID_ALTITUDE_BAROMETER>::offset: {
      float32_t d = subscribe->getValue<Data::UID_ALTITUDE_BAROMETER>();
      ui->tableWidget->item(2 + offset, 2 + id)
          ->setText(QString("%1").arg(d, 0, 'f', 3));
    } break;
    case Data::Structure<Data::UID_HEIGHT_HOMEPOOINT>::offset: {
      float32_t d = subscribe->getValue<Data::UID_HEIGHT_HOMEPOOINT>();
      ui->tableWidget->item(2 + offset, 2 + id)
          ->setText(QString("%1").arg(d, 0, 'f', 3));
    } break;
    case Data::Structure<Data::UID_HEIGHT_FUSION>::offset: {
      float32_t d = subscribe->getValue<Data::UID_HEIGHT_FUSION>();
      ui->tableWidget->item(2 + offset, 2 + id)
          ->setText(QString("%1").arg(d, 0, 'f', 3));
    } break;
    case Data::Structure<Data::UID_GPS_DATE>::offset: {
      uint32_t d = subscribe->getValue<Data::UID_GPS_DATE>();
      ui->tableWidget->item(2 + offset, 2 + id)->setText(QString("%1").arg(d));
    } break;
    case Data::Structure<Data::UID_GPS_TIME>::offset: {
      uint32_t d = subscribe->getValue<Data::UID_GPS_TIME>();
      ui->tableWidget->item(2 + offset, 2 + id)->setText(QString("%1").arg(d));
    } break;
    case Data::Structure<Data::UID_GPS_POSITION>::offset: {
      Data::Vector3d p = subscribe->getValue<Data::UID_GPS_POSITION>();
      ui->tableWidget->item(2 + offset, 2 + id)
          ->setText(QString("longitude: %1\n latitude : %2\n hmsl : %3")
                        .arg(p.x)
                        .arg(p.y)
                        .arg(p.z));
    } break;
    //! @todo implement
    // clang-format off
    case Data::Structure<Data::UID_GPS_VELOCITY             >::offset : break;
    case Data::Structure<Data::UID_GPS_DETAILS              >::offset : break;
    case Data::Structure<Data::UID_RTK_POSITION             >::offset : break;
    case Data::Structure<Data::UID_RTK_VELOCITY             >::offset : break;
    case Data::Structure<Data::UID_RTK_YAW                  >::offset : break;
    case Data::Structure<Data::UID_RTK_POSITION_INFO        >::offset : break;
    case Data::Structure<Data::UID_RTK_YAW_INFO             >::offset : break;
    case Data::Structure<Data::UID_COMPASS                  >::offset : break;
    case Data::Structure<Data::UID_RC                       >::offset : break;
    case Data::Structure<Data::UID_GIMBAL_ANGLES            >::offset : break;
    case Data::Structure<Data::UID_GIMBAL_STATUS            >::offset : break;
    case Data::Structure<Data::UID_STATUS_FLIGHT            >::offset : break;
    case Data::Structure<Data::UID_STATUS_DISPLAYMODE       >::offset : break;
    case Data::Structure<Data::UID_STATUS_LANDINGGEAR       >::offset : break;
    case Data::Structure<Data::UID_STATUS_MOTOR_START_ERROR >::offset : break;
    case Data::Structure<Data::UID_BATTERY_INFO             >::offset : break;
    case Data::Structure<Data::UID_CONTROL_DEVICE           >::offset : break;
    default: break;
      // clang-format on
  }
}

void SubscribePannel::on_btn_match_clicked() { subscribe->verify(); }

void SubscribePannel::on_btn_reset_clicked() { subscribe->reset(); }

void SubscribePannel::on_btn_subscribe_clicked() {
  uint8_t pkg = ui->cb_pkg->currentIndex() + 1;
  int size    = 0;
  uint32_t uidlst[40];
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
  DataSubscribe::Package *p = new DataSubscribe::Package(subscribe);
  p->setPackageID(ui->cb_pkg->currentIndex());
  p->setFreq(ui->le_freq->text().toInt());
  p->setSendStamp(ui->tableWidget->item(1, pkg + 1)->checkState() ==
                  Qt::Checked);
  p->allocClauseOffset(size);
  for (int i = 0; i < size; ++i)
    if (!p->addByOffset(uidlst[i])) {
      API_LOG(subscribe->getAPI()->getDriver(), ERROR_LOG,
              "fail to add data %d", i);
      delete p;
      return;
    }
  subscribe->setPackage(p);
  p->setUnpackHandler(packageUnpackCallback, this);
  p->start();
}

void SubscribePannel::on_btn_remove_clicked() {
  uint8_t pkg               = ui->cb_pkg->currentIndex();
  DataSubscribe::Package *p = subscribe->getPackage(pkg);
  if (p) p->stop();
}

void SubscribePannel::on_btn_pause_clicked() {
  uint8_t pkg = ui->cb_pkg->currentIndex();
  subscribe->getPackage(pkg)->pause();
}

void SubscribePannel::on_btn_resume_clicked() {
  uint8_t pkg = ui->cb_pkg->currentIndex();
  subscribe->getPackage(pkg)->resume();
}

void SubscribePannel::packageUnpackCallback(DataSubscribe::Package *pkg,
                                            Data::TimeStamp time,
                                            DJI::UserData THIS) {
  if (pkg) {
    SubscribePannel *This = (SubscribePannel *)THIS;
    if (pkg->getSendStamp()) {
      API_LOG(pkg->getSubscribe()->getAPI()->getDriver(), STATUS_LOG,
              "Time: %d %d", time.time_2p5ms, time.time_ns);
      This->ui->tableWidget->item(1, pkg->getPackageID() + 2)
          ->setText(QString(" s : %1\r\nns: %2")
                        .arg(time.time_2p5ms / 2.5, 0, 'f', 1)
                        .arg(time.time_ns));
    }
    uint32_t *clauses = pkg->getClauseOffset();
    size_t n          = pkg->getClauseNumber();
    for (int i = 0; i < n; ++i) {
      This->display(clauses[i], pkg->getPackageID());
    }
  }
}

#include <QDebug>

void SubscribePannel::on_tableWidget_itemChanged(QTableWidgetItem *item) {
  if (item->row() > 1 && item->column() > 1)
    if (item->checkState() == Qt::Checked) {
      display(item->row() - 2, item->column() - 2);
      ui->tableWidget->horizontalHeader()->setSectionResizeMode(
          QHeaderView::ResizeToContents);
      ui->tableWidget->verticalHeader()->setSectionResizeMode(
          QHeaderView::ResizeToContents);
    } else {
      item->setText("");
    }
}
