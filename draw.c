#include "draw.h"
#include <inttypes.h>

float edgeFunction(const vec3 a, const vec3 b, const vec3 c) 
{
	 return (c[0] - a[0]) * (b[1] - a[1]) - (c[1] - a[1]) * (b[0] - a[0]); 
}

void clearFrameBuffer(FrameBuffer framebuffer, const RGBA clearColor)
{
    for (uint32_t j = 0; j < FB_HEIGHT; ++j) { 
		for (uint32_t i = 0; i < FB_WIDTH; ++i) { 
            framebuffer[4*(j * FB_WIDTH + i) + 0] = (unsigned char)(clearColor[2] * 255); 
            framebuffer[4*(j * FB_WIDTH + i) + 1] = (unsigned char)(clearColor[1] * 255); 
            framebuffer[4*(j * FB_WIDTH + i) + 2] = (unsigned char)(clearColor[0] * 255); 
            framebuffer[4*(j * FB_WIDTH + i) + 3] = (unsigned char)(clearColor[3] * 255); 
        } 
	}
}

void drawTriangle(FrameBuffer framebuffer, const tri3 triangle, const RGB color)
{
	float area = edgeFunction(triangle[0], triangle[1], triangle[2]); 
 
	for (uint32_t j = 0; j < FB_HEIGHT; ++j) { 
		for (uint32_t i = 0; i < FB_WIDTH; ++i) { 
			float p [2]= {i + 0.5f, j + 0.5f}; 
			float w0 = edgeFunction(triangle[1], triangle[2], p); 
			float w1 = edgeFunction(triangle[2], triangle[0], p); 
			float w2 = edgeFunction(triangle[0], triangle[1], p); 
			if (w0 >= 0 && w1 >= 0 && w2 >= 0) { 
				w0 /= area; 
				w1 /= area; 
				w2 /= area; 

				//framebuffer in bgr format

				framebuffer[4*(j * FB_WIDTH + i) + 0] = (unsigned char)(color[2] * 255); 
				framebuffer[4*(j * FB_WIDTH + i) + 1] = (unsigned char)(color[1] * 255); 
				framebuffer[4*(j * FB_WIDTH + i) + 2] = (unsigned char)(color[0] * 255); 
				framebuffer[4*(j * FB_WIDTH + i) + 3] = (unsigned char)(1 * 255); 
			} 
		} 
	}
}
