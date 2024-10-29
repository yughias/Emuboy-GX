#include "SDL_MAINLOOP.h"
#include "gba.h"
#include "gba_recorder.h"
#include "frontend.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool pause = false;
int speed = 1;
gba_t gba;

SDL_AudioSpec audioSpec;
SDL_AudioDeviceID audioDev;

void freeAll(){
    frontend_writeSavToFile(&gba, getArgv(1));

    freeGbaRecorder();
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

    audioSpec.freq = 44100;
    audioSpec.channels = 2;
    audioSpec.format = AUDIO_S16;
    audioSpec.samples = SAMPLE_PER_CALL;
    audioSpec.callback = audioCallback;
    audioSpec.userdata = &gba.apu.sample_buffer;
    audioDev = SDL_OpenAudioDevice(NULL, 0, &audioSpec, &audioSpec, 0);

    initGba(&gba, bios_path, getArgv(1), audioSpec);

    noRender();

    init_keypad();

    onExit = freeAll;

    SDL_PauseAudioDevice(audioDev, 0);
}

void loop(){    
    check_controller_connection();

    if(isKeyReleased){
        if(keyReleased == '-')
            speed = speed == 1 ? 1 : speed >> 1;
        if(keyReleased == '=')
            speed <<= 1;
        if(keyReleased == SDLK_F1)
            frontend_triggerGbaAudioRecorder(audioDev, gba.apu.audioSpec, getArgv(1));
        if(keyReleased == SDLK_F2)
            frontend_startCheatEngineSearch(&gba);
        if(keyReleased == SDLK_F3)
            frontend_continueCheatEngineSearch(&gba);
        if(keyReleased == SDLK_F4)
            frontend_writeToFoundAddressesCheatEngine(&gba);
        if(keyReleased == SDLK_F5)
            frontend_writeToSingleAddressCheatEngine(&gba);
        if(keyReleased == SDLK_F12)
            frontend_writeScreenShotToFile(pixels, width, height, getArgv(1));

        if(keystate[SDL_SCANCODE_LCTRL]){
            if(keyReleased == SDLK_p)
                pause ^= 1;
            if(keyReleased == SDLK_r)
                resetGba(&gba);
            if(keyReleased == SDLK_s)
                frontend_writeSaveStateToFile(&gba, getArgv(1));
            if(keyReleased == SDLK_l)
                frontend_readSaveStateFromFile(&gba, getArgv(1));
        }

        gba.apu.samplePushRate = CYCLES_PER_FRAME * REFRESH_RATE * speed / gba.apu.audioSpec.freq;
        gba.ppu.frameSkip = speed >> 1;
    }

    for(int i = 0; i < speed && !pause; i++)
        emulateGba(&gba);
}