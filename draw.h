#ifndef DRAW_HEADER
#define DRAW_HEADER
#include "constants.h"
#include "vec.h"

void clearFrameBuffer(FrameBuffer framebuffer, const RGBA clearColor);
void drawTriangle(FrameBuffer framebuffer, const tri3 triangle, const RGB color);

#endif
