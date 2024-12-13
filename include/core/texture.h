#ifndef HANS_TEXTURE_HEADER
#define HANS_TEXTURE_HEADER

typedef enum {
  HANS_IMAGE_FORMAT_RGBA8,
  HANS_IMAGE_FORMAT_RGB8,
} hs_ImageFormat;

unsigned int hs_format_byte_size(hs_ImageFormat format);

typedef struct {
  hs_ImageFormat format;
  unsigned char *data;
  unsigned int width, height;
} hs_Image;

hs_Image hs_image_from_path(const char *path);
void hs_delete_image(hs_Image *image);

typedef struct hs_Texture2D hs_Texture2D;

typedef enum Texture2D_Filter {
  HANS_NEAREST,
  HANS_LINEAR,
} hs_Texture_Filter;

typedef enum Texture2D_WRAP {
  HANS_CLAMP,
  HANS_REPEAT,
} hs_Texture_Wrap;

typedef struct Texture2D_Params {
  hs_Texture_Filter mag, min;
  hs_Texture_Wrap wrap_s, wrap_t;
} Texture_Params;

hs_Texture2D *hs_texture_from_image(hs_Image image);
hs_Texture2D *hs_texture_from_image_ex(hs_Image image, Texture_Params params);
unsigned int hs_raw_texture_id(hs_Texture2D *texture);
void hs_bind_texture(hs_Texture2D* texture);
void hs_delete_texture(hs_Texture2D **texture);

#endif