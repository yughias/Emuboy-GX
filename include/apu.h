#ifndef __APU_H__
#define __APU_H__

#include <stdatomic.h>

#include "integer.h"

#include "SDL2/SDL.h"

#include "scheduler.h"

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

typedef struct sound_channel_t {
    bool length_enabled;
    u32 length;

    bool envelope_dir;
    u32 envelope_time;
    
    bool sample;
    u8 volume;
    u32 freq;
    bool enabled;

    scheduler_t* lengthExpired;
    scheduler_t* freqUpdate;
    scheduler_t* envUpdate;

} sound_channel_t;

typedef struct waveform_t {
    u8 selected;
    u8 idx;
} waveform_t;

typedef struct apu_t {
    u16 SOUNDBIAS;
    u16 SOUNDCNT_L;
    u16 SOUNDCNT_H;

    u16 SOUND1CNT_L;
    u16 SOUND1CNT_H;
    u16 SOUND1CNT_X;

    u16 SOUND2CNT_L;
    u16 SOUND2CNT_H;

    u16 SOUND4CNT_L;
    u16 SOUND4CNT_H;

    sound_channel_t sound_channels[4];
    waveform_t waveforms[2];
    u16 lfsr;

    fifo_t fifo[2];
    u8 timer_idx[2];
    u8 dma_sound_sample[2];
    bool dma_sound_enabled_left[2];
    bool dma_sound_enabled_right[2];
    bool dma_sound_volume[2];

    SDL_AudioDeviceID audioDev;
    SDL_AudioSpec audioSpec;
    u32 samplePushRate;
    atomic_fifo_t sample_buffer;
} apu_t;

typedef struct gba_t gba_t;

void pushIntoFifo(fifo_t* apu, u8 byte);
void apuCheckTimer(gba_t* gba, u8 tmr_idx);

void updateSOUND12CNT_Duty(gba_t* gba, u16 reg, int idx);
void updateSOUND12CNT_Freq(gba_t* gba, u16 reg, int idx);

void updateSOUND4CNT_L(gba_t* gba, u16 reg);
void updateSOUND4CNT_H(gba_t* gba, u16 reg);

void updateSoundHControl(apu_t* apu);

void event_pushSampleToAudioDevice(gba_t* gba, u32 arg1, u32 arg2);
void audioCallback(void* userdata, Uint8* stream, int len);
sample_t mixDmaSoundSample(apu_t* apu);

void event_lengthExpired(gba_t* gba, u32 idx, u32 dummy);
void event_updateEnvelope(gba_t* gba, u32 idx, u32 dummy);
void event_updateLfsr(gba_t* gba, u32 dummy1, u32 dummy2);
void event_updateWave(gba_t* gba, u32 idx, u32 dummy2);

#endif