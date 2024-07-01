#include "dma.h"
#include "gba.h"

#include "integer.h"

void triggerDma(gba_t* gba, int i){
    gba->dma_enabled[i] = true;
    gba->internal_dma_source[i] = gba->DMASAD[i];
    gba->internal_dma_dest[i] = gba->DMADAD[i];
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

    if(!n)
        n = 0xFFFF;

    // this cause bobbing on some games
    //cpu->cycles += 2*I_CYCLES;
    //cpu->cycles += 2*n*S_CYCLES;

    while(n){
        int step;
        if(transfer_size){
            step = 4;
            u32 word = cpu->readWord(cpu, gba->internal_dma_source[i]);
            cpu->writeWord(cpu, gba->internal_dma_dest[i], word);
        } else {
            step = 2;
            u16 halfword = cpu->readHalfWord(cpu, gba->internal_dma_source[i]);
            cpu->writeHalfWord(cpu, gba->internal_dma_dest[i], halfword);
        }

        switch(sa){
            case 0b00:
            case 0b11:
            gba->internal_dma_source[i] += step;
            break;

            case 0b01:
            gba->internal_dma_source[i] -= step;
            break;
        }

        switch(da){
            case 0b00:
            case 0b11:
            gba->internal_dma_dest[i] += step;
            break;

            case 0b01:
            gba->internal_dma_dest[i] -= step;
            break;
        }

        n--;
    }

    if(da == 0b11)
        gba->internal_dma_dest[i] = gba->DMADAD[i];

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