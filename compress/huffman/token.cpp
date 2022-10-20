#include "token.h"

#include <algorithm>
#include <cstring>
#include <iostream>

#define TEST_BIT(c, offset) !!(c & (0x01 << offset))

Token::Token(const char* ch) {
#if 1
  if (TEST_BIT(ch[0], 7) == 0) {
    type = Type::Length8;
    value.push_back(ch[0]);
    return;
  }
  if (TEST_BIT(ch[0], 7) == 1 && TEST_BIT(ch[0], 6) == 1 &&
      TEST_BIT(ch[0], 5) == 0 && TEST_BIT(ch[1], 7) == 1 &&
      TEST_BIT(ch[1], 6) == 0) {
    type = Type::Length16;
    value.push_back(ch[0]);
    value.push_back(ch[1]);
    return;
  }
  if (TEST_BIT(ch[0], 7) == 1 && TEST_BIT(ch[0], 6) == 1 &&
      TEST_BIT(ch[0], 5) == 1 && TEST_BIT(ch[0], 4) == 0 &&
      TEST_BIT(ch[1], 7) == 1 && TEST_BIT(ch[1], 6) == 0 &&
      TEST_BIT(ch[2], 7) == 1 && TEST_BIT(ch[2], 6) == 0) {
    type = Type::Length24;
    value.push_back(ch[0]);
    value.push_back(ch[1]);
    value.push_back(ch[2]);
    return;
  }
  if (TEST_BIT(ch[0], 7) == 1 && TEST_BIT(ch[0], 6) == 1 &&
      TEST_BIT(ch[0], 5) == 1 && TEST_BIT(ch[0], 4) == 1 &&
      TEST_BIT(ch[0], 3) == 0 && TEST_BIT(ch[1], 7) == 1 &&
      TEST_BIT(ch[1], 6) == 0 && TEST_BIT(ch[2], 7) == 1 &&
      TEST_BIT(ch[2], 6) == 0 && TEST_BIT(ch[3], 7) == 1 &&
      TEST_BIT(ch[3], 6) == 0) {
    type = Type::Length32;
    value.push_back(ch[0]);
    value.push_back(ch[1]);
    value.push_back(ch[2]);
    value.push_back(ch[3]);
    return;
  }
  if (TEST_BIT(ch[0], 7) == 1 && TEST_BIT(ch[0], 6) == 1 &&
      TEST_BIT(ch[0], 5) == 1 && TEST_BIT(ch[0], 4) == 1 &&
      TEST_BIT(ch[0], 3) == 0 && TEST_BIT(ch[0], 3) == 0 &&
      TEST_BIT(ch[1], 7) == 1 && TEST_BIT(ch[1], 6) == 0 &&
      TEST_BIT(ch[2], 7) == 1 && TEST_BIT(ch[2], 6) == 0 &&
      TEST_BIT(ch[3], 7) == 1 && TEST_BIT(ch[3], 6) == 0 &&
      TEST_BIT(ch[4], 7) == 1 && TEST_BIT(ch[4], 6) == 0) {
    type = Type::Length40;
    value.push_back(ch[0]);
    value.push_back(ch[1]);
    value.push_back(ch[2]);
    value.push_back(ch[3]);
    value.push_back(ch[4]);
    return;
  }
  if (TEST_BIT(ch[0], 7) == 1 && TEST_BIT(ch[0], 6) == 1 &&
      TEST_BIT(ch[0], 5) == 1 && TEST_BIT(ch[0], 4) == 1 &&
      TEST_BIT(ch[0], 3) == 0 && TEST_BIT(ch[0], 3) == 1 &&
      TEST_BIT(ch[0], 2) == 1 && TEST_BIT(ch[1], 7) == 1 &&
      TEST_BIT(ch[1], 6) == 0 && TEST_BIT(ch[2], 7) == 1 &&
      TEST_BIT(ch[2], 6) == 0 && TEST_BIT(ch[3], 7) == 1 &&
      TEST_BIT(ch[3], 6) == 0 && TEST_BIT(ch[4], 7) == 1 &&
      TEST_BIT(ch[4], 6) == 0 && TEST_BIT(ch[5], 7) == 1 &&
      TEST_BIT(ch[5], 6) == 0) {
    type = Type::Length48;
    value.push_back(ch[0]);
    value.push_back(ch[1]);
    value.push_back(ch[2]);
    value.push_back(ch[3]);
    value.push_back(ch[4]);
    value.push_back(ch[5]);
    return;
  }
#endif
  type = Type::Length8;
  value.push_back(ch[0]);
}

Token::~Token() = default;

std::vector<Token> Token::Tokenrise(const std::string& source) {
  std::vector<Token> tokens;

  for (int i = 0; i < source.size(); ++i) {
    tokens.emplace_back(Token(&(source[i])));
    i += static_cast<int>(tokens.back().type);
  }

  return tokens;
}

std::string Token::ToString() const {
  return std::string(value.data(), value.size());
}
