#ifndef _BOOLARRAY_
#define _BOOLARRAY_

#include <vector>
#include <cstddef>

extern const size_t INTBITS;

class BoolArray {
 private:
  std::vector<int> arr;
  size_t nubmer_of_bits_pushbacked = 0;

  class Proxy {
    friend class BoolArray;

   private:
    size_t p;
    BoolArray* bool_array;
    int create_bit() const;
    Proxy(BoolArray* rhs, size_t index) noexcept;

   public:
    ~Proxy();
    operator bool() const noexcept;
    Proxy& operator=(const bool x) noexcept;
    Proxy& operator=(const Proxy& x) noexcept;
  };
  int create_bit_for_push() const;

 public:
  BoolArray();
  ~BoolArray();
  void push_back(bool x);
  void pop_back();
  Proxy operator[](size_t p);
  size_t size() const noexcept;
};

#endif
