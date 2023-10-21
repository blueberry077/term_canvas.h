#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../include/term_canvas.h"

int main(void)
{
	struct Canvas canvas = new_canvas((struct SIZE){ 20, 20 });
	set_terminal_mode();
	for (int y = 0; y < 20; ++y) {
		for (int x = 0; x < 20; ++x) {
			if ((x == 1 || x == 19) || (y == 1 || y == 19))
				set_pixel(canvas, (struct Vec2){ x, y }, CANVAS_TINT_FILL);
		}
	}
	draw_canvas(canvas);
	free_canvas(canvas);
	return 0;
}