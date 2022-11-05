#include <cstring>
#include <iostream>

#include "lzw.h"

void printHelp() { std::cout << "Usage: decoder file [secret]" << std::endl; }

int main(int argc, char const *argv[]) {
  if (argc == 2) {
    std::string file_name(argv[1], strlen(argv[1]));
    lzw::decompress(new lzw::SafeVariableLengthDecompressor(18), file_name);
    return 0;
  }
  if (argc == 3) {
    std::string file_name(argv[1], strlen(argv[1]));

    int salt = std::stoi(std::string(argv[2], strlen(argv[2])));
    lzw::decompress(new lzw::SafeVariableLengthDecompressor(18, salt),
                    file_name);
    return 0;
  }

  printHelp();

  return 0;
}
