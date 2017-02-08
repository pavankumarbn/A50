#ifndef DJI_LIST_H
#define DJI_LIST_H

template <typename T>
class ListMemory {
 public:
  ListMemory();

 public:
  //! @note memory access APIs
  //! for Static list

 public:
  //! @note Linked list APIs
  void**      append();
  inline bool isEmpty();
  inline int  size();

 public:
  //! @note memory management

 private:
  void* array[1];
  int   begin;
  int   end;
  int   alloc;
};

template <typename T>
class List {
 public:
  List(alloc = 0);

  const T& at(int i) const;
  const T& operator[](int i) const;
  T& operator[](int i);
};

template <typename T, int alloc>
class StaticList : public List<T> {
 public:
  StaticList();

 private:
  ListMemory memory;
  void*      memoryPool[alloc];
};
#endif  // DJI_LIST_H
