#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include "arm7tdmi/arm7tdmi.h"
#include "memory.h"
#include "ppu.h"
#include "keypad.h"
#include "dma.h"
#include "timer.h"
#include "gamepak.h"
#include "apu.h"
#include "scheduler.h"

// 1 PPU
// 4 AUDIO
// 1 push sample to audio device 
#define GBA_SCHEDULER_POOL_SIZE 6

typedef struct gba_t {
    arm7tdmi_t cpu;
    ppu_t ppu;
    apu_t apu;

    // GBA RAM
    u8 WRAM_BOARD[WRAM_BOARD_SIZE];
    u8 WRAM_CHIP[WRAM_CHIP_SIZE];
    
    // BIOS
    u8* BIOS;
    
    gamepak_t gamepak;

    timer_t timers[4];

    // DMA DATA
    bool dma_enabled[4];
    u32 internal_dma_source[4];
    u32 DMASAD[4];
    u32 DMADAD[4];
    u32 DMACNT[4];

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