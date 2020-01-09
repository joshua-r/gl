#include <framebuffer.hpp>

namespace gl {

Framebuffer::Framebuffer() {
  glCreateFramebuffers(1, &m_id);
}

Framebuffer::Framebuffer(Framebuffer&& other) noexcept : m_id(other.m_id) {
  other.m_id = INVALID_ID;
}

Framebuffer::~Framebuffer() {
  if (is_valid()) {
    glDeleteFramebuffers(1, &m_id);
  }
}

Framebuffer& Framebuffer::operator=(Framebuffer&& other) noexcept {
  if (this != &other) {
    if (is_valid()) {
      glDeleteFramebuffers(1, &m_id);
    }

    m_id = std::move(other.m_id);

    other.m_id = INVALID_ID;
  }

  return *this;
}

void Framebuffer::bind(GLenum target) const {
  glBindFramebuffer(target, m_id);
}

void Framebuffer::unbind(GLenum target) {
  glBindFramebuffer(target, 0);
}

void Framebuffer::attach_texture(GLenum attachment, const Texture2d& texture, GLint level) {
  glNamedFramebufferTexture(m_id, attachment, texture.id(), level);
}

bool Framebuffer::is_valid() const {
  return glIsFramebuffer(m_id) != GL_FALSE;
}

bool Framebuffer::is_complete() const {
  return status() == GL_FRAMEBUFFER_COMPLETE;
}

GLenum Framebuffer::status(GLenum target) const {
  return glCheckNamedFramebufferStatus(m_id, target);
}

}  // namespace gl
