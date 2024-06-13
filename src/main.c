#include "SDL_MAINLOOP.h"
#include "gba.h"

#include <stdio.h>
#include <stdlib.h>

SDL_Window* bgPaletteWin;
SDL_Window* objPaletteWin;
SDL_Window* tileMapWin;

gba_t gba;

void freeAll(){
    free(gba.BIOS);
    free(gba.ROM);
}

void setup(){
    size(SCREEN_WIDTH, SCREEN_HEIGHT);
    setScaleMode(NEAREST);
    setTitle(u8"エミュボーイ　GX");
    setWindowIcon("data/logo.bmp");
    frameRate(REFRESH_RATE);
    initGba(&gba);
    #ifndef EMSCRIPTEN
    loadBios("data/gba_bios.bin", &gba.BIOS);
    #else
    loadBios("data/vba_bios.bin", &gba.BIOS);
    #endif
    gba.ROM_SIZE = loadRom(getArgv(1),&gba.ROM);
    arm7tdmi_pipeline_refill(&gba.cpu);
    init_keypad();

    noRender();

    #ifndef EMSCRIPTEN
    bgPaletteWin = SDL_CreateWindow("bg palette", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 16*20, 16*20, 0);
    objPaletteWin = SDL_CreateWindow("obj palette", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 16*20, 16*20, 0);
    tileMapWin = SDL_CreateWindow("tile map", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 256, 512, 0);
    #endif

    onExit = freeAll;
}

void loop(){
    emulateGba(&gba);

    #ifndef EMSCRIPTEN
    drawPaletteRam(bgPaletteWin, gba.ppu.PALETTE_RAM);
    drawPaletteRam(objPaletteWin, gba.ppu.PALETTE_RAM + 512);
    drawTileMap(tileMapWin, &gba.ppu);

    SDL_UpdateWindowSurface(bgPaletteWin);
    SDL_UpdateWindowSurface(objPaletteWin);
    SDL_UpdateWindowSurface(tileMapWin);
    #endif
}
