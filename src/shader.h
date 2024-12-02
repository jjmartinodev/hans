typedef struct Shader Shader;

Shader* hs_create_shader(const char* vertex_shader_source, const char* fragment_shader_source);
void hs_delete_shader(Shader** shader);