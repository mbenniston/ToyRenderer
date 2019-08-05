#include <math.h>
#include <time.h>
#include <stdio.h>
#include "vec.h"

const int SAMPLES = 100;

int main()
{
    mat4 testMats[2];
    mat4_setIdentity(testMats[0]);
    mat4_setIdentity(testMats[1]);

    printf("Starting multiplication test...\n");
    {
        clock_t totalTime = 0;
        for(int i = 0; i < SAMPLES; i++){
            clock_t start = clock(), end;
            mat4_mul(testMats[0], testMats[1], testMats[0]);
            end = clock();
            totalTime += end - start;
        }
        double avgTime = ((double)totalTime / SAMPLES) / CLOCKS_PER_SEC;
        printf("\tAvg time: %lfms\n", avgTime * powf(10, 3));
    }

    printf("Starting inverse test...\n");
    {
        mat4_setRotXYZ(10, 11, 100, testMats[0]);

        clock_t totalTime = 0;
        for(int i = 0; i < SAMPLES; i++){
            clock_t start = clock(), end;
            mat4_inverse(testMats[0], testMats[1]);
            end = clock();
            totalTime += end - start;
        }
        double avgTime = ((double)totalTime / SAMPLES) / CLOCKS_PER_SEC;
        printf("\tAvg time: %lfms\n", avgTime * powf(10, 3));
    }

    printf("Starting transpose test...\n");
    {
        mat4_setRotXYZ(10, 11, 100, testMats[0]);

        clock_t totalTime = 0;
        for(int i = 0; i < SAMPLES; i++){
            clock_t start = clock(), end;
            mat4_transpose(testMats[0], testMats[1]);
            end = clock();
            totalTime += end - start;
        }
        double avgTime = ((double)totalTime / SAMPLES) / CLOCKS_PER_SEC;
        printf("\tAvg time: %lfms\n", avgTime * powf(10, 3));
    }

    printf("Starting copy test...\n");
    {
        mat4_setRotXYZ(10, 11, 100, testMats[0]);

        clock_t totalTime = 0;
        for(int i = 0; i < SAMPLES; i++){
            clock_t start = clock(), end;
            mat4_cpy(testMats[0], testMats[1]);
            end = clock();
            totalTime += end - start;
        }
        double avgTime = ((double)totalTime / SAMPLES) / CLOCKS_PER_SEC;
        printf("\tAvg time: %lfms\n", avgTime * powf(10, 3));
    }


    return 0;
}