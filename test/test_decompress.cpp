#include <cstring>
#include <iostream>

#include "lzw/lzw.h"
#include "timer.h"

using namespace lzw;

void testDecompressor(const std::string& title, const std::string& fix,
                      Decompressor* decompressor) {
  std::cout << "=== " << title << " ===" << std::endl;
  Timer timer;
  {
    timer.reset();
    decompress(decompressor, "sgyy.txt." + fix + ".lzw");
    std::cout << "三国演义"
              << ":  \t" << timer.elapsed_micro() / 1000.0f << "ms"
              << std::endl;
  }
  {
    timer.reset();
    decompress(decompressor, "xyj.txt." + fix + ".lzw");
    std::cout << "西游记"
              << ":  \t" << timer.elapsed_micro() / 1000.0f << "ms"
              << std::endl;
  }
  {
    timer.reset();
    decompress(decompressor, "hlm.txt." + fix + ".lzw");
    std::cout << "红楼梦"
              << ":  \t" << timer.elapsed_micro() / 1000.0f << "ms"
              << std::endl;
  }
  {
    timer.reset();
    decompress(decompressor, "dpcq.txt." + fix + ".lzw");
    std::cout << "斗破苍穹"
              << ":  \t" << timer.elapsed_micro() / 1000.0f << "ms"
              << std::endl;
  }
  {
    timer.reset();
    decompress(decompressor, "lotr.txt." + fix + ".lzw");
    std::cout << "指环王"
              << ":  \t" << timer.elapsed_micro() / 1000.0f << "ms"
              << std::endl;
  }
  {
    timer.reset();
    decompress(decompressor, "dc.txt." + fix + ".lzw");
    std::cout << "大卫科波菲尔"
              << ":  \t" << timer.elapsed_micro() / 1000.0f << "ms"
              << std::endl;
  }
  {
    timer.reset();
    decompress(decompressor, "sherlock.txt." + fix + ".lzw");
    std::cout << "福尔摩斯全集"
              << ":  \t" << timer.elapsed_micro() / 1000.0f << "ms"
              << std::endl;
  }
  {
    timer.reset();
    decompress(decompressor, "image.jpg." + fix + ".lzw",
               "image.jpg." + fix + ".lzw.jpg");
    std::cout << "image"
              << ":  \t" << timer.elapsed_micro() / 1000.0f << "ms"
              << std::endl;
  }
}

int main(int argc, char const* argv[]) {
  // testDecompressor("BasicDecompressor", "basic", new BasicDecompressor);
  // testDecompressor("VariableLengthDecompressor", "vl",
  //                  new VariableLengthDecompressor);
  testDecompressor("SafeVariableLengthDecompressor", "safe",
                   new SafeVariableLengthDecompressor(0, 18));
  return 0;
}
