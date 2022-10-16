set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

enable_testing()

add_executable(test_token test_token.cpp)
target_link_libraries(test_token PUBLIC compression)
add_test(NAME test_token COMMAND test_token)
