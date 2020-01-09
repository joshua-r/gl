#pragma once

#include <utility>

#include <opengl.hpp>

namespace gl {

class Buffer {
 public:
  Buffer();
  Buffer(const Buffer& other) = delete;
  Buffer(Buffer&& other) noexcept;
  virtual ~Buffer();

  Buffer& operator=(const Buffer& other) = delete;
  Buffer& operator=(Buffer&& other) noexcept;

  void bind(GLenum target) const;
  static void unbind(GLenum target);
  void bind_range(GLenum target, GLuint index, GLintptr offset, GLsizeiptr size) const;
  static void unbind_range(GLenum target, GLuint index, GLintptr offset, GLsizeiptr size);
  void bind_base(GLenum target, GLuint index) const;
  static void unbind_base(GLenum target, GLuint index);

  void set_data(GLsizeiptr size, const void* data = nullptr, GLenum usage = GL_DYNAMIC_DRAW);
  void set_sub_data(GLintptr offset, GLsizeiptr size, const void* data);
  void clear_sub_data(GLenum internal_format,
                      GLintptr offset,
                      GLsizeiptr size,
                      GLenum format,
                      GLenum data_type,
                      const void* data = nullptr);
  void clear_data(GLenum internal_format, GLenum format, GLenum data_type, const void* data = nullptr);

  bool is_valid() const;
  GLsizeiptr size() const;
  GLenum usage() const;

  GLuint id() const;

 protected:
  GLint get_parameter(GLenum parameter) const;

 protected:
  GLuint m_id = INVALID_ID;
};

}  // namespace gl
