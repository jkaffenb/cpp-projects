
template <typename T>
priority_queue<T>::priority_queue(int (*cmp)(const T &, const T &))
{
  _size = 0;
  _capacity = 256;
  _data = new T[_capacity];
  _cmp = cmp;
}

template <typename T>
void priority_queue<T>::add(const T & item)
{
  _data[_size] = item;
  reheap_up(_size);
  _size++;
}

template <typename T>
void priority_queue<T>::remove()
{
  _data[0] = _data[_size-1];
  _size --;
  reheap_down(0);
}

template <typename T>
T priority_queue<T>::front() const
{
  return _data[0];
}

template <typename T>
size_t priority_queue<T>::size() const
{
  return _size;
}

template <typename T>
size_t priority_queue<T>::parent(size_t k)
{
  return (k-1)/2;
}

template <typename T>
size_t priority_queue<T>::left(size_t k)
{
  return (k*2) +1;
}

template <typename T>
size_t priority_queue<T>::right(size_t k)
{
  return (2*k) +2;
}

template <typename T>
void priority_queue<T>::reheap_up(size_t k)
{
  while (k> 0 and _cmp(_data[k], _data[parent(k)]) < 0){
    swap(_data[k], _data[parent(k)]);
    k = parent(k);
  }
}

template <typename T>
void priority_queue<T>::swap(T &first, T &second)
{
  T temp = first;
  first = second;
  second = temp;
}

template <typename T>
void priority_queue<T>::reheap_down(size_t k)
{
  // Find the smallest of a root, left and right field, and swap root with the
  // smallest, repeat until root is the smallest.
  size_t largest = k;

  if (left(k) < _size and _cmp(_data[left(k)], _data[largest]) < 0)
    largest = left(k);

  if (right(k) < _size and _cmp(_data[right(k)], _data[largest]) < 0)
    largest = right(k);

  if (largest != k){
    swap(_data[k], _data[largest]);
    reheap_down(largest);
  }
}
