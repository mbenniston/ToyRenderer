#include <MiniFB.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#include "draw.h"
#include "model.h"

extern int debug_RenderedTris;

vec3 camPos;

int forward = 0;
int strafe = 0;

void keyboard_cb(struct Window *window, Key key, KeyMod mod, bool isPressed)
{
	switch(key) {
		case KB_KEY_A:
			if(isPressed) { 
				strafe = -1;
			} else {
				strafe = 0;
			}
			break;
		case KB_KEY_D:
			if(isPressed) { 
				strafe = 1;
			} else {
				strafe = 0;
			}
			break;
		case KB_KEY_W:
			if(isPressed) { 
				forward = 1;
			} else {
				forward = 0;
			}
			break;
		case KB_KEY_S:
			if(isPressed) { 
				forward = -1;
			} else {
				forward = 0;
			}	
			break;
	}
}

int main()
{
	struct model mod, mod2;
	model_Load("sphere.obj", &mod);
	model_Load("cube.obj", &mod2);

	struct FrameBuffer framebuffer;
	framebuffer.width = FB_WIDTH;
	framebuffer.height= FB_HEIGHT;
	framebuffer.pixels = malloc(framebuffer.width * framebuffer.height * 4);
	
	struct FrameBuffer framebuffer_LowRes;
	framebuffer_LowRes.width = FB_WIDTH * RENDER_SCALE;
	framebuffer_LowRes.height= FB_HEIGHT * RENDER_SCALE;
	framebuffer_LowRes.pixels = malloc(framebuffer_LowRes.width * framebuffer_LowRes.height * 4);

	struct DepthBuffer depthbuffer;
	depthbuffer.width = framebuffer_LowRes.width;
	depthbuffer.height = framebuffer_LowRes.height;
	depthbuffer.depth = malloc(depthbuffer.width * depthbuffer.height * sizeof(float));

	printf("main framebuffer at %i x %i resolution\n", FB_WIDTH, FB_HEIGHT);
	printf("internal rendering framebuffer at %i x %i resolution\n", (int)(FB_WIDTH * RENDER_SCALE), (int)(FB_HEIGHT * RENDER_SCALE));

	struct Window* window = mfb_open_ex("Test", FB_WIDTH, FB_HEIGHT, WF_RESIZABLE);
	mfb_keyboard_callback(window, keyboard_cb);

	if (!window)
		return 0;

	camPos[0] = 0;
	camPos[1] = 0;
	camPos[2] = 0;

	clock_t start;
	clock_t end;
	double timeTaken = 0, fpsTimer = 0;
	int numFrames = 0;
	for (;;)
	{
		start = clock();

		//clear 
		RGBA clearCol = {0.1,0.1,0.23, 1};
		clearFrameBuffer(framebuffer_LowRes, clearCol);
		clearDepthBuffer(depthbuffer);

		camPos[2] += 10 * forward * timeTaken;
		camPos[0] += 10 * strafe * timeTaken;

		mat4 projMat;
		mat4_setPerspective(projMat, CAM_FOV, FB_ASPECT, CAM_NEAR, CAM_FAR);

		mat4 rotMat;
		mat4_setIdentity(rotMat);
		static float t = 0;
		t += timeTaken * 0.5f * PI;
		mat4_setRotXYZ(t * 0.75f, t, 0, rotMat);

		mat4 transMat;
		mat4_setIdentity(transMat);
		vec3 pos = {0,0, 5};
		mat4_setTranslation(transMat, pos[0], pos[1], pos[2]);

		mat4 modelMat;
		mat4_setIdentity(modelMat);
		mat4_mul(rotMat, transMat, modelMat);

		mat4 viewMat;
		mat4_setIdentity(viewMat);
		mat4_setTranslation(viewMat, -camPos[0], -camPos[1], -camPos[2]);

		debug_RenderedTris = 0;

		for(int i = 0; i < 4; i++) {
			mat4_setTranslation(modelMat, 3 * i, 0, 5);
			drawModel(framebuffer_LowRes, depthbuffer, i % 2 == 0 ? mod : mod2, projMat, viewMat, modelMat, camPos);
		}
		//upscale
		blitFrameBuffer(framebuffer_LowRes, framebuffer);

		int state = mfb_update(window, framebuffer.pixels);

		if (state < 0)
			break;

		end = clock();
		clock_t diff = end - start;
		timeTaken = (double)diff / CLOCKS_PER_SEC;
		// if(timeTaken < 1.0f / 30.0f) {
		// 	usleep((1.0f / 30.0f - timeTaken) * powf(10, 6));
		// }

		numFrames++;
		fpsTimer += timeTaken;
		if(fpsTimer > 1.0) { 
			printf("fps: %f\n", numFrames / fpsTimer);
			printf("%i triangles rendered\n", debug_RenderedTris);
			numFrames = 0;
			fpsTimer = 0.0;
		}
		
	}

	free(framebuffer.pixels);
	free(framebuffer_LowRes.pixels);
	free(depthbuffer.depth);
	model_Free(&mod);

	return 0;
}
