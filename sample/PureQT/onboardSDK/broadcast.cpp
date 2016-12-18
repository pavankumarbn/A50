#include "broadcast.h"
#include <QDebug>
#include "ui_broadcast.h"

using namespace DJI;
using namespace DJI::onboardSDK;

Broadcast::Broadcast(QWidget *parent) : QWidget(parent), ui(new Ui::Broadcast) {
  ui->setupUi(this);
  qDebug() << "UID: " << Data::DataBase[1].uid;
}

Broadcast::~Broadcast() { delete ui; }
