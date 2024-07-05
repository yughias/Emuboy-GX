#include "apu.h"
#include "gba.h"

#define IS_SOUND_DMA(x) (((x >> 28) & 0b11) == 0b11)

void resetFifo(fifo_t* fifo);
u8 popFifo(fifo_t* fifo);
void refillFifo(gba_t* gba, u32 fifo_addr);

void updateChannelMixing(apu_t* apu){
    for(int i = 0; i < 2; i++){
        apu->timer_idx[i] = (apu->SOUNDCNT_H & (1 << (10 + i*4))) & 1 ;
        if(apu->SOUNDCNT_H & (1 << (11 + i*4)))
            resetFifo(&apu->fifo[i]);
    }

    apu->SOUNDCNT_H &= ~( (1 << 11) | (1 << 15) );
}

void apuCheckTimer(gba_t* gba, u8 tmr_idx){
    apu_t* apu = &gba->apu;
    for(int i = 0; i < 2; i++){
        if(apu->timer_idx[i] == tmr_idx){
            fifo_t* fifo = &apu->fifo[i];
            if(fifo->size <= APU_FIFO_REQUEST)
                refillFifo(gba, BASE_FIFO_ADDR + i*4);
            apu->dma_sample[i] = popFifo(fifo);
        }
    }
}

void pushIntoFifo(fifo_t* fifo, u8 byte){
    if(fifo->size == APU_FIFO_LENGTH)
        return;

    fifo->size += 1;
    fifo->data[fifo->w_idx] = byte;
    fifo->w_idx = (fifo->w_idx + 1) % APU_FIFO_LENGTH;
}

void resetFifo(fifo_t* fifo){
    fifo->size = 0;
    fifo->r_idx = 0;
    fifo->w_idx = 0;
}

u8 popFifo(fifo_t* fifo){
    if(!fifo->size)
        return 0;
    u8 out = fifo->data[fifo->r_idx];
    fifo->size -= 1;
    fifo->r_idx = (fifo->r_idx + 1) % APU_FIFO_LENGTH;
    return out;
}

void refillFifo(gba_t* gba, u32 fifo_addr){
    arm7tdmi_t* cpu = &gba->cpu;
    u32 old_cycles = cpu->cycles;

    for(int i = 1; i <= 2; i++){
        if(IS_SOUND_DMA(gba->DMACNT[i]) && gba->DMADAD[i] == fifo_addr && gba->dma_enabled[i]){
            int step = 0;
            switch((gba->DMACNT[i] >> 17) & 0b11){
                case 0b00:
                step = 4;
                break;

                case 0b01:
                step = -4;
                break;
            }

            for(int j = 0; j < 4; j++){
                u32 word = cpu->readWord(cpu, gba->internal_dma_source[i]);
                gba->internal_dma_source[i] += step;
                cpu->writeWord(cpu, fifo_addr, word);
            }

            if((gba->DMACNT[i] >> 0x1E) & 1){
                gba->IF |= 1 << (0x8 + i);
                checkInterrupts(gba);
            }
        }
    }

    gba->cpu.cycles = old_cycles;
}

void event_pushSampleToAudioDevice(gba_t* gba, u32 arg1, u32 arg2){
    apu_t* apu = &gba->apu;
    atomic_fifo_t* buffer = &apu->sample_buffer;
    
    if(buffer->size != SAMPLE_BUFFER_SIZE){
        sample_t* sample = &buffer->data[buffer->w_idx];
        buffer->w_idx = (buffer->w_idx + 1) % SAMPLE_BUFFER_SIZE; 
        buffer->size += 1;
        sample->right = sample->left = ((i16)(i8)gba->apu.dma_sample[0] + (i16)(i8)gba->apu.dma_sample[1])*32 + gba->apu.audioSpec.silence;
    }

    scheduler_t* block = occupySchedulerBlock(gba->scheduler_pool, GBA_SCHEDULER_POOL_SIZE);
    block->remaining = gba->apu.samplePushRate;
    addEventToScheduler(&gba->scheduler_head, block);
}

void audioCallback(void* userdata, Uint8* stream, int len){
    atomic_fifo_t* fifo = userdata;
    int sample_len = len / sizeof(sample_t);

    if(fifo->size >= sample_len){
        for(int i = 0; i < sample_len; i++){
            ((sample_t*)stream)[i] = fifo->data[fifo->r_idx];
            fifo->r_idx = (fifo->r_idx + 1) % SAMPLE_BUFFER_SIZE; 
            fifo->size -= 1;
        }
    } else {
       for(int i = 0; i < sample_len; i++)
            ((sample_t*)stream)[i] = fifo->data[fifo->r_idx];
    }
}