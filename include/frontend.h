#ifndef __FRONTEND_H__
#define __FRONTEND_H__

#include <SDL2/SDL.h>
#include "gba.h"

#include <stdio.h>

extern gba_t frontend_gba;
extern SDL_AudioDeviceID frontend_audioDev;
extern bool frontend_pause;
extern int frontend_speed;
extern char frontend_filename[FILENAME_MAX];
extern char frontend_bios_path[FILENAME_MAX];

void frontend_writeSavToFile(gba_t* gba, const char* baseFilename);
void frontend_triggerGbaAudioRecorder(SDL_AudioDeviceID audioDev, SDL_AudioSpec audioSpec, const char* baseFilename);
void frontend_writeScreenShotToFile(void* pixels, int width, int height, const char* baseFilename);
void frontend_startCheatEngineSearch(gba_t* gba);
void frontend_continueCheatEngineSearch(gba_t* gba);
void frontend_writeToFoundAddressesCheatEngine(gba_t* gba);
void frontend_writeToSingleAddressCheatEngine(gba_t* gba);
void frontend_writeSaveStateToFile(gba_t* gba, const char* baseFilename);
void frontend_readSaveStateFromFile(gba_t* gba, const char* baseFilename);
void frontend_loadGame();
void frontend_increaseSpeed();
void frontend_decreaseSpeed();
void frontend_createMenu();
void frontend_free();
void frontend_changePauseState();
void frontend_reset();

#endif