#ifndef __PPU_H__
#define __PPU_H__

#include <SDL2/SDL.h>
#include "integer.h"

typedef struct gba_t gba_t;

#define DRAW_CYCLES 960
#define HBLANK_CYCLES 272
#define SCANLINE_CYCLES 1232
#define VBLANK 197120
#define CYCLES_PER_FRAME 280896

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160
#define REFRESH_RATE 59.73
#define SCANLINE 228

extern bool isHblank;

void composeDispstat();
void updatePPU(gba_t* gba, int cycle_count);

void drawPaletteRam(SDL_Window* win, u8* ptr);
void drawTileMap(SDL_Window* win);

#endif