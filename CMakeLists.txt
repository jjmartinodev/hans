cmake_minimum_required(VERSION 3.16)

project(hans)

find_package(glfw3 REQUIRED)
add_subdirectory(glew/build/cmake)

include_directories(
  ${GLFW_INCLUDE_DIRS}
  glew/include
)

add_library(
  ${PROJECT_NAME}
  STATIC
  src/window.c
  src/texture.c
)
target_link_libraries(${PROJECT_NAME} ${OPENGL_GL_LIBRARY} glew glfw m)

add_executable(clear_example examples/clear.c)
target_link_libraries(clear_example ${PROJECT_NAME})

add_executable(manyaliens_example examples/manyaliens.c)
target_link_libraries(manyaliens_example ${PROJECT_NAME})