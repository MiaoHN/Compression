#include "huffman.h"

int main(int argc, char const *argv[]) {
  std::string source = "abcdacae";

  auto tokens = Token::Tokenrise(source);
  auto tree = huffman::CreateTree(tokens);

  return 0;
}
