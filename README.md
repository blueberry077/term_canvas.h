# Terminal Canvas
Terminal Canvas is a C library that uses braille  
to display pixel on the terminal. **WORK IN PROGRESS**
The docs can be found [here](./docs/docs.md)!
## Quickstart
```bash
> gcc -Wall -Wextra exemples\sine -o sine -lm -O3
> sine.exe
```
## Exemples
```c
/* Include Standard Libraries */
#include "../include/term_canvas.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
/* Entry Point .............. */
int main(void) {
	struct Canvas canvas = new_canvas((struct SIZE){ 120, 24 });
	set_terminal_mode();
	for (float x = 0; x < canvas.width; ++x) {
		set_color(canvas, (struct Vec2){ 0 + x, (sin((x / 240) / (M_PI / 180.0)) * 10) + 12 }, DEFAULT, DEFAULT);
		set_pixel(canvas, (struct Vec2){ 0 + x, (sin((x / 240) / (M_PI / 180.0)) * 10) + 12 }, CANVAS_TINT_FILL);
	}
	draw_canvas(canvas);
	free_canvas(canvas);
	return 0;
}
/* .......................... */

```
![image](https://github.com/blueberry077/term_canvas.h/assets/118677993/4352e547-bed1-40fd-994a-842479b8c5ae)


