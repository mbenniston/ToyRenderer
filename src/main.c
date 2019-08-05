#include <MiniFB.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#include "util.h"
#include "draw.h"
#include "model.h"


extern int debug_RenderedTris, debug_SkippedTris;

vec3 camPos;
float camRot;

int rotSpeed = 0;
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
		case KB_KEY_LEFT: 
			if(isPressed) { 
				rotSpeed = 1;
			} else {
				rotSpeed = 0;
			}	
			break;
		case KB_KEY_RIGHT: 
			if(isPressed) { 
				rotSpeed = -1;
			} else {
				rotSpeed = 0;
			}	
			break;
		default:
			break;
	}
}

int main()
{
	struct model mod, mod2, floor;
	model_Load("./res/sphere.obj", &mod);
	model_Load("./res/cube.obj", &mod2);
	model_Load("./res/floor.obj", &floor);

	struct framebuffer framebuffer;
	framebuffer.width = FB_WIDTH;
	framebuffer.height= FB_HEIGHT;
	framebuffer.pixels = malloc(framebuffer.width * framebuffer.height * 4);
	
	struct framebuffer framebuffer_LowRes;
	framebuffer_LowRes.width = FB_WIDTH * RENDER_SCALE;
	framebuffer_LowRes.height= FB_HEIGHT * RENDER_SCALE;
	framebuffer_LowRes.pixels = malloc(framebuffer_LowRes.width * framebuffer_LowRes.height * 4);

	struct depthbuffer depthbuffer;
	depthbuffer.width = framebuffer_LowRes.width;
	depthbuffer.height = framebuffer_LowRes.height;
	depthbuffer.depth = malloc(depthbuffer.width * depthbuffer.height * sizeof(float));

	printf("main framebuffer at %i x %i resolution\n", FB_WIDTH, FB_HEIGHT);
	printf("internal rendering framebuffer at %i x %i resolution\n", (int)(FB_WIDTH * RENDER_SCALE), (int)(FB_HEIGHT * RENDER_SCALE));

	struct Window* window = mfb_open_ex("Test", FB_WIDTH, FB_HEIGHT, WF_RESIZABLE);
	mfb_keyboard_callback(window, keyboard_cb);

	if (!window)
		return 0;

	camPos.x = 0;
	camPos.y = 0;
	camPos.z = 0;

	camRot = 0;

	clock_t start;
	clock_t end;
	double timeTaken = 0, fpsTimer = 0;
	int numFrames = 0;
	for (;;)
	{
		start = clock();

		//clear 
		rgba clearCol = {0.1,0.1,0.23, 1};
		clearframebuffer(framebuffer, clearCol);
		clearframebuffer(framebuffer_LowRes, clearCol);
		cleardepthbuffer(depthbuffer);

		camPos.x += -sin(camRot) * 10 * forward * timeTaken;
		camPos.z += cos(camRot) * 10 * forward * timeTaken;

		camPos.x += cos(camRot) * 10 *  strafe * timeTaken;
		camPos.z += sin(camRot) * 10 *  strafe * timeTaken;

		camRot += 0.5f * rotSpeed * timeTaken;

		mat4 projMat;
		mat4_setPerspective(projMat, CAM_FOV, FB_ASPECT, CAM_NEAR, CAM_FAR);

		mat4 modelMat;
		static float t = 0;
		t += timeTaken * 0.5f * PI;
		mat4_setIdentity(modelMat);
		// mat4_setScale(modelMat, 0.01f + fabs(sin(t)), 0.01f + fabs(sin(t)), 0.01f + fabs(sin(t)));
		// mat4_rotate(modelMat, t * 0.75f, t, 0, modelMat);

		mat4 viewMat;
		mat4_setIdentity(viewMat);
		mat4_setTranslation(viewMat, -camPos.x, -camPos.y, -camPos.z);
		mat4_rotate(viewMat, 0, camRot, 0, viewMat);

		debug_RenderedTris = 0;
		debug_SkippedTris = 0;

		for(int i = 0; i < 1; i++) {
			// mat4_setTranslation(modelMat, 3 * (i % 10), sin(t + i%10), 5 + 3 * (i / 10));
			mat4_setTranslation(modelMat, 3 * (i % 10), 0, 5 + 3 * (i / 10));

			drawModel(framebuffer_LowRes, depthbuffer, i % 2 == 0 ? mod2 : mod2 , projMat, viewMat, modelMat, camPos);
		}

		//upscale
		blitframebuffer(framebuffer_LowRes, framebuffer);

		int state = mfb_update(window, framebuffer.pixels);

		if (state < 0)
			break;

		end = clock();
		clock_t diff = end - start;
		timeTaken = (double)diff / CLOCKS_PER_SEC;

		numFrames++;
		fpsTimer += timeTaken;
		if(fpsTimer > 1.0) { 
			printf("fps: %f\n", numFrames / fpsTimer);
			printf("%i triangles rendered\n", debug_RenderedTris);
			printf("%i triangles not rendered\n", debug_SkippedTris);
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
