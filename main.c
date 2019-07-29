#include <MiniFB.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>
#include <math.h>

#include "draw.h"

int main()
{
	FrameBuffer framebuffer = malloc(800 * 600 * 4);

	struct Window* window = mfb_open_ex("Test", 800, 600, WF_RESIZABLE);
	if (!window)
		return 0;

	for (;;)
	{
		tri3 tri = {
			{0, 600, 0},
			{800,600, 0},
			{400, 0, 0}
		};
		RGB col = {1,1,1};

		//clear 
		RGBA clearCol = {0,0,0, 1};
		clearFrameBuffer(framebuffer, clearCol);
		
		//draw triangle
		//convert to screen coordinates
		drawTriangle(framebuffer, tri, col);

		int state = mfb_update(window, framebuffer);

		if (state < 0)
			break;
	}

	free(framebuffer);

	return 0;
}
