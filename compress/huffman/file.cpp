#include "file.h"

#include <fstream>
#include <iostream>

std::vector<char> GetRawFromFile(const std::string& path) {
  std::ifstream f(path, std::ios::binary);
  if (f.fail()) {
    std::cout << "GetStringFromFile: Error to open file '" << path << "'!!!"
              << std::endl;
    exit(-1);
  }
  std::vector<char> buffer((std::istreambuf_iterator<char>(f)),
                           std::istreambuf_iterator<char>());
  return buffer;
}

std::string GetStringFromFile(const std::string& path) {
  std::ifstream f(path, std::ios::binary);
  if (f.fail()) {
    std::cout << "GetStringFromFile: Error to open file '" << path << "'!!!"
              << std::endl;
    exit(-1);
  }
  std::string buffer((std::istreambuf_iterator<char>(f)),
                     std::istreambuf_iterator<char>());
  return buffer;
}
