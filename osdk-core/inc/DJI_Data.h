#ifndef DATASUBSCRIBE_H
#define DATASUBSCRIBE_H

class DataSubscribe {
 public:
  DataSubscribe();

  void verify();
  void subscribe();
  void add();
  void remove();
  void updateFreq();
  void pause();
  void info();
  void packageInfo();

 private:
  void verifyAuthorty();
  void verifyVersion();

 private:
};

class DataPublish {
  //! @todo
 public:
  DataPublish();

 private:
};

#endif  // DATASUBSCRIBE_H
