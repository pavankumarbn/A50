#include "qwaypoints.h"
#include <QDebug>
#include "DJI_HardDriver.h"
#include "DJI_Type.h"
#include "ui_qwaypoints.h"

#define DEG2RAD 0.01745329252

QWaypoints::QWaypoints(QWidget *parent)
    : QWidget(parent), ui(new Ui::Waypoints) {
  ui->setupUi(this);
  ui->btn_waypointDownload->setVisible(false);
  ui->btn_waypoint_reset->setVisible(false);
}

QWaypoints::~QWaypoints() { delete ui; }

DJI::onboardSDK::CoreAPI *QWaypoints::getApi() const { return api; }

void QWaypoints::setAPI(DJI::onboardSDK::CoreAPI *value) { api = value; }

DJI::onboardSDK::Waypoints *QWaypoints::getWp() const { return wp; }

void QWaypoints::setWp(DJI::onboardSDK::Waypoints *value) { wp = value; }

void QWaypoints::initWayPoint() {
  wp           = new DJI::onboardSDK::Waypoints(api);
  waypointData = new QStandardItemModel();
  waypointData->setHorizontalHeaderItem(0,
                                        new QStandardItem(QObject::tr("No.")));
  waypointData->setHorizontalHeaderItem(
      1, new QStandardItem(QObject::tr("Latitude")));
  waypointData->setHorizontalHeaderItem(
      2, new QStandardItem(QObject::tr("Longitude")));
  waypointData->setHorizontalHeaderItem(
      3, new QStandardItem(QObject::tr("Altitude")));
  waypointData->setHorizontalHeaderItem(
      4, new QStandardItem(QObject::tr("Damping")));
  waypointData->setHorizontalHeaderItem(5,
                                        new QStandardItem(QObject::tr("Yaw")));
  waypointData->setHorizontalHeaderItem(
      6, new QStandardItem(QObject::tr("Pitch")));
  waypointData->setHorizontalHeaderItem(
      7, new QStandardItem(QObject::tr("TurnMode")));
  waypointData->setHorizontalHeaderItem(
      8, new QStandardItem(QObject::tr("Anction Num")));
  waypointData->setHorizontalHeaderItem(
      9, new QStandardItem(QObject::tr("Time limit")));
  waypointData->setHorizontalHeaderItem(
      10, new QStandardItem(QObject::tr("Repeat times")));

  nullAction    = initAction();
  currentAction = nullAction;

  ui->tv_waypoint_actions->setItemDelegateForColumn(0, new ReadOnlyDelegate());
  ui->tv_waypoint_actions->setItemDelegateForColumn(1, new ReadOnlyDelegate());
  ui->tv_waypoint_actions->setItemDelegateForColumn(2, new ActionDelegate());
  ui->tv_waypoint_actions->setModel(currentAction);
  ui->tv_waypoint_actions->verticalHeader()->hide();
  ui->tv_waypoint_actions->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);

  ui->tv_waypoint_data->setItemDelegateForColumn(0, new ReadOnlyDelegate());
  ui->tv_waypoint_data->setItemDelegateForColumn(7, new TurnModeDelegate());
  ui->tv_waypoint_data->setItemDelegateForColumn(8, new ReadOnlyDelegate());
  ui->tv_waypoint_data->setModel(waypointData);
  ui->tv_waypoint_data->verticalHeader()->hide();
  ui->tv_waypoint_data->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);

  connect(
      waypointData, SIGNAL(dataChanged(QModelIndex, QModelIndex, QVector<int>)),
      this,
      SLOT(on_waypoint_data_changed(QModelIndex, QModelIndex, QVector<int>)));

  ui->cb_waypoint_point->addItem("Null");
}

