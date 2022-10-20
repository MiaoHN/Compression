enable_testing()

include_directories(../compress)

add_executable(test_byte_array test_byte_array.cpp)
target_link_libraries(test_byte_array PUBLIC huffmanlib)
add_test(NAME test_byte_array COMMAND test_byte_array)

add_executable(test_token test_token.cpp)
target_link_libraries(test_token PUBLIC huffmanlib)
add_test(NAME test_token COMMAND test_token)

add_executable(test_encode test_encode.cpp)
target_link_libraries(test_encode PUBLIC huffmanlib)
add_test(NAME test_encode COMMAND test_encode)

add_executable(test_decode test_decode.cpp)
target_link_libraries(test_decode PUBLIC huffmanlib)
add_test(NAME test_decode COMMAND test_decode)

add_executable(test_bitarray test_bitarray.cpp)
target_link_libraries(test_bitarray PUBLIC lzwlib)
add_test(NAME test_bitarray COMMAND test_bitarray)

add_executable(test_compress test_compress.cpp)
target_link_libraries(test_compress PUBLIC lzwlib)
add_test(NAME test_compress COMMAND test_compress)

add_executable(test_decompress test_decompress.cpp)
target_link_libraries(test_decompress PUBLIC lzwlib)
add_test(NAME test_decompress COMMAND test_decompress)
