#include "bit_array.h"

#include <iostream>

BitArray::BitArray(int len) : cursor_(0), offset_(-1) {
  for (int i = 0; i < len; ++i) pushBit(0);
}

BitArray::BitArray() : cursor_(0), offset_(-1) {}

BitArray::BitArray(int value, int len) : cursor_(0), offset_(-1) {
  pushInt(value, len);
}

BitArray::BitArray(const std::string& source) : cursor_(0), offset_(-1) {
  pushString(source);
}

BitArray::BitArray(const std::vector<char>& source) : cursor_(0), offset_(-1) {
  pushVector(source);
}
BitArray::~BitArray() {}

void BitArray::pushBit(bool bit) {
  if (data_.empty() || offset_ == 7) {
    resize(data_.size() + 1);
  }
  offset_ = (offset_ + 1) % 8;
  if (bit == true) {
    data_.back() |= (0x01 << (7 - offset_));
  } else {
    data_.back() &= ~(0x01 << (7 - offset_));
  }
}

void BitArray::setInt(int num) {
  // if (getLength() > 32) {
  //   std::cout << "BitArray::setInt(int): Unimplement length!" << std::endl;
  //   return;
  // }
  for (int i = 0; i < getLength(); ++i) {
    setBit(i, !!(num & (1 << (getLength() - i - 1))));
  }
}

void BitArray::pushInt(int number, int length) {
  unsigned char val;
  for (int i = length - 1; i >= 0; --i) {
    val = (number >> i) & 1;
    pushBit(val);
  }
}

void BitArray::setCursor(int cursor) { cursor_ = cursor; }

void BitArray::pushChar(char c) {
  for (int i = 0; i < 8; ++i) {
    auto bit = !!(c & (1 << (7 - i)));
    pushBit(bit);
  }
}

void BitArray::pushString(const std::string& str) {
  for (auto& c : str) {
    pushChar(c);
  }
}

void BitArray::pushVector(const std::vector<char>& str) {
  for (auto& c : str) {
    pushChar(c);
  }
}

bool BitArray::getBit(int position) const {
  int cursor = position / 8;
  int offset = position % 8;
  return (data_[cursor] >> (7 - offset)) & 0x01;
}

void BitArray::setBit(int position, int value) {
  if (position >= getLength()) {
    return;
  }
  int index = position / 8;
  int offset = position - index * 8;
  if (value == true) {
    data_[index] |= (0x01 << (7 - offset));
  } else {
    data_[index] &= ~(0x01 << (7 - offset));
  }
}

bool BitArray::operator<(const BitArray& rhs) const {
  int length1 = getLength();
  int length2 = rhs.getLength();
  int len = std::min(length1, length2);
  for (int i = 0; i < len; ++i) {
    bool bit1 = getBit(i);
    bool bit2 = rhs.getBit(i);
    if (bit1 == bit2) continue;
    if (bit1 < bit2) {
      return true;
    } else {
      return false;
    }
  }
  return length1 < length2;
}

void BitArray::operator+=(const BitArray& rhs) {
  for (int i = 0; i < rhs.getLength(); ++i) {
    pushBit(rhs.getBit(i));
  }
}

bool BitArray::operator==(const BitArray& rhs) const {
  if (getLength() != rhs.getLength()) return false;
  for (int i = 0; i < getLength(); ++i) {
    if (getBit(i) != rhs.getBit(i)) return false;
  }
  return true;
}

BitArray BitArray::operator+(const BitArray& rhs) {
  BitArray bytes(*this);
  bytes.cursor_ = 0;

  for (int i = 0; i < rhs.getLength(); ++i) {
    bytes.pushBit(rhs.getBit(i));
  }

  return bytes;
}

int BitArray::getLength() const {
  if (empty())
    return 0;
  else
    return data_.size() * 8 + offset_ - 7;
}

int BitArray::getOffset() const { return 7 - offset_; }

std::string BitArray::toString() const {
  std::string str;
  for (int i = 0; i < getLength(); ++i) {
    str += getBit(i) ? "1" : "0";
  }
  return str;
}

std::vector<char> BitArray::getData() const { return data_; }

void BitArray::clear() {
  data_.clear();
  cursor_ = 0;
  offset_ = 0;
}

void BitArray::resize(int size) {
  if (size < data_.size()) {
    std::cout << "BitArray::Resize: Warning!!! new size is lower than before"
              << std::endl;
  }
  data_.resize(size);
}

BitArray BitArray::popFront(int len) {
  BitArray result;
  for (int i = 0; i < len; ++i) {
    if (cursor_ + i >= getLength()) {
      cursor_ = getLength();
      return result;
    }
    result.pushBit(getBit(cursor_ + i));
  }
  cursor_ += len;
  return result;
}

int BitArray::popFrontInt(int len) {
  int result = 0;
  while (len--) {
    result |= popFrontBit();
    if (len > 0) result <<= 1;
  }
  return result;
}

bool BitArray::popFrontBit() { return popFront(1).getBit(0); }