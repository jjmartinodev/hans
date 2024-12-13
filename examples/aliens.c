#include "../cglm/include/cglm/cglm.h"
#include "../include/core/mesh.h"
#include "../include/core/shader.h"
#include "../include/hans.h"
#include <stdio.h>
#include <stdlib.h>

#define ALIEN_COUNT 10
#define ALIEN_SIZE 0.05f
#define ALIEN_SPEED 0.01f

typedef struct {
  vec2 position;
  vec2 direction;
  int kind;
} Alien;

typedef struct {
  float position[2];
  float uv[2];
} Vertex;

const Vertex vertices[4] = {
    -ALIEN_SIZE, -ALIEN_SIZE, 1.0, 1.0, ALIEN_SIZE,  -ALIEN_SIZE, 0.0, 1.0,
    ALIEN_SIZE,  ALIEN_SIZE,  0.0, 0.0, -ALIEN_SIZE, ALIEN_SIZE,  1.0, 0.0,
};

const unsigned int indices[6] = {0, 1, 2, 0, 2, 3};

const char vs_source[] =
    "#version 330 core\n"
    "layout(location = 0) in vec2 in_position;\n"
    "layout(location = 1) in vec2 in_uv;\n"
    "out vec2 out_uv;\n"
    "\n"
    "uniform vec2 offset;\n"
    "\n"
    "void main() {\n"
    "\n"
    "gl_Position = vec4(in_position / vec2(800.0/600.0,1.0) + offset,0,1);\n"
    "out_uv = in_uv;\n"
    "\n"
    "}\n";

const char fs_source[] =
    "#version 330 core\n"
    "in vec2 out_uv;\n"
    "\n"
    "uniform vec2 kind;\n"
    "uniform sampler2D tex;\n"
    "\n"
    "void main() {\n"
    "vec4 sampled = texture(tex, vec2(out_uv) / 4. + kind);\n"
    "if (sampled.a < 0.5) discard;\n"
    "gl_FragColor = sampled;\n"
    "\n"
    "}\n";

int main(void) {
  if (hs_init(800, 600, "aliens!!") != HANS_SUCESSFUL) {
    printf("failed to init hans!\n");
    return 1;
  }

  hs_Image atlas = hs_image_from_path("examples/resources/aliens.png");
  Texture_Params params = {
      .mag = HANS_NEAREST,
      .min = HANS_NEAREST,
      .wrap_s = HANS_CLAMP,
      .wrap_t = HANS_CLAMP,
  };

  hs_Texture2D *texture = hs_texture_from_image_ex(atlas, params);

  hs_delete_image(&atlas);

  hs_Shader *shader = hs_create_shader(vs_source, fs_source);
  hs_UniformLocation offset_uniform = hs_get_uniform_location(shader, "offset");
  hs_UniformLocation kind_uniform = hs_get_uniform_location(shader, "kind");

  hs_VertexAttribute attributes[2] = {HANS_FLOAT2, HANS_FLOAT2};
  hs_VertexBufferDescriptor buffer_descriptor = {};
  buffer_descriptor.attributes = attributes;
  buffer_descriptor.attribute_count =
      sizeof(attributes) / sizeof(hs_VertexAttribute);
  hs_Mesh *mesh = hs_create_mesh(buffer_descriptor, (void *)vertices,
                                 sizeof(vertices) / sizeof(Vertex),
                                 sizeof(Vertex), (unsigned int *)indices,
                                 sizeof(indices) / sizeof(unsigned int));

  Alien aliens[ALIEN_COUNT] = {0};
  const int position_scale = 100;
  for (int i = 0; i < ALIEN_COUNT; i++) {
    aliens[i].direction[0] = (float)(rand() % 200 - 100) * ALIEN_SPEED;
    aliens[i].direction[1] = (float)(rand() % 200 - 100) * ALIEN_SPEED;
    aliens[i].position[0] = (float)(rand() % 200 - 100);
    aliens[i].position[1] = (float)(rand() % 200 - 100);
    aliens[i].kind = rand() % (3 * 3);
  }

  float past = (float)hs_time();
  float t = 0.0;
  float a = 0.0;

  while (hs_running()) {
    hs_uptade_window();
    hs_clear(0.7, 0.3, 0.5, 0.0);

    float now = (float)hs_time();
    t += now - past;
    past = now;

    for (int i = 0; i < ALIEN_COUNT; i++) {
      hs_use_shader(shader);
      hs_bind_texture(texture);
      hs_uniform_2f(shader, offset_uniform, aliens[i].position[0] / 100.,
                    aliens[i].position[1] / 100.);
      float kind_x = (float)(aliens[i].kind % 4);
      float kind_y = roundf((float)aliens[i].kind / 4.);
      hs_uniform_2f(shader, kind_uniform, kind_x / 4., kind_y / 4.);
      hs_draw_mesh(mesh);
    }

    for (int i = 0; i < ALIEN_COUNT; i++) {
      glm_vec2_add(aliens[i].position, aliens[i].direction, aliens[i].position);
      if (aliens[i].position[0] < -100.0) {
        aliens[i].direction[0] = -aliens[i].direction[0];
      }
      if (aliens[i].position[1] < -100.0) {
        aliens[i].direction[1] = -aliens[i].direction[1];
      }
      if (aliens[i].position[0] > 100.0) {
        aliens[i].direction[0] = -aliens[i].direction[0];
      }
      if (aliens[i].position[1] > 100.0) {
        aliens[i].direction[1] = -aliens[i].direction[1];
      }
    }
  }

  hs_delete_texture(&texture);
  hs_delete_mesh(&mesh);
  hs_delete_shader(&shader);

  hs_deinit();
}