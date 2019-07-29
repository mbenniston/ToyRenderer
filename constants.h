#ifndef FB_HEADER
#define FB_HEADER

typedef unsigned char* FrameBuffer;
#define FB_WIDTH 800 
#define FB_HEIGHT 600
#define FB_ASPECT (800.0f / 600.0f)
#define CAM_NEAR 0.5f
#define CAM_FAR 600.0f
#define CAM_FOV 80.0f //degrees

typedef float RGB[3];
typedef float RGBA[4];



#endif