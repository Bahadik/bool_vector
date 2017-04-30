#include "bool_array.h"

const size_t INTBITS = sizeof(int) * 8;

int BoolArray::Proxy::create_bit() const { return 1 << (p % INTBITS); }
BoolArray::Proxy::Proxy(BoolArray* rhs, size_t index) noexcept
    : bool_array(rhs),
      p(index) {}
BoolArray::Proxy::~Proxy() { bool_array = nullptr; };
BoolArray::Proxy::operator bool() const noexcept {
  int temp = bool_array->arr[p / INTBITS];
  return temp & create_bit();
}
BoolArray::Proxy& BoolArray::Proxy::operator=(const bool x) noexcept {
  int& temp = bool_array->arr[p / INTBITS];
  if (x) {
    temp |= create_bit();
  } else {
    temp &= ~create_bit();
  }
  return *this;
}
BoolArray::Proxy& BoolArray::Proxy::operator=(const Proxy& x) noexcept {
  return (*this = static_cast<bool>(x));
}
int BoolArray::create_bit_for_push() const {
  return 1 << (nubmer_of_bits_pushbacked);
}

BoolArray::BoolArray() = default;
BoolArray::~BoolArray() = default;

void BoolArray::push_back(bool x) {
  if (arr.size() == 0) {
    arr.push_back(0);
  }
  if (nubmer_of_bits_pushbacked < INTBITS) {
    if (x) {
      arr[arr.size() - 1] |= create_bit_for_push();

    } else {
      arr[arr.size() - 1] &= ~create_bit_for_push();
    }
  } else {
    nubmer_of_bits_pushbacked = 0;
    arr.push_back(0);
    if (x) {
      arr[arr.size() - 1] |= create_bit_for_push();
    } else {
      arr[arr.size() - 1] &= ~create_bit_for_push();
    }
  }
  ++nubmer_of_bits_pushbacked;
  return;
}

void BoolArray::pop_back() {
  --nubmer_of_bits_pushbacked;
  if (nubmer_of_bits_pushbacked < 0 && arr.size() != 0) {
    arr.pop_back();
    nubmer_of_bits_pushbacked = INTBITS;
  }
  return;
}

BoolArray::Proxy BoolArray::operator[](size_t p) { return Proxy(this, p); }

size_t BoolArray::size() const noexcept {
  return (arr.size() - 1) * INTBITS + nubmer_of_bits_pushbacked;
}
