#include <cstring>
#include <iostream>

#include "lzw/lzw.h"
#include "timer.h"

using namespace lzw;

void testCompressor(const std::string& title, const std::string& fix,
                    Compressor* compressor) {
  std::cout << "=== " << title << " ===" << std::endl;
  Timer timer;
  {
    timer.reset();
    compress(compressor, "sgyy.txt", "sgyy.txt." + fix + ".lzw");
    std::cout << "三国演义"
              << ":  \t" << timer.elapsed_micro() / 1000.0f << "ms"
              << std::endl;
  }
  {
    timer.reset();
    compress(compressor, "xyj.txt", "xyj.txt." + fix + ".lzw");
    std::cout << "西游记"
              << ":  \t" << timer.elapsed_micro() / 1000.0f << "ms"
              << std::endl;
  }
  {
    timer.reset();
    compress(compressor, "hlm.txt", "hlm.txt." + fix + ".lzw");
    std::cout << "红楼梦"
              << ":  \t" << timer.elapsed_micro() / 1000.0f << "ms"
              << std::endl;
  }
  {
    timer.reset();
    compress(compressor, "dpcq.txt", "dpcq.txt." + fix + ".lzw");
    std::cout << "斗破苍穹"
              << ":  \t" << timer.elapsed_micro() / 1000.0f << "ms"
              << std::endl;
  }
  {
    timer.reset();
    compress(compressor, "lotr.txt", "lotr.txt." + fix + ".lzw");
    std::cout << "指环王"
              << ":  \t" << timer.elapsed_micro() / 1000.0f << "ms"
              << std::endl;
  }
  {
    timer.reset();
    compress(compressor, "dc.txt", "dc.txt." + fix + ".lzw");
    std::cout << "大卫科波菲尔"
              << ":  \t" << timer.elapsed_micro() / 1000.0f << "ms"
              << std::endl;
  }
  {
    timer.reset();
    compress(compressor, "sherlock.txt", "sherlock.txt." + fix + ".lzw");
    std::cout << "福尔摩斯全集"
              << ":  \t" << timer.elapsed_micro() / 1000.0f << "ms"
              << std::endl;
  }
  {
    timer.reset();
    compress(compressor, "image.jpg", "image.jpg." + fix + ".lzw");
    std::cout << "image"
              << ":  \t" << timer.elapsed_micro() / 1000.0f << "ms"
              << std::endl;
  }
}

int main(int argc, char const* argv[]) {
  // testCompressor("BasicCompressor", "basic", new BasicCompressor);
  // testCompressor("VariableLengthCompressor12", "vl12",
  //                new VariableLengthCompressor(12));
  // testCompressor("VariableLengthCompressor14", "vl14",
  //                new VariableLengthCompressor(14));
  // testCompressor("VariableLengthCompressor16", "vl16",
  //                new VariableLengthCompressor(16));
  // testCompressor("VariableLengthCompressor18", "vl18",
  //                new VariableLengthCompressor(18));
  // testCompressor("VariableLengthCompressor20", "vl20",
  //                new VariableLengthCompressor(20));
  // testCompressor("VariableLengthCompressor22", "vl22",
  //                new VariableLengthCompressor(22));
  // testCompressor("VariableLengthCompressor24", "vl24",
  //                new VariableLengthCompressor(24));
  testCompressor("SafeVariableLengthCompressor", "safe",
                 new SafeVariableLengthCompressor(0, 18));
  return 0;
}
