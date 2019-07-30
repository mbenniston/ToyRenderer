#ifndef FB_HEADER
#define FB_HEADER

typedef unsigned char* FrameBuffer;
typedef float* DepthBuffer;
#define FB_WIDTH 800 
#define FB_HEIGHT 600
#define FB_ASPECT ((float)FB_WIDTH / FB_HEIGHT)
// #define FB_ASPECT ((float)1920 / 1080)
#define CAM_NEAR 0.1f
#define CAM_FAR 100.0f
#define CAM_FOV 90.0f //degrees

typedef float RGB[3];
typedef float RGBA[4];



#endif