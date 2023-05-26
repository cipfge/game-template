cmake_minimum_required(VERSION 3.22)

project(glad VERSION 1.0.0 LANGUAGES C)

set(GLAD_SOURCE_FILES
    "include/glad/glad.h"
    "include/KHR/khrplatform.h"
    "src/glad.c"
    )

add_library(glad ${GLAD_SOURCE_FILES})

target_include_directories(glad PUBLIC "include")
