find_package(OpenGL REQUIRED)
find_package(Freetype REQUIRED)

set(GAME_SOURCE_FILES
    "game.hpp"
    "game.cpp"
    "game_object.hpp"
    "game_object.cpp"
    "logger.hpp"
    "logger.cpp"
    "platform.hpp"
    "renderer.hpp"
    "renderer.cpp"
    "shader.hpp"
    "shader.cpp"
    "texture.hpp"
    "texture.cpp"
    "utils.hpp"
    "main.cpp"
    )

set(APPLICATION_TYPE "")
if (WIN32)
    set(APPLICATION_TYPE "WIN32")
endif()

add_executable(game ${APPLICATION_TYPE} ${GAME_SOURCE_FILES})

target_include_directories(game
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        "../thirdparty/glad/include"
        "../thirdparty/glfw/include"
        "../thirdparty/glm"
        "../thirdparty/stb"
        ${FREETYPE_INCLUDE_DIRS}
    )

target_link_libraries(game
    PRIVATE
        OpenGL::GL
        glad
        glfw
        glm
        stb
        ${FREETYPE_LIBRARIES}
    )

set_target_properties(game
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    )

target_compile_definitions(game
    PRIVATE
        "$<$<CONFIG:Debug>:GAME_DEBUG_ENABLED>"
)
