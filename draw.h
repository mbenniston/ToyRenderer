#ifndef DRAW_HEADER
#define DRAW_HEADER
#include "constants.h"
#include "vec.h"
#include "model.h"

void clearFrameBuffer(struct FrameBuffer framebuffer, const RGBA clearColor);
void clearDepthBuffer(struct DepthBuffer buffer);
void blitFrameBuffer(const struct FrameBuffer read_buf, struct FrameBuffer write_buf);
void drawTriangle(struct FrameBuffer framebuffer, const struct triangle tri, const RGB color);
void drawModel(struct FrameBuffer framebuffer, struct DepthBuffer depthbuffer, const struct model m, const mat4 projMat, const mat4 viewMat, const mat4 modelMat, const vec3 camPos);

#endif
