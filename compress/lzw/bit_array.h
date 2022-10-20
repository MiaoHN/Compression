#ifndef __BIT_ARRAY_H__
#define __BIT_ARRAY_H__

#include <string>
#include <vector>

class BitArray {
 public:
  BitArray(int len);

  BitArray(int value, int len);

  BitArray();
  BitArray(const std::string& source);
  BitArray(const std::vector<char>& source);
  ~BitArray();

  BitArray popFront(int len);

  int popFrontInt(int len);

  bool popFrontBit();

  void pushBit(bool bit);

  void setInt(int num);

  void pushInt(int number, int length = 32);

  void setCursor(int cursor);

  void pushChar(char c);

  void pushString(const std::string& str);

  void pushVector(const std::vector<char>& str);

  bool getBit(int position) const;
  void setBit(int position, int value);

  bool operator<(const BitArray& rhs) const;

  void operator+=(const BitArray& rhs);

  bool operator==(const BitArray& rhs) const;

  BitArray operator+(const BitArray& rhs);

  bool empty() const { return data_.empty(); }

  int bitsToRead() const { return getLength() - cursor_; }

  int getLength() const;

  int getOffset() const;

  std::string toString() const;

  std::vector<char> getData() const;

  void clear();

 private:
  void resize(int size);

 private:
  std::vector<char> data_;

  int cursor_;  // read position
  int offset_;  // last byte of data_
};

#endif  // __BIT_ARRAY_H__