void QWaypoints::wpAddPoint() {
  int number = waypointData->rowCount();
  waypointData->setItem(number, 0, new QStandardItem(QString::number(number)));
  waypointData->setItem(
      number, 1,
      new QStandardItem(QString::number(
          /*! @todo replace api->getBroadcastData().pos.latitude*/ 0 /
          DEG2RAD)));
  waypointData->setItem(
      number, 2,
      new QStandardItem(QString::number(
          /*! @todo replace api->getBroadcastData().pos.longitude*/ 0 /
          DEG2RAD)));
  waypointData->setItem(
      number, 3,
      new QStandardItem(QString::number(
          /*! @todo replace api->getBroadcastData().pos.altitude*/ 0)));
  waypointData->setItem(number, 4, new QStandardItem("not available now"));
  waypointData->setItem(number, 5, new QStandardItem("0"));
  waypointData->setItem(number, 6, new QStandardItem("0"));
  waypointData->setItem(number, 7, new QStandardItem("Clockwise"));
  waypointData->setItem(number, 8, new QStandardItem("0"));

  actionData.append(initAction());
  ui->cb_waypoint_point->addItem(
      QString::number(ui->cb_waypoint_point->count() - 1));
}

void QWaypoints::wpRemovePoint() {
  if (ui->cb_waypoint_point->count() != 1) {
    ui->cb_waypoint_point->removeItem(ui->cb_waypoint_point->count() - 1);
    QStandardItemModel *last = actionData.last();
    actionData.removeLast();
    delete last;
    waypointData->removeRow(waypointData->rowCount() - 1);
  }
}

void QWaypoints::on_btn_waypoint_init_clicked() {
  DJI::onboardSDK::WayPointInitData data = wp->getInfo();
  data.indexNumber    = ui->le_waypoint_number->text().toInt();
  data.maxVelocity    = ui->le_wp_mv->text().toFloat();
  data.idleVelocity   = ui->le_wp_iv->text().toFloat();
  data.finishAction   = ui->cb_wp_fa->currentIndex();
  data.executiveTimes = ui->le_wp_exec->text().toInt();
  data.yawMode        = ui->cb_wp_yaw->currentIndex();
  //! @note not available for flight control yet.
  data.traceMode    = 0;  // ui->cb_wp_mov->currentIndex()
  data.RCLostAction = ui->cb_wp_rcl->currentIndex();
  data.gimbalPitch  = ui->cb_wp_gb->currentIndex();
  data.latitude     = ui->le_wp_la->text().toDouble();
  data.longitude    = ui->le_wp_lo->text().toDouble();
  data.altitude     = ui->le_wp_al->text().toFloat();
  //! @note these are two different way to offer a same init.
  // wp->setInfo(data);
  // wp->init();
  wp->init(&data);
// on_btn_waypoint_add_clicked();
#ifdef GROUNDSTATION
  initMap();
#endif  // GROUNDSTATION
}

void QWaypoints::on_cb_waypoint_point_currentIndexChanged(int index) {
  if (index != 0) {
    if (actionData.length() >= (index - 1)) {
      ui->tv_waypoint_actions->setModel(actionData[index - 1]);
      currentAction = actionData[index - 1];
    }
  } else {
    ui->tv_waypoint_actions->setModel(nullAction);
    currentAction = nullAction;
  }
}

void QWaypoints::on_le_waypoint_number_editingFinished() {
  while (ui->le_waypoint_number->text().toInt() != waypointData->rowCount()) {
    if (ui->le_waypoint_number->text().toInt() > waypointData->rowCount())
      wpAddPoint();
    else
      wpRemovePoint();
  }
}

void QWaypoints::on_btn_waypoint_action_clicked() {
  if (currentAction != nullAction) {
    int number = currentAction->rowCount();
    if (number <= 15 && ui->cb_waypoint_point->currentIndex() != -1) {
      currentAction->setItem(number, 0,
                             new QStandardItem(QString::number(number)));
      currentAction->setItem(number, 1,
                             new QStandardItem(QString::number(
                                 ui->cb_waypoint_point->currentIndex() - 1)));
      waypointData->setData(
          waypointData->index(ui->cb_waypoint_point->currentIndex() - 1, 8),
          currentAction->rowCount());
    } else {
      API_LOG(api->getDriver(), STATUS_LOG,
              "The maximum number of actions is 15");
    }
  }
}

