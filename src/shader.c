#include "shader.h"
#include <GL/glew.h>
#include <stdlib.h>

typedef struct Shader {
  GLuint id;
} Shader;

GLuint load_shader(GLenum kind, const char *source) {
  GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);

  int success;
  char info_log[512] = {0};
  glGetShaderiv(shader, GL_LINK_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, info_log);
  }
  return shader;
}
 
Shader *hs_create_shader(const char *vertex_shader_source,
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
  }

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  Shader *shader = malloc(sizeof(Shader));
  shader->id = program;

  return shader;
}

void hs_delete_shader(Shader **shader) {
  glDeleteProgram((*shader)->id);
  shader = NULL;
}