#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include "arm7tdmi/arm7tdmi.h"
#include "memory.h"
#include "ppu.h"
#include "keypad.h"
#include "dma.h"
#include "timer.h"

typedef struct gba_t {
    arm7tdmi_t cpu;

    u8 WRAM_BOARD[1 << 18];
    u8 WRAM_CHIP[1 << 15];
    
    u8* BIOS;
    u8* ROM;
    size_t ROM_SIZE;

    u8 SRAM[1 << 16];

    timer_t timers[4];

    bool dma_enabled[4];
    u32 DMASAD[4];
    u32 DMADAD[4];
    u32 DMACNT[4];

    u16 IE;
    u16 IF;
    u16 IME;
    bool HALTCNT;

    u16 KEYINPUT;
    u16 KEYCNT;

    u16 RCNT;
    u8 POSTFLG;
    u16 SOUNDBIAS;
u16 WAITCNT;
} gba_t;

void checkInterrupts(gba_t* gba);
void emulateGba(gba_t* gba);
void initGba(gba_t* gba);

#endif