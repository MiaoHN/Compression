#ifndef __BYTE_ARRAY_H__
#define __BYTE_ARRAY_H__

#include <iostream>
#include <vector>

class ByteArray {
 public:
  ByteArray() : capacity_(0), offset_(0) {}
  ~ByteArray() {}

  void PushBit(bool bit) {
    if (offset_ == 7 || capacity_ == 0) {
      Resize(capacity_ + 1);
    }
    if (bit == true) {
      data_[capacity_ - 1] |= (0x01 << (7 - offset_));
    } else {
      data_[capacity_ - 1] &= ~(0x01 << (7 - offset_));
    }
    offset_ = (offset_ + 1) % 8;
  }

  bool GetBit(int position) const {
    int cursor = position / 8;
    int offset = position % 8;
    return !!(data_[cursor] & (0x01 << (7 - offset)));
  }

  void operator+=(const ByteArray& rhs) {
    for (int i = 0; i < rhs.GetLength(); ++i) {
      PushBit(rhs.GetBit(i));
    }
  }

  ByteArray operator+(const ByteArray& rhs) {
    ByteArray bytes(*this);

    for (int i = 0; i < rhs.GetLength(); ++i) {
      bytes.PushBit(rhs.GetBit(i));
    }

    return bytes;
  }

  int GetLength() const { return (capacity_ - 1) * 8 + offset_; }

  std::string ToString() {
    std::string str;
    for (int i = 0; i < (capacity_ - 1) * 8 + offset_; ++i) {
      str += GetBit(i) ? "1" : "0";
    }
    return str;
  }

 private:
  void Resize(int size) {
    if (size < capacity_) {
      std::cout << "ByteArray::Resize: Warning!!! new size is lower than before"
                << std::endl;
    }
    data_.resize(size);
    capacity_ = size;
  }

 private:
  std::vector<char> data_;

  int capacity_;  // length of data_
  int offset_;    // last byte of data_
};

#endif  // __BYTE_ARRAY_H__