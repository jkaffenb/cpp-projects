#ifndef PQ
#define PQ

template <typename T>
class priority_queue {
 private:
  int (*_cmp)(const T &, const T &);
  size_t _capacity;
  size_t _size;
  T* _data;

 public:
  priority_queue(int (*cmp)(const T &, const T &));
  void add(const T & item);
  void remove();
  T front() const;
  size_t size() const;
  size_t parent(size_t k);
  size_t left(size_t k);
  size_t right(size_t k);
  void reheap_up(size_t k);
  void swap(T &first, T &second);
  void reheap_down(size_t k);
};

#include "pq.cc"

#endif
