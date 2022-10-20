#include <cstring>
#include <iostream>

#include "lzw/lzw.h"

int main(int argc, char const *argv[]) {
  lzw::compress("test.txt", "test.txt.8.10.lzw", 8, 10);
  std::cout << __LINE__ << std::endl;
  lzw::compress("test.txt", "test.txt.8.12.lzw", 8, 12);
  std::cout << __LINE__ << std::endl;
  lzw::compress("test.txt", "test.txt.8.14.lzw", 8, 14);
  std::cout << __LINE__ << std::endl;
  lzw::compress("test.txt", "test.txt.8.16.lzw", 8, 16);
  std::cout << __LINE__ << std::endl;
  lzw::compress("test.txt", "test.txt.8.20.lzw", 8, 20);
  std::cout << __LINE__ << std::endl;
  return 0;
}
