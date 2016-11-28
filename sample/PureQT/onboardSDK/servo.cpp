#include "servo.h"
#include "ui_servo.h"

Servo::Servo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Servo)
{
    ui->setupUi(this);
}

Servo::~Servo()
{
    delete ui;
}

DJI::onboardSDK::Servo *Servo::getServo() const
{
    return servo;
}

#include <QDebug>
void Servo::setServo(DJI::onboardSDK::Servo *value)
{
    servo = value;
    qDebug()<<"SERVO"<<value;
}
void Servo::on_pushButton_clicked()
{
    servo->setPosition(ui->lineEdit_2->text().toInt(),ui->lineEdit->text().toInt());
    qDebug()<<ui->lineEdit_2->text().toInt()<<ui->lineEdit->text().toInt();
}
