#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <string>
#include <vector>

class Token {
 public:
  Token(const char* ch);
  ~Token();

  static std::vector<Token> Tokenrise(const std::string& source);

  enum Type : uint8_t {
    Length8 = 0,   // 0xxxxxxx
    Length16 = 1,  // 110xxxxx 10xxxxxx
    Length24 = 2,  // 1110xxxx 10xxxxxx 10xxxxxx
    Length32 = 3,  // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    Length40 = 4,  // 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
    Length48 = 5,  // 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
  };

  std::string ToString() const;

  std::vector<char> value;
  Type type;
};

#endif  // __TOKEN_H__