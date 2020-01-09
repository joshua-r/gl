#pragma once

#include <utility>

#include <opengl.hpp>

namespace gl {

class Texture {
 public:
  Texture(GLenum target);
  Texture(const Texture& other) = delete;
  Texture(Texture&& other) noexcept;
  virtual ~Texture() = 0;

  Texture& operator=(const Texture& other) = delete;
  Texture& operator=(Texture&& other) noexcept;

  void bind() const;
  static void unbind(GLenum target);
  void bind_unit(GLuint unit) const;
  bool is_valid() const;

  static void set_active(GLenum texture_unit);

  void generate_mipmap();

  void set_wrap_s(GLenum mode);
  void set_wrap_t(GLenum mode);
  void set_wrap_r(GLenum mode);

  void set_min_filter(GLenum mode);
  void set_mag_filter(GLenum mode);

  GLuint id() const;

 protected:
  GLint get_parameter(GLenum parameter) const;

 protected:
  GLuint m_id = INVALID_ID;
  GLenum m_target = GL_NONE;
};

}  // namespace gl
