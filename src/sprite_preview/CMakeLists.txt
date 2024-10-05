cmake_minimum_required(VERSION 3.16)
project(sprite_preview)
set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(external/glad/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(GLAD_SRC external/glad/src/glad.c)

file(GLOB SHADER_FILES
    "src/*.glsl"
    "src/**/*.glsl"
)

function (embed_shaders output_file)
    file(WRITE ${output_file} "")
    foreach(file IN LISTS ARGN)
        get_filename_component(shader_name ${file} NAME_WE)
        file(READ ${file} shader_code)
        file(APPEND ${output_file} "const char* ${shader_name}_shader = R\"(${shader_code})\";\n")
    endforeach()
endfunction()


file(GLOB src_files
    "src/**/*.hpp"
    "src/**/*.cpp"
    "src/*.cpp"
    "src/*.hpp"
    "external"
)

embed_shaders(${CMAKE_CURRENT_BINARY_DIR}/embedded_shaders.hpp ${SHADER_FILES})

add_executable(sprite_preview ${src_files} ${GLAD_SRC})

target_link_libraries(sprite_preview glfw OpenGL::GL)