#include "SDL_MAINLOOP.h"
#include "gba.h"

#include <stdio.h>
#include <stdlib.h>

int speed = 1;
gba_t gba;

void freeAll(){
    if(gba.gamepak.type != GAMEPAK_ROM_ONLY && gba.gamepak.type != NO_GAMEPAK){
        char savFilename[FILENAME_MAX];
        getSavFilename(savFilename, getArgv(1));
        FILE* fptr = fopen(savFilename, "wb");
        if(fptr){
            fwrite(gba.gamepak.savMemory, 1, gba.gamepak.savMemorySize, fptr);
            fclose(fptr);
        }
    }

    freeGba(&gba);
}

void setup(){
    size(SCREEN_WIDTH, SCREEN_HEIGHT);
    setScaleMode(NEAREST);
    setTitle(u8"エミュボーイ　GX");
    setWindowIcon("data/logo.bmp");
    frameRate(REFRESH_RATE);
    #ifndef EMSCRIPTEN
    initGba(&gba, "data/gba_bios.bin", getArgv(1));
    #else
    initGba(&gba, "data/vba_bios.bin", getArgv(1));
    #endif

    noRender();

    init_keypad();

    onExit = freeAll;
}

void loop(){
    if(isKeyReleased){
        if(keyReleased == '-')
            speed = speed == 1 ? 1 : speed >> 1;
        if(keyReleased == '=')
            speed <<= 1;
        gba.apu.samplePushRate = CYCLES_PER_FRAME * REFRESH_RATE * speed / gba.apu.audioSpec.freq;
        gba.ppu.frameSkip = speed >> 1;
    }

    for(int i = 0; i < speed; i++)
        emulateGba(&gba);
}
