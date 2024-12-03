#include "window.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

namespace hs {

namespace window {

GLFWwindow *window = NULL;

int init(unsigned int width, unsigned int height, const char *title) {
  if (glfwInit() != GLFW_TRUE) {
    fprintf(stderr, "failed to init glfw\n");
    return HANS_FAILED;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
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

void uptade_window() {
  glfwPollEvents();
  glfwSwapBuffers(window);
}

int running() { return glfwWindowShouldClose(window); }

void deinit() {
  glfwDestroyWindow(window);
  glfwTerminate();
}

} // namespace window

} // namespace hs