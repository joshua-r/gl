#pragma once

#include <utility>

#include <buffer.hpp>
#include <opengl.hpp>

namespace gl {

class VertexArray {
 public:
  VertexArray();
  VertexArray(const VertexArray& other) = delete;
  VertexArray(VertexArray&& other) noexcept;
  virtual ~VertexArray();

  VertexArray& operator=(const VertexArray& other) = delete;
  VertexArray& operator=(VertexArray&& other) noexcept;

  void bind() const;
  static void unbind();
  bool is_valid() const;

  void set_element_buffer(const Buffer& buffer);

  void set_vertex_buffer(GLuint binding_index, const Buffer& buffer, GLintptr offset = 0, GLsizei stride = 1);
  void set_attribute_enabled(GLuint index, bool enabled);
  void set_attribute_binding(GLuint index, GLuint binding_index);
  void set_attribute_format(GLuint index, GLint size, GLenum type, bool normalized = false, GLuint relative_offset = 0);
  void set_attribute_format_integer(GLuint index, GLint size, GLenum type, GLuint relative_offset = 0);
  void set_attribute_format_long(GLuint index, GLint size, GLenum type, GLuint relative_offset = 0);

  GLuint id() const;

 protected:
  GLint get_parameter(GLenum parameter) const;
  GLint get_attribute_parameter(GLuint index, GLenum parameter) const;

 protected:
  GLuint m_id = INVALID_ID;
};

}  // namespace gl
