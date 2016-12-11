#ifndef RECORDER_H
#define RECORDER_H

#include <QWidget>

namespace Ui {
class recorder;
}

class recorder : public QWidget
{
    Q_OBJECT

public:
    explicit recorder(QWidget *parent = 0);
    ~recorder();

private:
    Ui::recorder *ui;
};

#endif // RECORDER_H
