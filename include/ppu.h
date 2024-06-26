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
#define N_SCANLINES 228

#define PALETTE_RAM_SIZE (1 << 10)
#define VRAM_SIZE (0x18000)
#define OAM_SIZE (1 << 10)

typedef struct ppu_t {
    u8 PALETTE_RAM[PALETTE_RAM_SIZE];
    u8 VRAM[VRAM_SIZE];
    u8 OAM[OAM_SIZE];

    u16 DISPCNT;
    u16 DISPSTAT;
    u16 VCOUNT;

    u16 BGCNT[4];
    u16 BGHOFS[4];
    u16 BGVOFS[4];

    u32 BGX[2];
    u32 BGY[2];
    u32 INTERNAL_BGX[2];
    u32 INTERNAL_BGY[2];
    u16 BGP[2*4];

    u16 WINH[2];
    u16 WINV[2];
    u16 WININ;
    u16 WINOUT;

    u16 BLDCNT;
    u16 BLDALPHA;
    u16 BLDY;

    bool isHBlank;
    bool isVBlank;
    bool isVCount;    
} ppu_t;

void composeDispstat(ppu_t* ppu);
void updatePPU(gba_t* gba, u32 cycle_count);
void checkVCount(gba_t* gba);

void drawPaletteRam(SDL_Window* win, u8* ptr);
void drawTileMap(SDL_Window* win, ppu_t* ppu);

void event_startScanline(gba_t* gba, u32 vcount, u32 dummy);
void event_startHBlank(gba_t* gba, u32 dummy1, u32 dummy2);

#endif