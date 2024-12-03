typedef enum {
  HANS_IMAGE_FORMAT_RGBA8,
  HANS_IMAGE_FORMAT_RGB8,
} ImageFormat;

typedef struct {
  ImageFormat format;
  unsigned char *data;
  unsigned int width, height;
} Image;


Image hs_image_from_path(const char *path);
void hs_delete_image(Image *image);

typedef struct Texture2D Texture2D;

typedef enum Texture2D_Filter {
  HANS_NEAREST,
  HANS_LINEAR,
}Texture2D_Filter;

typedef enum Texture2D_WRAP {
  HANS_CLAMP,
  HANS_REPEAT,
}Texture2D_Wrap;

typedef struct Texture2D_Params {
  Texture2D_Filter mag, min;
  Texture2D_Wrap wrap_s, wrap_t;
}Texture2D_Params;

Texture2D *hs_texture_from_image(Image image);
Texture2D *hs_texture_from_image_ex(Image image, Texture2D_Params params);
unsigned int hs_raw_texture_id(Texture2D* texture);
void hs_delete_texture(Texture2D **texture);