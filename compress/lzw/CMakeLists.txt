add_library(lzwlib bit_array.cpp lzw.cpp)

add_executable(lzw main.cpp)
target_link_libraries(lzw PUBLIC lzwlib)

add_executable(encoder encoder.cpp)
target_link_libraries(encoder PUBLIC lzwlib)
add_executable(decoder decoder.cpp)
target_link_libraries(decoder PUBLIC lzwlib)
