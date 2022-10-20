#ifndef __LZW_H__
#define __LZW_H__

#include <map>
#include <string>
#include <vector>

#include "bit_array.h"

namespace lzw {

namespace detail {

class Lzw {
 public:
  Lzw(int part_len = 8, int code_len = 12);

  std::vector<char> compress(const std::vector<char>& bytes);

  std::vector<char> decompress(const std::vector<char>& bytes);

 private:
  int part_len_;      // 分段长度
  int max_code_len_;  // 编码长度，同时为字典最大值

  int dict_size_;  //初始字典大小
  int sig_clear_;  // clear 符号
};

}  // namespace detail

void compress(const std::string& file_name, const std::string& output_name,
              int part_len = 8, int code_len = 12);

void decompress(const std::string& file_name);

}  // namespace lzw

#endif  // __LZW_H__