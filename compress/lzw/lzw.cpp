#include "lzw.h"

#include <cstring>
#include <fstream>
#include <iostream>

#include "random_generator.h"

namespace lzw {

std::vector<char> BasicCompressor::compress(const std::vector<char>& bytes) {
  BitArray result;

  std::map<std::string, int> dict;
  for (int i = 0; i < (1 << 8); i++) {
    dict[std::string(1, i)] = dict.size();
  }

  std::string p;

  for (int i = 0; i < bytes.size(); ++i) {
    std::string c;
    c += bytes[i];
    if (dict.find(p + c) != dict.end()) {
      p += c;
    } else {
      int code = dict[p];
      result.pushInt(code, 12);
      dict[p + c] = dict.size();
      if (dict.size() >= 4095) {
        dict.clear();
        for (int i = 0; i < (1 << 8); i++) {
          dict[std::string(1, i)] = dict.size();
        }
        result.pushInt(4095, 12);
      }
      p = c;
    }
  }
  if (!p.empty()) result.pushInt(dict[p], 12);

  return result.getData();
}

std::vector<char> BasicDecompressor::decompress(
    const std::vector<char>& bytes) {
  BitArray input_stream(bytes);

  std::string result;

  std::map<int, std::string> dict;
  std::map<int, std::string>::iterator iter;
  for (int i = 0; i < (1 << 8); ++i) {
    dict[dict.size()] = std::string(1, i);
  }

  int code;

  std::string old_bits, new_bits;

  code = input_stream.popFrontInt(12);
  if (input_stream.bitsToRead() >= 0) {
    old_bits = dict[code];
    result += old_bits;
  }

  while (input_stream.bitsToRead() >= 12) {
    code = input_stream.popFrontInt(12);

    if (code == 4095) {
      dict.clear();
      for (int i = 0; i < (1 << 8); i++) {
        dict[dict.size()] = std::string(1, i);
      }
      old_bits.clear();
      new_bits.clear();
      code = input_stream.popFrontInt(12);
      if (input_stream.bitsToRead() >= 12) {
        old_bits = dict[code];
        result += old_bits;
      }
      continue;
    }

    if ((iter = dict.find(code)) != dict.end()) {
      new_bits = iter->second;
      dict[dict.size()] = old_bits + new_bits[0];
    } else {
      new_bits = old_bits + old_bits[0];
      dict[dict.size()] = new_bits;
    }

    result += new_bits;
    old_bits = new_bits;
  }

  return std::vector<char>(result.begin(), result.end());
}

VariableLengthCompressor::VariableLengthCompressor(int codeLength)
    : maxCodeLength_(codeLength), sigClear_((1 << maxCodeLength_) - 1) {}

std::vector<char> VariableLengthCompressor::compress(
    const std::vector<char>& bytes) {
  BitArray result;

  std::map<std::string, int> dict;
  for (int i = 0; i < (1 << 8); i++) {
    dict[std::string(1, i)] = dict.size();
  }

  int codeLength = 9;

  std::string p;

  for (int i = 0; i < bytes.size(); ++i) {
    std::string c;
    c += bytes[i];
    if (dict.find(p + c) != dict.end()) {
      p += c;
    } else {
      int code = dict[p];
      while (code >= (1 << codeLength) - 1 && codeLength <= maxCodeLength_) {
        result.pushInt((1 << codeLength) - 1, codeLength);
        codeLength++;
      }
      result.pushInt(code, codeLength);
      dict[p + c] = dict.size();
      if (dict.size() >= sigClear_) {
        dict.clear();
        for (int i = 0; i < (1 << 8); i++) {
          dict[std::string(1, i)] = dict.size();
        }
        result.pushInt(sigClear_, maxCodeLength_);

        codeLength = 9;
      }
      p = c;
    }
  }
  if (!p.empty()) result.pushInt(dict[p], codeLength);

  return result.getData();
}

VariableLengthDecompressor::VariableLengthDecompressor(int codeLength)
    : maxCodeLength_(codeLength), sigClear_((1 << maxCodeLength_) - 1) {}

std::vector<char> VariableLengthDecompressor::decompress(
    const std::vector<char>& bytes) {
  BitArray input_stream(bytes);
  std::string result;

  std::map<int, std::string> dict;
  std::map<int, std::string>::iterator iter;
  for (int i = 0; i < (1 << 8); ++i) {
    dict[dict.size()] = std::string(1, i);
  }

  int code;
  int codeLength = 9;

  std::string old_bits, new_bits;

  code = input_stream.popFrontInt(codeLength);
  if (input_stream.bitsToRead() >= 0) {
    old_bits = dict[code];
    result += old_bits;
  }

  while (input_stream.bitsToRead() >= codeLength) {
    code = input_stream.popFrontInt(codeLength);

    if (code == sigClear_) {
      dict.clear();
      for (int i = 0; i < (1 << 8); i++) {
        dict[dict.size()] = std::string(1, i);
      }
      old_bits.clear();
      new_bits.clear();
      codeLength = 9;
      code = input_stream.popFrontInt(codeLength);
      if (input_stream.bitsToRead() >= codeLength) {
        old_bits = dict[code];
        result += old_bits;
      }
      continue;
    }

    while (code == (1 << codeLength) - 1 && codeLength <= maxCodeLength_ &&
           input_stream.bitsToRead() >= codeLength) {
      codeLength++;
      code = input_stream.popFrontInt(codeLength);
    }

    if ((iter = dict.find(code)) != dict.end()) {
      new_bits = iter->second;
      dict[dict.size()] = old_bits + new_bits[0];
    } else {
      new_bits = old_bits + old_bits[0];
      dict[dict.size()] = new_bits;
    }

    result += new_bits;
    old_bits = new_bits;
  }

  return std::vector<char>(result.begin(), result.end());
}

SafeVariableLengthCompressor::SafeVariableLengthCompressor(int salt,
                                                           int codeLength)
    : salt_(salt),
      maxCodeLength_(codeLength),
      sigClear_((1 << maxCodeLength_) - 1) {}

std::vector<char> SafeVariableLengthCompressor::compress(
    const std::vector<char>& bytes) {
  RandomGenerator generator(salt_, maxCodeLength_);
  BitArray result;

  std::map<std::string, int> dict;
  for (int i = 0; i < (1 << 8); i++) {
    dict[std::string(1, i)] = generator.get();
  }

  int codeLength = 9;

  std::string p;

  for (int i = 0; i < bytes.size(); ++i) {
    std::string c;
    c += bytes[i];
    if (dict.find(p + c) != dict.end()) {
      p += c;
    } else {
      int code = dict[p];
      while (code >= (1 << codeLength) - 1 && codeLength <= maxCodeLength_) {
        result.pushInt((1 << codeLength) - 1, codeLength);
        codeLength++;
      }
      result.pushInt(code, codeLength);
      dict[p + c] = generator.get();
      if (dict.size() >= sigClear_) {
        dict.clear();
        generator.reset();
        for (int i = 0; i < (1 << 8); i++) {
          dict[std::string(1, i)] = generator.get();
        }
        result.pushInt(sigClear_, maxCodeLength_);

        codeLength = 9;
      }
      p = c;
    }
  }
  if (!p.empty()) result.pushInt(dict[p], codeLength);

  return result.getData();
}

SafeVariableLengthDecompressor::SafeVariableLengthDecompressor(int salt,
                                                               int codeLength)
    : salt_(salt),
      maxCodeLength_(codeLength),
      sigClear_((1 << maxCodeLength_) - 1) {}

std::vector<char> SafeVariableLengthDecompressor::decompress(
    const std::vector<char>& bytes) {
  BitArray input_stream(bytes);
  RandomGenerator generator(salt_, maxCodeLength_);
  std::string result;

  std::map<int, std::string> dict;
  std::map<int, std::string>::iterator iter;
  for (int i = 0; i < (1 << 8); ++i) {
    dict[generator.get()] = std::string(1, i);
  }

  int code;
  int codeLength = 9;

  std::string old_bits, new_bits;

  code = input_stream.popFrontInt(codeLength);
  if (input_stream.bitsToRead() >= 0) {
    old_bits = dict[code];
    result += old_bits;
  }

  while (input_stream.bitsToRead() >= codeLength) {
    code = input_stream.popFrontInt(codeLength);

    if (code == sigClear_) {
      dict.clear();
      generator.reset();
      for (int i = 0; i < (1 << 8); i++) {
        dict[generator.get()] = std::string(1, i);
      }
      old_bits.clear();
      new_bits.clear();
      codeLength = 9;
      code = input_stream.popFrontInt(codeLength);
      if (input_stream.bitsToRead() >= codeLength) {
        old_bits = dict[code];
        result += old_bits;
      }
      continue;
    }

    while (code == (1 << codeLength) - 1 && codeLength <= maxCodeLength_ &&
           input_stream.bitsToRead() >= codeLength) {
      codeLength++;
      code = input_stream.popFrontInt(codeLength);
    }

    if ((iter = dict.find(code)) != dict.end()) {
      new_bits = iter->second;
      dict[generator.get()] = old_bits + new_bits[0];
    } else {
      new_bits = old_bits + old_bits[0];
      dict[generator.get()] = new_bits;
    }

    result += new_bits;
    old_bits = new_bits;
  }

  return std::vector<char>(result.begin(), result.end());
}

void compress(Compressor* compressor, const std::string& fileName,
              const std::string& outputName) {
  std::ifstream f(fileName);
  if (f.fail()) {
    std::cout << "error to open '" << fileName << "'!!!" << std::endl;
    return;
  }

  std::vector<char> buffer((std::istreambuf_iterator<char>(f)),
                           std::istreambuf_iterator<char>());
  f.close();

  std::vector<char> result = compressor->compress(buffer);

  std::ofstream out((outputName == "") ? (fileName + ".lzw") : outputName);
  out.write(result.data(), result.size());
  out.close();
}

void decompress(Decompressor* decompressor, const std::string& fileName,
                const std::string& outputName) {
  std::ifstream f(fileName);
  if (f.fail()) {
    std::cout << "error to open '" << fileName << "'!!!" << std::endl;
    return;
  }

  std::vector<char> buffer((std::istreambuf_iterator<char>(f)),
                           std::istreambuf_iterator<char>());
  f.close();

  std::vector<char> result = decompressor->decompress(buffer);

  std::ofstream out((outputName == "") ? (fileName + ".raw") : outputName);
  out.write(result.data(), result.size());
  out.close();
}

}  // namespace lzw
