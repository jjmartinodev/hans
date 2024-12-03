#include "../include/hans/window.hpp"
#include <iostream>


int main(void) {
  if (!hs::window::init(800, 600, "hii")) {
    std::cerr << "failed to init hans!" << std::endl;
    return 1;
  }
  while (!hs::window::running()) {
    hs::window::uptade_window();
  }
  hs::window::deinit();
}