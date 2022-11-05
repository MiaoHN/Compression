#ifndef __LZW_H__
#define __LZW_H__

#include <map>
#include <string>
#include <vector>

#include "bit_array.h"

namespace lzw {

class Compressor {
 public:
  virtual std::vector<char> compress(const std::vector<char>& bytes) = 0;

 private:
};

class Decompressor {
 public:
  virtual std::vector<char> decompress(const std::vector<char>& bytes) = 0;
};

class BasicCompressor : public Compressor {
 public:
  std::vector<char> compress(const std::vector<char>& bytes) override;
};

class BasicDecompressor : public Decompressor {
 public:
  std::vector<char> decompress(const std::vector<char>& bytes) override;
};

class VariableLengthCompressor : public Compressor {
 public:
  VariableLengthCompressor(int codeLength = 12);

  std::vector<char> compress(const std::vector<char>& bytes) override;

 private:
  int maxCodeLength_;
  int sigClear_;
};

class VariableLengthDecompressor : public Decompressor {
 public:
  VariableLengthDecompressor(int codeLength = 12);

  std::vector<char> decompress(const std::vector<char>& bytes) override;

 private:
  int maxCodeLength_;
  int sigClear_;
};

class SafeVariableLengthCompressor : public Compressor {
 public:
  SafeVariableLengthCompressor(int salt = 0, int codeLength = 12);

  std::vector<char> compress(const std::vector<char>& bytes) override;

 private:
  int salt_;

  int maxCodeLength_;
  int sigClear_;
};

class SafeVariableLengthDecompressor : public Decompressor {
 public:
  SafeVariableLengthDecompressor(int salt = 0, int codeLength = 12);

  std::vector<char> decompress(const std::vector<char>& bytes) override;

 private:
  int salt_;

  int maxCodeLength_;
  int sigClear_;
};

void compress(Compressor* compressor, const std::string& fileName,
              const std::string& outputName = "");

void decompress(Decompressor* decompressor, const std::string& fileName,
                const std::string& outputName = "");

}  // namespace lzw

#endif  // __LZW_H__