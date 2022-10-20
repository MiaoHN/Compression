file(GLOB HUFFMAN_SOURCE "./*.cpp")

add_executable(huffman ${HUFFMAN_SOURCE})

add_library(huffmanlib file.cpp huffman.cpp token.cpp)
