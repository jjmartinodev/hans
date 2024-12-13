#include "../include/hans.h"
#include <GL/glew.h>
#include <stdio.h>

int main(void) {
  if (hs_init(800, 600, "hii") != HANS_SUCESSFUL) {
    printf("failed to init hans!");
    return 1;
  }
  while (hs_running()) {
    hs_uptade_window();
    hs_clear(0.7, 0.3, 0.5, 1.0);
  }
  hs_deinit();
}