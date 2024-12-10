#include "../src/mesh.h"
#include "../src/shader.h"
#include "../src/window.h"
#include <GL/glew.h>
#include <math.h>
#include <stdio.h>

typedef struct {
  float position[2];
  unsigned char color[4];
} Vertex;

const Vertex vertices[4] = {
    -0.1, -0.1, 255, 0,   0, 0, 0.1,  -0.1, 255, 255, 0,   0,
    0.1,  0.1,  0,   255, 0, 0, -0.1, 0.1,  0,   0,   255, 0,
};

const unsigned int indices[6] = {0, 1, 2, 0, 2, 3};

const char vs_source[] = "#version 330 core\n"
                         "layout(location = 0) in vec2 in_position;\n"
                         "layout(location = 1) in vec4 in_color;\n"
                         "out vec4 out_color;\n"
                         "out vec2 out_position;\n"
                         "\n"
                         "uniform vec2 offset;\n"
                         "\n"
                         "void main() {\n"
                         "\n"
                         "gl_Position = vec4(in_position + offset,0,1);\n"
                         "out_color = in_color;\n"
                         "out_position = in_position+offset;\n"
                         "\n"
                         "}\n";

const char fs_source[] = "#version 330 core\n"
                         "in vec4 out_color;\n"
                         "in vec2 out_position;\n"
                         "\n"
                         "uniform vec2 offset;\n"
                         "\n"
                         "void main() {\n"
                         "\n"
                         "float dst = distance(out_position, offset);"
                        " if (dst > 0.1) discard;\n"
                         "gl_FragColor = vec4(out_color);\n"
                         "\n"
                         "}\n";

int main(void) {
  if (hs_init(800, 600, "hii") != HANS_SUCESSFUL) {
    printf("failed to init hans!");
    return 1;
  }

  hs_Shader *shader = hs_create_shader(vs_source, fs_source);
  hs_UniformLocation offset_uniform = hs_get_uniform_location(shader, "offset");

  hs_VertexAttribute attributes[2] = {HANS_FLOAT2, HANS_UNORM_UNSIGNED_BYTE4};
  hs_VertexBufferDescriptor buffer_descriptor = {.attributes = attributes,
                                                 .attribute_count = 2};
  hs_Mesh *mesh = hs_create_mesh(buffer_descriptor, (void *)vertices, 4,
                                 sizeof(Vertex), (unsigned int *)indices, 6);

  float past = (float)hs_time();
  float t = 100.0;

  while (hs_running()) {
    hs_uptade_events();
    hs_clear(0.7, 0.3, 0.5);

    float now = (float)hs_time();
    t += now - past;
    past = now;

    hs_use_shader(shader);
    for (float a = 0.0f; a < 100.f; a += 0.1) {
      float x = cosf(a + t) * 0.5;
      float y = tanf(a + t) * 0.5;

      hs_uniform_2f(shader, offset_uniform, x, y);
      hs_draw_mesh(mesh);
    }
  }
  hs_delete_mesh(&mesh);
  hs_delete_shader(&shader);
  hs_deinit();
}