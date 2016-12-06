#ifndef WAYPOINTS_H
#define WAYPOINTS_H

#include <QStandardItemModel>

#include <QWidget>
#include "DJI_API.h"
#include "DJI_WayPoint.h"
#include "SDKWidgets.h"

namespace Ui {
class Waypoints;
}

class QWaypoints : public QWidget {
  Q_OBJECT

 public:
  explicit QWaypoints(QWidget *parent = 0);
  ~QWaypoints();

  DJI::onboardSDK::CoreAPI *getApi() const;
  void setApi(DJI::onboardSDK::CoreAPI *value);

  DJI::onboardSDK::Waypoints *getWp() const;
  void setWp(DJI::onboardSDK::Waypoints *value);

  void initWayPoint();
  void wpAddPoint();
  void wpRemovePoint();

 private slots:
  void on_btn_waypoint_init_clicked();

  void on_cb_waypoint_point_currentIndexChanged(int index);
  void on_le_waypoint_number_editingFinished();
  void on_btn_waypoint_action_clicked();
  void on_btn_waypoint_reset_clicked();
  void on_btn_waypoint_removeAction_clicked();
  void on_btn_waypoint_viewPoint_clicked();
  void on_btn_wp_ivset_clicked();
  void on_btn_wp_ivRead_clicked();
  void on_btn_waypoint_add_clicked();
  void on_btn_waypoint_remove_clicked();

  void on_btn_wp_pr_clicked(bool checked);
  void on_le_wp_exec_editingFinished();
  void on_btn_wp_loadAll_clicked();
  void on_btn_wp_start_stop_clicked(bool checked);
  void on_btn_wp_loadOne_clicked();
  void on_waypoint_data_changed(const QModelIndex &topLeft,
                                const QModelIndex &bottomRight,
                                const QVector<int> &roles);

  void on_btn_webTool_clicked(bool checked);

  void on_btn_AbortWaypoint_clicked();

 private:
  QStandardItemModel *initAction();

  Ui::Waypoints *ui;

  DJI::onboardSDK::WayPointData wayPointDataTmp;

  DJI::onboardSDK::CoreAPI *api;
  DJI::onboardSDK::Waypoints *wp;
  QStandardItemModel *waypointData;
  QStandardItemModel *currentAction;
  QStandardItemModel *nullAction;
  QList<QStandardItemModel *> actionData;
};

#endif  // WAYPOINTS_H
