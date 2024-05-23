#include "dma.h"
#include "gba.h"
#include "memory.h"

#include "integer.h"

void triggerDma(gba_t* gba, int i){
    gba->dma_enabled[i] = true;
    u8 dma_mode = (gba->DMACNT[i] >> 0x1C) & 0b11; 
    if(!dma_mode)
        transferDma(gba, i);
}

void transferDma(gba_t* gba, int i){
    arm7tdmi_t* cpu = &gba->cpu;
    u32 DMACNT = gba->DMACNT[i];
    u16 n = DMACNT & 0xFFFF;
    u8 da = (DMACNT >> 0x15) & 0b11;
    u8 sa = (DMACNT >> 0x17) & 0b11;
    bool transfer_size = (DMACNT >> 0x1A) & 1;
    bool repeat_mode = (DMACNT >> 0x19) & 1;
    bool irq_enable = (DMACNT >> 0x1E) & 1;
    u8 timing_mode = (DMACNT >> 0x1C) & 0b11;

    u32 source = gba->DMASAD[i];
    u32 dest = gba->DMADAD[i];

    if(!n)
        n = 0xFFFF;

    while(n){
        int step;
        if(transfer_size){
            step = 4;
            u32 word = readWord(cpu, source);
            writeWord(cpu, dest, word);
        } else {
            step = 2;
            u16 halfword = readHalfWord(cpu, source);
            writeHalfWord(cpu, dest, halfword);
        }

        switch(sa){
            case 0b00:
            case 0b11:
            source += step;
            break;

            case 0b01:
            source -= step;
            break;
        }

        switch(da){
            case 0b00:
            case 0b11:
            dest += step;
            break;

            case 0b01:
            dest -= step;
            break;
        }

        n--;
    }

    if(sa < 0b10)
        gba->DMASAD[i] = source;

    if(da < 0b10)
        gba->DMADAD[i] = dest;

    if(repeat_mode && (timing_mode == 0b01 || timing_mode == 0b10))
        gba->dma_enabled[i] = true;
    else {
        gba->dma_enabled[i] = false;
        gba->DMACNT[i] &= ~(1 << 31);
    }

    if(irq_enable){
        gba->IF |= 1 << (0x8 + i);
        checkInterrupts(gba);
    }
}

void updateHblankDma(gba_t* gba){
    if(gba->ppu.VCOUNT < SCREEN_HEIGHT)
        for(int i = 0; i < 4; i++){
            if(gba->dma_enabled[i] && (((gba->DMACNT[i] >> 0x1C) & 0b11) == 0b10)){
                transferDma(gba, i);
            }
        }
}


void updateVblankDma(gba_t* gba){
    if(gba->ppu.VCOUNT == SCREEN_HEIGHT)
        for(int i = 0; i < 4; i++)
            if(gba->dma_enabled[i] && (((gba->DMACNT[i] >> 0x1C) & 0b11) == 0b01))
                transferDma(gba, i);
}