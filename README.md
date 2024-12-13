# HANS

### What is it?
Hans is a game engine written in C and OpenGL (GLFW and glew).

### Why?
because, I want to make games and write code. Game engines like Godot or Unity have a really high level approach, with things like C# or GDScript. My approach would be to bring things like high level abstractions of textures, meshes, etc..., and structures that solve game programming problems, like rendering tilemaps, sprites, particles, simulating object physics, and more. All this while having control of the game loop.

## How to build

### CMake

step 1: download the source and add it to your project's folder.

step 2: include the directory in your CMakeLists file by writing
```
# "hans" is hans' path in your project's folder
add_subdirectory(hans)
include_directories(hans/include)
target_link_libraries(my_binary hans)
```