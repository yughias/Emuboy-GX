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
    frameRate(REFRESH_RATE*4);
    initGba(&gba);
    #ifndef EMSCRIPTEN
    loadBios("data/gba_bios.bin", &gba.BIOS);
    #else
    loadBios("data/vba_bios.bin", &gba.BIOS);
    #endif
    gba.ROM_SIZE = loadRom(getArgv(1),&gba.ROM);
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
    printf("%f\n", 1000.0f/ deltaTime);

    emulateGba(&gba);

    #ifndef EMSCRIPTEN
    drawPaletteRam(bgPaletteWin, PALETTE_RAM);
    drawPaletteRam(objPaletteWin, PALETTE_RAM + 512);
    drawTileMap(tileMapWin);

    SDL_UpdateWindowSurface(bgPaletteWin);
    SDL_UpdateWindowSurface(objPaletteWin);
    SDL_UpdateWindowSurface(tileMapWin);
    #endif
}
