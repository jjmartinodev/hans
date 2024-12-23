#include "texture.h"
#include <GL/glew.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int hs_format_byte_size(hs_ImageFormat format) {

  switch (format) {
  case HANS_IMAGE_FORMAT_RGB8:
    return 3;
    break;
  case HANS_IMAGE_FORMAT_RGBA8:
    return 4;
    break;
  default:
    fprintf(stderr, "unsupported image format\n");
    break;
  }
}

hs_Image hs_image_from_path(const char *path) {
  int width = 0, height = 0, channels = 0;
  unsigned char *data = stbi_load(path, &width, &height, &channels, 0);

  if (data == NULL) {
    fprintf(stderr, "failed to load image at %s\n", path);
  }

  hs_ImageFormat format = 0;
  switch (channels) {
  case 3:
    format = HANS_IMAGE_FORMAT_RGB8;
    break;
  case 4:
    format = HANS_IMAGE_FORMAT_RGBA8;
    break;
  default:
    fprintf(stderr, "unsupported image format %s\n", path);
    break;
  }

  hs_Image image = {.data = data,
                    .width = (unsigned int)width,
                    .height = (unsigned int)height,
                    .format = format};

  return image;
}

void hs_delete_image(hs_Image *image) { stbi_image_free(image->data); }

typedef struct hs_Texture2D {
  GLuint id;
} hs_Texture2D;

hs_Texture2D *hs_texture_from_image(hs_Image image) {
  hs_Texture2D *texture = malloc(sizeof(hs_Texture2D));
  glGenTextures(1, &texture->id);
  glBindTexture(GL_TEXTURE_2D, texture->id);
  GLenum format;
  switch (image.format) {
  case HANS_IMAGE_FORMAT_RGB8:
    format = GL_RGB;
    break;
  case HANS_IMAGE_FORMAT_RGBA8:
    format = GL_RGBA;
    break;
  default:
    fprintf(stderr, "unknown image format provided");
    return NULL;
    break;
  }
  glTexImage2D(GL_TEXTURE_2D, 0, format, (GLsizei)image.width,
               (GLsizei)image.height, 0, format, GL_UNSIGNED_BYTE, image.data);
  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);
  return texture;
}
unsigned int hs_raw_texture_id(hs_Texture2D *texture) { return texture->id; }

void switch_on_params(GLenum kind, Texture_Params params) {
  switch (params.mag) {
  case HANS_LINEAR:
    glTexParameteri(kind, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    break;
  case HANS_NEAREST:
    glTexParameteri(kind, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    break;
  default:
    fprintf(stderr, "unknown filter chosen\n");
    break;
  }
  switch (params.min) {
  case HANS_LINEAR:
    glTexParameteri(kind, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    break;
  case HANS_NEAREST:
    glTexParameteri(kind, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    break;
  default:
    fprintf(stderr, "unknown filter chosen\n");
    break;
  }
  switch (params.wrap_s) {
  case HANS_REPEAT:
    glTexParameteri(kind, GL_TEXTURE_WRAP_S, GL_REPEAT);
    break;
  case HANS_CLAMP:
    glTexParameteri(kind, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    break;
  default:
    fprintf(stderr, "unknown wrap chosen\n");
    break;
  }
  switch (params.wrap_t) {
  case HANS_REPEAT:
    glTexParameteri(kind, GL_TEXTURE_WRAP_T, GL_REPEAT);
    break;
  case HANS_CLAMP:
    glTexParameteri(kind, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    break;
  default:
    fprintf(stderr, "unknown wrap chosen\n");
    break;
  }
}

hs_Texture2D *hs_texture_from_image_ex(hs_Image image, Texture_Params params) {
  hs_Texture2D *texture = malloc(sizeof(hs_Texture2D));
  glGenTextures(1, &texture->id);
  glBindTexture(GL_TEXTURE_2D, texture->id);
  switch_on_params(GL_TEXTURE_2D, params);
  GLenum format;
  switch (image.format) {
  case HANS_IMAGE_FORMAT_RGB8:
    format = GL_RGB;
    break;
  case HANS_IMAGE_FORMAT_RGBA8:
    format = GL_RGBA;
    break;
  default:
    fprintf(stderr, "unknown image format provided");
    return NULL;
    break;
  }
  glTexImage2D(GL_TEXTURE_2D, 0, format, (GLsizei)image.width,
               (GLsizei)image.height, 0, format, GL_UNSIGNED_BYTE, image.data);
  glGenerateMipmap(GL_TEXTURE_2D);
  return texture;
}

void hs_bind_texture(hs_Texture2D* texture) {
  glBindTexture(GL_TEXTURE_2D, texture->id);
}

void hs_delete_texture(hs_Texture2D **texture) {
  (*texture)->id = 0;
  free(*texture);
  *texture = NULL;
}