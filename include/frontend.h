#ifndef __FRONTEND_H__
#define __FRONTEND_H__

#include <SDL2/SDL.h>
#include "gba.h"

void frontend_writeSavToFile(gba_t* gba, const char* baseFilename);
void frontend_triggerGbaAudioRecorder(SDL_AudioDeviceID audioDev, SDL_AudioSpec audioSpec, const char* baseFilename);
void frontend_writeScreenShotToFile(void* pixels, int width, int height, const char* baseFilename);
void frontend_startCheatEngineSearch(gba_t* gba);
void frontend_continueCheatEngineSearch(gba_t* gba);
void frontend_writeToFoundAddressesCheatEngine(gba_t* gba);
void frontend_writeToSingleAddressCheatEngine(gba_t* gba);
void frontend_writeSaveStateToFile(gba_t* gba, const char* baseFilename);
void frontend_readSaveStateFromFile(gba_t* gba, const char* baseFilename);

#endif