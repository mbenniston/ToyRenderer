#include "draw.h"
#include <inttypes.h>
#include <string.h>
#include <stdio.h>

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

void clearDepthBuffer(DepthBuffer buffer) {
	for(int i = 0; i < FB_WIDTH * FB_HEIGHT; i++){
		buffer[i] = INFINITY;
	}
}

void drawTriangle(FrameBuffer framebuffer, const struct triangle tri, const RGB color)
{
	float area = edgeFunction(tri.vertices[0], tri.vertices[1], tri.vertices[2]); 
 
	for (uint32_t j = 0; j < FB_HEIGHT; ++j) { 
		for (uint32_t i = 0; i < FB_WIDTH; ++i) { 
			float p [2]= {i + 0.5f, j + 0.5f}; 
			float w0 = edgeFunction(tri.vertices[1], tri.vertices[2], p); 
			float w1 = edgeFunction(tri.vertices[2], tri.vertices[0], p); 
			float w2 = edgeFunction(tri.vertices[0], tri.vertices[1], p); 
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

void drawTriangleDepthTested(FrameBuffer framebuffer, DepthBuffer depthbuffer, const struct triangle tri, const RGB color)
{
	float area = edgeFunction(tri.vertices[0], tri.vertices[1], tri.vertices[2]); 
 
	for (uint32_t j = 0; j < FB_HEIGHT; ++j) { 
		for (uint32_t i = 0; i < FB_WIDTH; ++i) { 
			float p [2]= {i + 0.5f, j + 0.5f}; 
			float w0 = edgeFunction(tri.vertices[1], tri.vertices[2], p); 
			float w1 = edgeFunction(tri.vertices[2], tri.vertices[0], p); 
			float w2 = edgeFunction(tri.vertices[0], tri.vertices[1], p); 
			if (w0 >= 0 && w1 >= 0 && w2 >= 0) { 
				w0 /= area; 
				w1 /= area; 
				w2 /= area; 
				
				float oneOverZ = tri.vertices[0][2] * w0 + tri.vertices[1][2] * w1 + tri.vertices[2][2] * w2;

				float depthOfPixel = oneOverZ;
				if(depthOfPixel >= depthbuffer[j * FB_WIDTH + i]) continue;

				//framebuffer in bgr format
				framebuffer[4*(j * FB_WIDTH + i) + 0] = (unsigned char)(color[2] * 255); 
				framebuffer[4*(j * FB_WIDTH + i) + 1] = (unsigned char)(color[1] * 255); 
				framebuffer[4*(j * FB_WIDTH + i) + 2] = (unsigned char)(color[0] * 255); 
				framebuffer[4*(j * FB_WIDTH + i) + 3] = (unsigned char)(1 * 255); 

				depthbuffer[(j * FB_WIDTH + i)] = depthOfPixel;
			} 
		} 
	}
}

void drawModel(FrameBuffer framebuffer, DepthBuffer depthbuffer, const struct model m, const mat4 projMat, const mat4 modelMat)
{
	mat4 normalMat;
	mat4_cpy(modelMat, normalMat);
	mat4 temp;
	mat4_inverse(normalMat, temp);
	mat4_transpose(temp, normalMat);

	for(int i = 0; i < m.numTriangles; i++){
		//project triangle
		struct triangle projectedTri;
		for(int v = 0; v < 3; v++){
			vec4 vec = {m.triangles[i].vertices[v][0],m.triangles[i].vertices[v][1],m.triangles[i].vertices[v][2],1};
			vec4 vec2;
			vec4 projectedPos;
			vec4_mul_mat4(vec, modelMat, vec2);
			vec4_mul_mat4(vec2, projMat, projectedPos);
			projectedPos[0] /= projectedPos[3];
			projectedPos[1] /= projectedPos[3];
			projectedPos[2] /= projectedPos[3];

			//coords now in ndc
			projectedPos[0] += 1; 
			projectedPos[0] *= FB_WIDTH*0.5f; 

			projectedPos[1] += 1; 
			projectedPos[1] *= FB_HEIGHT*0.5f; 
			vec3_cpy(projectedPos, projectedTri.vertices[v]);  
		
			vec4 normal = {m.triangles[i].normals[v][0],m.triangles[i].normals[v][1],m.triangles[i].normals[v][2],1};
			vec4 newNormal;
			vec4_mul_mat4(normal, normalMat, newNormal);
			vec3_cpy(newNormal, projectedTri.normals[v]);  
		}
		vec3 lightDir = {0.1, -0.5, -1};
		vec3_neg(lightDir, lightDir);
		vec3_normalize(lightDir, lightDir);

		float ndotl = fmax(0.05f, vec3_dot(projectedTri.normals[1], lightDir));
		RGB col = {ndotl, ndotl, ndotl};

		drawTriangleDepthTested(framebuffer, depthbuffer, projectedTri, col);
	}
}
