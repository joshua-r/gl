#pragma once

#include <utility>

#include <opengl.hpp>
#include <texture2d.hpp>

namespace gl {

class Framebuffer {
 public:
  Framebuffer();
  Framebuffer(const Framebuffer& other) = delete;
  Framebuffer(Framebuffer&& other) noexcept;
  virtual ~Framebuffer();

  Framebuffer& operator=(const Framebuffer& other) = delete;
  Framebuffer& operator=(Framebuffer&& other) noexcept;

  void bind(GLenum target = GL_FRAMEBUFFER) const;
  static void unbind(GLenum target);

  void attach_texture(GLenum attachment, const Texture2d& texture, GLint level = 0);

  bool is_valid() const;
  bool is_complete() const;

  GLenum status(GLenum target = GL_FRAMEBUFFER) const;

  GLuint id() const;

 protected:
  GLint get_parameter(GLenum parameter) const;

 protected:
  GLuint m_id = INVALID_ID;
};

}  // namespace gl
