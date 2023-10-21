/* Compiler Directives ...... */
#ifndef TERM_CANVAS__H
#define TERM_CANVAS__H
/* Include Standard Libraries */
#ifdef _WIN32
#include <io.h>
#else
#include <locale.h>
#endif
#include <math.h>
#include <wchar.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
/* Macros ................... */
#define min(a, b)    ((a) < (b)) ? (a) : (b)
#define max(a, b)    ((a) > (b)) ? (a) : (b)
#define mid(a, b, c) (min(max(a, b), c))
// Colors
#define BLACK		30
#define RED			31
#define GREEN		32
#define YELLOW		33
#define BLUE		34
#define MAGENTA		35
#define CYAN		36
#define WHITE		37
#define BR_BLACK	90
#define BR_RED		91
#define BR_GREEN	92
#define BR_YELLOW	93
#define BR_BLUE		94
#define BR_MAGENTA	95
#define BR_CYAN		96
#define BR_WHITE	97
#define DEFAULT		39
/* Enumerations ............. */
enum CANVAS_TINT {
	CANVAS_TINT_BLANK,
	CANVAS_TINT_FILL,
};
/* Structures ............... */
struct Canvas {
	size_t	height; // As to be a multiple of 4
	size_t	width;  // As to be a multiple of 2
	int	*	buffer;
	int *	attr;	// Color Buffer Attr
};
struct Vec2 { float x, y; };
struct SIZE { int w, h; };
/* Functions ................ */
void set_terminal_mode(void)
	/* This function sets stdout *
	 * mode to UTF-16. ......... */
{
#ifdef _WIN32
	_setmode(_fileno(stdout), 0x00020000);
#else
	setlocale(LC_ALL, "en_US.UTF-8");
#endif
}
struct Canvas new_canvas(struct SIZE size)
	/* This function creates a new canvas *
	 * and allocates the buffer. ........ */
{
  struct Canvas ret = {
      .height = size.h,
      .width = size.w,
      .buffer = calloc(size.w * size.h, sizeof(int)),
      .attr = calloc((size.w / 2) * (size.h / 4), sizeof(int)),
  };
  return ret;
}
void set_pixel(struct Canvas c, struct Vec2 pos, enum CANVAS_TINT t)
	/* This function places a pixel *
	 * in the canvas buffer. ...... */
{
	if ((pos.x > 0) && (pos.x < c.width) && (pos.y > 0) && (pos.y < c.height)) {
		c.buffer[(int)floorf(pos.y) * c.width + (int)floorf(pos.x)] = t;
	}
}
void set_color(struct Canvas c, struct Vec2 pos, int fc, int bg)
	/* This function places a pixel *
	 * in the canvas buffer. ...... */
{
	if ((pos.x > 0) && (pos.x < c.width) && (pos.y > 0) && (pos.y < c.height)) {
		c.attr[(int)(floorf(pos.y) / 4) * (c.width / 2) + (int)(floorf(pos.x) / 2)] = (fc << 8) | (bg + 10);
	}
}
void draw_line(struct Canvas c, struct Vec2 pos1, struct Vec2 pos2,
			   int fc, int bg, enum CANVAS_TINT t)
	/* This functions draws a line *
 	 * in the canvas buffer. ..... */
{
	int e2;
	int dx = abs((int)pos2.x - (int)pos1.x);
	int sx = pos1.x < pos2.x ? 1 : -1;
	int dy = -abs((int)pos2.y - (int)pos1.y);
	int sy = pos1.y < pos2.y ? 1 : -1;
	int err = dx + dy;
	for (;;) {
		set_pixel(c, (struct Vec2){ pos1.x, pos1.y }, t);
		set_color(c, (struct Vec2){ pos1.x, pos1.y }, fc, bg);
		if ((pos1.x == pos2.x) && (pos1.y == pos2.y)) {
			break;
		}
		e2 = err * 2;
		if (e2 >= dy) {
			err += dy;
			pos1.x += sx;
		}
		if (e2 <= dx) {
			err += dx;
			pos1.y += sy;
		}
	}
}
void draw_wire_frame_triangle(struct Canvas c,
							  struct Vec2 pos1,
							  struct Vec2 pos2,
							  struct Vec2 pos3,
							  int fg, int bg,
							  enum CANVAS_TINT t)
	/* This functions draws a wire frame *
 	 * triangle in the canvas buffer. .. */
{
	draw_line(c, pos1, pos2, fg, bg, t);
	draw_line(c, pos2, pos3, fg, bg, t);
	draw_line(c, pos3, pos1, fg, bg, t);
}
void draw_fill_triangle(struct Canvas c,
						struct Vec2 pos1,
						struct Vec2 pos2,
						struct Vec2 pos3,
						int fg, int bg,
						enum CANVAS_TINT t)
	/* This functions draws a filled triangle *
 	 * in the canvas buffer. ................ */
{
	int hx = max(max(pos1.x, pos2.x), pos3.x);
	int hy = max(max(pos1.y, pos2.y), pos3.y);
	int lx = min(min(pos1.x, pos2.x), pos3.x);
	int ly = min(min(pos1.y, pos2.y), pos3.y);
	for (int _y = 0; _y < hy; ++_y) {
		for (int _x = 0; _x < hx; ++_x) {
			float Px = lx + _x;
			float Py = ly + _y;

			float s1 = pos2.y - pos1.y;
			float s2 = pos2.x - pos1.x;
			float s3 = pos3.y - pos1.y;
			float s4 = Py - pos1.y;

			float w1 = (pos1.x * s1 + s4 * s2 - Px * s1) / (s3 * s2 - (pos3.x - pos1.x) * s1);
			float w2 = (s4 - w1 * s3) / s1;
			if ((w1 >= 0) && (w2 >= 0) && ((w1 + w2) <= 1)) {
				set_pixel(c, (struct Vec2){ lx + _x, ly + _y }, t);
				set_color(c, (struct Vec2){ lx + _x, ly + _y }, fg, bg);
			}
		}
	}
}
void draw_rectangle(struct Canvas c,
					struct Vec2 pos,
					struct SIZE size,
					size_t fg, size_t bg,
                    enum CANVAS_TINT t)
	/* This functions draws *
	 * a rectangle on the . *
	 * canvas. ............ */
{
	for (size_t _y = 0; _y < size.h; ++_y) {
		for (size_t _x = 0; _x < size.w; ++_x) {
			set_pixel(c, (struct Vec2){ pos.x + _x, pos.y + _y }, t);
			set_color(c, (struct Vec2){ pos.x + _x, pos.y + _y }, fg, bg);
		}
	}
}
void draw_circle(struct Canvas c,
				 struct Vec2 pos,
				 int r,
				 enum CANVAS_TINT t)
	/* This functions draws *
	 * a circle on the .... *
	 * canvas. ............ */
{
	for (int _y = -r; _y < r; ++_y) {
		for (int _x = -r; _x < r; ++_x) {
			if (_x * _x + _y * _y < r * r) {
				set_pixel(c, (struct Vec2){ pos.x + r + _x, pos.y + r + _y }, t);
			}
		}
	}
}
void clear_canvas(struct Canvas c, int fg, int bg, enum CANVAS_TINT t)
	/* This functions draws a filled triangle *
 	 * in the canvas buffer. ................ */
{
	draw_rectangle(c, (struct Vec2){ 0, 0 }, (struct SIZE){ c.width, c.height }, fg, bg, t);
}
void draw_canvas(struct Canvas c)
	/* This function draws the canvas buffer *
	 * the standard output as braille ...... *
	 * characters. ......................... */
{
	int oc = 0;
	for (int y = 0; y < c.height; y += 4) {
		for (int x = 0; x < c.width; x += 2) {
			if (oc != c.attr[(y / 4) * (c.width / 2) + (x / 2)]) {
				wprintf(L"\033[%d;%dm", c.attr[(y / 4) * (c.width / 2) + (x / 2)] >> 0x08,
										c.attr[(y / 4) * (c.width / 2) + (x / 2)] &  0xFF);
				oc = c.attr[(y / 4) * (c.width / 2) + (x / 2)];
			}
			putwc(0x2800 | ((c.buffer[(y + 0) * c.width + x] * 0x01) +
						    (c.buffer[(y + 0) * c.width + (x + 1)] * 0x08) +
						    (c.buffer[(y + 1) * c.width + x] * 0x02) +
						    (c.buffer[(y + 1) * c.width + (x + 1)] * 0x10) +
						    (c.buffer[(y + 2) * c.width + x] * 0x04) +
						    (c.buffer[(y + 2) * c.width + (x + 1)] * 0x20) +
						    (c.buffer[(y + 3) * c.width + x] * 0x40) +
						    (c.buffer[(y + 3) * c.width + (x + 1)] * 0x80)),
				stdout);
		}
		wprintf(L"\n");
	}
}
void free_canvas(struct Canvas c)
	/* This functions frees the *
	 * canvas buffer. ........ */
{
	free(c.buffer); c.buffer = NULL;
	free(c.attr); c.attr = NULL;
}
/* Compiler Directives ...... */
#endif // TERM_CANVAS__H
/* .......................... */
