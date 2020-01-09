#include <memory>

#include <include/cef_app.h>
#include <glm/glm.hpp>

#include <opengl.hpp>
#include <program.hpp>
#include <shader.hpp>
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
  settings.windowless_rendering_enabled = 1;

  CefInitialize(args, settings, nullptr, nullptr);

  // setup window
  gl::init_glfw();
  auto window = std::make_unique<gl::Window>();
  window->init();
  gl::init_opengl();

  CefWindowInfo window_info;
  window_info.SetAsWindowless(0);
  CefBrowserSettings browser_settings;
  auto browser =
      CefBrowserHost::CreateBrowserSync(window_info, new WebView, "https://www.google.com/", browser_settings, nullptr);

  auto vert_shader = std::make_shared<gl::Shader>(GL_VERTEX_SHADER);
  vert_shader->load_source("shaders/fullscreen.vert");

  auto frag_shader = std::make_shared<gl::Shader>(GL_FRAGMENT_SHADER);
  frag_shader->load_source("shaders/texture.frag");

  auto program = std::make_unique<gl::Program>(std::set<gl::ShaderPtr>{vert_shader, frag_shader});

  // main loop
  while (!window->should_close()) {
    window->clear();
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    window->swap_buffers();
    CefDoMessageLoopWork();
    glfwPollEvents();
    glClearColor(0.0, 0.0, 1.0, 1.0);
  }

  // cleanup
  window = nullptr;
  glfwTerminate();
  browser = nullptr;
  CefShutdown();

  return 0;
}
