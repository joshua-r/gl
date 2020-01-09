#include <texture.hpp>

namespace gl {

Texture::Texture(GLenum target) : m_target(target) {
  glCreateTextures(m_target, 1, &m_id);
}

Texture::Texture(Texture&& other) noexcept : m_id(other.m_id), m_target(other.m_target) {
  other.m_id = INVALID_ID;
  other.m_target = GL_NONE;
}

Texture::~Texture() {
  if (is_valid()) {
    glDeleteTextures(1, &m_id);
  }
}

Texture& Texture::operator=(Texture&& other) noexcept {
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

void Texture::bind() const {
  glBindTexture(m_target, m_id);
}

void Texture::unbind(GLenum target) {
  glBindTexture(target, 0);
}

void Texture::bind_unit(GLuint unit) const {
  glBindTextureUnit(unit, m_id);
}

bool Texture::is_valid() const {
  return glIsTexture(m_id) && m_target != GL_NONE;
}

void Texture::set_active(GLenum texture_unit) {
  glActiveTexture(GL_TEXTURE0 + texture_unit);
}

void Texture::generate_mipmap() {
  glGenerateTextureMipmap(m_id);
}

void Texture::set_wrap_s(GLenum mode) {
  glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, mode);
}

void Texture::set_wrap_t(GLenum mode) {
  glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, mode);
}

void Texture::set_wrap_r(GLenum mode) {
  glTextureParameteri(m_id, GL_TEXTURE_WRAP_R, mode);
}

void Texture::set_min_filter(GLenum mode) {
  glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, mode);
}

void Texture::set_mag_filter(GLenum mode) {
  glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, mode);
}

GLuint Texture::id() const {
  return m_id;
}

}  // namespace gl
