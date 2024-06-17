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
    ppu_t ppu;

    // GBA RAM
    u8 WRAM_BOARD[WRAM_BOARD_SIZE];
    u8 WRAM_CHIP[WRAM_CHIP_SIZE];
    
    // BIOS + ROM
    u8* BIOS;
    u8* ROM;
    size_t ROM_SIZE;

    // EXTERNAL MEMORY RAM
    u8 SRAM[SRAM_SIZE];

    timer_t timers[4];

    // DMA DATA
    bool dma_enabled[4];
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
    u16 SOUNDBIAS;
    u16 WAITCNT;
} gba_t;

void checkInterrupts(gba_t* gba);
void emulateGba(gba_t* gba);
void initGba(gba_t* gba, const char* biosFilename, const char* romFilename);

#endif