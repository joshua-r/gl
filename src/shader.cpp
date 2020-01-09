#include <shader.hpp>

namespace gl {

Shader::Shader(GLenum type) : m_id(glCreateShader(type)) {}

Shader::Shader(const std::string& filename, GLenum type) {
  if (type == GL_FALSE) {
    type = detect_type_from_filename(filename);
  }

  // create new shader from source given via filename
  m_id = glCreateShader(type);
  load_source(filename);

  // compile the shader
  if (!compile()) {
    throw std::runtime_error("Failed to compile shader loaded from file '" + filename + "'!");
  }
}

Shader::Shader(Shader&& other) noexcept : m_id(std::move(other.m_id)) {
  other.m_id = INVALID_ID;
}

Shader::~Shader() {
  if (is_valid()) {
    glDeleteShader(m_id);
  }
}

Shader& Shader::operator=(Shader&& other) noexcept {
  if (this != &other) {
    if (is_valid()) {
      glDeleteShader(m_id);
    }

    m_id = std::move(other.m_id);
    other.m_id = INVALID_ID;
  }

  return *this;
}

GLenum Shader::detect_type_from_filename(const std::string& filename) {
  auto file_ending_2 = filename.substr(filename.length() - 2, 2);
  auto file_ending_4 = filename.substr(filename.length() - 4, 4);
  if (file_ending_4 == "vert" || file_ending_2 == "vs") {
    return GL_VERTEX_SHADER;
  } else if (file_ending_4 == "tesc") {
    return GL_TESS_CONTROL_SHADER;
  } else if (file_ending_4 == "tese") {
    return GL_TESS_EVALUATION_SHADER;
  } else if (file_ending_4 == "geom") {
    return GL_GEOMETRY_SHADER;
  } else if (file_ending_4 == "frag" || file_ending_2 == "fs") {
    return GL_FRAGMENT_SHADER;
  } else {
    throw std::runtime_error("Shader: Failed to detect shader type from filename '" + filename + "'!");
  }
}

void Shader::set_source(const std::string& source) const {
  auto shader_cstring = source.c_str();
  glShaderSource(m_id, 1, &shader_cstring, nullptr);
}

bool Shader::load_source(const std::string& filename) const {
  std::ifstream filestream(filename);
  if (!filestream.is_open()) {
    throw std::runtime_error("Failed to load shader from file '" + filename + "'!");
  }

  set_source(std::string(std::istreambuf_iterator<char>(filestream), std::istreambuf_iterator<char>()));
  return true;
}

bool Shader::compile() const {
  glCompileShader(m_id);

  GLint compiled = 0;
  glGetShaderiv(m_id, GL_COMPILE_STATUS, &compiled);
  if (compiled == GL_FALSE) {
    GLint max_length = 0;
    glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &max_length);

    std::vector<GLchar> error_log_vec(max_length);
    glGetShaderInfoLog(m_id, max_length, &max_length, &error_log_vec[0]);
    std::string error_log(std::begin(error_log_vec), std::end(error_log_vec));
    throw std::runtime_error("Compiling shader failed:\n" + error_log);

    glDeleteShader(m_id);
    return false;
  }

  return true;
}

GLuint Shader::id() const {
  return m_id;
}

GLenum Shader::type() const {
  return get_parameter(GL_SHADER_TYPE);
}

std::string Shader::source() const {
  GLsizei source_length = get_parameter(GL_SHADER_SOURCE_LENGTH);
  std::string result;
  result.resize(source_length);
  glGetShaderSource(m_id, source_length, nullptr, &result[0]);
  return result;
}

bool Shader::is_valid() const {
  return m_id != INVALID_ID;
}

GLint Shader::get_parameter(GLenum param) const {
  GLint result;
  glGetShaderiv(m_id, param, &result);
  return result;
}

}  // namespace gl
