#ifndef QGIMBAL_H
#define QGIMBAL_H

#include <QWidget>

namespace Ui {
class qGimbal;
}

class qGimbal : public QWidget
{
    Q_OBJECT

public:
    explicit qGimbal(QWidget *parent = 0);
    ~qGimbal();

private:
    Ui::qGimbal *ui;
};

#endif // QGIMBAL_H
