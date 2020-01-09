#include <opengl.hpp>

namespace gl {

void init() {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::runtime_error("Failed to initialize OpenGL with glad!");
  }
}

}  // namespace gl
