#include <memory>

#include <glm/glm.hpp>

#include <opengl.hpp>
#include <window.hpp>

int main() {
  // setup window
  gl::init_glfw();
  auto window = std::make_unique<gl::Window>();
  window->init();
  window->set_clear_color(glm::vec4{0.14901960784313725, 0.19607843137254902, 0.2196078431372549, 1.0});
  gl::init_opengl();

  // main loop
  while (!window->should_close()) {
    window->clear();
    window->swap_buffers();
    glfwPollEvents();
  }

  // cleanup
  window = nullptr;
  glfwTerminate();

  return 0;
}
