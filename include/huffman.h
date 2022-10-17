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

TreeNode* CreateTree(const std::vector<Token>& tokens);

std::map<Token, ByteArray> GenerateMap(TreeNode* root);

ByteArray GetDecodeBytes(const std::vector<Token>& tokens,
                         std::map<Token, ByteArray>& map);

}  // namespace huffman

#endif  // __HUFFMAN_H__