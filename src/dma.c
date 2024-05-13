#include "dma.h"
#include "memory.h"
#include "hardware.h"

#include "integer.h"

bool dma_enabled[4];

void triggerDma(int i){
    dma_enabled[i] = true;
    u8 dma_mode = (DMACNT[i] >> 0x1C) & 0b11; 
    if(!dma_mode)
        transferDma(i);
}

void transferDma(int i){
    u16 n = DMACNT[i] & 0xFFFF;
    u8 da = (DMACNT[i] >> 0x15) & 0b11;
    u8 sa = (DMACNT[i] >> 0x17) & 0b11;
    bool transfer_size = (DMACNT[i] >> 0x1A) & 1;
    bool repeat_mode = (DMACNT[i] >> 0x19) & 1;
    bool irq_enable = (DMACNT[i] >> 0x1E) & 1;
    u8 timing_mode = (DMACNT[i] >> 0x1C) & 0b11;

    u32 source = DMASAD[i];
    u32 dest = DMADAD[i];

    if(!n)
        n = 0xFFFF;

    while(n){
        int step;
        if(transfer_size){
            step = 4;
            u32 word = readWord(&cpu, source);
            writeWord(&cpu, dest, word);
        } else {
            step = 2;
            u16 halfword = readHalfWord(&cpu, source);
            writeHalfWord(&cpu, dest, halfword);
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
        DMASAD[i] = source;

    if(da < 0b10)
        DMADAD[i] = dest;

    if(repeat_mode && (timing_mode == 0b01 || timing_mode == 0b10))
        dma_enabled[i] = true;
    else {
        dma_enabled[i] = false;
        DMACNT[i] &= ~(1 << 31);
    }

    if(irq_enable)
        IF |= 1 << (0x8 + i);
}

void updateHblankDma(){
    if(VCOUNT < SCREEN_HEIGHT)
        for(int i = 0; i < 4; i++){
            if(dma_enabled[i] && (((DMACNT[i] >> 0x1C) & 0b11) == 0b10)){
                transferDma(i);
            }
        }
}


void updateVblankDma(){
    if(VCOUNT == SCREEN_HEIGHT)
        for(int i = 0; i < 4; i++)
            if(dma_enabled[i] && (((DMACNT[i] >> 0x1C) & 0b11) == 0b01))
                transferDma(i);
}