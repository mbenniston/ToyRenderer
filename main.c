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

vec3 camPos;

int forward = 0;
int strafe = 0;

void keyboard_cb(struct Window *window, Key key, KeyMod mod, bool isPressed)
{
	switch(key) {
		case KB_KEY_A:
			if(isPressed) { 
				strafe = 1;
			} else {
				strafe = 0;
			}
			break;
		case KB_KEY_D:
			if(isPressed) { 
				strafe = -1;
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
	struct model mod;
	model_Load("sphere.obj", &mod);

	FrameBuffer framebuffer = malloc(FB_WIDTH * FB_HEIGHT * 4);
	DepthBuffer depthbuffer = malloc(FB_WIDTH * FB_HEIGHT * sizeof(float));

	struct Window* window = mfb_open_ex("Test", FB_WIDTH, FB_HEIGHT, WF_RESIZABLE);
	mfb_keyboard_callback(window, keyboard_cb);

	if (!window)
		return 0;


	clock_t start;
	clock_t end;
	double timeTake ;
	for (;;)
	{
		start = clock();

		//clear 
		RGBA clearCol = {0.1,0.1,0.1, 1};
		clearFrameBuffer(framebuffer, clearCol);
		clearDepthBuffer(depthbuffer);

		camPos[2] += 10 * forward * timeTake;
		camPos[0] += 10 * strafe * timeTake;

		//for 3d scene
		/* 
			- Process each triangle indiviually
			- Apply camera transform to each vertex
			- Project vertex with projection matrix
			- Perspective divide
			- Convert to device coords
			- Raster triangle with depth testing and clipping
		*/
		mat4 projMat;
		mat4_setPerspective(projMat, CAM_FOV, FB_ASPECT, CAM_NEAR, CAM_FAR);

		mat4 rotMat;
		mat4_setIdentity(rotMat);
		static float t = 0;
		t += timeTake * 0.5f * PI;
		mat4_setRotXYZ(t * 0.5f, t, 0, rotMat);

		mat4 transMat;
		mat4_setIdentity(transMat);
		vec3 pos = {0,0, 50};
		vec3_sub(pos, camPos, pos);
		mat4_setTranslation(transMat, pos[0], pos[1], pos[2]);

		mat4 modelMat;
		mat4_setIdentity(modelMat);
		mat4_mul(rotMat, transMat, modelMat);

		drawModel(framebuffer, depthbuffer, mod, projMat, modelMat);

		int state = mfb_update(window, framebuffer);

		if (state < 0)
			break;

		end = clock();
		clock_t diff = end - start;
		timeTake = (double)diff / CLOCKS_PER_SEC;
		// if(timeTake < 1.0f / 30.0f) {
		// 	usleep((1.0f / 30.0f - timeTake) * powf(10, -3));
		// }
	}

	free(framebuffer);
	free(depthbuffer);
	model_Free(&mod);

	return 0;
}
