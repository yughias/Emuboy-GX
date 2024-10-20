#ifndef __GBA_RECORDER_H__
#define __GBA_RECORDER_H__

#include <SDL2/SDL.h>

#include "integer.h"

extern bool isRecordingAudio;

void recordAudioCallback(void* userdata, Uint8* stream, int len);
void freeGbaRecorder();
void startGbaRecorder();
void stopGbaRecorder(const char* filename);

#endif