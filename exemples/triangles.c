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
	struct Canvas canvas = new_canvas(320, 240);
	set_terminal_mode();
	for (size_t i = 0; i < 100; ++i) {
		wprintf(L"\033[H\n");
		clear_canvas(canvas, 0);
		for (size_t j = 0; j < 10; ++j) {
			int x1 = rand() % canvas.width;
			int y1 = rand() % canvas.height;
			int x2 = rand() % canvas.width;
			int y2 = rand() % canvas.height;
			int x3 = rand() % canvas.width;
			int y3 = rand() % canvas.height;
			draw_fill_triangle(canvas, x1, y1, x2, y2, x3, y3, 1);
		}
		draw_canvas(canvas);
	}
	wprintf(L"[ DBG ] Program Ended\n");
	free_canvas(canvas);
	return 0;
}
/* .......................... */
