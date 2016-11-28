#ifndef SERVO_H
#define SERVO_H

#include <QWidget>
#include "dji_servo.h"

namespace Ui {
class Servo;
}

class Servo : public QWidget
{
    Q_OBJECT

public:
    explicit Servo(QWidget *parent = 0);
    ~Servo();

    DJI::onboardSDK::Servo *getServo() const;
    void setServo(DJI::onboardSDK::Servo *value);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Servo *ui;
    DJI::onboardSDK::Servo *servo;

};

#endif // SERVO_H
