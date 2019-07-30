#ifndef DRAW_HEADER
#define DRAW_HEADER
#include "constants.h"
#include "vec.h"
#include "model.h"

void clearFrameBuffer(FrameBuffer framebuffer, const RGBA clearColor);
void clearDepthBuffer(DepthBuffer buffer);
void drawTriangle(FrameBuffer framebuffer, const struct triangle tri, const RGB color);
void drawModel(FrameBuffer framebuffer, DepthBuffer depthbuffer, const struct model m, const mat4 projMat, const mat4 modelMat);

#endif
