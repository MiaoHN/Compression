#ifndef __BYTE_ARRAY_H__
#define __BYTE_ARRAY_H__

#include <iostream>
#include <vector>

#define TEST_BIT(c, offset) !!(c & (0x01 << offset))

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

  void PushInt(int number) {
    char c1 = number & 0xff000000 >> 24;
    char c2 = number & 0x00ff0000 >> 16;
    char c3 = number & 0x0000f000 >> 8;
    char c4 = number & 0x000000ff;
    PushChar(c1);
    PushChar(c2);
    PushChar(c3);
    PushChar(c4);
  }

  void PushChar(char c) {
    for (int i = 0; i < 8; ++i) {
      PushBit(TEST_BIT(c, i));
    }
  }

  void PushString(const std::string& str) {
    for (auto& c : str) {
      PushChar(c);
    }
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

  int GetOffset() const { return 7 - offset_; }

  std::string ToString() {
    std::string str;
    for (int i = 0; i < (capacity_ - 1) * 8 + offset_; ++i) {
      str += GetBit(i) ? "1" : "0";
    }
    return str;
  }

  std::vector<char> GetData() const { return data_; }

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