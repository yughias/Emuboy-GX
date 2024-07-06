#ifndef __APU_H__
#define __APU_H__

#include <stdatomic.h>

#include "integer.h"

#include "SDL2/SDL.h"

#define APU_FIFO_LENGTH 32
#define APU_FIFO_REQUEST 16
#define BASE_FIFO_ADDR 0x040000A0

#define SAMPLE_PER_CALL 512
#define SAMPLE_BUFFER_SIZE 4096

typedef struct sample_t {
    u16 left;
    u16 right;
} sample_t;

typedef struct atomic_fifo_t {
    sample_t data[SAMPLE_BUFFER_SIZE];
    atomic_int r_idx;
    atomic_int w_idx;
    atomic_int size;
} atomic_fifo_t;

typedef struct fifo_t {
    u8 data[APU_FIFO_LENGTH];
    u8 size;
    u8 r_idx;
    u8 w_idx;
} fifo_t;


typedef struct apu_t {
    u16 SOUNDBIAS;
    u16 SOUNDCNT_L;
    u16 SOUNDCNT_H;

    fifo_t fifo[2];
    u8 timer_idx[2];
    u8 dma_sample[2];

    SDL_AudioDeviceID audioDev;
    SDL_AudioSpec audioSpec;
    u32 samplePushRate;
    atomic_fifo_t sample_buffer;
} apu_t;

typedef struct gba_t gba_t;

void pushIntoFifo(fifo_t* apu, u8 byte);
void apuCheckTimer(gba_t* gba, u8 tmr_idx);
void updateChannelMixing(apu_t* apu);

void event_pushSampleToAudioDevice(gba_t* gba, u32 arg1, u32 arg2);
void audioCallback(void* userdata, Uint8* stream, int len);

#endif