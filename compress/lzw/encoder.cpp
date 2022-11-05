#include <cstring>
#include <iostream>

#include "lzw.h"

void printHelp() { std::cout << "Usage: encoder file [secret]" << std::endl; }

int main(int argc, char const *argv[]) {
  if (argc == 2) {
    std::string file_name(argv[1], strlen(argv[1]));
    std::string output_name = file_name + ".lzw";
    lzw::compress(new lzw::SafeVariableLengthCompressor(18), file_name,
                  output_name);
    return 0;
  }
  if (argc == 3) {
    std::string file_name(argv[1], strlen(argv[1]));

    std::string output_name = file_name + ".lzw";

    int salt = std::stoi(std::string(argv[2], strlen(argv[2])));
    lzw::compress(new lzw::SafeVariableLengthCompressor(18, salt), file_name,
                  output_name);
    return 0;
  }
  printHelp();

  return 0;
}
