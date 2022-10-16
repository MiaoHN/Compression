cmake_minimum_required(VERSION 3.10)

project(TextCompression)

include_directories(include)

file(GLOB COMPRESSION_SOURCE "source/*.cpp")

add_library(compression ${COMPRESSION_SOURCE})

add_subdirectory(test)
