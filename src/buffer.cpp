#include <buffer.hpp>

namespace gl {

Buffer::Buffer() {
  glCreateBuffers(1, &m_id);
}

Buffer::Buffer(Buffer&& other) noexcept : m_id(other.m_id) {
  other.m_id = INVALID_ID;
}

Buffer::~Buffer() {
  if (is_valid()) {
    glDeleteBuffers(1, &m_id);
  }
}

Buffer& Buffer::operator=(Buffer&& other) noexcept {
  if (this != &other) {
    if (is_valid()) {
      glDeleteBuffers(1, &m_id);
    }

    m_id = std::move(other.m_id);
    other.m_id = INVALID_ID;
  }

  return *this;
}

void Buffer::bind(GLenum target) const {
  glBindBuffer(target, m_id);
}

void Buffer::unbind(GLenum target) {
  glBindBuffer(target, 0);
}

void Buffer::bind_range(GLenum target, GLuint index, GLintptr offset, GLsizeiptr size) const {
  glBindBufferRange(target, index, m_id, offset, size);
}

void Buffer::unbind_range(GLenum target, GLuint index, GLintptr offset, GLsizeiptr size) {
  glBindBufferRange(target, index, 0, offset, size);
}

void Buffer::bind_base(GLenum target, GLuint index) const {
  glBindBufferBase(target, index, m_id);
}

void Buffer::unbind_base(GLenum target, GLuint index) {
  glBindBufferBase(target, index, 0);
}

void Buffer::set_data(GLsizeiptr size, const void* data, GLenum usage) {
  glNamedBufferData(m_id, size, data, usage);
}

void Buffer::set_sub_data(GLintptr offset, GLsizeiptr size, const void* data) {
  glNamedBufferSubData(m_id, offset, size, data);
}

void Buffer::clear_sub_data(GLenum internal_format,
                            GLintptr offset,
                            GLsizeiptr size,
                            GLenum format,
                            GLenum data_type,
                            const void* data) {
  glClearNamedBufferSubData(m_id, internal_format, offset, size, format, data_type, data);
}

void Buffer::clear_data(GLenum internal_format, GLenum format, GLenum data_type, const void* data) {
  glClearNamedBufferData(m_id, internal_format, format, data_type, data);
}

bool Buffer::is_valid() const {
  return glIsBuffer(m_id) != GL_FALSE;
}

GLsizeiptr Buffer::size() const {
  return get_parameter(GL_BUFFER_SIZE);
}

GLenum Buffer::usage() const {
  return get_parameter(GL_BUFFER_USAGE);
}

GLuint Buffer::id() const {
  return m_id;
}

GLint Buffer::get_parameter(GLenum parameter) const {
  GLint result;
  glGetNamedBufferParameteriv(m_id, parameter, &result);
  return result;
}

}  // namespace gl
