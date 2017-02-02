#include "qgimbal.h"
#include "ui_qgimbal.h"

qGimbal::qGimbal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::qGimbal)
{
    ui->setupUi(this);
}

qGimbal::~qGimbal()
{
    delete ui;
}
