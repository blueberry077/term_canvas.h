# term canvas library docs 
___

## // Structures
### Canvas: The canvas that the library uses
```c
struct Canvas {
    size_t	height; // As to be a multiple of 4
    size_t	width;  // As to be a multiple of 2
    int	*	buffer;
    int *	attr;	// Color Buffer Attr
};
```
#### Others
```c
struct Vec2 { float x, y; }; // 2D Point
struct SIZE { int w, h; };
```
---
## // Functions
```c
struct Canvas set_terminal_mode(void);
```
Sets the terminal mode to UTF-16 mode

___
```c
struct Canvas new_canvas(
    struct SIZE size
);
```
Creates a new canvas
___
```c
void set_pixel(
    struct Canvas c,
    struct Vec2 pos,
    enum CANVAS_TINT t
);
```
Sets a pixel in the canvas
___
```c
void set_color(
    struct Canvas c,
    struct Vec2 pos,
    int fc,
    int bg
);
```
Sets a color in the canvas
___
```c
void draw_line(
    struct Canvas c,
    struct Vec2 pos1,
    struct Vec2 pos2,
    int fc,
    int bg,
    enum CANVAS_TINT t
);
```
Draws a line
___
```c
void draw_wire_frame_triangle(
    struct Canvas c,
    struct Vec2 pos1,
    struct Vec2 pos2,
    struct Vec2 pos3,
    int fg,
    int bg,
    enum CANVAS_TINT t
);
```
Draws a wire frame triangles
```c
void draw_fill_triangle(
    struct Canvas c,
    struct Vec2 pos1,
    struct Vec2 pos2,
    struct Vec2 pos3,
    int fg,
    int bg,
    enum CANVAS_TINT t
);
```
Draw a filled triangle
___
```c
void draw_rectangle(
    struct Canvas c,
    struct Vec2 pos,
    struct SIZE size,
    size_t fg,
    size_t bg,
    enum CANVAS_TINT t
);
```
Draws a rectangle
___
```c
void draw_circle(
    struct Canvas c,
    struct Vec2 pos,
    int r,
    int fg,
    int bg,
    enum CANVAS_TINT t
);
```
Draws a Circle
___
```c
void clear_canvas(
    struct Canvas c,
    int fg,
    int bg,
    enum CANVAS_TINT t
);
```
Fills the canvas with a color
___
```c
void draw_canvas(
    struct Canvas c
);
```
Prints the buffer to the terminal
___
```c
void free_canvas(
    struct Canvas c
);
```
Frees the allocated memory that a canvas uses
___


