#include "../include/hans/window.h"
#include "../include/hans/texture.h"
#include <GL/glew.h>
#include <stdio.h>

#define N 100

struct Sprite {
  // Texture
  float x, y;
};

int main(void) {
  if (hs_init(800, 600, "hii") != HANS_SUCESSFUL) {
    fprintf(stderr, "failed to init hans!");
    return 1;
  }
  Image image = hs_image_from_path("examples/resources/aliens.png");
  printf("%d %d %d\n", image.width, image.height, image.format);
  Texture2D_Params params_pixel = {
      .mag = HANS_NEAREST,
      .min = HANS_NEAREST,
      .wrap_s = HANS_REPEAT,
      .wrap_t = HANS_REPEAT,
  };
  Texture2D *texture = hs_texture_from_image_ex(image, params_pixel);
  //  Sprite Array
  struct Sprite sprites[N] = {0};
  // Sprite Renderer
  // define shader && parameters?
  while (!hs_running()) {
    hs_uptade_events();
    hs_clear(0.7, 0.3, 0.5);
    glBindTexture(GL_TEXTURE_2D, hs_raw_texture_id(texture));
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);

    glVertex2f(-1.0, -1.0);
    glTexCoord2i(0, 0);
    glVertex2f(-1.0, 1.0);
    glTexCoord2i(0, 1);
    glVertex2f(1.0, 1.0);
    glTexCoord2i(1, 1);
    glVertex2f(1.0, -1.0);
    glTexCoord2i(1, 0);
    glEnd();
  }
  hs_delete_texture(&texture);
  hs_delete_image(&image);
  hs_deinit();
}