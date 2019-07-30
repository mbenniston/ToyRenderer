#include "model.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define INITIAL_TRIANGLES 1024
#define TRIANGLE_SIZE (3 * 3 * sizeof(float))

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

    vec3* verticesBuffer = malloc(1024 * 3 * sizeof(float));
    size_t currentVertexIndex = 0;

    vec3* normalsBuffer = malloc(1024 * 3 * sizeof(float));
    size_t currentNormalIndex = 0;

    struct face* facesBuffer = malloc(1024 * sizeof(struct face));
    size_t currentFaceIndex = 0;

    //Parse file
    while(!feof(file)) {
        char lineBuffer[255];
        char* line = fgets(lineBuffer, 255, file);
        if(line) {
            
            if(strncmp(line, "v ", 2) == 0) {
                //handle vertex
                vec3* vertex = &verticesBuffer[currentVertexIndex];
                sscanf(line, "v %f %f %f\n", &((*vertex)[0]), &((*vertex)[1]), &((*vertex)[2]));    
                currentVertexIndex++;
                //check if buffer is exceeded

            } else if(strncmp(line, "vn ", 3) == 0) {
                //handle normal
                vec3* normal = &normalsBuffer[currentNormalIndex];
                sscanf(line, "vn %f %f %f\n", &((*normal)[0]), &((*normal)[1]), &((*normal)[2]));    
                currentNormalIndex++;
                //check if buffer is exceeded

            }else if(strncmp(line, "f ", 2) == 0) {
                //handle face
                struct face* face = &facesBuffer[currentFaceIndex];
                int ret = sscanf(line, "f %i/%i/%i %i/%i/%i %i/%i/%i",
                    &face->v0, &face->t0, &face->n0, 
                    &face->v1, &face->t1, &face->n1, 
                    &face->v2, &face->t2, &face->n2 
                );    
                if(ret != 9) exit(1); 
                
                currentFaceIndex++;
                //check if buffer is exceeded
             }
        }
    }

    //Allocate memory for triangles
    m->triangles = malloc(INITIAL_TRIANGLES * TRIANGLE_SIZE);
    m->numTriangles = 0;

    //compile faces
    for(int i = 0; i < currentFaceIndex; i++) {
        struct face f = facesBuffer[i];
        struct triangle* tri = &m->triangles[m->numTriangles];
        vec3_cpy(verticesBuffer[f.v0 - 1], (*tri).vertices[0]);
        vec3_cpy(verticesBuffer[f.v1 - 1], (*tri).vertices[1]);
        vec3_cpy(verticesBuffer[f.v2 - 1], (*tri).vertices[2]);

        vec3_cpy(normalsBuffer[f.n0 - 1], (*tri).normals[0]);
        vec3_cpy(normalsBuffer[f.n1 - 1], (*tri).normals[1]);
        vec3_cpy(normalsBuffer[f.n2 - 1], (*tri).normals[2]);

        m->numTriangles++;
    }

    //Cleanup
    free(facesBuffer);
    free(verticesBuffer);
    free(normalsBuffer);
    fclose(file);
}

void model_Free(struct model* m) 
{
    free(m->triangles);
    m->numTriangles = 0;
}