void QWaypoints::on_btn_waypoint_reset_clicked() {
  while (actionData.length() != 0) {
    on_btn_waypoint_remove_clicked();
  }
}

void QWaypoints::on_btn_waypoint_removeAction_clicked() {
  //! @todo implement removeAction
}

void QWaypoints::on_btn_waypoint_viewPoint_clicked() {
  ui->le_wp_la->setText(QString::number(
      /*! @todo replaceapi->getBroadcastData().pos.latitude*/ 0 / DEG2RAD));
  ui->le_wp_lo->setText(QString::number(
      /*! @todo replace api->getBroadcastData().pos.longitude*/ 0 / DEG2RAD));
  ui->le_wp_al->setText(QString::number(
      /*! @todo replace api->getBroadcastData().pos.altitude*/ 0));
}

void QWaypoints::on_btn_wp_ivset_clicked() {
  wp->updateIdleVelocity(ui->le_wp_iv->text().toFloat());
}

void QWaypoints::on_btn_wp_ivRead_clicked() { wp->readIdleVelocity(); }

void QWaypoints::on_btn_waypoint_add_clicked() {
  wpAddPoint();
  ui->le_waypoint_number->setText(QString::number(waypointData->rowCount()));
  //    waypointData->item(waypointData->rowCount()-1,1)->setText(QString::number(10.0));//api->getBroadcastData().pos.latitude);
  //    waypointData->item(waypointData->rowCount()-1,2)->setText(QString::number(10.0));//api->getBroadcastData().pos.longitude);
  //    waypointData->item(waypointData->rowCount()-1,3)->setText(QString::number(10.0));//api->getBroadcastData().pos.altitude);
}

void QWaypoints::on_btn_waypoint_remove_clicked() {
  wpRemovePoint();
  ui->le_waypoint_number->setText(QString::number(waypointData->rowCount()));
}

void QWaypoints::on_btn_wp_pr_clicked(bool checked) {
  if (checked)
    ui->btn_wp_pr->setText("Resume");
  else
    ui->btn_wp_pr->setText("Pause");
  wp->pause(checked);
}

void QWaypoints::on_le_wp_exec_editingFinished() {
  //! @note the range of exectimes is 1-255, 0xFF means infinite loop
  int times = ui->le_wp_exec->text().toInt();
  if (times > 255) ui->le_wp_exec->setText("255");
  if (times <= 0) ui->le_wp_exec->setText("1");
}

void QWaypoints::on_btn_wp_loadAll_clicked() {
  for (int i = 0; i < ui->cb_waypoint_point->count() - 1; ++i) {
    ui->cb_waypoint_point->setCurrentIndex(i + 1);
    on_btn_wp_loadOne_clicked();
  }
}

void QWaypoints::on_btn_wp_start_stop_clicked(bool checked) {
  wp->start();
  /*
    if (checked)
    {
        wp->start();
        ui->btn_wp_start_stop->setText("Stop");
    }
    else
    {
        wp->stop();
        ui->btn_wp_start_stop->setText("Start");
    }
*/
}

