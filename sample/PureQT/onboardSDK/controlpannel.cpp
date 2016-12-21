#include "controlpannel.h"
#include <QDebug>
#include "DJI_HardDriver.h"
#include "ui_controlpannel.h"

ControlPannel::ControlPannel(QWidget *parent)
    : QWidget(parent), ui(new Ui::ControlPannel) {
  ui->setupUi(this);
  controler = new DJI::onboardSDK::Control(0);
}

ControlPannel::~ControlPannel() {
  delete ui;
  delete controler;
}

void ControlPannel::setAPI(DJI::onboardSDK::CoreAPI *api) {
  controler->setAPI(api);
}

void ControlPannel::on_btn_flight_runCommand_clicked() {
  DJI::onboardSDK::Control::COMMAND c;
  switch (ui->cb_command->currentIndex()) {
    case 0:
      c = DJI::onboardSDK::Control::COMMAND_TAKEOFF;
      break;
    case 1:
      c = DJI::onboardSDK::Control::COMMAND_LANDING;
      break;
    case 2:
      c = DJI::onboardSDK::Control::COMMAND_CURSELOCK;
      break;
    case 3:
      c = DJI::onboardSDK::Control::COMMAND_GOHOME;
      break;
    case 4:
      c = DJI::onboardSDK::Control::COMMAND_STARTMOTOR;
      break;
    case 5:
      c = DJI::onboardSDK::Control::COMMAND_STOPMOTOR;
      break;
    case 6:
      c = DJI::onboardSDK::Control::COMMAND_CALIBRATE_COMPASS;
      break;
    case 7:
      c = DJI::onboardSDK::Control::COMMAND_EXIT_GOHOME;
      break;
    case 8:
      c = DJI::onboardSDK::Control::COMMAND_EXIT_TAKEOFF;
      break;
    case 9:
      c = DJI::onboardSDK::Control::COMMAND_EXIT_LANDING;
      break;
    case 10:
      c = DJI::onboardSDK::Control::COMMADN_EXIT_CALIBRATE_COMPASS;
      break;
    case 11:
      c = DJI::onboardSDK::Control::COMMAND_EXIT_PACK_MODE;
      break;
    case 12:
      c = DJI::onboardSDK::Control::COMMAND_LANGDING_GEAR_UP;
      break;
    case 13:
      c = DJI::onboardSDK::Control::COMMAND_LANDING_GEAR_DOWN;
      break;
    default:
      API_LOG(controler->getApi()->getDriver(), ERROR_LOG, "Unknown command %d",
              ui->cb_command->currentIndex());
      break;
  }
  qDebug() << ui->cb_command->currentIndex() << c;
  controler->command(c);
}
