#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include <map>

#include "byte_array.h"
#include "file.h"
#include "token.h"

namespace huffman {

struct TreeNode {
  Token token;
  int freq;
  TreeNode* left;
  TreeNode* right;

  TreeNode(Token token = Token(), int freq = 0, TreeNode* l = nullptr,
           TreeNode* r = nullptr)
      : token(token), freq(freq), left(l), right(r) {}

  bool IsLeaf() { return left == nullptr && right == nullptr; }
};

std::map<Token, int> GetConsequence(const std::vector<Token>& tokens);

TreeNode* CreateTree(std::map<Token, int>& counts);

std::map<Token, ByteArray> GenerateMap(TreeNode* root);

ByteArray GetDecodeBytes(const std::vector<Token>& tokens,
                         std::map<Token, ByteArray>& map);

ByteArray GenerateFileHeader(std::map<Token, int>& map);

ByteArray BindFileHeaderWithDecode(const ByteArray& file_header,
                                   const ByteArray& decoded);

bool OutputToFile(const std::string& output_path, const ByteArray& bytes);

bool SeparateFileHeader(const std::vector<char>& source, ByteArray& file_header,
                        ByteArray& bytes);

void compress(const std::string& file_name, const std::string& output_file);

void decompress(const std::string& file_name, const std::string& output_file);

}  // namespace huffman

#endif  // __HUFFMAN_H__