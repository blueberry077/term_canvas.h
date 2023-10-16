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
  setlocale(LC_ALL, "en_US.UTF-16");
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

void draw_full_triangle(struct Canvas c, size_t x, size_t y, size_t height,
                        int t) {
  size_t pyramid_width = height * 2 - 1;
  size_t half_width = pyramid_width / 2;

  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < half_width - i; j++) {
      set_pixel(c, x + j, y + i, !t);
    }
    for (size_t j = half_width - i; j <= half_width + i; j++) {
      set_pixel(c, x + j, y + i, t);
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

void draw_triangle(struct Canvas c, size_t x, size_t y, size_t height, int t) {
  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j <= i; j++) {
      set_pixel(c, x + j, y + i, t);
    }
  }
}

void set_pixel(struct Canvas c, size_t x, size_t y, int t)
/* This function places a pixel *
 * in the canvas buffer. ...... */
{
  if ((x > 0) && (x < c.width) && (y > 0) && (y < c.height)) {
    c.buffer[y * c.width + x] = t;
  }
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
