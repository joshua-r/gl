#pragma once

#include <utility>

#include <opengl.hpp>
#include <texture.hpp>

namespace gl {

class Texture2d : public Texture {
 public:
  Texture2d();
  Texture2d(const Texture2d& other) = delete;
  Texture2d(Texture2d&& other) noexcept;

  Texture2d& operator=(const Texture2d& other) = delete;
  Texture2d& operator=(Texture2d&& other) noexcept;

  void set_storage(GLsizei levels, GLenum internal_format, GLsizei width, GLsizei height);

  void set_sub_image(GLint level,
                     GLint x,
                     GLint y,
                     GLsizei width,
                     GLsizei height,
                     GLenum format,
                     GLenum type,
                     const void* data);
  void copy_sub_image(GLint level,
                      GLint x,
                      GLint y,
                      GLint read_buffer_x,
                      GLint read_buffer_y,
                      GLsizei width,
                      GLsizei height);
};

}  // namespace gl
