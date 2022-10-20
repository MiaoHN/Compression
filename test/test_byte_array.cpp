#include <cassert>
#include <iostream>

#include "huffman/byte_array.h"

int main(int argc, char const *argv[]) {
  ByteArray bytes;
  bytes.PushBit(1);  // 0
  bytes.PushBit(0);  // 1
  bytes.PushBit(1);  // 2
  bytes.PushBit(0);  // 3
  bytes.PushBit(1);  // 4
  bytes.PushBit(0);  // 5
  bytes.PushBit(1);  // 6
  bytes.PushBit(0);  // 7
  bytes.PushBit(1);  // 8
  bytes.PushBit(0);  // 9
  bytes.PushBit(1);  // 10
  bytes.PushBit(0);  // 11
  bytes.PushBit(0);  // 12

  assert(bytes.GetBit(0) == 1);
  assert(bytes.GetBit(1) == 0);
  assert(bytes.GetBit(2) == 1);
  assert(bytes.GetBit(3) == 0);

  ByteArray b1;
  ByteArray b2;

  b1.PushBit(1);
  b1.PushBit(0);
  b2.PushBit(0);
  b2.PushBit(1);

  ByteArray add = b1 + b2;
  std::cout << b1.ToString() << " + " << b2.ToString() << " = "
            << add.ToString() << std::endl;

  return 0;
}
