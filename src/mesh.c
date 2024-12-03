#include "mesh.h"
#include <GL/glew.h>
#include <stdlib.h>

typedef struct Mesh {
  GLuint vertex_buffer, index_buffer;
  unsigned int index_count;
} Mesh;

Mesh *hs_create_mesh(void *vertices, unsigned int vertex_size,
                  unsigned int vertex_count, unsigned int *indices,
                  unsigned int index_count) {

  Mesh *mesh = malloc(sizeof(Mesh));

  glGenBuffers(1, &mesh->vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, mesh->vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(vertex_count * vertex_size),
               vertices, GL_STATIC_DRAW);

  glGenBuffers(1, &mesh->index_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->vertex_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               (GLsizeiptr)(index_count * sizeof(unsigned int)), indices,
               GL_STATIC_DRAW);

  mesh->index_count = index_count;

  return mesh;
}

void hs_delete_mesh(Mesh **mesh) {
  glDeleteBuffers(1, &(*mesh)->vertex_buffer);
  glDeleteBuffers(1, &(*mesh)->index_buffer);
}