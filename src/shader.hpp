#pragma once

#include <fstream>
#include <memory>
#include <streambuf>
#include <string>
#include <utility>
#include <vector>

#include <opengl.hpp>

namespace gl {

class Shader {
 public:
  Shader(GLenum type);
  Shader(const std::string& filename, GLenum type = GL_FALSE);
  Shader(const Shader& other) = delete;
  Shader(Shader&& other) noexcept;
  virtual ~Shader();

  Shader& operator=(const Shader& other) = delete;
  Shader& operator=(Shader&& other) noexcept;

  static GLenum detect_type_from_filename(const std::string& filename);

  void set_source(const std::string& source) const;
  bool load_source(const std::string& filename) const;
  bool compile() const;

  GLuint id() const;
  GLenum type() const;
  std::string source() const;

  bool is_valid() const;

 protected:
  GLint get_parameter(GLenum param) const;

 protected:
  GLuint m_id = INVALID_ID;
};

using ShaderPtr = std::shared_ptr<Shader>;

}  // namespace gl
