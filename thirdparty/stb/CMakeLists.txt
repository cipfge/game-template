cmake_minimum_required(VERSION 3.22)

project(stb VERSION 1.0.0 LANGUAGES CXX)

set(STB_SOURCE_FILES
    "stb_image.h"
    "stb_image.cpp"
    )

add_library(stb ${STB_SOURCE_FILES})

target_include_directories(stb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
