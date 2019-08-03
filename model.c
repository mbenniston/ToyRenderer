#include "model.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

#include "util.h"

#define INITIAL_TRIANGLES 1024

struct face {
    unsigned int v0, v1, v2; //indicies
    unsigned int t0, t1, t2; //indicies
    unsigned int n0, n1, n2; //indicies
};

void model_Load(const char* filePath, struct model* const m)
{
    //Open file
    FILE* file = fopen(filePath, "r");
    if(!file) {
        printf("Could not open file: %s\n", filePath);
        exit(1);
    } else {
        printf("Opened %s for reading\n", filePath);
    }

    // vec3* verticesBuffer = malloc(1024 * 3 * sizeof(float));
    // size_t currentVertexIndex = 0;

    struct array_list verticesBuffer, normalsBuffer, facesBuffer;
    array_list_Init(sizeof(vec3), 100, &verticesBuffer);
    array_list_Init(sizeof(vec3), 100, &normalsBuffer);
    array_list_Init(sizeof(struct face), 100, &facesBuffer);

    //Parse file
    while(!feof(file)) {
        char lineBuffer[255];
        char* line = fgets(lineBuffer, 255, file);
        if(line) {
            
            if(strncmp(line, "v ", 2) == 0) {
                //handle vertex
                vec3 vertex;
                int ret = sscanf(line, "v %f %f %f\n", &vertex[0], &vertex[1], &vertex[2]);    
                assert(ret == 3);
                array_list_Push(&verticesBuffer, vertex);

            } else if(strncmp(line, "vn ", 3) == 0) {
                //handle normal
                vec3 normal;
                int ret = sscanf(line, "vn %f %f %f\n", &normal[0], &normal[1], &normal[2]);    
                assert(ret == 3);
                array_list_Push(&normalsBuffer, normal);

            }else if(strncmp(line, "f ", 2) == 0) {
                //handle face
                struct face face;
                int ret = sscanf(line, "f %i/%i/%i %i/%i/%i %i/%i/%i",
                    &face.v0, &face.t0, &face.n0, 
                    &face.v1, &face.t1, &face.n1, 
                    &face.v2, &face.t2, &face.n2 
                );    
                assert(ret == 9);

                array_list_Push(&facesBuffer, &face);
                
                //check if buffer is exceeded
             }
        }
    }

    //Allocate memory for triangles
    m->triangles = malloc(facesBuffer.currentItem * 3 * sizeof(struct triangle));
    m->numTriangles = 0;

    //compile faces
    for(int i = 0; i < facesBuffer.currentItem; i++) {
        struct face f = ((struct face*)facesBuffer.array)[i];
        struct triangle* tri = &m->triangles[m->numTriangles];
        vec3_cpy(((vec3*)verticesBuffer.array)[f.v0 - 1], (*tri).vertices[0]);
        vec3_cpy(((vec3*)verticesBuffer.array)[f.v1 - 1], (*tri).vertices[1]);
        vec3_cpy(((vec3*)verticesBuffer.array)[f.v2 - 1], (*tri).vertices[2]);

        vec3_cpy(((vec3*)normalsBuffer.array)[f.n0 - 1], (*tri).normals[0]);
        vec3_cpy(((vec3*)normalsBuffer.array)[f.n1 - 1], (*tri).normals[1]);
        vec3_cpy(((vec3*)normalsBuffer.array)[f.n2 - 1], (*tri).normals[2]);

        m->numTriangles++;
    }

    //Cleanup
    array_list_Free(&verticesBuffer);
    array_list_Free(&facesBuffer);
    array_list_Free(&normalsBuffer);
    fclose(file);

    printf("Loaded %li triangles\n", m->numTriangles);
}

void model_Free(struct model* m) 
{
    free(m->triangles);
    m->numTriangles = 0;
}
