#include <window.hpp>

namespace gl {

Window::Window() : m_title{"New Window"} {}

Window::Window(std::string title) : m_title{title} {}

bool Window::init(const glm::uvec2& resolution, std::string monitor_name) {
  // use the primary monitor by default
  GLFWmonitor* monitor = glfwGetPrimaryMonitor();

  // find the monitor with the given name if one was given
  if (!monitor_name.empty()) {
    int monitor_count;
    GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);
    for (int i = 0; i < monitor_count; ++i) {
      auto name = std::string{glfwGetMonitorName(monitors[i])};
      if (name == monitor_name) {
        monitor = monitors[i];
        break;
      }
    }

    if (!monitor) {
      throw std::runtime_error("Monitor '" + monitor_name + "' was not found!");
    }
  } else {
    // get the primary monitor's name
    monitor_name = std::string{glfwGetMonitorName(monitor)};
  }

  auto mode = glfwGetVideoMode(monitor);

  if (resolution.x > 0 && resolution.y > 0) {
    m_resolution = resolution;
  } else {
    m_resolution = glm::uvec2{mode->width, mode->height};
  }

  auto window = glfwCreateWindow(m_resolution.x, m_resolution.y, m_title.c_str(), monitor, nullptr);

  // store the screen size
  int width_mm, height_mm;
  glfwGetMonitorPhysicalSize(monitor, &width_mm, &height_mm);
  m_screen_size = glm::vec2{width_mm, height_mm} / 1000.0f;  // convert from mm to m

  if (!window) {
    return false;
  }

  glfwMakeContextCurrent(window);
  m_window = std::unique_ptr<GLFWwindow, DestroyGlfwWin>(window);

  // set this class as user pointer to access it in callbacks
  glfwSetWindowUserPointer(m_window.get(), this);

  // error callback
  glfwSetErrorCallback([](int code, const char* description) {
    // simply log the error
    std::cerr << "GLFW Error " << code << ": " << description << std::endl;
  });

  // framebuffer size callback
  glfwSetFramebufferSizeCallback(m_window.get(), [](GLFWwindow* window, int width, int height) {
    auto win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    win->on_resize(width, height);
  });

  // keyboard callback
  glfwSetKeyCallback(m_window.get(), [](GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    win->on_key(key, scancode, action, mods);
  });

  // mouse cursor pos callback
  glfwSetCursorPosCallback(m_window.get(), [](GLFWwindow* window, double x, double y) {
    auto win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    win->on_mouse_move(x, y);
  });

  // mouse button callback
  glfwSetMouseButtonCallback(m_window.get(), [](GLFWwindow* window, int button, int action, int mods) {
    auto win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    win->on_mouse_button(button, action, mods);
  });

  // scroll callback
  glfwSetScrollCallback(m_window.get(), [](GLFWwindow* window, double x, double y) {
    auto win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    win->on_scroll(x, y);
  });

  return window;
}

void Window::clear() const {
  glfwMakeContextCurrent(m_window.get());
  glClearColor(m_clear_color.r, m_clear_color.g, m_clear_color.b, m_clear_color.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::swap_buffers() const {
  glfwSwapBuffers(m_window.get());
}

const glm::vec2 Window::screen_size() const {
  return m_screen_size;
}

const glm::vec4 Window::clear_color() const {
  return m_clear_color;
}

const glm::uvec2 Window::resolution() const {
  return m_resolution;
}

bool Window::should_close() const {
  return glfwWindowShouldClose(m_window.get());
}

void Window::set_screen_size(const glm::vec2& size) {
  m_screen_size = size;
}

void Window::set_clear_color(const glm::vec4& clear_color) {
  m_clear_color = clear_color;
}

void Window::set_should_close(bool should_close) const {
  glfwSetWindowShouldClose(m_window.get(), should_close);
}

void Window::set_vsync(bool enable) const {
  enable ? glfwSwapInterval(1) : glfwSwapInterval(0);
}

void Window::on_resize(int width, int height) {
  m_resolution = glm::uvec2{width, height};
}

void Window::on_key(int key, int scancode, int action, int mods) {
#ifndef NDEBUG
  if (action == GLFW_PRESS) {
    auto key_name = glfwGetKeyName(key, scancode);
    if (key_name) {
      std::cout << "Key '" << key_name << "' was pressed" << std::endl;
    } else {
      std::cout << "Key '" << key << "' was pressed" << std::endl;
    }
  }
#endif

  if (action == GLFW_PRESS && (key == GLFW_KEY_ESCAPE) || (key == GLFW_KEY_Q)) {
    set_should_close(true);
  }
}

void Window::on_mouse_move(double x, double y) {}

void Window::on_mouse_button(int button, int action, int mods) {}

void Window::on_scroll(double x, double y) {}

}  // namespace gl
