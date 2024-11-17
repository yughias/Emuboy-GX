#include "frontend.h"
#include "gba_recorder.h"
#include "bmp_writer.h"
#include "gba_serializer.h"
#include "cheat_engine.h"

#include "tinyfiledialogs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "SDL_MAINLOOP.h"

SDL_AudioDeviceID frontend_audioDev;
gba_t frontend_gba;
bool frontend_pause = false;
int frontend_speed = 1;
char frontend_filename[FILENAME_MAX];
char frontend_bios_path[FILENAME_MAX];

#define SET_SPEED(x) frontend_speed = x; frontend_gba.ppu.frameSkip = x >> 1

#define SPEED_LEVELS 4
static buttonId speed_buttons[SPEED_LEVELS];

#define DEF_FRONTEND_BUTTON_FUNC(name, body) \
void button_ ## name () { body }

DEF_FRONTEND_BUTTON_FUNC(frontend_writeSaveStateToFile, frontend_writeSaveStateToFile(&frontend_gba, frontend_filename);)
DEF_FRONTEND_BUTTON_FUNC(frontend_readSaveStateFromFile, frontend_readSaveStateFromFile(&frontend_gba, frontend_filename);)
DEF_FRONTEND_BUTTON_FUNC(frontend_startCheatEngineSearch, frontend_startCheatEngineSearch(&frontend_gba); )
DEF_FRONTEND_BUTTON_FUNC(frontend_continueCheatEngineSearch, frontend_continueCheatEngineSearch(&frontend_gba); )
DEF_FRONTEND_BUTTON_FUNC(frontend_writeToFoundAddressesCheatEngine, frontend_writeToFoundAddressesCheatEngine(&frontend_gba); )
DEF_FRONTEND_BUTTON_FUNC(frontend_writeToSingleAddressCheatEngine, frontend_writeToSingleAddressCheatEngine(&frontend_gba); )

DEF_FRONTEND_BUTTON_FUNC(frontend_setSpeed1, SET_SPEED(1); )
DEF_FRONTEND_BUTTON_FUNC(frontend_setSpeed2, SET_SPEED(2); )
DEF_FRONTEND_BUTTON_FUNC(frontend_setSpeed4, SET_SPEED(4); )
DEF_FRONTEND_BUTTON_FUNC(frontend_setSpeed8, SET_SPEED(8); )

DEF_FRONTEND_BUTTON_FUNC(frontend_writeScreenShotToFile, 
    char bmpFileName[FILENAME_MAX];
    getFilenameWithDate(bmpFileName, frontend_filename);
    frontend_writeScreenShotToFile(pixels, width, height, bmpFileName);
)

DEF_FRONTEND_BUTTON_FUNC(frontend_triggerGbaAudioRecorder, 
    char wavFileName[FILENAME_MAX];
    getFilenameWithDate(wavFileName, frontend_filename);
    frontend_triggerGbaAudioRecorder(frontend_audioDev, frontend_gba.apu.audioSpec, wavFileName);
)

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
    char* input = tinyfd_inputBox("NEW CHEAT ENGINE SEARCH", "value to search?", "0");
    if(!input)
        return;
    value = atoi(input);

    cheatEngineNewSearch(gba, value);
    cheatEnginePrintAddresses();
}

void frontend_continueCheatEngineSearch(gba_t* gba){
    u32 value;
    char* input = tinyfd_inputBox("CONTINUE CHEAT ENGINE SEARCH", "value to search?", "0");
    if(!input)
        return;
    value = atoi(input);

    cheatEngineContinueSearch(gba, value);
    cheatEnginePrintAddresses();
}

void frontend_writeToFoundAddressesCheatEngine(gba_t* gba){
    u32 value;
    char* input = tinyfd_inputBox("WRITE VALUE TO ALL FOUND ADDRESSES", "value to write?", "0");
    if(!input)
        return;
    value = atoi(input);
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

void frontend_createMenu(){
    menuId fileMenu = addMenuTo(-1, L"File", false);
    menuId emulationMenu = addMenuTo(-1, L"Emulation", false);
    menuId toolsMenu = addMenuTo(-1, L"Tools", false);

    addButtonTo(fileMenu, L"Open ROM\tCtrl+O", frontend_loadGame);
    addButtonTo(fileMenu, L"Load State\tCtrl+L", button_frontend_readSaveStateFromFile);
    addButtonTo(fileMenu, L"Save State\tCtrl+S", button_frontend_writeSaveStateToFile);

    addButtonTo(emulationMenu, L"Pause\tCtrl+P", frontend_changePauseState);
    addButtonTo(emulationMenu, L"Reset\tCtrl+R", frontend_reset);
    menuId speedMenu = addMenuTo(emulationMenu, L"Speed", true);

    speed_buttons[0] = addButtonTo(speedMenu, L"1x", button_frontend_setSpeed1);
    speed_buttons[1] = addButtonTo(speedMenu, L"2x", button_frontend_setSpeed2);
    speed_buttons[2] = addButtonTo(speedMenu, L"4x", button_frontend_setSpeed4);
    speed_buttons[3] = addButtonTo(speedMenu, L"8x", button_frontend_setSpeed8);
    checkRadioButton(speed_buttons[0]);

    addButtonTo(toolsMenu, L"ScreenShot\tF12", button_frontend_writeScreenShotToFile);
    addButtonTo(toolsMenu, L"Record Audio\tF1", button_frontend_triggerGbaAudioRecorder); 

    menuId cheatEngineMenu = addMenuTo(toolsMenu, L"Cheat Engine", false);
    addButtonTo(cheatEngineMenu, L"Start New Scan\tF2", button_frontend_startCheatEngineSearch);
    addButtonTo(cheatEngineMenu, L"Continue Scan\tF3", button_frontend_continueCheatEngineSearch);
    addButtonTo(cheatEngineMenu, L"Write Value To All Results\tF4", button_frontend_writeToFoundAddressesCheatEngine);
    addButtonTo(cheatEngineMenu, L"Write Value To Address\tF5", button_frontend_writeToSingleAddressCheatEngine);
}

void frontend_changePauseState(){
    frontend_pause ^= 1;
}

void frontend_reset(){
    resetGba(&frontend_gba);
}

void frontend_setNewSpeed(int new_speed){
    SET_SPEED(new_speed);
    int idx = log(new_speed)/log(2);
    checkRadioButton(speed_buttons[idx]);
}

void frontend_increaseSpeed(){
    int new_speed = frontend_speed * 2;
    if(new_speed != 1 << SPEED_LEVELS)
        frontend_setNewSpeed(new_speed);
}

void frontend_decreaseSpeed(){
    int new_speed = frontend_speed / 2;
    if(new_speed != 0)
        frontend_setNewSpeed(new_speed);
}

void frontend_loadGame(){
    char* new_filename;
    char const* ext[2] = {"*.gba", "*.zip"};

    new_filename = tinyfd_openFileDialog(
        "Select ROM",
	    NULL,
	    2, 
	    ext,
	    NULL,
	    0
    );

    if(!new_filename)
        return;

    frontend_free();
    strcpy(frontend_filename, new_filename);
    SDL_AudioSpec audioSpec = frontend_gba.apu.audioSpec;
    initGba(&frontend_gba, frontend_bios_path, frontend_filename, audioSpec);
}

void frontend_free(){
    frontend_writeSavToFile(&frontend_gba, frontend_filename);

    freeGbaRecorder();
    freeGba(&frontend_gba);
}