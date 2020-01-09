#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace gl {

// source: https://github.com/acdemiralp/gl/blob/master/include/gl/auxiliary/glm_uniforms.hpp
#define SPECIALIZE_SET_UNIFORM_VECTORS(TYPE, GL_POSTFIX)                                                \
  template <>                                                                                           \
  inline void Program::set_uniform(GLint location, const TYPE& value) {                                 \
    glProgramUniform##GL_POSTFIX##v(m_id, location, 1, glm::value_ptr(value));                          \
  }                                                                                                     \
  template <>                                                                                           \
  inline void Program::set_uniform_vector(GLint location, const std::vector<TYPE>& values) {            \
    glProgramUniform##GL_POSTFIX##v(m_id, location, (GLsizei)values.size(), glm::value_ptr(values[0])); \
  }

SPECIALIZE_SET_UNIFORM_VECTORS(glm::ivec2, 2i)
SPECIALIZE_SET_UNIFORM_VECTORS(glm::ivec3, 3i)
SPECIALIZE_SET_UNIFORM_VECTORS(glm::ivec4, 4i)
SPECIALIZE_SET_UNIFORM_VECTORS(glm::uvec2, 2ui)
SPECIALIZE_SET_UNIFORM_VECTORS(glm::uvec3, 3ui)
SPECIALIZE_SET_UNIFORM_VECTORS(glm::uvec4, 4ui)
SPECIALIZE_SET_UNIFORM_VECTORS(glm::fvec2, 2f)
SPECIALIZE_SET_UNIFORM_VECTORS(glm::fvec3, 3f)
SPECIALIZE_SET_UNIFORM_VECTORS(glm::fvec4, 4f)
SPECIALIZE_SET_UNIFORM_VECTORS(glm::dvec2, 2d)
SPECIALIZE_SET_UNIFORM_VECTORS(glm::dvec3, 3d)
SPECIALIZE_SET_UNIFORM_VECTORS(glm::dvec4, 4d)
#undef SPECIALIZE_SET_UNIFORM_VECTORS

#define SPECIALIZE_SET_UNIFORM_MATRICES(TYPE, GL_POSTFIX)                                      \
  template <>                                                                                  \
  inline void Program::set_uniform(GLint location, const TYPE& value) {                        \
    glProgramUniformMatrix##GL_POSTFIX##v(m_id, location, 1, GL_FALSE, glm::value_ptr(value)); \
  }                                                                                            \
  template <>                                                                                  \
  inline void Program::set_uniform_vector(GLint location, const std::vector<TYPE>& values) {   \
    glProgramUniformMatrix##GL_POSTFIX##v(m_id, location, (GLsizei)values.size(), GL_FALSE,    \
                                          glm::value_ptr(values[0]));                          \
  }

SPECIALIZE_SET_UNIFORM_MATRICES(glm::fmat2, 2f)
SPECIALIZE_SET_UNIFORM_MATRICES(glm::fmat3, 3f)
SPECIALIZE_SET_UNIFORM_MATRICES(glm::fmat4, 4f)
SPECIALIZE_SET_UNIFORM_MATRICES(glm::dmat2, 2d)
SPECIALIZE_SET_UNIFORM_MATRICES(glm::dmat3, 3d)
SPECIALIZE_SET_UNIFORM_MATRICES(glm::dmat4, 4d)
#undef SPECIALIZE_SET_UNIFORM_MATRICES

}  // namespace gl
