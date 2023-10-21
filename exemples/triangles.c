/* Include Standard Libraries */
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../include/term_canvas.h"
/* Entry Point .............. */
int main(void)
{
	srand(time(NULL));
	struct Canvas canvas = new_canvas((struct SIZE){ 320, 240 });
	set_terminal_mode();
	for (size_t i = 0; i < 10; ++i) {
		wprintf(L"\033[H\n");
		clear_canvas(canvas, 0, 0, 0);
		for (size_t j = 0; j < 15; ++j) {
			int x1 = rand() % canvas.width;
			int y1 = rand() % canvas.height;
			int x2 = rand() % canvas.width;
			int y2 = rand() % canvas.height;
			int x3 = rand() % canvas.width;
			int y3 = rand() % canvas.height;
			int c1 = RED + (rand() % 6);
			int c2 = BR_RED + (rand() % 6);
			draw_fill_triangle(canvas, (struct Vec2){ x1, y1 },
									   (struct Vec2){ x2, y2 },
									   (struct Vec2){ x3, y3 },
									   c1, c2, 1);
			// draw_wire_frame_triangle(canvas, (struct Vec2){ x1, y1 },
											 // (struct Vec2){ x2, y2 },
											 // (struct Vec2){ x3, y3 },
											 // c1, 39, 1);
		}
		draw_canvas(canvas);
	}
	wprintf(L"\033[0m");
	wprintf(L"[ DBG ] Program Ended\n");
	free_canvas(canvas);
	return 0;
}
/* .......................... */
