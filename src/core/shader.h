#ifndef HANS_SHADER_HEADER
#define HANS_SHADER_HEADER

typedef struct hs_Shader hs_Shader;
typedef unsigned int hs_UniformLocation;

hs_Shader* hs_create_shader(const char* vertex_shader_source, const char* fragment_shader_source);
unsigned int hs_raw_program_id(hs_Shader* shader);
hs_UniformLocation hs_get_uniform_location(hs_Shader* shader, const char* name);
void hs_uniform_1f(hs_Shader* shader, hs_UniformLocation location, float v);
void hs_uniform_2f(hs_Shader* shader, hs_UniformLocation location, float v1, float v2);
void hs_uniform_3f(hs_Shader* shader, hs_UniformLocation location, float v1, float v2, float v3);
void hs_uniform_4f(hs_Shader* shader, hs_UniformLocation location, float v1, float v2, float v3, float v4);
void hs_uniform_1u(hs_Shader* shader, hs_UniformLocation location, unsigned int v);
void hs_uniform_2u(hs_Shader* shader, hs_UniformLocation location, unsigned int v1, unsigned int v2);
void hs_uniform_3u(hs_Shader* shader, hs_UniformLocation location, unsigned int v1, unsigned int v2, unsigned int v3);
void hs_uniform_4u(hs_Shader* shader, hs_UniformLocation location, unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4);
void hs_uniform_mat4x4f(hs_Shader* shader, hs_UniformLocation location, float* v);
void hs_use_shader(hs_Shader* shader);
void hs_delete_shader(hs_Shader** shader);

#endif