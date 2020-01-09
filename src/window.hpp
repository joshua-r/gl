#pragma once

#include <iostream>
#include <memory>
#include <string>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace gl {

struct DestroyGlfwWin {
  void operator()(GLFWwindow* ptr) { glfwDestroyWindow(ptr); }
};

class Window {
 public:
  Window();
  Window(std::string title);
  Window(const Window&) = delete;
  Window(Window&&) = default;
  ~Window() = default;

  Window& operator=(const Window& other) = delete;
  Window& operator=(Window&& other) = default;

  bool init(const glm::uvec2& resolution = glm::uvec2(0), std::string monitor_name = "");
  void clear() const;
  void swap_buffers() const;

  const glm::vec2 screen_size() const;
  const glm::vec4 clear_color() const;
  bool should_close() const;

  void set_screen_size(const glm::vec2& size);
  void set_clear_color(const glm::vec4& clear_color);
  void set_should_close(bool should_close = true) const;
  void set_vsync(bool enable) const;

  // callbacks
  virtual void on_resize(int width, int height);
  virtual void on_key(int key, int scancode, int action, int mods);
  virtual void on_mouse_move(double x, double y);
  virtual void on_mouse_button(int button, int action, int mods);
  virtual void on_scroll(double x, double y);

 protected:
  std::unique_ptr<GLFWwindow, DestroyGlfwWin> m_window;
  std::string m_title;
  glm::vec2 m_screen_size;
  glm::vec4 m_clear_color;
  glm::uvec2 m_resolution;
};

}  // namespace gl
