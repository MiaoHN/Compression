#include <iostream>
#include <vector>

#include "lzw/lzw.h"
#include "test.h"

using namespace lzw;

TEST(BitArray, Constructor) {
  BitArray bits1;
  BitArray bits2(10);
  BitArray bits3(10, 10);
  BitArray bits4("abcdefghijklmnopqrstuvwxyz");
  std::vector<char> vec = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
  BitArray bits5(vec);

  EXPECT_TRUE(bits1.getLength() == 0);
  EXPECT_TRUE(bits2.getLength() == 10);
  EXPECT_TRUE(bits3.getLength() == 10);
  EXPECT_TRUE(bits4.getLength() == 26 * 8);
  EXPECT_TRUE(bits5.getLength() == 7 * 8);
}

TEST(BitArray, PushBit) {
  BitArray bits;
  bits.pushBit(1);
  bits.pushBit(0);
  bits.pushBit(0);
  bits.pushBit(1);
  bits.pushBit(1);
  EXPECT_TRUE(bits.getBit(0) == 1);
  EXPECT_TRUE(bits.getBit(1) == 0);
  EXPECT_TRUE(bits.getBit(2) == 0);
  EXPECT_TRUE(bits.getBit(3) == 1);
  EXPECT_TRUE(bits.getBit(4) == 1);
}

TEST(BitArray, PushChar) {
  BitArray bits;
  bits.pushChar('a');
  bits.pushChar('b');
  bits.pushChar('c');
  bits.pushChar('d');
  bits.pushChar('e');
  EXPECT_TRUE(bits.popFrontInt(8) == 'a');
  EXPECT_TRUE(bits.popFrontInt(8) == 'b');
  EXPECT_TRUE(bits.popFrontInt(8) == 'c');
  EXPECT_TRUE(bits.popFrontInt(8) == 'd');
  EXPECT_TRUE(bits.popFrontInt(8) == 'e');
  EXPECT_TRUE(bits.bitsToRead() == 0);
}

TEST(BitArray, PopFront) {
  BitArray bits;
  bits.pushString("0123456789");
  bits.setCursor(8);
  EXPECT_TRUE(bits.popFront(8) == BitArray('1', 8));
}

TEST(BitArray, Compare) {
  BitArray bits1("11111");
  BitArray bits2("11111");
  BitArray bits3("12111");
  BitArray bits4("121111");
  EXPECT_TRUE(bits1 == bits2);
  EXPECT_TRUE(bits2 < bits3);
  EXPECT_TRUE(bits3 < bits4);
}