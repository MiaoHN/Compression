#include "huffman.h"

#include <algorithm>
#include <map>

namespace huffman {

TreeNode* CreateTree(const std::vector<Token>& tokens) {
  // 1. Get Consequence of each Token
  std::map<Token, int> counts;
  for (auto& token : tokens) {
    if (counts.find(token) == counts.end()) counts[token] = 0;
    ++counts[token];
  }

  std::vector<TreeNode*> nodes;
  for (auto& item : counts) {
    nodes.emplace_back(new TreeNode(item.first, item.second));
  }
  sort(nodes.begin(), nodes.end(),
       [](TreeNode* a, TreeNode* b) { return a->freq > b->freq; });

  // 2. Generate tree
  while (nodes.size() > 1) {
    TreeNode* last1 = nodes.back();
    nodes.pop_back();
    TreeNode* last2 = nodes.back();
    nodes.pop_back();
    TreeNode* new_node =
        new TreeNode(Token(), last1->freq + last2->freq, last1, last2);
    int position;
    for (position = 0; position < nodes.size() - 1; ++position) {
      if (new_node->freq >= nodes[position]->freq) break;
    }
    nodes.insert(nodes.begin() + position, new_node);
  }

  return nodes[0];
}

}  // namespace huffman
