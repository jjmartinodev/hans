#include "shader.h"
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct hs_Shader {
  GLuint id;
} hs_Shader;

GLuint load_shader(GLenum kind, const char *source) {
  GLuint shader = glCreateShader(kind);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);

  int success;
  char info_log[512] = {0};
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, info_log);
    printf("%s\n", info_log);
  }
  return shader;
}
unsigned int hs_raw_program_id(hs_Shader *shader) { return shader->id; }
hs_UniformLocation hs_get_uniform_location(hs_Shader *shader,
                                           const char *name) {
  return glGetUniformLocation(shader->id, name);
}
void hs_uniform_1f(hs_Shader *shader, hs_UniformLocation location, float v) {
  glUseProgram(shader->id);
  glUniform1f(location, v);
}
void hs_uniform_2f(hs_Shader *shader, hs_UniformLocation location, float v1,
                   float v2) {
  glUseProgram(shader->id);
  glUniform2f(location, v1, v2);
}
void hs_uniform_3f(hs_Shader *shader, hs_UniformLocation location, float v1,
                   float v2, float v3) {
  glUseProgram(shader->id);
  glUniform3f(location, v1, v2, v3);
}
void hs_uniform_4f(hs_Shader *shader, hs_UniformLocation location, float v1,
                   float v2, float v3, float v4) {
  glUseProgram(shader->id);
  glUniform4f(location, v1, v2, v3, v4);
}
void hs_uniform_mat4x4f(hs_Shader *shader, hs_UniformLocation location,
                        float *v) {
  glUseProgram(shader->id);
  glUniformMatrix4fv(location, 1, GL_FALSE, v);
}
void hs_uniform_1u(hs_Shader *shader, hs_UniformLocation location,
                   unsigned int v) {
  glUseProgram(shader->id);
  glUniform1ui(location, v);
}
void hs_uniform_2u(hs_Shader *shader, hs_UniformLocation location,
                   unsigned int v1, unsigned int v2) {
  glUseProgram(shader->id);
  glUniform2ui(location, v1, v2);
}
void hs_uniform_3u(hs_Shader *shader, hs_UniformLocation location,
                   unsigned int v1, unsigned int v2, unsigned int v3) {
  glUseProgram(shader->id);
  glUniform3ui(location, v1, v2, v3);
}
void hs_uniform_4u(hs_Shader *shader, hs_UniformLocation location,
                   unsigned int v1, unsigned int v2, unsigned int v3,
                   unsigned int v4) {
  glUseProgram(shader->id);
  glUniform4ui(location, v1, v2, v3, v4);
}

hs_Shader *hs_create_shader(const char *vertex_shader_source,
                            const char *fragment_shader_source) {
  GLuint vertex_shader = load_shader(GL_VERTEX_SHADER, vertex_shader_source);
  GLuint fragment_shader =
      load_shader(GL_FRAGMENT_SHADER, fragment_shader_source);
  GLuint program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);
  int success;
  char info_log[512] = {0};
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, 512, NULL, info_log);
    printf("%s\n", info_log);
  }

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  hs_Shader *shader = malloc(sizeof(hs_Shader));
  shader->id = program;

  return shader;
}
void hs_use_shader(hs_Shader *shader) { glUseProgram(shader->id); }

void hs_delete_shader(hs_Shader **shader) {
  glDeleteProgram((*shader)->id);
  shader = NULL;
}