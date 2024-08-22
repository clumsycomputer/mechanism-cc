#include "types.h"
#include "ImagePixels.h"

typedef struct {
    HeapAllocation arenaAllocation;
    __ImagePixels arenaPixels;
} ImageArena;

ImageArena createRgb8bitImageArena(U16 pixelsWidth, U16 pixelsHeight);
ImageArena createRgb16bitImageArena();

