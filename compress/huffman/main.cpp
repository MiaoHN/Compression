#include <cstring>
#include <iostream>

#include "huffman.h"

void printHelp() {
  std::cout << "Usage: huffman [option] file" << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "  -c  compress" << std::endl;
  std::cout << "  -d  decompress" << std::endl;
}

int main(int argc, char const *argv[]) {
  if (argc > 2) {
    if (strcmp(argv[1], "-c") == 0) {
      // compress
      std::string file_name(argv[2], strlen(argv[2]));
      std::string output_name = file_name + ".huffman";
      huffman::compress(file_name, output_name);
    } else if (strcmp(argv[1], "-d") == 0) {
      // decompress
      std::string file_name(argv[2], strlen(argv[2]));
      std::string output_name = file_name + ".raw";
      huffman::decompress(file_name, output_name);
    } else {
      printHelp();
    }
  } else {
    printHelp();
  }

  return 0;
}
