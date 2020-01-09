cmake_minimum_required(VERSION 3.2)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(gl)

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake
    ${CMAKE_CURRENT_SOURCE_DIR}/external/cef-cmake/cmake
)

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

# download and build cef
set(CEF_USE_SANDBOX OFF CACHE BOOL "Force turning off of sandbox")
include(cef_cmake)
add_subdirectory(external/cef-cmake)

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

add_subdirectory(samples/simple)
add_subdirectory(samples/cef)
