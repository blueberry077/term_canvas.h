/* Include Standard Libraries */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "include/term_canvas.h"
/* Entry Point .............. */
int main(void)
{
	struct Canvas canvas = new_canvas(120, 24);
	set_terminal_mode();
	for (float x = 0; x < canvas.width; ++x) {
		set_pixel(canvas, 0 + x, (sin((x / 240) / (M_PI / 180.0)) * 12) + 12, 1);
	}
	draw_canvas(canvas);
	free_canvas(canvas);
	return 0;
}
/* .......................... */