void QWaypoints::on_btn_wp_loadOne_clicked() {
  if (ui->cb_waypoint_point->currentIndex() != 0) {
    int index = ui->cb_waypoint_point->currentIndex() - 1;
    // WayPointData data;
    wayPointDataTmp.index = index;
    wayPointDataTmp.latitude =
        waypointData->index(index, 1).data().toDouble() * DEG2RAD;
    wayPointDataTmp.longitude =
        waypointData->index(index, 2).data().toDouble() * DEG2RAD;
    wayPointDataTmp.altitude = waypointData->index(index, 3).data().toDouble();
    wayPointDataTmp.damping  = 0;  //! @note not available now

    wayPointDataTmp.yaw         = waypointData->index(index, 5).data().toInt();
    wayPointDataTmp.gimbalPitch = waypointData->index(index, 6).data().toInt();
    wayPointDataTmp.turnMode =
        waypointData->index(index, 7).data().toByteArray() == "Clockwise" ? 0
                                                                          : 1;

    wayPointDataTmp.hasAction       = 0;
    wayPointDataTmp.actionTimeLimit = 0;
    wayPointDataTmp.actionNumber    = 0;
    wayPointDataTmp.actionRepeat    = 0;
    for (int i = 0; i < 16; ++i) {
      wayPointDataTmp.commandList[i]      = 0;
      wayPointDataTmp.commandParameter[i] = 0;
    }

    if (waypointData->index(index, 8).data().toInt() != 0) {
      wayPointDataTmp.hasAction = 1;
      wayPointDataTmp.actionNumber =
          waypointData->index(index, 8).data().toInt();
      wayPointDataTmp.actionTimeLimit =
          waypointData->index(index, 9).data().toInt();
      wayPointDataTmp.actionRepeat =
          waypointData->index(index, 10).data().toInt();
      for (int i = 0; i < 15; ++i) {
        if (i < actionData[index]->rowCount()) {
          ActionDelegate temp;
          QComboBox *find = static_cast<QComboBox *>(
              temp.createEditor(0, QStyleOptionViewItem(), QModelIndex()));
          wayPointDataTmp.commandList[i] = find->findText(
              actionData[index]->index(i, 2).data().toByteArray().data());
          wayPointDataTmp.commandParameter[i] =
              actionData[index]->index(i, 3).data().toInt();
        } else
          break;
      }
    }
    //! @note test code
    //        qDebug() << wayPointDataTmp.index << wayPointDataTmp.latitude <<
    //        wayPointDataTmp.longitude << wayPointDataTmp.altitude
    //                 << wayPointDataTmp.damping;
    //        qDebug() << wayPointDataTmp.yaw << wayPointDataTmp.gimbalPitch <<
    //        wayPointDataTmp.turnMode;
    //        qDebug() << wayPointDataTmp.hasAction <<
    //        wayPointDataTmp.actionTimeLimit << wayPointDataTmp.actionNumber
    //                 << wayPointDataTmp.actionRepeat;
    //        for (int i = 0; i < 15; ++i)
    //            qDebug() << wayPointDataTmp.commandList[i] <<
    //            wayPointDataTmp.commandParameter[i];
    if (!wp->uploadIndexData(&wayPointDataTmp)) qDebug() << "fail";
  }
}

void QWaypoints::on_waypoint_data_changed(const QModelIndex &topLeft __UNUSED,
                                          const QModelIndex &bottomRight
                                              __UNUSED,
                                          const QVector<int> &roles __UNUSED) {
  //! @todo waypoint data modify
  //    API_LOG(api->getDriver(), STATUS_LOG, "c: %d r: %d %s",
  //    bottomRight.column(),
  //          bottomRight.row(), topLeft.data().toByteArray().data());
  //    API_LOG(api->getDriver(), STATUS_LOG, "c: %d r: %d %lf",
  //    bottomRight.column(),
  //        bottomRight.row(), topLeft.data().toDouble());
}

void QWaypoints::on_btn_webTool_clicked(bool checked) {
  if (checked) {
    ui->gb_wp->setMaximumHeight(20);
    ui->gb_wp->setMinimumHeight(20);
  } else {
    ui->gb_wp->setMinimumHeight(480);
    ui->gb_wp->setMaximumHeight(480);
  }
}

void QWaypoints::on_btn_AbortWaypoint_clicked() { wp->stop(); }

QStandardItemModel *QWaypoints::initAction() {
  QStandardItemModel *action = new QStandardItemModel();
  action->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("No.")));
  action->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("Index")));
  action->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("Type")));
  action->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("Data")));
  return action;
}
