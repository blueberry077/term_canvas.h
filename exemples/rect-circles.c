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
	draw_rectangle(canvas, 0, 0, canvas.width, canvas.height, 1);
	draw_rectangle(canvas, 3, 3, canvas.width-5, canvas.height-5, 0);
	draw_rectangle(canvas, 5, 5, canvas.width-9, (canvas.height-9)/2-1, 1);
	draw_rectangle(canvas, 5, (canvas.height)/2+1, (canvas.width-9)/2-1, (canvas.height-9)/2, 1);
	draw_rectangle(canvas, 5+(canvas.width-9)/2+1, (canvas.height)/2+1, (canvas.width-9)/2, (canvas.height-9)/2, 1);
	draw_circle(canvas, (canvas.width/2)-20, (canvas.height/2)-20, 20, 0);
	draw_circle(canvas, (canvas.width/2)-10, (canvas.height/2)-10, 10, 1);
	draw_canvas(canvas);
	wprintf(L"[ DBG ] Program Ended\n");
	free_canvas(canvas);
	return 0;
}
/* .......................... */
