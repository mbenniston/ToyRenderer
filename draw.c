#include "draw.h"
#include <inttypes.h>
#include <string.h>
#include <stdio.h>

int debug_RenderedTris;

float edgeFunction(const vec3 a, const vec3 b, const vec3 c) 
{
	 return (c[0] - a[0]) * (b[1] - a[1]) - (c[1] - a[1]) * (b[0] - a[0]); 
}

void clearFrameBuffer(struct FrameBuffer framebuffer, const RGBA clearColor)
{
    for (uint32_t j = 0; j < framebuffer.height; ++j) { 
		for (uint32_t i = 0; i < framebuffer.width; ++i) { 
            framebuffer.pixels[4*(j * framebuffer.width + i) + 0] = (unsigned char)(clearColor[2] * 255); 
            framebuffer.pixels[4*(j * framebuffer.width + i) + 1] = (unsigned char)(clearColor[1] * 255); 
            framebuffer.pixels[4*(j * framebuffer.width + i) + 2] = (unsigned char)(clearColor[0] * 255); 
            framebuffer.pixels[4*(j * framebuffer.width + i) + 3] = (unsigned char)(clearColor[3] * 255); 
        } 
	}
}

void blitFrameBuffer(const struct FrameBuffer read_buf, struct FrameBuffer write_buf)
{
	for(int i = 0; i < write_buf.width; i++){
		for(int j = 0; j < write_buf.height; j++){
			float ndcX = (i + 0.5f) / write_buf.width;
			float ndcY = (j + 0.5f) / write_buf.height;
			
			int projX = round(ndcX * read_buf.width);
			int projY = round(ndcY * read_buf.height);
			int readIndex = 4*(projX + projY * read_buf.width);
			int Index = 4*(i + j * write_buf.width);
			memcpy(&write_buf.pixels[Index], &read_buf.pixels[readIndex], 4);
		}
	}
}

void clearDepthBuffer(struct DepthBuffer buffer) {
	for(int i = 0; i < buffer.width * buffer.height; i++){
		buffer.depth[i] = INFINITY;
	}
}

void drawTriangle(struct FrameBuffer framebuffer, const struct triangle tri, const RGB color)
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

				framebuffer.pixels[4*(j * FB_WIDTH + i) + 0] = (unsigned char)(color[2] * 255); 
				framebuffer.pixels[4*(j * FB_WIDTH + i) + 1] = (unsigned char)(color[1] * 255); 
				framebuffer.pixels[4*(j * FB_WIDTH + i) + 2] = (unsigned char)(color[0] * 255); 
				framebuffer.pixels[4*(j * FB_WIDTH + i) + 3] = (unsigned char)(1 * 255); 
			} 
		} 
	}
}

void drawTriangleDepthTested(struct FrameBuffer framebuffer, struct DepthBuffer depthbuffer, const struct triangle tri, const RGB color)
{
	float area = edgeFunction(tri.vertices[0], tri.vertices[1], tri.vertices[2]); 
 
	for (uint32_t j = 0; j < framebuffer.height; ++j) { 
		for (uint32_t i = 0; i < framebuffer.width; ++i) { 
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
				if(depthOfPixel > 1 || depthOfPixel >= depthbuffer.depth[j * depthbuffer.width + i]) continue;

				//framebuffer in bgr format
				framebuffer.pixels[4*(j * framebuffer.width + i) + 0] = (unsigned char)(color[2] * 255); 
				framebuffer.pixels[4*(j * framebuffer.width + i) + 1] = (unsigned char)(color[1] * 255); 
				framebuffer.pixels[4*(j * framebuffer.width + i) + 2] = (unsigned char)(color[0] * 255); 
				framebuffer.pixels[4*(j * framebuffer.width + i) + 3] = (unsigned char)(1 * 255); 

				depthbuffer.depth[(j * depthbuffer.width + i)] = depthOfPixel;
			} 
		} 
	}
}

void drawModel(struct FrameBuffer framebuffer, struct DepthBuffer depthbuffer, const struct model m, const mat4 projMat, const mat4 viewMat, const mat4 modelMat, const vec3 camPos)
{
	mat4 normalMat;
	mat4_cpy(modelMat, normalMat);
	mat4 temp;
	mat4_inverse(normalMat, temp);
	mat4_transpose(temp, normalMat);

	for(int i = 0; i < m.numTriangles; i++){
		//project triangle
		struct triangle projectedTri;
		int offScreenCnt = 0;
		for(int v = 0; v < 3; v++){
			vec4 projectedPos = {m.triangles[i].vertices[v][0],m.triangles[i].vertices[v][1],m.triangles[i].vertices[v][2],1};
			vec4_mul_mat4(projectedPos, modelMat, projectedPos);
			vec4_mul_mat4(projectedPos, viewMat, projectedPos);

			//position of vertex in camera space
			vec3 camSpaceN;
			vec3_neg(projectedPos, camSpaceN);
			vec3_normalize(camSpaceN, camSpaceN);

			vec4_mul_mat4(projectedPos, projMat, projectedPos);
			projectedPos[0] /= projectedPos[3];
			projectedPos[1] /= projectedPos[3];
			projectedPos[2] /= projectedPos[3];

			//coords now in ndc
			//dont render triangles that are not in the viewport
			if(projectedPos[0] < -1 || projectedPos[0] > 1 || projectedPos[1] < -1 || projectedPos[1] > 1 || projectedPos[2] < -1 || projectedPos[2] > 1 ) {
				offScreenCnt++;
			}
			
			//bring the vertex into raster-space
			projectedPos[0] += 1; 
			projectedPos[0] *= framebuffer.width*0.5f; 

			projectedPos[1] += 1; 
			projectedPos[1] *= framebuffer.height*0.5f; 
			vec3_cpy(projectedPos, projectedTri.vertices[v]);  

			//transform normal
			vec4 normal = {m.triangles[i].normals[v][0],m.triangles[i].normals[v][1],m.triangles[i].normals[v][2],1};
			vec4 newNormal;
			vec4_mul_mat4(normal, normalMat, newNormal);
			vec3_cpy(newNormal, projectedTri.normals[v]);  

			//backface cull
			float n = vec3_dot(newNormal, camSpaceN);
			if(n < 0) {
				offScreenCnt = 3;
				continue;
			}
		}

		if(offScreenCnt == 3) continue;

		vec3 lightDir = {-0.7, -0.5, 1};
		vec3_neg(lightDir, lightDir);
		vec3_normalize(lightDir, lightDir);

		float ndotl = fmax(0.05f, vec3_dot(projectedTri.normals[1], lightDir));
		RGB col = {ndotl,0  * ndotl,0.5 * ndotl};

		drawTriangleDepthTested(framebuffer, depthbuffer, projectedTri, col);
		debug_RenderedTris++;
	}
}
