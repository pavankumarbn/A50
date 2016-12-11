#include "recorder.h"
#include "ui_recorder.h"

recorder::recorder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::recorder)
{
    ui->setupUi(this);
}

recorder::~recorder()
{
    delete ui;
}
