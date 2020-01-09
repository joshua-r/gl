#pragma once

#include <limits>
#include <stdexcept>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

namespace gl {

constexpr GLuint INVALID_ID = std::numeric_limits<GLuint>::max();

void init();

}  // namespace gl
