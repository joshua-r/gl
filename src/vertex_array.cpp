#include <vertex_array.hpp>

namespace gl {

VertexArray::VertexArray() {
  glCreateVertexArrays(1, &m_id);
}

VertexArray::VertexArray(VertexArray&& other) noexcept : m_id(other.m_id) {
  other.m_id = INVALID_ID;
}

VertexArray::~VertexArray() {
  if (is_valid()) {
    glDeleteVertexArrays(1, &m_id);
  }
}

VertexArray& VertexArray::operator=(VertexArray&& other) noexcept {
  if (this != &other) {
    if (is_valid()) {
      glDeleteVertexArrays(1, &m_id);
    }

    m_id = std::move(other.m_id);
    other.m_id = INVALID_ID;
  }

  return *this;
}

void VertexArray::bind() const {
  glBindVertexArray(m_id);
}

void VertexArray::unbind() {
  glBindVertexArray(0);
}

bool VertexArray::is_valid() const {
  return glIsVertexArray(m_id) != GL_FALSE;
}

void VertexArray::set_element_buffer(const Buffer& buffer) {
  glVertexArrayElementBuffer(m_id, buffer.id());
}

void VertexArray::set_vertex_buffer(GLuint binding_index, const Buffer& buffer, GLintptr offset, GLsizei stride) {
  glVertexArrayVertexBuffer(m_id, binding_index, buffer.id(), offset, stride);
}

void VertexArray::set_attribute_enabled(GLuint index, bool enabled) {
  if (enabled) {
    glEnableVertexArrayAttrib(m_id, index);
  } else {
    glDisableVertexArrayAttrib(m_id, index);
  }
}

void VertexArray::set_attribute_binding(GLuint index, GLuint binding_index) {
  glVertexArrayAttribBinding(m_id, index, binding_index);
}

void VertexArray::set_attribute_format(GLuint index, GLint size, GLenum type, bool normalized, GLuint relative_offset) {
  glVertexArrayAttribFormat(m_id, index, size, type, normalized, relative_offset);
}

void VertexArray::set_attribute_format_integer(GLuint index, GLint size, GLenum type, GLuint relative_offset) {
  glVertexArrayAttribIFormat(m_id, index, size, type, relative_offset);
}

void VertexArray::set_attribute_format_long(GLuint index, GLint size, GLenum type, GLuint relative_offset) {
  glVertexArrayAttribLFormat(m_id, index, size, type, relative_offset);
}

GLuint VertexArray::id() const {
  return m_id;
}

GLint VertexArray::get_parameter(GLenum parameter) const {
  GLint result;
  glGetVertexArrayiv(m_id, parameter, &result);
  return result;
}

GLint VertexArray::get_attribute_parameter(GLuint index, GLenum parameter) const {
  GLint result;
  glGetVertexArrayIndexediv(m_id, index, parameter, &result);
  return result;
}

}  // namespace gl
