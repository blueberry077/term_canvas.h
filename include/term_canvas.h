/* Compiler Directives ...... */
#ifndef TERM_CANVAS__H
#define TERM_CANVAS__H
/* Include Standard Libraries */
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
/* Structures ............... */
struct Canvas {
	size_t	height;		// As to be a multiple of 4
	size_t	width;		// As to be a multiple of 2
	int *	buffer;
};
/* Functions ................ */
void set_terminal_mode(void)
	/* This function sets stdout *
	 * mode to UTF-16. ......... */
{
	_setmode(_fileno(stdout), 0x00020000);
}
struct Canvas new_canvas(size_t w, size_t h)
	/* This function creates a new canvas *
	 * and allocates the buffer. ........ */
{
	struct Canvas ret = {
		.height = h,
		.width  = w,
		.buffer = calloc(w * h, sizeof(int)),
	};
	return ret;
}
void set_pixel(struct Canvas c, int x, int y, int t)
	/* This function places a pixel *
	 * in the canvas buffer. ...... */
{
	c.buffer[y * c.width + x] = t;
}
void draw_canvas(struct Canvas c)
	/* This function draws the canvas buffer *
	 * the standard output as braille ..... *
	 * characters. ........................ */
{
	for (size_t y = 0; y < c.height; y += 4) {
		for (size_t x = 0; x < c.width; x += 2) {
			wprintf(L"%lc", 0x2800 | ((c.buffer[(y + 0) * c.width + x] * 0x01) + (c.buffer[(y + 0) * c.width + (x + 1)] * 0x08) +
						     		  (c.buffer[(y + 1) * c.width + x] * 0x02) + (c.buffer[(y + 1) * c.width + (x + 1)] * 0x10) +
									  (c.buffer[(y + 2) * c.width + x] * 0x04) + (c.buffer[(y + 2) * c.width + (x + 1)] * 0x20) +
									  (c.buffer[(y + 3) * c.width + x] * 0x40) + (c.buffer[(y + 3) * c.width + (x + 1)] * 0x80)));
		}
		wprintf(L"\n");
	}
}
void free_canvas(struct Canvas c)
	/* This functions frees the *
	 * canvas buffer. ........ */
{
	free(c.buffer);
	c.buffer = NULL;
}
/* Compiler Directives ...... */
#endif // TERM_CANVAS__H
/* .......................... */
