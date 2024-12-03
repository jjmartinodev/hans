#define HANS_SUCESSFUL 1
#define HANS_FAILED 0

int hs_init(unsigned int width, unsigned int height, const char *title);
void hs_uptade_events();
int hs_running();
void hs_clear(float red, float green, float blue);
void hs_deinit();