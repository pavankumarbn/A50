#include "controlpannel.h"
#include <QDebug>
#include "DJI_HardDriver.h"
#include "ui_controlpannel.h"

using namespace DJI;
using namespace DJI::onboardSDK;

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
      API_LOG(controler->getAPI()->getDriver(), ERROR_LOG, "Unknown command %d",
              ui->cb_command->currentIndex());
      break;
  }
  qDebug() << ui->cb_command->currentIndex() << c;
  controler->command(c);
}

void ControlPannel::on_btn_control_clicked(bool checked) {
  if (checked)
    controler->obtain();
  else
    controler->release();
}

void ControlPannel::setControlCallback(CoreAPI *This, Header *header,
                                       UserData userData) {
  ControlPannel *sdk      = (ControlPannel *)userData;
  unsigned short ack_data = ACK_COMMON_NO_RESPONSE;
  unsigned char data      = 0x1;

  if (header->length - CoreAPI::PackageMin <= 2) {
    memcpy((unsigned char *)&ack_data,
           ((unsigned char *)header) + sizeof(Header),
           (header->length - CoreAPI::PackageMin));
  } else {
    API_LOG(This->getDriver(), ERROR_LOG,
            "ACK is exception,seesion id %d,sequence %d\n", header->sessionID,
            header->sequenceNumber);
  }

  switch (ack_data) {
    case ACK_SETCONTROL_ERROR_MODE:
      if (sdk) {
        sdk->ui->btn_control->setText("Switch to mod P");
      } else
        API_LOG(This->getDriver(), ERROR_LOG, "known SDK pointer 0.");
      break;
    case ACK_SETCONTROL_RELEASE_SUCCESS:
      if (sdk)
        sdk->ui->btn_control->setText("Obtain Control");
      else
        API_LOG(This->getDriver(), ERROR_LOG, "known SDK pointer 0.");
      break;
    case ACK_SETCONTROL_OBTAIN_SUCCESS:
      if (sdk)
        sdk->ui->btn_control->setText("Release Control");
      else
        API_LOG(This->getDriver(), ERROR_LOG, "known SDK pointer 0.");
      break;
    case ACK_SETCONTROL_OBTAIN_RUNNING:
      This->send(2, encrypt, SET_CONTROL, CODE_SETCONTROL, &data, 1, 500, 2,
                 ControlPannel::setControlCallback, userData);
      break;
    case ACK_SETCONTROL_RELEASE_RUNNING:
      data = 0;
      This->send(2, encrypt, SET_CONTROL, CODE_SETCONTROL, &data, 1, 500, 2,
                 ControlPannel::setControlCallback, userData);
      break;
  }
}
