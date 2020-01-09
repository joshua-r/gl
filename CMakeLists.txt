cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

project(gl)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

# glfw
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)
add_subdirectory(external/glfw)
include_directories(external/glfw/include)

# glad
include_directories(external/glad/include)

# glm
include_directories(external/glm)

include_directories(src)
add_library(gl
    external/glad/src/glad.c
    src/buffer.cpp
    src/framebuffer.cpp
    src/opengl.cpp
    src/program.cpp
    src/shader.cpp
    src/texture.cpp
    src/texture2d.cpp
    src/vertex_array.cpp
    src/window.cpp
)
target_link_libraries(gl PUBLIC
    ${OPENGL_LIBRARIES}
    glfw
)
