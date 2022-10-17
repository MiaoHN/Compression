#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include <map>

#include "byte_array.h"
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

struct FileHeader {
  std::map<Token, ByteArray> map;
  int length;
};

TreeNode* CreateTree(const std::vector<Token>& tokens);

std::map<Token, ByteArray> GenerateMap(TreeNode* root);

ByteArray GetDecodeBytes(const std::vector<Token>& tokens,
                         std::map<Token, ByteArray>& map);

ByteArray GenerateFileHeader(std::map<Token, ByteArray>& map);

bool OutputToFile(const std::string& output_path, const ByteArray& file_header,
                  const ByteArray& decoded);

}  // namespace huffman

#endif  // __HUFFMAN_H__