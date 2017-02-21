#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>

namespace DJI {

// template <typename T>
// class LoopQueue {
// public:
//  LoopQueue();

// public:
//  bool write(T data);
//  bool read(T &data);
//  int write(T *data, int len);
//  int read(T *data, int len);

// public:
//  bool isReadable() const;
//  bool isWriteable() const;
//  bool isEmpty() const;
//  bool isFull() const;
//  int  length() const;
//  int  size() const;
//  void flush(int len = 0);

// private:
//  bool isOnHold(int pos);

// private:
//  volatile bool readable : 1;
//  volatile bool writeable : 1;
//  volatile T *  memory;
//  int           size;
//  volatile int  readFrom;
//  volatile int  writeTo;
//};

// template <typename T>
// class StaticLoopQueue : public LoopQueue<T> {
// public:
//  StaticLoopQueue();
//};

// typedef LoopQueue<uint8_t>       Buffer;
// typedef StaticLoopQueue<uint8_t> StaticBuffer;

}  // namespace  DJI

#endif  // BUFFER_H
