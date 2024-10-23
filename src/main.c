#include "SDL_MAINLOOP.h"
#include "gba.h"
#include "gba_recorder.h"
#include "cheat_engine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

bool pause = false;
int speed = 1;
gba_t gba;

SDL_AudioSpec audioSpec;
SDL_AudioDeviceID audioDev;

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

    freeGbaRecorder();
    freeGba(&gba);
}

void setup(){
    srand(time(NULL));
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
        if(keyReleased == SDLK_F1){
            SDL_PauseAudioDevice(audioDev, 1);
            SDL_CloseAudioDevice(audioDev);
            isRecordingAudio ? stopGbaRecorder("audio.wav") : startGbaRecorder();
            audioSpec.callback = isRecordingAudio ? recordAudioCallback : audioCallback;
            audioDev = SDL_OpenAudioDevice(NULL, 0, &audioSpec, &audioSpec, 0);
            SDL_PauseAudioDevice(audioDev, 0);
        }
        if(keyReleased == SDLK_F2){
            u32 value;
            printf("(start scan for value?) ");
            scanf("%d", &value);
            cheatEngineNewSearch(&gba, value);
            cheatEnginePrintAddresses();
        }
        if(keyReleased == SDLK_F3){
            u32 value;
            printf("(continue scan for value?) ");
            scanf("%d", &value);
            cheatEngineContinueSearch(&gba, value);
            cheatEnginePrintAddresses();
        }
        if(keyReleased == SDLK_F4){
            u32 value;
            printf("(write value?) ");
            scanf("%d", &value);
            cheatEngineWriteToFoundAddresses(&gba, value);
        }
        if(keyReleased == SDLK_F5){
            u32 address, value;
            u32 type;
            printf("(type?) ");
            scanf("%d", &type);
            printf("(write value?) ");
            scanf("%d", &value);
            printf("(address?) ");
            scanf("%X", &address);
            cheatEngineWriteToAddress(&gba, address, value, type);
        }
        if(keystate[SDL_SCANCODE_LCTRL]){
            if(keyReleased == SDLK_p)
                pause ^= 1;
        }

        gba.apu.samplePushRate = CYCLES_PER_FRAME * REFRESH_RATE * speed / gba.apu.audioSpec.freq;
        gba.ppu.frameSkip = speed >> 1;
    }

    for(int i = 0; i < speed && !pause; i++)
        emulateGba(&gba);
}