
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#define HANS_SUCESSFUL 1
#define HANS_FAILED 0

struct ClearColor {
  float r, g, b;
};

struct ClearColor clear_color = {
    .r = 0.,
    .g = 0.,
    .b = 0.,
};

GLFWwindow *window = NULL;

int hs_init(unsigned int width, unsigned int height, const char *title) {
  if (glfwInit() != GLFW_TRUE) {
    fprintf(stderr, "failed to init glfw\n");
    return HANS_FAILED;
  }
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  window = glfwCreateWindow((int)width, (int)height, title, NULL, NULL);
  if (window == NULL) {
    fprintf(stderr, "failed to init window\n");
    glfwTerminate();
    return HANS_FAILED;
  }

  glfwMakeContextCurrent(window);

  GLenum err;

  if ((err = glewInit()) == GLEW_OK) {
    fprintf(stderr, "failed to init glew %s\n", glewGetErrorString(err));
    glfwDestroyWindow(window);
    glfwTerminate();
    return HANS_FAILED;
  }

  return HANS_SUCESSFUL;
}
void hs_uptade_events() { glfwPollEvents(); }
int hs_running() { return glfwWindowShouldClose(window); }
void hs_clear(float red, float green, float blue) {
  glfwSwapBuffers(window);
  if (clear_color.r != red || clear_color.g != green || clear_color.b != blue) {
    glClearColor(red, green, blue, 0.0f);
  }
  glClear(GL_COLOR_BUFFER_BIT);
}
void hs_deinit() {
  glfwDestroyWindow(window);
  glfwTerminate();
}