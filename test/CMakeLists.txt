set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

enable_testing()

add_executable(test_byte_array test_byte_array.cpp)
target_link_libraries(test_byte_array PUBLIC compression)
add_test(NAME test_byte_array COMMAND test_byte_array)

add_executable(test_token test_token.cpp)
target_link_libraries(test_token PUBLIC compression)
add_test(NAME test_token COMMAND test_token)

add_executable(test_huffman test_huffman.cpp)
target_link_libraries(test_huffman PUBLIC compression)
add_test(NAME test_huffman COMMAND test_huffman)
