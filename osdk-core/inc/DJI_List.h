#ifndef DJI_LIST_H
#define DJI_LIST_H

namespace DJI {

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

 public:
  inline int count() const { /*! @todo implement*/
    return 0;
  }
  inline int  length() const { return count(); }
  inline bool isEmpty() const;
  void append(const T& t);
  void append(const List<T>& t);

  const T& at(int i) const;
  const T& operator[](int i) const;
  T& operator[](int i);

 private:
};

template <typename T, int alloc>
class StaticList : public List<T> {
 public:
  StaticList();

 private:
  ListMemory memory;
  void*      memoryPool[alloc];
};
}  // namespace DJI
#endif  // DJI_LIST_H
