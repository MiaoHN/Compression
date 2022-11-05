#ifndef __RANDOM_GENERATOR_H__
#define __RANDOM_GENERATOR_H__

#include <algorithm>
#include <random>
#include <vector>

class RandomGenerator {
 public:
  RandomGenerator(int salt, int maxLen)
      : salt_(salt), maxLen_(maxLen), cursor_(0) {
    initIntegers();
  }

  void reset() { cursor_ = 0; }

  bool end() { return !(cursor_ < integers_.size()); }

  int get() { return integers_[cursor_++]; }

 private:
  void initIntegers() {
    integers_.clear();
    auto engine = std::default_random_engine(salt_);
    std::vector<std::vector<int>> vecs;
    {
      std::vector<int> vec;
      for (int i = 0; i < (1 << 9) - 1; ++i) {
        vec.push_back(i);
      }
      std::shuffle(vec.begin(), vec.end() - 1, engine);
      vecs.push_back(vec);
    }
    for (int i = 9; i < maxLen_; ++i) {
      std::vector<int> vec;
      for (int j = (1 << (i)); j < (1 << (i + 1)); ++j) vec.push_back(j);
      if (salt_ != -1) {
        if (i == maxLen_ - 1) {
          std::shuffle(vec.begin(), vec.end() - 1, engine);
        } else {
          std::shuffle(vec.begin(), vec.end(), engine);
        }
      }
      vecs.push_back(vec);
    }

    for (auto& vec : vecs) {
      for (auto& num : vec) {
        integers_.push_back(num);
      }
    }
  }

 private:
  int salt_;
  int maxLen_;
  int cursor_;
  std::vector<int> integers_;
};

#endif  // __RANDOM_GENERATOR_H__