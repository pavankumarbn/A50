#include <stdio.h>
#include <QApplication>
#include <QDebug>
#include "DJI_HardDriver_Qt.h"
#include "djionboardsdk.h"

int main(int argc, char *argv[]) {
  /******/
  qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");

  /******/

  QApplication a(argc, argv);
  DJIonboardSDK w;
  w.showMaximized();

  return a.exec();
}
