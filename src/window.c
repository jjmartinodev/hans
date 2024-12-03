#include "window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

GLFWwindow *window;

int hs_init(unsigned int width, unsigned int height, const char *title) {
  if (!glfwInit()) {
    return HANS_FAILED;
  }
  window =
      glfwCreateWindow((int)width, (int)height, "hiii", (void *)0, (void *)0);
  if (!window) {
    glfwTerminate();
    return HANS_FAILED;
  }
  glfwMakeContextCurrent(window);
  GLenum err;
  if ((err = glewInit()) == GLEW_OK) {
    fprintf(stderr, "failed here");
    glfwDestroyWindow(window);
    glfwTerminate();
    return HANS_FAILED;
  }
  return HANS_SUCESSFUL;
}
void hs_uptade_events() {
  glfwPollEvents();
  glfwSwapBuffers(window);
}
int hs_running() { return !glfwWindowShouldClose(window); }
float gred = 0.0, ggreen = 0.0, gblue = 0.0;
void hs_clear(float red, float green, float blue) {
  if (gred != red || ggreen != green || gblue != blue) {
    glClearColor(red, green, blue, 0.0);
    gred = red, ggreen = green, gblue = blue;
  }
  glClear(GL_COLOR_BUFFER_BIT);
}
void hs_deinit() {
  glfwDestroyWindow(window);
  glfwTerminate();
}