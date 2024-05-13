#include "SDL_MAINLOOP.h"
#include "hardware.h"

#include <stdio.h>
#include <stdlib.h>

SDL_Window* bgPaletteWin;
SDL_Window* objPaletteWin;
SDL_Window* tileMapWin;

void freeAll(){
    free(BIOS);
    free(ROM);
}

void setup(){
    size(SCREEN_WIDTH, SCREEN_HEIGHT);
    setScaleMode(NEAREST);
    frameRate(REFRESH_RATE);
    loadBios("gba_bios.bin");
    loadRom(getArgv(1));
    init_keypad();

    noRender();

    bgPaletteWin = SDL_CreateWindow("bg palette", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 16*20, 16*20, 0);
    objPaletteWin = SDL_CreateWindow("obj palette", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 16*20, 16*20, 0);
    tileMapWin = SDL_CreateWindow("tile map", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 256, 512, 0);

    onExit = freeAll;
}

void loop(){
    emulateHardware();

    drawPaletteRam(bgPaletteWin, PALETTE_RAM);
    drawPaletteRam(objPaletteWin, PALETTE_RAM + 512);
    drawTileMap(tileMapWin);

    SDL_UpdateWindowSurface(bgPaletteWin);
    SDL_UpdateWindowSurface(objPaletteWin);
    SDL_UpdateWindowSurface(tileMapWin);
}
