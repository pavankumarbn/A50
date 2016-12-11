#include "mfiopannel.h"
#include "ui_mfiopannel.h"

MFIOPannel::MFIOPannel(QWidget *parent)
    : QWidget(parent), ui(new Ui::MFIOPannel) {
  ui->setupUi(this);
}

MFIOPannel::~MFIOPannel() { delete ui; }

void MFIOPannel::on_btn_init_clicked() {
  mfio->init((DJI::onboardSDK::MFIO::MODE)ui->cb_mode->currentIndex(),
             (DJI::onboardSDK::MFIO::CHANNEL)ui->cb_channel->currentIndex(),
             QString(ui->le_val->text()).toUInt(),
             QString(ui->le_freq->text()).toUInt(), 0, 0);
}

void MFIOPannel::setMfio(DJI::onboardSDK::MFIO *value) { mfio = value; }
