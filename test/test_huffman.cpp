#include <cstring>

#include "file.h"
#include "huffman.h"

int main(int argc, char const* argv[]) {
  std::string source = "test";
  if (argc == 2) {
    source = GetStringFromFile(std::string(argv[1], strlen(argv[1])));
  }

  std::cout << "tokenrising..." << std::endl;
  auto tokens = Token::Tokenrise(source);
  std::cout << "tokenrisd done" << std::endl;
  std::cout << "tree creating..." << std::endl;
  auto tree = huffman::CreateTree(tokens);
  std::cout << "tree created done" << std::endl;
  std::cout << "map generating..." << std::endl;
  auto map = huffman::GenerateMap(tree);
  std::cout << "map generated done" << std::endl;
  std::cout << "decoding..." << std::endl;
  auto decode = huffman::GetDecodeBytes(tokens, map);
  std::cout << "decoded done" << std::endl;

  std::cout << "map size: " << map.size() << std::endl;

  std::cout << "raw text length: " << source.size() << " bytes" << std::endl;
  std::cout << "decoded length:  " << decode.GetLength() / 8.0 << "bytes"
            << std::endl;

  std::cout << "percent: " << (float)decode.GetLength() / (source.size() * 8)
            << "%" << std::endl;

  return 0;
}
