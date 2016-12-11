#ifndef QONBOARDSDK_H
#define QONBOARDSDK_H

#include <DJI_API.h>
#include <DJI_Camera.h>
#include <DJI_Flight.h>
#include <DJI_Follow.h>
#include <DJI_HardDriver.h>
#include <DJI_HotPoint.h>
#include <DJI_MFIO.h>
#include <DJI_VirtualRC.h>
#include <DJI_WayPoint.h>
#include <QMutex>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTextBrowser>
#include <QThread>

using namespace DJI::onboardSDK;

class QHardDriver : public HardDriver {
 public:
  QHardDriver(QSerialPort *Port);

  void init();
  DJI::time_ms getTimeStamp();
  size_t send(const uint8_t *buf, size_t len);
  size_t readall(uint8_t *buf, size_t maxlen);

  void lockMemory();
  void freeMemory();

  void lockMSG();
  void freeMSG();

  void lockACK() { ack.lock(); }
  void freeACK() { ack.unlock(); }

  void notify() {}
  void wait(int timeout) {}

  void displayLog(const char *buf = 0);

  void setBaudrate(int value);

  QTextBrowser *getDisplay() const;
  void setDisplay(QTextBrowser *value);

 private:
  QHardDriver();

 private:
  int baudrate;
  QSerialPort *port;
  QMutex memory;
  QMutex msg;
  QMutex ack;
  QMutex sendLock;
  QMutex bufferLock;
  QTextBrowser *display;
};

class APIThread : public QThread {
  Q_OBJECT

 public:
  APIThread();
  APIThread(CoreAPI *API, int Type, QObject *parent = 0);

  void run();

  size_t getCallTimes() const;
  void setCallTimes(const size_t &value);

 private:
  CoreAPI *api;
  int type;
  size_t callTimes;
};

#endif  // QONBOARDSDK_H
