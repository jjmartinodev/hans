#include "window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

GLFWwindow *window;

int hs_init(unsigned int width, unsigned int height, const char *title) {
  if (glfwInit() != GLFW_TRUE) {
    fprintf(stderr, "failed to init glfw\n");
    return HANS_FAILED;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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
int hs_running() { return !glfwWindowShouldClose(window); }
float gred = 0.0, ggreen = 0.0, gblue = 0.0, galpha = 0.0;
void hs_clear(float red, float green, float blue, float alpha) {
  if (gred != red || ggreen != green || gblue != blue || galpha != alpha) {
    glClearColor(red, green, blue, alpha);
    gred = red, ggreen = green, gblue = blue, galpha = alpha;
  }
  glClear(GL_COLOR_BUFFER_BIT);
}
void hs_uptade_window() {
  hs_uptade_window_events();
  hs_uptade_window_framebuffer();
}
void hs_uptade_window_framebuffer() {
  glfwSwapBuffers(window);
}
void hs_uptade_window_events() {
  glfwPollEvents();
}
unsigned int window_width() {
  int x, unused_y;
  glfwGetWindowSize(window, &x, &unused_y);
  return x;
}
unsigned int window_height() {
  int unused_x, y;
  glfwGetWindowSize(window, &unused_x, &y);
  return y;
}
void hs_deinit() {
  glfwDestroyWindow(window);
  glfwTerminate();
}
double hs_time() {
  return glfwGetTime();
}