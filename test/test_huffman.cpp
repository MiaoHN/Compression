#include <cstring>

#include "file.h"
#include "huffman.h"

int main(int argc, char const* argv[]) {
  std::string source = "test";
  if (argc == 2) {
    source = GetStringFromFile(std::string(argv[1], strlen(argv[1])));
  }

  auto tokens = Token::Tokenrise(source);
  auto tree = huffman::CreateTree(tokens);
  auto map = huffman::GenerateMap(tree);
  auto decode = huffman::GetDecodeBytes(tokens, map);
  auto file_header = huffman::GenerateFileHeader(map);
  bool status = huffman::OutputToFile(source + ".huffman", file_header, decode);

  std::cout << "map size: " << map.size() << std::endl;
  std::cout << "raw text length: " << source.size() << " bytes" << std::endl;
  std::cout << "decoded length:  " << decode.GetLength() / 8.0 << "bytes"
            << std::endl;

  std::cout << "percent: " << (float)decode.GetLength() / (source.size() * 8)
            << "%" << std::endl;

  return 0;
}
