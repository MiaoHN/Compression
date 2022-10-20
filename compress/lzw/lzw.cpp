#include "lzw.h"

#include <cstring>
#include <fstream>
#include <iostream>

namespace lzw {

namespace detail {

Lzw::Lzw(int part_len, int code_len)
    : part_len_(part_len),
      max_code_len_(code_len),
      dict_size_(1 << part_len_),
      sig_clear_((1 << max_code_len_) - 1) {}

std::vector<char> Lzw::compress(const std::vector<char>& bytes) {
  BitArray input_stream(bytes);
  BitArray result;
  // 将压缩的参数保存到前两个 char 中
  result.pushChar(static_cast<char>(part_len_));
  result.pushChar(static_cast<char>(max_code_len_));

  std::map<BitArray, int> dict;
  for (int i = 0; i < dict_size_; i++) {
    dict[BitArray(i, part_len_)] = i;
  }

  int code_len = part_len_ + 1;
  int code_index = dict.size();

  BitArray p;

  while (input_stream.bitsToRead() >= part_len_) {
    BitArray c = input_stream.popFront(part_len_);
    if (dict.find(p + c) != dict.end()) {
      p += c;
    } else {
      int code = dict[p];
      while (code >= (1 << code_len) - 1 && code_len <= max_code_len_) {
        result.pushInt((1 << code_len) - 1, code_len);
        code_len++;
      }
      result.pushInt(code, code_len);
      dict[p + c] = code_index++;
      if (code_index >= sig_clear_) {
        dict.clear();
        for (int i = 0; i < dict_size_; i++) {
          dict[BitArray(i, part_len_)] = i;
        }
        result.pushInt(sig_clear_, max_code_len_);

        code_len = part_len_ + 1;
        code_index = dict_size_;
      }
      p = c;
    }
  }
  if (!p.empty()) result.pushInt(dict[p], code_len);

  return result.getData();
}

std::vector<char> Lzw::decompress(const std::vector<char>& bytes) {
  BitArray input_stream(bytes);
  BitArray result;

  std::map<int, BitArray> dict;
  std::map<int, BitArray>::iterator iter;
  for (int i = 0; i < dict_size_; ++i) {
    dict[i] = BitArray(i, part_len_);
  }

  int code;
  int code_len = part_len_ + 1;
  int code_index = dict_size_;

  BitArray old_bits, new_bits;

  code = input_stream.popFrontInt(code_len);
  if (input_stream.bitsToRead() >= 0) {
    old_bits = dict[code];
    result += old_bits;
  }

  while (input_stream.bitsToRead() >= code_len) {
    code = input_stream.popFrontInt(code_len);

    if (code == sig_clear_) {
      dict.clear();
      for (int i = 0; i < dict_size_; i++) {
        dict[i] = BitArray(i, part_len_);
      }
      old_bits.clear();
      new_bits.clear();
      code_len = part_len_ + 1;
      code_index = dict_size_;
      code = input_stream.popFrontInt(code_len);
      if (input_stream.bitsToRead() >= code_len) {
        old_bits = dict[code];
        result += old_bits;
      }
      continue;
    }

    while (code == (1 << code_len) - 1 && code_len <= max_code_len_ &&
           input_stream.bitsToRead() >= code_len) {
      code_len++;
      code = input_stream.popFrontInt(code_len);
    }

    if ((iter = dict.find(code)) != dict.end()) {
      new_bits = iter->second;
      dict[code_index++] = old_bits + new_bits.popFront(part_len_);
    } else {
      BitArray tmp = old_bits;
      tmp.setCursor(0);
      new_bits = old_bits + tmp.popFront(part_len_);
      dict[code_index++] = new_bits;
    }

    result += new_bits;
    old_bits = new_bits;
  }

  return result.getData();
}

}  // namespace detail

void compress(const std::string& file_name, const std::string& output_name,
              int part_len, int code_len) {
  std::string input_path = file_name;
  std::ifstream f(input_path);
  if (f.fail()) {
    std::cout << "error to open '" << file_name << "'!!!" << std::endl;
    return;
  }

  std::vector<char> buffer((std::istreambuf_iterator<char>(f)),
                           std::istreambuf_iterator<char>());
  f.close();

  detail::Lzw lzw(part_len, code_len);
  std::vector<char> result = lzw.compress(buffer);

  std::ofstream out(output_name);
  out.write(result.data(), result.size());
  out.close();
}

void decompress(const std::string& file_name) {
  std::string input_path = file_name;
  std::ifstream f(input_path);
  if (f.fail()) {
    std::cout << "error to open '" << file_name << "'!!!" << std::endl;
    return;
  }

  std::vector<char> buffer((std::istreambuf_iterator<char>(f)),
                           std::istreambuf_iterator<char>());
  f.close();

  int part_len = static_cast<int>(buffer[0]);
  int code_len = static_cast<int>(buffer[1]);
  buffer.erase(buffer.begin());
  buffer.erase(buffer.begin());

  detail::Lzw lzw(part_len, code_len);
  std::vector<char> result = lzw.decompress(buffer);

  std::string output_path = input_path + ".raw";

  std::ofstream out(output_path);
  out.write(result.data(), result.size());
  out.close();
}

}  // namespace lzw
