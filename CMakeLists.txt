cmake_minimum_required(VERSION 3.16)

project(hans)

find_package(OpenGL REQUIRED)

option(HANS_BUILD_EXAMPLES "build hans' example programs" OFF)

add_subdirectory(glew/build/cmake)
add_subdirectory(cglm)
add_subdirectory(glfw)

include_directories(
  glfw/include
  glew/include
  cglm/include
)

add_library(
  ${PROJECT_NAME}
  STATIC
  src/core/window.c
  src/core/texture.c
  src/core/mesh.c
  src/core/shader.c
)

target_link_libraries(
  ${PROJECT_NAME}
  ${OPENGL_GL_LIBRARY}
  glew_s
  glfw
  cglm
  m
)

if (HANS_BUILD_EXAMPLES)
  target_link_libraries(${PROJECT_NAME} m)
  add_executable(clear_example examples/clear.c)
  target_link_libraries(clear_example ${PROJECT_NAME})

  add_executable(mesh_example examples/mesh.c)
  target_link_libraries(mesh_example ${PROJECT_NAME})

  add_executable(aliens_example examples/aliens.c)
  target_link_libraries(aliens_example ${PROJECT_NAME})
endif()