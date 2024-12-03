cmake_minimum_required(VERSION 3.16)

project(hans)

find_package(OpenGL REQUIRED)
add_subdirectory(glew/build/cmake)
add_subdirectory(glfw)

include_directories(
  glfw/include
  glew/include
)

add_library(
  ${PROJECT_NAME}
  STATIC
  src/window.c
  src/texture.c
  src/mesh.c
  src/shader.c
)
target_link_libraries(${PROJECT_NAME} ${OPENGL_GL_LIBRARY} glew_s glfw m)

add_executable(clear_example examples/clear.c)
target_link_libraries(clear_example ${PROJECT_NAME})