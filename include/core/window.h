#ifndef HANS_WINDOW_HEADER
#define HANS_WINDOW_HEADER

#define HANS_SUCESSFUL 1
#define HANS_FAILED 0

int hs_init(unsigned int width, unsigned int height, const char *title);
int hs_running();
void hs_clear(float red, float green, float blue, float alpha);
void hs_uptade_window();
void hs_uptade_window_framebuffer();
void hs_uptade_window_events();
unsigned int window_width();
unsigned int window_height();
void hs_deinit();
double hs_time();

#endif