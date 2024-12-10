
#include "mesh.h"
#include <GL/glew.h>
#include <stdlib.h>

typedef struct hs_Mesh {
  GLuint object_buffer, vertex_buffer, index_buffer;
  unsigned int index_count;
} hs_Mesh;

unsigned int attribute_size(hs_VertexAttribute attrib) {
  switch (attrib) {
  case HANS_FLOAT1:
    return sizeof(GLfloat) * 1;
  case HANS_FLOAT2:
    return sizeof(GLfloat) * 2;
  case HANS_FLOAT3:
    return sizeof(GLfloat) * 3;
  case HANS_FLOAT4:
    return sizeof(GLfloat) * 4;
  case HANS_UNORM_UNSIGNED_BYTE1:
    return sizeof(GLubyte) * 1;
  case HANS_UNORM_UNSIGNED_BYTE2:
    return sizeof(GLubyte) * 2;
  case HANS_UNORM_UNSIGNED_BYTE3:
    return sizeof(GLubyte) * 3;
  case HANS_UNORM_UNSIGNED_BYTE4:
    return sizeof(GLubyte) * 4;
  }
}

unsigned int attribute_format(hs_VertexAttribute attrib) {
  switch (attrib) {
  case HANS_FLOAT1:
  case HANS_FLOAT2:
  case HANS_FLOAT3:
  case HANS_FLOAT4:
    return GL_FLOAT;
  case HANS_UNORM_UNSIGNED_BYTE1:
  case HANS_UNORM_UNSIGNED_BYTE2:
  case HANS_UNORM_UNSIGNED_BYTE3:
  case HANS_UNORM_UNSIGNED_BYTE4:
    return GL_UNSIGNED_INT;
  }
}

unsigned int attribute_count(hs_VertexAttribute attrib) {
  switch (attrib) {
  case HANS_FLOAT1:
  case HANS_UNORM_UNSIGNED_BYTE1:
    return 1;

  case HANS_FLOAT2:
  case HANS_UNORM_UNSIGNED_BYTE2:
    return 2;

  case HANS_FLOAT3:
  case HANS_UNORM_UNSIGNED_BYTE3:
    return 3;

  case HANS_FLOAT4:
  case HANS_UNORM_UNSIGNED_BYTE4:
    return 4;
  }
}

int attribute_norm(hs_VertexAttribute attrib) {
  switch (attrib) {
  case HANS_FLOAT1:
  case HANS_FLOAT2:
  case HANS_FLOAT3:
  case HANS_FLOAT4:
    return GL_FALSE;

  case HANS_UNORM_UNSIGNED_BYTE1:
  case HANS_UNORM_UNSIGNED_BYTE2:
  case HANS_UNORM_UNSIGNED_BYTE3:
  case HANS_UNORM_UNSIGNED_BYTE4:
    return GL_TRUE;
  }
}

unsigned int descriptor_stride(hs_VertexBufferDescriptor descriptor) {
  unsigned int stride = 0;
  for (unsigned int i = 0; i < descriptor.attribute_count; i++) {
    stride += attribute_size(descriptor.attributes[i]);
  }
  return stride;
}

void hs_draw_mesh(hs_Mesh *mesh) {
  glBindVertexArray(mesh->object_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->index_buffer);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

hs_Mesh *hs_create_mesh(hs_VertexBufferDescriptor descriptor, void *vertices,
                        unsigned int vertex_count, unsigned int vertex_size,
                        unsigned int *indices, unsigned int index_count) {
  hs_Mesh *mesh = malloc(sizeof(hs_Mesh));

  glGenVertexArrays(1, &mesh->object_buffer);
  glBindVertexArray(mesh->object_buffer);

  glGenBuffers(1, &mesh->vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, mesh->vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, vertex_count * vertex_size, vertices,
               GL_STATIC_DRAW);

  unsigned long offset = 0;
  unsigned int stride = descriptor_stride(descriptor);

  for (unsigned int i = 0; i < descriptor.attribute_count; i++) {
    glVertexAttribPointer(i, attribute_count(descriptor.attributes[i]),
                          attribute_format(descriptor.attributes[i]),
                          attribute_norm(descriptor.attributes[i]), stride,
                          (void *)offset);
    glEnableVertexAttribArray(i);
    offset += attribute_size(descriptor.attributes[i]);
  }
  
  glGenBuffers(1, &mesh->index_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->index_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(unsigned int),
               (void *)indices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  mesh->index_count = index_count;

  return mesh;
}

void hs_delete_mesh(hs_Mesh **mesh) {
  glDeleteVertexArrays(1, &(*mesh)->object_buffer);
  glDeleteBuffers(1, &(*mesh)->vertex_buffer);
  glDeleteBuffers(1, &(*mesh)->index_buffer);
  free(*mesh);
}