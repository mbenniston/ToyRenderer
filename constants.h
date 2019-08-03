#ifndef FB_HEADER
#define FB_HEADER

#include <stdlib.h>

struct framebuffer 
{
    unsigned char* pixels;
    size_t width, height;
};

struct depthbuffer 
{
    float * depth;
    size_t width, height;
};

#define FB_WIDTH 800
#define FB_HEIGHT 600
#define RENDER_SCALE 0.5f
#define FB_ASPECT ((float)FB_WIDTH / FB_HEIGHT)
#define CAM_NEAR 0.1f
#define CAM_FAR 100.0f
#define CAM_FOV 75.0f //degrees

typedef float rgb[3];
typedef float rgba[4];

#endif