# term canvas library docs 
___

## Structs 
___

### Canvas: The canvas that the library uses
| Name   | Type     | Description              |
|--------|----------|--------------------------|
| width  | `size_t` | The width of the canvas  |
| height | `size_t` | The height of the canvas |
| buffer | `int *`  | The actual canvas data   |

---
## Functions
___

### set_terminal_mode: Sets the terminal mode to UTF-16 mode

#### Parameters
void

#### Returns
void

___

### new_canvas: Creates a new canvas

#### Parameters
| Name | Type     | Description              |
|------|----------|--------------------------|
| w    | `size_t` | The height of the canvas |
| h    | `size_t` | The width of the canvas  |

#### Returns
Struct canvas

___

### draw_line: Draws a line

#### Parameters
| Name | Type            | Description                                    |
|------|-----------------|------------------------------------------------|
| c    | `Struct Canvas` | The canvas that this should be added into      |
| x1   | `size_t`        |                                                |
| y1   | `size_t`        |                                                |
| x2   | `size_t`        |                                                |
| y2   | `size_t`        |                                                |
| t    | `int`           | The char that needed to be drawn on the canvas |

#### Returns
 void
______

### draw_full_line: Draws a line

#### Parameters
| Name | Type            | Description                                    |
|------|-----------------|------------------------------------------------|
| c    | `Struct Canvas` | The canvas that this should be added into      |
| x1   | `size_t`        |                                                |
| y1   | `size_t`        |                                                |
| x2   | `size_t`        |                                                |
| y2   | `size_t`        |                                                |
| x3   | `size_t`        |                                                |
| y3   | `size_t`        |                                                |
| t    | `int`           | The char that needed to be drawn on the canvas |

#### Returns
 void
___
___

### draw_rectangle: Draws a draw_rectangle

#### Parameters
| Name | Type            | Description                                    |
|------|-----------------|------------------------------------------------|
| c    | `Struct Canvas` | The canvas that this should be added into      |
| x    | `size_t`        |                                                |
| y    | `size_t`        |                                                |
| w    | `size_t`        |                                                |
| h    | `size_t`        |                                                |
| t    | `int`           | The char that needed to be drawn in the canvas |

#### Returns
 void
___
___

### draw_rectangle: Draws a draw_rectangle

#### Parameters
| Name | Type            | Description                                    |
|------|-----------------|------------------------------------------------|
| c    | `Struct Canvas` | The canvas that this should be added into      |
| x    | `size_t`        |                                                |
| y    | `size_t`        |                                                |
| w    | `size_t`        |                                                |
| h    | `size_t`        |                                                |
| t    | `int`           | The char that needed to be drawn in the canvas |

#### Returns
 void
___
___

### draw_circle: Draws a circle

#### Parameters
| Name | Type            | Description                                    |
|------|-----------------|------------------------------------------------|
| c    | `Struct Canvas` | The canvas that this should be added into      |
| x    | `size_t`        |                                                |
| y    | `size_t`        |                                                |
| r    | `size_t`        |                                                |
| t    | `int`           | The char that needed to be drawn in the canvas |

#### Returns
 void
___
___

### set_pixel: Sets a pixel in the canvas

#### Parameters
| Name | Type            | Description                                  |
|------|-----------------|----------------------------------------------|
| c    | `Struct Canvas` | The canvas that this should be added into    |
| x    | `size_t`        |                                              |
| y    | `size_t`        |                                              |
| t    | `int`           | The char that needed to be set in the canvas |

#### Returns
 void
___
___

### draw_canvas: Prints the canvas to the screen

#### Parameters
| Name | Type            | Description                            |
|------|-----------------|----------------------------------------|
| c    | `Struct Canvas` | The canvas that is going to be printed |

#### Returns
 void
___
___

### free_canvas: Frees the memory that a canvas is using

#### Parameters
| Name | Type            | Description                          |
|------|-----------------|--------------------------------------|
| c    | `Struct Canvas` | The canvas that is going to be freed |

#### Returns
 void
___


