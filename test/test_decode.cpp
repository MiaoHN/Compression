#include <cstring>
#include <iostream>

#include "file.h"
#include "huffman.h"

int main(int argc, char const *argv[]) {
  std::vector<char> source;
  std::string input_path = "tmp";
  if (argc == 2) {
    input_path = std::string(argv[1], strlen(argv[1]));
    source = GetRawFromFile(input_path);
  }

  ByteArray file_header;
  ByteArray bytes;

  huffman::SeparateFileHeader(source, file_header, bytes);



  return 0;
}
