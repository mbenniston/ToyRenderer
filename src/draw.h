#ifndef DRAW_HEADER
#define DRAW_HEADER
#include "constants.h"
#include "vec.h"
#include "model.h"

void clearframebuffer(struct framebuffer framebuffer, const rgba clearColor);
void cleardepthbuffer(struct depthbuffer buffer);
void blitframebuffer(const struct framebuffer read_buf, struct framebuffer write_buf);
void drawModel(struct framebuffer framebuffer, struct depthbuffer depthbuffer, const struct model m, const mat4 projMat, const mat4 viewMat, const mat4 modelMat, const vec3 camPos);

#endif
