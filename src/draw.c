#include "draw.h"

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <math.h>

int max(int l, int r) 
{
	return l > r ? l : r;
}

int min(int l, int r) 
{
	return l < r ? l : r;
}

int clamp(int value, int minValue, int maxValue)
{
	return min(max(value, minValue), maxValue); 
}

float edgeFunction(const vec3 a, const vec3 b, const vec3 c) 
{
	 return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x); 
}

int debug_RenderedTris, debug_SkippedTris;

void clearframebuffer(struct framebuffer framebuffer, const rgba clearColor)
{
	unsigned char clearCol[4] = {
		clearColor[2] * 255,
		clearColor[1] * 255,
		clearColor[0] * 255,
		clearColor[3] * 255
	};

    for (uint32_t j = 0; j < framebuffer.height; ++j) { 
		for (uint32_t i = 0; i < framebuffer.width; ++i) { 
			size_t Index = 4*(j * framebuffer.width + i);
			memcpy(&framebuffer.pixels[Index], clearCol, 4);
        } 
	}
}

void blitframebuffer(const struct framebuffer read_buf, struct framebuffer write_buf)
{
	for(int i = 0; i < write_buf.width; i++){
		for(int j = 0; j < write_buf.height; j++){
			float ndcX = (i + 0.5f) / write_buf.width;
			float ndcY = (j + 0.5f) / write_buf.height;
			
			int projX = floor(ndcX * read_buf.width);
			int projY = floor(ndcY * read_buf.height);
			int readIndex = 4*(projX + projY * read_buf.width);
			int Index = 4*(i + j * write_buf.width);
			memcpy(&write_buf.pixels[Index], &read_buf.pixels[readIndex], 4);
		}
	}
}

void cleardepthbuffer(struct depthbuffer buffer) {
	for(int i = 0; i < buffer.width * buffer.height; i++){
		buffer.depth[i] = INFINITY;
	}
}

void drawTriangleDepthTested(struct framebuffer framebuffer, struct depthbuffer depthbuffer, const struct triangle tri, const rgb color)
{
	float minx = fminf(tri.vertices[2].x, fminf(tri.vertices[0].x, tri.vertices[1].x));
	float miny = fminf(tri.vertices[2].y, fminf(tri.vertices[0].y, tri.vertices[1].y));
	float maxx = fmaxf(tri.vertices[2].x, fmaxf(tri.vertices[0].x, tri.vertices[1].x));
	float maxy = fmaxf(tri.vertices[2].y, fmaxf(tri.vertices[0].y, tri.vertices[1].y));

	int startX =  clamp(minx, 0, framebuffer.width - 1);
	int startY =  clamp(miny, 0, framebuffer.height - 1);

	int endX =  clamp(round(maxx), 0, framebuffer.width - 1);
	int endY =  clamp(round(maxy), 0, framebuffer.height - 1);

	float area = edgeFunction(tri.vertices[0], tri.vertices[1], tri.vertices[2]); 
 
	for (size_t j = startY; j < endY; ++j) { 
		for (size_t i = startX; i < endX; ++i) { 
			vec3 p = {i + 0.5f, j + 0.5f, 0}; 
			float w0 = edgeFunction(tri.vertices[1], tri.vertices[2], p); 
			float w1 = edgeFunction(tri.vertices[2], tri.vertices[0], p); 
			float w2 = edgeFunction(tri.vertices[0], tri.vertices[1], p); 
			if (w0 >= 0 && w1 >= 0 && w2 >= 0) { 
				w0 /= area; 
				w1 /= area; 
				w2 /= area; 
				
				int invJ = j;
				float oneOverZ = tri.vertices[0].z * w0 + tri.vertices[1].z * w1 + tri.vertices[2].z * w2;

				float depthOfPixel = oneOverZ;
				if(depthOfPixel <= 1 && depthOfPixel < depthbuffer.depth[invJ * depthbuffer.width + i]){

					//framebuffer in bgr format
					size_t Index = 4*(invJ * framebuffer.width + i);
					framebuffer.pixels[Index    ] = (unsigned char)(color[2] * 255); 
					framebuffer.pixels[Index + 1] = (unsigned char)(color[1] * 255); 
					framebuffer.pixels[Index + 2] = (unsigned char)(color[0] * 255); 
					framebuffer.pixels[Index + 3] = (unsigned char)(1 * 255); 

					depthbuffer.depth[(invJ * depthbuffer.width + i)] = depthOfPixel;
				}
			} 
		} 
	}
}

