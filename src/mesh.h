
typedef struct Mesh Mesh;

Mesh *hs_create_mesh(void *vertices, unsigned int vertex_size,
                  unsigned int vertex_count, unsigned int *indices,
                  unsigned int index_count);

void hs_delete_mesh(Mesh** mesh);