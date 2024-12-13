#ifndef HANS_MESH_HEADER
#define HANS_MESH_HEADER

typedef enum {
  HANS_FLOAT1,
  HANS_FLOAT2,
  HANS_FLOAT3,
  HANS_FLOAT4,
  HANS_UNORM_UNSIGNED_BYTE1,
  HANS_UNORM_UNSIGNED_BYTE2,
  HANS_UNORM_UNSIGNED_BYTE3,
  HANS_UNORM_UNSIGNED_BYTE4,
} hs_VertexAttribute;

typedef struct {
  const hs_VertexAttribute *attributes;
  unsigned int attribute_count;
} hs_VertexBufferDescriptor;

typedef struct hs_Mesh hs_Mesh;

hs_Mesh *hs_create_mesh(hs_VertexBufferDescriptor descriptor, void *vertices,
                        unsigned int vertex_count, unsigned int vertex_size,
                        unsigned int *indices, unsigned int index_count);
void hs_draw_mesh(hs_Mesh *mesh);
void hs_delete_mesh(hs_Mesh **mesh);

#endif