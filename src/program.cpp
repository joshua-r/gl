#include <program.hpp>

namespace gl {

Program::Program() : m_id(glCreateProgram()) {}

Program::Program(const std::set<ShaderPtr>& shaders) : Program() {
  for (const auto& shader : shaders) {
    attach_shader(shader);
  }
  link();
}

Program::Program(Program&& other) noexcept : m_id(std::move(other.m_id)), m_shaders(std::move(other.m_shaders)) {
  other.m_id = INVALID_ID;
  other.m_shaders.clear();
}

Program::~Program() {
  if (is_valid()) {
    detach_shaders();
    glDeleteProgram(m_id);
  }
}

Program& Program::operator=(Program&& other) noexcept {
  if (this != &other) {
    if (is_valid()) {
      detach_shaders();
      glDeleteProgram(m_id);
    }

    m_id = std::move(other.m_id);
    m_shaders = std::move(other.m_shaders);

    other.m_id = INVALID_ID;
    other.m_shaders.clear();
  }

  return *this;
}

void Program::attach_shader(std::shared_ptr<Shader> shader) {
  m_shaders.insert_or_assign(shader->type(), shader);
}

void Program::detach_shaders() {
  for (const auto& [type, shader] : m_shaders) {
    glDetachShader(m_id, shader->id());
  }
  m_shaders.clear();
}

bool Program::link() {
  // attach the shaders and try to link the program
  for (const auto& [type, shader] : m_shaders) {
    glAttachShader(m_id, shader->id());
  }
  glLinkProgram(m_id);

  // check for errors while linking
  GLint is_linked = get_parameter(GL_LINK_STATUS);
  if (is_linked != GL_TRUE) {
    GLint max_length = get_parameter(GL_INFO_LOG_LENGTH);
    std::vector<GLchar> info_log_vec(max_length);
    glGetProgramInfoLog(m_id, max_length, &max_length, &info_log_vec[0]);

    // log the linking error messages
    std::string info_log(std::begin(info_log_vec), std::end(info_log_vec));
    throw std::runtime_error("Linking shader program failed:\n" + info_log);
  }

  // always detach shaders to clean up
  detach_shaders();

  return is_linked == GL_TRUE;
}

void Program::use() const {
  glUseProgram(m_id);
}

void Program::unuse() {
  glUseProgram(0);
}

bool Program::is_valid() const {
  return glIsProgram(m_id) != 0;
}

GLuint Program::id() const {
  return m_id;
}

GLint Program::uniform_location(const std::string& name) const {
  return glGetUniformLocation(m_id, name.c_str());
}

void Program::set_uniform_1i(GLint location, GLint value) {
  glProgramUniform1i(m_id, location, value);
}

void Program::set_uniform_1i(GLint location, const std::vector<GLint>& value) {
  glProgramUniform1iv(m_id, location, static_cast<GLsizei>(value.size()), value.data());
}

void Program::set_uniform_2i(GLint location, const std::array<GLint, 2>& value) {
  glProgramUniform2i(m_id, location, value[0], value[1]);
}

void Program::set_uniform_2i(GLint location, const std::vector<GLint>& value) {
  glProgramUniform2iv(m_id, location, static_cast<GLsizei>(value.size()), value.data());
}

void Program::set_uniform_3i(GLint location, const std::array<GLint, 3>& value) {
  glProgramUniform3i(m_id, location, value[0], value[1], value[2]);
}

void Program::set_uniform_3i(GLint location, const std::vector<GLint>& value) {
  glProgramUniform3iv(m_id, location, static_cast<GLsizei>(value.size()), value.data());
}

void Program::set_uniform_4i(GLint location, const std::array<GLint, 4>& value) {
  glProgramUniform4i(m_id, location, value[0], value[1], value[2], value[3]);
}

void Program::set_uniform_4i(GLint location, const std::vector<GLint>& value) {
  glProgramUniform4iv(m_id, location, static_cast<GLsizei>(value.size()), value.data());
}

void Program::set_uniform_1ui(GLint location, GLuint value) {
  glProgramUniform1ui(m_id, location, value);
}

void Program::set_uniform_1ui(GLint location, const std::vector<GLuint>& value) {
  glProgramUniform1uiv(m_id, location, static_cast<GLsizei>(value.size()), value.data());
}

void Program::set_uniform_2ui(GLint location, const std::array<GLuint, 2>& value) {
  glProgramUniform2ui(m_id, location, value[0], value[1]);
}

void Program::set_uniform_2ui(GLint location, const std::vector<GLuint>& value) {
  glProgramUniform2uiv(m_id, location, static_cast<GLsizei>(value.size()), value.data());
}

void Program::set_uniform_3ui(GLint location, const std::array<GLuint, 3>& value) {
  glProgramUniform3ui(m_id, location, value[0], value[1], value[2]);
}

void Program::set_uniform_3ui(GLint location, const std::vector<GLuint>& value) {
  glProgramUniform3uiv(m_id, location, static_cast<GLsizei>(value.size()), value.data());
}

void Program::set_uniform_4ui(GLint location, const std::array<GLuint, 4>& value) {
  glProgramUniform4ui(m_id, location, value[0], value[1], value[2], value[3]);
}

void Program::set_uniform_4ui(GLint location, const std::vector<GLuint>& value) {
  glProgramUniform4uiv(m_id, location, static_cast<GLsizei>(value.size()), value.data());
}

void Program::set_uniform_1f(GLint location, GLfloat value) {
  glProgramUniform1f(m_id, location, value);
}

void Program::set_uniform_1f(GLint location, const std::vector<GLfloat>& value) {
  glProgramUniform1fv(m_id, location, static_cast<GLsizei>(value.size()), value.data());
}

void Program::set_uniform_2f(GLint location, const std::array<GLfloat, 2>& value) {
  glProgramUniform2f(m_id, location, value[0], value[1]);
}

void Program::set_uniform_2f(GLint location, const std::vector<GLfloat>& value) {
  glProgramUniform2fv(m_id, location, static_cast<GLsizei>(value.size()), value.data());
}

void Program::set_uniform_3f(GLint location, const std::array<GLfloat, 3>& value) {
  glProgramUniform3f(m_id, location, value[0], value[1], value[2]);
}

void Program::set_uniform_3f(GLint location, const std::vector<GLfloat>& value) {
  glProgramUniform3fv(m_id, location, static_cast<GLsizei>(value.size()), value.data());
}

void Program::set_uniform_4f(GLint location, const std::array<GLfloat, 4>& value) {
  glProgramUniform4f(m_id, location, value[0], value[1], value[2], value[3]);
}

void Program::set_uniform_4f(GLint location, const std::vector<GLfloat>& value) {
  glProgramUniform4fv(m_id, location, static_cast<GLsizei>(value.size()), value.data());
}

void Program::set_uniform_1d(GLint location, GLdouble value) {
  glProgramUniform1d(m_id, location, value);
}

void Program::set_uniform_1d(GLint location, const std::vector<GLdouble>& value) {
  glProgramUniform1dv(m_id, location, static_cast<GLsizei>(value.size()), value.data());
}

void Program::set_uniform_2d(GLint location, const std::array<GLdouble, 2>& value) {
  glProgramUniform2d(m_id, location, value[0], value[1]);
}

void Program::set_uniform_2d(GLint location, const std::vector<GLdouble>& value) {
  glProgramUniform2dv(m_id, location, static_cast<GLsizei>(value.size()), value.data());
}

void Program::set_uniform_3d(GLint location, const std::array<GLdouble, 3>& value) {
  glProgramUniform3d(m_id, location, value[0], value[1], value[2]);
}

void Program::set_uniform_3d(GLint location, const std::vector<GLdouble>& value) {
  glProgramUniform3dv(m_id, location, static_cast<GLsizei>(value.size()), value.data());
}

void Program::set_uniform_4d(GLint location, const std::array<GLdouble, 4>& value) {
  glProgramUniform4d(m_id, location, value[0], value[1], value[2], value[3]);
}

void Program::set_uniform_4d(GLint location, const std::vector<GLdouble>& value) {
  glProgramUniform4dv(m_id, location, static_cast<GLsizei>(value.size()), value.data());
}

GLint Program::get_parameter(GLenum parameter) const {
  GLint result;
  glGetProgramiv(m_id, parameter, &result);
  return result;
}

}  // namespace gl
