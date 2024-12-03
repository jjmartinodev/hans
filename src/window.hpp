#ifndef HANS_WINDOW_H
#define HANS_WINDOW_H

namespace hs {

namespace window {

constexpr bool HANS_SUCESSFUL = true;
constexpr bool HANS_FAILED = false;

int init(unsigned int width, unsigned int height, const char *title);
void uptade_window();
int running();
void deinit();

} // namespace window

} // namespace hs

#endif