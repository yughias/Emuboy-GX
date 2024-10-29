#include "frontend.h"
#include "gba_recorder.h"
#include "bmp_writer.h"
#include "gba_serializer.h"
#include "cheat_engine.h"

#include <stdio.h>
#include <stdlib.h>

#include "SDL_MAINLOOP.h"

static u16 convert_bgr555_to_rgb555_pixel(u16 pix){
    u16 out = 0;
    u8 r = pix & 0x1F;
    u8 g = (pix >> 5) & 0x1F;
    u8 b = (pix >> 10) & 0x1F;
    out = b | (g << 5) | (r << 10);
    return out;
}

static void* convert_bgr555_to_rgb555_array(u16* pixels, int length){
    u16* tmp_pix = malloc(sizeof(u16)*length);
    for(int i = 0; i < length; i++){
        tmp_pix[i] = convert_bgr555_to_rgb555_pixel(pixels[i]);
    }
    return tmp_pix;
}

void frontend_writeSavToFile(gba_t* gba, const char* baseFilename){
    if(gba->gamepak.type != GAMEPAK_ROM_ONLY && gba->gamepak.type != NO_GAMEPAK){
        char savFilename[FILENAME_MAX];
        changeFilenameExtension(savFilename, baseFilename, ".sav");
        FILE* fptr = fopen(savFilename, "wb");
        if(fptr){
            fwrite(gba->gamepak.savMemory, 1, gba->gamepak.savMemorySize, fptr);
            fclose(fptr);
        }
    }
}

void frontend_triggerGbaAudioRecorder(SDL_AudioDeviceID audioDev, SDL_AudioSpec audioSpec, const char* baseFilename){
    char wavFilename[FILENAME_MAX];
    changeFilenameExtension(wavFilename, baseFilename, ".wav");
    
    SDL_PauseAudioDevice(audioDev, 1);
    SDL_CloseAudioDevice(audioDev);
    
    isRecordingAudio ? stopGbaRecorder(wavFilename) : startGbaRecorder();
    audioSpec.callback = isRecordingAudio ? recordAudioCallback : audioCallback;
    audioDev = SDL_OpenAudioDevice(NULL, 0, &audioSpec, &audioSpec, 0);

    SDL_PauseAudioDevice(audioDev, 0);
}

void frontend_writeScreenShotToFile(void* pixels, int width, int height, const char* baseFilename){
    size_t size;
    void* tmp_pix = convert_bgr555_to_rgb555_array(pixels, width*height);
    void* bmp_data = bmp_write(tmp_pix, width, height, 16, &size);
    char bmpFilename[FILENAME_MAX];
    changeFilenameExtension(bmpFilename, baseFilename, ".bmp");
    FILE* fptr = fopen(bmpFilename, "wb");
    if(!fptr)
        return;
    fwrite(bmp_data, size, 1, fptr);
    fclose(fptr);
    free(bmp_data);
    free(tmp_pix);
}

void frontend_startCheatEngineSearch(gba_t* gba){
    u32 value;
    printf("(start scan for value?) ");
    scanf("%d", &value);
    cheatEngineNewSearch(gba, value);
    cheatEnginePrintAddresses();
}

void frontend_continueCheatEngineSearch(gba_t* gba){
    u32 value;
    printf("(continue scan for value?) ");
    scanf("%d", &value);
    cheatEngineContinueSearch(gba, value);
    cheatEnginePrintAddresses();
}

void frontend_writeToFoundAddressesCheatEngine(gba_t* gba){
    u32 value;
    printf("(write value?) ");
    scanf("%d", &value);
    cheatEngineWriteToFoundAddresses(gba, value);
}

void frontend_writeToSingleAddressCheatEngine(gba_t* gba){
    u32 address, value;
    u32 type;
    printf("(type?) ");
    scanf("%d", &type);
    printf("(write value?) ");
    scanf("%d", &value);
    printf("(address?) ");
    scanf("%X", &address);
    cheatEngineWriteToAddress(gba, address, value, type);
}

void frontend_writeSaveStateToFile(gba_t* gba, const char* baseFilename){
    size_t bmp_size;
    void* tmp_pix = convert_bgr555_to_rgb555_array(pixels, width*height);
    void* bmp_data = bmp_write(tmp_pix, width, height, 16, &bmp_size);
    char savestateFilename[FILENAME_MAX];
    changeFilenameExtension(savestateFilename, baseFilename, ".state.bmp");
    FILE* fptr = fopen(savestateFilename, "wb");
    if(!fptr)
        return;
    fwrite(bmp_data, bmp_size, 1, fptr);
    free(tmp_pix);
    free(bmp_data);
    vector_t v;
    vector_init(&v, 1 << 18);
    serializeGba(&v, gba);
    fwrite(v.buffer, v.size, 1, fptr);
    vector_free(&v);
    fclose(fptr);
}

void frontend_readSaveStateFromFile(gba_t* gba, const char* baseFilename){
    char savestateFilename[FILENAME_MAX];
    int bmp_size;
    int savestate_size;
    void* savestate_data;
    changeFilenameExtension(savestateFilename, baseFilename, ".state.bmp");
    FILE* fptr = fopen(savestateFilename, "rb");
    if(!fptr)
        return;
    fseek(fptr, 0x02, SEEK_SET);
    fread(&bmp_size, 4, 1, fptr);
    fseek(fptr, 0, SEEK_END);
    savestate_size = ftell(fptr) - bmp_size;
    fseek(fptr, bmp_size, SEEK_SET);
    savestate_data = malloc(savestate_size);
    fread(savestate_data, savestate_size, 1, fptr);
    fclose(fptr);
    deserializeGba(savestate_data, gba);
    free(savestate_data);
}