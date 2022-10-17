#include <cstring>

#include "file.h"
#include "huffman.h"

int main(int argc, char const* argv[]) {
  std::string source = "test";
  std::string input_path = "tmp";
  if (argc == 2) {
    input_path = std::string(argv[1], strlen(argv[1]));
    source = GetStringFromFile(input_path);
  }

  auto tokens = Token::Tokenrise(source);
  auto counts = huffman::GetConsequence(tokens);
  auto tree = huffman::CreateTree(counts);
  auto map = huffman::GenerateMap(tree);
  auto decode = huffman::GetDecodeBytes(tokens, map);
  auto file_header = huffman::GenerateFileHeader(counts);
  ByteArray final_bytes =
      huffman::BindFileHeaderWithDecode(file_header, decode);
  bool status = huffman::OutputToFile(input_path + ".huffman", final_bytes);

  std::cout << "map size: " << map.size() << std::endl;
  std::cout << "header length:   " << file_header.GetLength() / 8.0 << "bytes"
            << std::endl;
  std::cout << "raw text length: " << source.size() << " bytes" << std::endl;
  std::cout << "decoded length:  " << decode.GetLength() / 8.0 << "bytes"
            << std::endl;

  std::cout << "percent: " << (float)decode.GetLength() / (source.size() * 8)
            << "%" << std::endl;

  std::cout << "percent(with header): "
            << (float)final_bytes.GetLength() / (source.size() * 8) << "%"
            << std::endl;

  return 0;
}
