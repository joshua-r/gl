#pragma once

#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include <glad/glad.h>

#include <opengl.hpp>
#include <shader.hpp>

namespace gl {

class Program {
 public:
  Program();
  Program(const std::set<ShaderPtr>& shaders);
  Program(const Program& other) = delete;
  Program(Program&& other) noexcept;
  virtual ~Program();

  Program& operator=(const Program& other) = delete;
  Program& operator=(Program&& other) noexcept;

  void attach_shader(ShaderPtr shader);
  void detach_shaders();
  bool link();
  void use() const;
  static void unuse();
  bool is_valid() const;

  GLuint id() const;
  GLint uniform_location(const std::string& name) const;

  // uniform setters
  void set_uniform_1i(GLint location, GLint value);
  void set_uniform_1i(GLint location, const std::vector<GLint>& value);
  void set_uniform_2i(GLint location, const std::array<GLint, 2>& value);
  void set_uniform_2i(GLint location, const std::vector<GLint>& value);
  void set_uniform_3i(GLint location, const std::array<GLint, 3>& value);
  void set_uniform_3i(GLint location, const std::vector<GLint>& value);
  void set_uniform_4i(GLint location, const std::array<GLint, 4>& value);
  void set_uniform_4i(GLint location, const std::vector<GLint>& value);

  void set_uniform_1ui(GLint location, GLuint value);
  void set_uniform_1ui(GLint location, const std::vector<GLuint>& value);
  void set_uniform_2ui(GLint location, const std::array<GLuint, 2>& value);
  void set_uniform_2ui(GLint location, const std::vector<GLuint>& value);
  void set_uniform_3ui(GLint location, const std::array<GLuint, 3>& value);
  void set_uniform_3ui(GLint location, const std::vector<GLuint>& value);
  void set_uniform_4ui(GLint location, const std::array<GLuint, 4>& value);
  void set_uniform_4ui(GLint location, const std::vector<GLuint>& value);

  void set_uniform_1f(GLint location, GLfloat value);
  void set_uniform_1f(GLint location, const std::vector<GLfloat>& value);
  void set_uniform_2f(GLint location, const std::array<GLfloat, 2>& value);
  void set_uniform_2f(GLint location, const std::vector<GLfloat>& value);
  void set_uniform_3f(GLint location, const std::array<GLfloat, 3>& value);
  void set_uniform_3f(GLint location, const std::vector<GLfloat>& value);
  void set_uniform_4f(GLint location, const std::array<GLfloat, 4>& value);
  void set_uniform_4f(GLint location, const std::vector<GLfloat>& value);

  void set_uniform_1d(GLint location, GLdouble value);
  void set_uniform_1d(GLint location, const std::vector<GLdouble>& value);
  void set_uniform_2d(GLint location, const std::array<GLdouble, 2>& value);
  void set_uniform_2d(GLint location, const std::vector<GLdouble>& value);
  void set_uniform_3d(GLint location, const std::array<GLdouble, 3>& value);
  void set_uniform_3d(GLint location, const std::vector<GLdouble>& value);
  void set_uniform_4d(GLint location, const std::array<GLdouble, 4>& value);
  void set_uniform_4d(GLint location, const std::vector<GLdouble>& value);

  // uniform templates for glm types
  template <typename T>
  void set_uniform(GLint location, const T& value);
  template <typename T>
  void set_uniform_vector(GLint location, const std::vector<T>& values);

 protected:
  GLint get_parameter(GLenum parameter) const;

 protected:
  GLuint m_id = INVALID_ID;
  std::map<GLuint, ShaderPtr> m_shaders;
};

}  // namespace gl

#include <glm_uniforms.hpp>
