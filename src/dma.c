#include "dma.h"
#include "gba.h"

#include "integer.h"

void triggerDma(gba_t* gba, int i){
    dma_t* dma = &gba->dmas[i];
    dma->internal_source = dma->DMASAD;
    dma->internal_dest = dma->DMADAD;
    u8 dma_mode = (dma->DMACNT >> 0x1C) & 0b11; 
    if(!dma_mode)
        transferDma(gba, i);
}

void transferDma(gba_t* gba, int i){
    arm7tdmi_t* cpu = &gba->cpu;
    dma_t* dma = &gba->dmas[i];
    u32 DMACNT = dma->DMACNT;
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
            u32 word = cpu->readWord(cpu, dma->internal_source);
            cpu->writeWord(cpu, dma->internal_dest, word);
        } else {
            step = 2;
            u16 halfword = cpu->readHalfWord(cpu, dma->internal_source);
            cpu->writeHalfWord(cpu, dma->internal_dest, halfword);
        }

        switch(sa){
            case 0b00:
            case 0b11:
            dma->internal_source += step;
            break;

            case 0b01:
            dma->internal_source -= step;
            break;
        }

        switch(da){
            case 0b00:
            case 0b11:
            dma->internal_dest += step;
            break;

            case 0b01:
            dma->internal_dest -= step;
            break;
        }

        n--;
    }

    if(da == 0b11)
        dma->internal_dest = dma->DMADAD;

    if(!repeat_mode || !timing_mode)
        dma->DMACNT &= ~(1 << 31);

    if(irq_enable){
        gba->IF |= 1 << (0x8 + i);
        checkInterrupts(gba);
    }
}

void updateHblankDma(gba_t* gba){
    if(gba->ppu.VCOUNT < SCREEN_HEIGHT)
        for(int i = 0; i < 4; i++){
            dma_t* dma = &gba->dmas[i];
            bool enabled = dma->DMACNT >> 31;
            if(enabled && (((dma->DMACNT >> 0x1C) & 0b11) == 0b10)){
                transferDma(gba, i);
            }
        }
}


void updateVblankDma(gba_t* gba){
    if(gba->ppu.VCOUNT == SCREEN_HEIGHT)
        for(int i = 0; i < 4; i++){
            dma_t* dma = &gba->dmas[i];
            bool enabled = dma->DMACNT >> 31;
            if(enabled && (((dma->DMACNT >> 0x1C) & 0b11) == 0b01))
                transferDma(gba, i);
        }
}