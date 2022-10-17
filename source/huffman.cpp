#include "huffman.h"

#include <algorithm>
#include <fstream>
#include <map>

namespace huffman {

std::map<Token, int> GetConsequence(const std::vector<Token>& tokens) {
  std::map<Token, int> counts;
  for (auto& token : tokens) {
    if (counts.find(token) == counts.end()) counts[token] = 0;
    ++counts[token];
  }
  return counts;
}

TreeNode* CreateTree(std::map<Token, int>& counts) {
  std::vector<TreeNode*> nodes;
  for (auto& item : counts) {
    nodes.emplace_back(new TreeNode(item.first, item.second));
  }
  sort(nodes.begin(), nodes.end(),
       [](TreeNode* a, TreeNode* b) { return a->freq > b->freq; });

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

void Dfs(std::map<Token, ByteArray>& map, ByteArray routine, TreeNode* node) {
  if (node->IsLeaf()) {
    map[node->token] = routine;
    return;
  }
  ByteArray left_routine = routine;
  ByteArray right_routine = routine;
  left_routine.PushBit(0);
  right_routine.PushBit(1);
  if (node->left) Dfs(map, left_routine, node->left);
  if (node->right) Dfs(map, right_routine, node->right);
}

std::map<Token, ByteArray> GenerateMap(TreeNode* root) {
  std::map<Token, ByteArray> result;
  Dfs(result, ByteArray(), root);
  return result;
}

ByteArray GetDecodeBytes(const std::vector<Token>& tokens,
                         std::map<Token, ByteArray>& map) {
  ByteArray result;

  for (const auto& token : tokens) {
    result += map[token];
  }

  return result;
}

ByteArray GenerateFileHeader(std::map<Token, int>& map) {
  ByteArray bytes;

  bytes.PushInt(map.size());

  for (auto& item : map) {
    bytes.PushString(item.first.ToString());
    bytes.PushInt(item.second);
  }

  return bytes;
}

ByteArray BindFileHeaderWithDecode(const ByteArray& file_header,
                                   const ByteArray& decoded) {
  ByteArray bytes;
  bytes += file_header;
  bytes.PushInt(decoded.GetOffset());
  bytes += decoded;
  return bytes;
}

bool OutputToFile(const std::string& output_path, const ByteArray& bytes) {
  std::ofstream f(output_path);
  if (f.fail()) {
    std::cout << "OutputToFile: Error opening file '" << output_path << "'!!!"
              << std::endl;
    return false;
  }

  f.write(bytes.GetData().data(), bytes.GetData().size());

  f.close();

  return true;
}

bool SeparateFileHeader(const std::vector<char>& source, ByteArray& file_header,
                        ByteArray& bytes) {
  int map_length = *(int*)&source[3];
  std::cout << map_length << std::endl;

  // TODO File header


  return false;
}

}  // namespace huffman
