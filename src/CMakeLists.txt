set(GAME_SOURCE_FILES
    "main.cpp"
    )

add_executable(snake ${GAME_SOURCE_FILES})

target_include_directories(snake
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
    )

set_target_properties(snake
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    )

target_compile_definitions(snake
    PRIVATE
        "$<$<CONFIG:Debug>:GAME_DEBUG_ENABLED>"
)
