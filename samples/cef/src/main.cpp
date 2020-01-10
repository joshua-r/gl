#include <memory>

#include <include/cef_app.h>
#include <glm/glm.hpp>

#include <framebuffer.hpp>
#include <opengl.hpp>
#include <program.hpp>
#include <shader.hpp>
#include <vertex_array.hpp>
#include <web_view.hpp>
#include <window.hpp>

int main(int argc, char* argv[]) {
  CefMainArgs args(argc, argv);

  int result = CefExecuteProcess(args, nullptr, nullptr);
  if (result >= 0) {
    return result;
  }

  CefSettings settings;
  settings.no_sandbox = true;
  settings.windowless_rendering_enabled = true;
  settings.command_line_args_disabled = true;

  CefInitialize(args, settings, nullptr, nullptr);

  // setup window
  gl::init_glfw();
  auto window = std::make_unique<gl::Window>();
  window->init();
  gl::init_opengl();

  auto vert_shader = std::make_shared<gl::Shader>(GL_VERTEX_SHADER);
  vert_shader->load_source("shaders/fullscreen.vert");

  auto frag_shader = std::make_shared<gl::Shader>(GL_FRAGMENT_SHADER);
  frag_shader->load_source("shaders/texture.frag");

  auto vao = std::make_unique<gl::VertexArray>();
  auto program = std::make_unique<gl::Program>(std::set<gl::ShaderPtr>{vert_shader, frag_shader});
  program->use();
  auto tex_loc = program->uniform_location("tex");
  program->set_uniform_1i(tex_loc, 0);

  auto web_view = std::make_unique<WebView>(window->resolution().x, window->resolution().y);

  // main loop
  while (!window->should_close()) {
    glViewport(0, 0, window->resolution().x, window->resolution().y);
    window->set_clear_color(glm::vec4{0.0, 0.0, 1.0, 1.0});
    window->clear();

    vao->bind();
    program->use();

    web_view->bind_texture();
    glDrawArrays(GL_TRIANGLES, 0, 3);

    window->swap_buffers();

    CefDoMessageLoopWork();
    glfwPollEvents();
  }

  // cleanup
  web_view = nullptr;
  window = nullptr;
  glfwTerminate();
  CefShutdown();

  return 0;
}
