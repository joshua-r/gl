#include <texture2d.hpp>

namespace gl {

Texture2d::Texture2d() : Texture(GL_TEXTURE_2D) {}

Texture2d::Texture2d(Texture2d&& other) noexcept : Texture(std::move(other)) {}

Texture2d& Texture2d::operator=(Texture2d&& other) noexcept {
  if (this != &other) {
    if (is_valid()) {
      glDeleteTextures(1, &m_id);
    }

    m_id = std::move(other.m_id);
    m_target = std::move(other.m_target);

    other.m_id = INVALID_ID;
    other.m_target = GL_NONE;
  }

  return *this;
}

void Texture2d::set_storage(GLsizei levels, GLenum internal_format, GLsizei width, GLsizei height) {
  glTextureStorage2D(m_id, levels, internal_format, width, height);
}

void Texture2d::set_sub_image(GLint level,
                              GLint x,
                              GLint y,
                              GLsizei width,
                              GLsizei height,
                              GLenum format,
                              GLenum type,
                              const void* data) {
  glTextureSubImage2D(m_id, level, x, y, width, height, format, type, data);
}

void Texture2d::copy_sub_image(GLint level,
                               GLint x,
                               GLint y,
                               GLint read_buffer_x,
                               GLint read_buffer_y,
                               GLsizei width,
                               GLsizei height) {
  glCopyTextureSubImage2D(m_id, level, x, y, read_buffer_x, read_buffer_y, width, height);
}

}  // namespace gl
