set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

enable_testing()

add_executable(test_byte_array test_byte_array.cpp)
target_link_libraries(test_byte_array PUBLIC compression)
add_test(NAME test_byte_array COMMAND test_byte_array)

add_executable(test_token test_token.cpp)
target_link_libraries(test_token PUBLIC compression)
add_test(NAME test_token COMMAND test_token)

add_executable(test_encode test_encode.cpp)
target_link_libraries(test_encode PUBLIC compression)
add_test(NAME test_encode COMMAND test_encode)

add_executable(test_decode test_decode.cpp)
target_link_libraries(test_decode PUBLIC compression)
add_test(NAME test_decode COMMAND test_decode)

add_custom_target(DownloadTestFiles
  COMMAND echo "Download test files..."
  COMMAND python3 ${PROJECT_SOURCE_DIR}/scripts/generate_data.py 
  WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
)

add_dependencies(test_encode DownloadTestFiles)