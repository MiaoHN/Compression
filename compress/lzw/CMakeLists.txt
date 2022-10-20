file(GLOB LZW_SOURCE "./*.cpp")

add_executable(lzw ${LZW_SOURCE})

add_library(lzwlib bit_array.cpp lzw.cpp)
