#ifndef __FILE_H__
#define __FILE_H__

#include <string>
#include <vector>

std::vector<char> GetRawFromFile(const std::string& path);

std::string GetStringFromFile(const std::string& path);

#endif  // __FILE_H__