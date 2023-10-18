/* Compiler Directives ...... */
#ifndef TERM_CANVAS__H
#define TERM_CANVAS__H
/* Include Standard Libraries */
#ifdef _WIN32
#include <io.h>
#else
#include <locale.h>
#endif
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
/* Macros ................... */
#define min(a, b)    ((a) < (b)) ? (a) : (b)
#define max(a, b)    ((a) > (b)) ? (a) : (b)
#define mid(a, b, c) (min(max(a, b), c))
/* Structures ............... */
struct Canvas {
  size_t height; // As to be a multiple of 4
  size_t width;  // As to be a multiple of 2
  int *buffer;
};
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
struct Canvas new_canvas(size_t w, size_t h)
/* This function creates a new canvas *
 * and allocates the buffer. ........ */
{
  struct Canvas ret = {
      .height = h,
      .width = w,
      .buffer = calloc(w * h, sizeof(int)),
  };
  return ret;
}
void set_pixel(struct Canvas c, size_t x, size_t y, int t)
/* This function places a pixel *
 * in the canvas buffer. ...... */
{
  if ((x > 0) && (x < c.width) && (y > 0) && (y < c.height)) {
    c.buffer[y * c.width + x] = t;
  }
}
void draw_line(struct Canvas c, size_t x1, size_t y1, size_t x2, size_t y2, int t)
{
  int dx = abs((int)x2 - (int)x1);
  int sx = x1 < x2 ? 1 : -1;
  int dy = -abs((int)y2 - (int)y1);
  int sy = y1 < y2 ? 1 : -1;
  int err = dx + dy;
  int e2;
  while (1) {
    set_pixel(c, x1, y1, t);
    if ((x1 == x2) && (y1 == y2)) {
      break;
    }
    e2 = 2 * err;
    if (e2 >= dy) {
      err += dy;
      x1 += sx;
    }
    if (e2 <= dx) {
      err += dx;
      y1 += sy;
    }
  }
}
void draw_wire_frame_triangle(struct Canvas c, int x1, int y1, int x2, int y2, int x3, int y3, int t)
{
  draw_line(c, x1, y1, x2, y2, t);
  draw_line(c, x2, y2, x3, y3, t);
  draw_line(c, x3, y3, x1, y1, t);
}
float sign(int x1, int y1, int x2, int y2, int x3, int y3)
{
	return (x3 - x1) * (y3 - y2) - (x2 - x3) * (y1 - y3);
}
void draw_fill_triangle(struct Canvas c, int x1, int y1, int x2, int y2, int x3, int y3, int t)
{
  int hx = max(max(x1, x2), x3);
  int hy = max(max(y1, y2), y3);
  int lx = min(min(x1, x2), x3);
  int ly = min(min(y1, y2), y3);
  for (int _y = 0; _y < hy; ++_y) {
    for (int _x = 0; _x < hx; ++_x) {
      float Px = lx + _x;
      float Py = ly + _y;
	  
	  float s1 = y2 - y1;
	  float s2 = x2 - x1;
	  float s3 = y3 - y1;
	  float s4 = Py - y1;
      
	  float w1 = (x1 * s1 + s4 * s2 - Px * s1) / (s3 * s2 - (x3 - x1) * s1);
      float w2 = (s4 - w1 * s3) / s1;
	  if ((w1 >= 0) && (w2 >= 0) && ((w1 + w2) <= 1))
		set_pixel(c, lx + _x, ly + _y, t);
    }
  }
}
void draw_rectangle(struct Canvas c, size_t x, size_t y, size_t w, size_t h,
                    int t)
/* This functions draws *
 * a rectangle on the . *
 * canvas. ............ */
{
  for (size_t _y = 0; _y < h; ++_y) {
    for (size_t _x = 0; _x < w; ++_x) {
      set_pixel(c, x + _x, y + _y, t);
    }
  }
}
void draw_circle(struct Canvas c, int x, int y, int r, int t)
/* This functions draws *
 * a circle on the .... *
 * canvas. ............ */
{
  for (int _y = -r; _y < r; ++_y) {
    for (int _x = -r; _x < r; ++_x) {
      if (_x * _x + _y * _y < r * r) {
        set_pixel(c, x + r + _x, y + r + _y, t);
      }
    }
  }
}
void clear_canvas(struct Canvas c, int t)
{
	draw_rectangle(c, 0, 0, c.width, c.height, t);
}
void draw_canvas(struct Canvas c)
/* This function draws the canvas buffer *
 * the standard output as braille ..... *
 * characters. ........................ */
{
  for (size_t y = 0; y < c.height; y += 4) {
    for (size_t x = 0; x < c.width; x += 2) {
      wprintf(L"%lc",
              0x2800 | ((c.buffer[(y + 0) * c.width + x] * 0x01) +
                        (c.buffer[(y + 0) * c.width + (x + 1)] * 0x08) +
                        (c.buffer[(y + 1) * c.width + x] * 0x02) +
                        (c.buffer[(y + 1) * c.width + (x + 1)] * 0x10) +
                        (c.buffer[(y + 2) * c.width + x] * 0x04) +
                        (c.buffer[(y + 2) * c.width + (x + 1)] * 0x20) +
                        (c.buffer[(y + 3) * c.width + x] * 0x40) +
                        (c.buffer[(y + 3) * c.width + (x + 1)] * 0x80)));
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