void drawLine(struct framebuffer framebuffer, struct depthbuffer depthbuffer, const vec3 lineStart, const vec3 lineEnd, const rgb color)
{
	int dx = lineEnd.x - lineStart.x, dy = lineEnd.y - lineStart.y;

	int steps = 0;

	if(abs(dx) > abs(dy)){
		steps = abs(dx);
	} else {
		steps = abs(dy);
	}

	float xInc = dx / (float)steps; 
	float yInc = dy / (float)steps;

	float x = lineStart.x;
	float y = lineStart.y;

	for(int i = 0; i < steps; i++){
		x+= xInc;
		y+= yInc;

		if(x >= 0 && x < framebuffer.width && y >= 0 && y < framebuffer.height){
			size_t Index = 4*(round(y) * framebuffer.width + round(x));
			framebuffer.pixels[Index    ] = (unsigned char)(color[2] * 255); 
			framebuffer.pixels[Index + 1] = (unsigned char)(color[1] * 255); 
			framebuffer.pixels[Index + 2] = (unsigned char)(color[0] * 255); 
			framebuffer.pixels[Index + 3] = (unsigned char)(1 * 255); 
		}
	}
}

vec3 vec3_mul_mat4(const vec3 vec, const mat4 mat)
{
	vec4 v = {vec.x, vec.y, vec.z, 1.0f}, outV;
	outV = vec4_mul_mat4(v, mat);
	vec3 outVec3;
	outVec3.x = outV.x;
	outVec3.y = outV.y;
	outVec3.z = outV.z;
	return outVec3;
}

void drawModel(struct framebuffer framebuffer, struct depthbuffer depthbuffer, const struct model m, const mat4 projMat, const mat4 viewMat, const mat4 modelMat, const vec3 camPos)
{
	for(int i = 0; i < m.numTriangles; i++){

		//calculate vertices positions in world space
		vec3 worldSpaceVerts[3];
		worldSpaceVerts[0] = vec3_mul_mat4(m.triangles[i].vertices[0], modelMat);
		worldSpaceVerts[1] = vec3_mul_mat4(m.triangles[i].vertices[1], modelMat);
		worldSpaceVerts[2] = vec3_mul_mat4(m.triangles[i].vertices[2], modelMat);

		//calculate vertices positions in view space
		vec3 viewSpaceVerts[3];
		viewSpaceVerts[0] = vec3_mul_mat4(worldSpaceVerts[0], viewMat);
		viewSpaceVerts[1] = vec3_mul_mat4(worldSpaceVerts[1], viewMat);
		viewSpaceVerts[2] = vec3_mul_mat4(worldSpaceVerts[2], viewMat);

		//backface cull
		//calculate normal
		vec3 normal, d1, d2;
		d1 = vec3_sub(viewSpaceVerts[0], viewSpaceVerts[1]);
		d2 = vec3_sub(viewSpaceVerts[0], viewSpaceVerts[2]);
		normal = vec3_cross(d1, d2);
		normal = vec3_normalize(normal);
		
		int skip = 0;
		for(int v = 0; v < 3; v++) {
			vec3 toCameraVec;
			toCameraVec = vec3_neg(viewSpaceVerts[v]);
			toCameraVec = vec3_normalize(toCameraVec);

			float n = vec3_dot(normal, toCameraVec);
			if(n < 0.0f){
				skip =  1;
				debug_SkippedTris++;
				break;
			}
		}
		if(skip) continue; //changeme

		//calculate vertices positions in clip space
		vec3 clipSpaceVerts[3];

		//calculte the vertices positions in raster space
		for(int v = 0; v < 3; v++){
			vec3 vert = viewSpaceVerts[v];
			vec4 vertex;
			vertex.x = vert.x;
			vertex.y = vert.y;
			vertex.z = vert.z;
			vertex.w = 1.0f;
			vertex = vec4_mul_mat4(vertex, projMat);

			vertex.x /= vertex.w;
			vertex.y /= vertex.w;
			vertex.z /= vertex.w;

			clipSpaceVerts[v].x = vertex.x;
			clipSpaceVerts[v].y = vertex.y;
			clipSpaceVerts[v].z = vertex.z;

			clipSpaceVerts[v].x += 1.0f;
			clipSpaceVerts[v].x *= framebuffer.width * 0.5f;

			clipSpaceVerts[v].y += 1.0f;
			clipSpaceVerts[v].y *= framebuffer.height * 0.5f;
		}

		struct triangle projectedTri;
		memcpy(projectedTri.vertices, clipSpaceVerts, 3 * sizeof(vec3));
		rgb col = {1,1,1};
		drawTriangleDepthTested(framebuffer, depthbuffer, projectedTri, col);
		debug_RenderedTris++;
	}
}