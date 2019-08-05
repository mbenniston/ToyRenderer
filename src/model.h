#ifndef MODEL_H
#define MODEL_H

#include <stdlib.h>
#include "vec.h"

struct model {
    struct triangle* triangles;
    size_t numTriangles;
};

void model_Load(const char* filePath, struct model* const m);
void model_Free(struct model* m);

#endif