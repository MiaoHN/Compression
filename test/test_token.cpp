#include <iostream>

#include "token.h"

int main(int argc, char const* argv[]) {
  std::string str = "西安交通大学 - Xi'an JiaoTong University";
  auto tokens = Token::Tokenrise(str);

  for (auto& token : tokens) {
    std::cout << "value: " << token.ToString()
              << ", type: " << static_cast<int>(token.type) << std::endl;
  }
  return 0;
}
