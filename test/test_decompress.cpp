#include <cstring>
#include <iostream>

#include "lzw/lzw.h"

int main(int argc, char const *argv[]) {
  lzw::decompress("test.txt.lzw");
  return 0;
}
