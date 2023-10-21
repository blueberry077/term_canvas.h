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
	draw_rectangle(canvas, (struct Vec2){ 0, 0 }, 										 (struct SIZE){ canvas.width, canvas.height }, 				  DEFAULT, DEFAULT, CANVAS_TINT_FILL);
	draw_rectangle(canvas, (struct Vec2){ 3, 3 }, 										 (struct SIZE){ canvas.width-5, canvas.height-5 }, 			  DEFAULT, DEFAULT, CANVAS_TINT_BLANK);
	draw_rectangle(canvas, (struct Vec2){ 5, 5 }, 										 (struct SIZE){ canvas.width-9, (canvas.height-9)/2-1 },      DEFAULT, DEFAULT, CANVAS_TINT_FILL);
	draw_rectangle(canvas, (struct Vec2){ 5, (canvas.height)/2+1 }, 					 (struct SIZE){ (canvas.width-9)/2-1, (canvas.height-9)/2 },  DEFAULT, DEFAULT, CANVAS_TINT_FILL);
	draw_rectangle(canvas, (struct Vec2){ 5+(canvas.width-9)/2+1, (canvas.height)/2+1 }, (struct SIZE){ (canvas.width-9)/2, (canvas.height-9)/2 },    DEFAULT, DEFAULT, CANVAS_TINT_FILL);
	draw_circle(canvas, (struct Vec2){ (canvas.width/2)-20, (canvas.height/2)-20 }, 20, DEFAULT, DEFAULT, CANVAS_TINT_BLANK);
	draw_circle(canvas, (struct Vec2){ (canvas.width/2)-10, (canvas.height/2)-10 }, 10, DEFAULT, DEFAULT, CANVAS_TINT_FILL);
	draw_canvas(canvas);
	wprintf(L"[ DBG ] Program Ended\n");
	free_canvas(canvas);
	return 0;
}
/* .......................... */
