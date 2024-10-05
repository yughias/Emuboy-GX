#include "SDL_MAINLOOP.h"
#include "gba.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    char* exe_path = SDL_GetBasePath();
    char data_path[FILENAME_MAX];
    char logo_path[FILENAME_MAX];
    char bios_path[FILENAME_MAX];

    strncpy(data_path, exe_path, FILENAME_MAX - 1);
    strncat(data_path, "data/", FILENAME_MAX - 1);
    strncpy(logo_path, data_path, FILENAME_MAX - 1);
    strncpy(bios_path, data_path, FILENAME_MAX - 1);

    strncat(logo_path, "logo.bmp", FILENAME_MAX - 1);

    setWindowIcon(logo_path);
    frameRate(REFRESH_RATE);
    #ifndef EMSCRIPTEN
    strncat(bios_path, "gba_bios.bin", FILENAME_MAX - 1);
    #else
    strncat(bios_path, "vba_bios.bin", FILENAME_MAX - 1);
    #endif

    initGba(&gba, bios_path, getArgv(1));

    noRender();

    init_keypad();

    onExit = freeAll;
}

void loop(){    
    check_controller_connection();

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