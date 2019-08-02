#ifndef FB_HEADER
#define FB_HEADER

#include <stdlib.h>

struct FrameBuffer 
{
    unsigned char* pixels;
    size_t width, height;
};

struct DepthBuffer 
{
    float * depth;
    size_t width, height;
};

#define FB_WIDTH 800
#define FB_HEIGHT 600
#define RENDER_SCALE 1.0f
#define FB_ASPECT ((float)FB_WIDTH / FB_HEIGHT)
#define CAM_NEAR 0.1f
#define CAM_FAR 100.0f
#define CAM_FOV 75.0f //degrees

typedef float RGB[3];
typedef float RGBA[4];



#endif