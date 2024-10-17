#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include "arm7tdmi/arm7tdmi.h"
#include "memory.h"
#include "ppu.h"
#include "keypad.h"
#include "dma.h"
#include "timer.h"
#include "gamepak.h"
#include "prefetcher.h"
#include "apu.h"
#include "scheduler.h"

// 1 PPU
// 4 TIMERS
// 1 SWEEP FOR CHANNEL 1
// 2*3 TONE CHANNEL: LENGTH + UPDATE TONE + ENVELOPE
// 2 WAVE CHANNEL: LENGTH + UPDATE WAVE
// 3 NOISE CHANNEL: LENGTH + UPDATE LFSR + ENVELOPE
// 1 push sample to audio device 
#define GBA_SCHEDULER_POOL_SIZE 18

typedef struct gba_t {
    arm7tdmi_t cpu;
    ppu_t ppu;
    apu_t apu;
    prefetcher_t prefetcher;

    // GBA RAM
    u8 EWRAM[EWRAM_SIZE];
    u8 IWRAM[IWRAM_SIZE];
    
    // BIOS
    bios_t bios;
    
    gamepak_t gamepak;

    gba_tmr_t timers[4];

    // DMA
    DMA_IDX active_dma;
    dma_t dmas[4];

    // INTERRUPT REGS
    u16 IE;
    u16 IF;
    u16 IME;
    bool HALTCNT;

    // INPUT REGS
    u16 KEYINPUT;
    u16 KEYCNT;

    // MISC REGS
    u16 RCNT;
    u8 POSTFLG;
    u16 WAITCNT;    

    // SCHEDULER
    scheduler_t scheduler_pool[GBA_SCHEDULER_POOL_SIZE];
    scheduler_t* scheduler_head;

    // counters
    u64 frame_clock;
    u32 clock_before_scheduling;
} gba_t;

void checkInterrupts(gba_t* gba);
void emulateGba(gba_t* gba);
void initGba(gba_t* gba, const char* biosFilename, const char* romFilename);
void freeGba(gba_t* gba);

#endif