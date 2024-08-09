#include "apu.h"
#include "gba.h"

#include <stdio.h>

#define IS_SOUND_DMA(x) (((x >> 28) & 0b11) == 0b11)
#define LENGTH_UNIT (1 << 16)
#define NOISE_FREQ_UNIT (1 << 5)
#define ENV_UNIT (1 << 18)
#define WAVE_FREQ_UNIT (1 << 4)
#define CALCULATE_LENGTH_TIME(reg) (64 - (reg)) * LENGTH_UNIT

bool waveforms[4][8] = {
    { 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 1, 1, 1 },
    { 0, 1, 1, 1, 1, 1, 1, 0 }
};

void resetFifo(fifo_t* fifo);
u8 popFifo(fifo_t* fifo);
void refillFifo(gba_t* gba, u32 fifo_addr);

void restartEnvelopeEvent(gba_t* gba, sound_channel_t* ch, int idx){
    if(ch->envelope_time && ((ch->envelope_dir && ch->volume != 15) || (!ch->envelope_dir && ch->volume != 0))){
        ch->envUpdate = occupySchedulerBlock(gba->scheduler_pool, GBA_SCHEDULER_POOL_SIZE);
        ch->envUpdate->arg1 = idx;
        ch->envUpdate->event = event_updateEnvelope;
        ch->envUpdate->remaining = ch->envelope_time;
        addEventToScheduler(&gba->scheduler_head, ch->envUpdate);
    } else {
        ch->envUpdate = NULL;
    }
}

void triggerChannel(gba_t* gba, sound_channel_t* ch, u8 idx, eventFunc lengthFunc, eventFunc envFunc, eventFunc freqFunc){
    scheduler_t** scheduler = &gba->scheduler_head;

    if(ch->lengthExpired)
        removeEventToScheduler(scheduler, ch->lengthExpired);

    if(ch->envUpdate)
        removeEventToScheduler(scheduler, ch->envUpdate);

    if(ch->freqUpdate)
        removeEventToScheduler(scheduler, ch->freqUpdate);

    ch->freqUpdate = occupySchedulerBlock(gba->scheduler_pool, GBA_SCHEDULER_POOL_SIZE);
    ch->freqUpdate->arg1 = idx;
    ch->freqUpdate->event = freqFunc;
    ch->freqUpdate->remaining = ch->freq;
    addEventToScheduler(scheduler, ch->freqUpdate);

    if(ch->length_enabled){
        ch->lengthExpired = occupySchedulerBlock(gba->scheduler_pool, GBA_SCHEDULER_POOL_SIZE);
        ch->lengthExpired->arg1 = idx;
        ch->lengthExpired->event = lengthFunc;
        ch->lengthExpired->remaining = ch->length;
        addEventToScheduler(scheduler, ch->lengthExpired);
    } else {
        ch->lengthExpired = NULL;
    }

    restartEnvelopeEvent(gba, ch, idx);
}

void restartFreqEvent(gba_t* gba, sound_channel_t* sound_channel, int idx, eventFunc freqFunc){
    sound_channel->freqUpdate = occupySchedulerBlock(gba->scheduler_pool, GBA_SCHEDULER_POOL_SIZE);
    sound_channel->freqUpdate->remaining = sound_channel->freq;
    sound_channel->freqUpdate->event = freqFunc;
    sound_channel->freqUpdate->arg1 = idx;
    addEventToScheduler(&gba->scheduler_head, sound_channel->freqUpdate);
}

void updateSOUND12CNT_Duty(gba_t* gba, u16 reg, int idx){
    sound_channel_t* ch = &gba->apu.sound_channels[idx];
    waveform_t* waveform = &gba->apu.waveforms[idx];
    ch->length = CALCULATE_LENGTH_TIME(reg & 0x3F);
    waveform->selected = (reg >> 6) & 0x3;
    ch->envelope_time = ((reg >> 8) & 0b111) * ENV_UNIT;
    ch->envelope_dir = reg & (1 << 11);
    ch->volume = (reg >> 12) & 0xF;
}

void updateSOUND12CNT_Freq(gba_t* gba, u16 reg, int idx){
    sound_channel_t* ch = &gba->apu.sound_channels[idx];
    ch->freq = (2048 - (reg & 0x7FF)) * WAVE_FREQ_UNIT;
    u32 old_l = ch->length_enabled;
    ch->length_enabled = reg & (1 << 14);
    
    if(reg & (1 << 15)){
        ch->enabled = true;
        triggerChannel(gba, ch, idx, event_lengthExpired, event_updateEnvelope, event_updateWave);
    }
}

void updateSOUND4CNT_L(gba_t* gba, u16 reg){
    sound_channel_t* noise_channel = &gba->apu.sound_channels[3];
    noise_channel->length = CALCULATE_LENGTH_TIME(reg & 0x3F);
    noise_channel->envelope_time = ((reg >> 8) & 0b111) * ENV_UNIT;
    noise_channel->envelope_dir = reg & (1 << 11);
    noise_channel->volume = (reg >> 12) & 0xF;
}

void updateSOUND4CNT_H(gba_t* gba, u16 reg){
    sound_channel_t* noise_channel = &gba->apu.sound_channels[3];
    u8 r = reg & 0x7;
    u8 s = (reg >> 4) & 0xF;
    noise_channel->freq = NOISE_FREQ_UNIT << (s+1);
    
    if(!r)
        noise_channel->freq >>= 1;
    else
        noise_channel->freq *= r; 

    noise_channel->length_enabled = reg & (1 << 14);

    if(reg & (1 << 15)){
        noise_channel->enabled = true;

        if(reg & (1 << 3))
            gba->apu.lfsr = 0x40;
        else
            gba->apu.lfsr = 0x4000;

        triggerChannel(gba, noise_channel, 3, event_lengthExpired, event_updateEnvelope, event_updateLfsr);
    }
}

void updateSoundHControl(apu_t* apu){
    for(int i = 0; i < 2; i++){
        apu->timer_idx[i] = (bool)(apu->SOUNDCNT_H & (1 << (10 + i*4)));
        if(apu->SOUNDCNT_H & (1 << (11 + i*4)))
            resetFifo(&apu->fifo[i]);
        apu->dma_sound_volume[i] = apu->SOUNDCNT_H & (1 << (2 + i));
        apu->dma_sound_enabled_left[i] = apu->SOUNDCNT_H & (1 << (9 + i*4));
        apu->dma_sound_enabled_right[i] = apu->SOUNDCNT_H & (1 << (8 + i*4));
    }

    apu->SOUNDCNT_H &= ~( (1 << 11) | (1 << 15) | (0xF << 4));
}

void apuCheckTimer(gba_t* gba, u8 tmr_idx){
    apu_t* apu = &gba->apu;
    for(int i = 0; i < 2; i++){
        if(apu->timer_idx[i] == tmr_idx){
            fifo_t* fifo = &apu->fifo[i];
            if(fifo->size <= APU_FIFO_REQUEST)
                refillFifo(gba, BASE_FIFO_ADDR + i*4);
            apu->dma_sound_sample[i] = popFifo(fifo);
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
        dma_t* dma = &gba->dmas[i];
        bool enabled = dma->DMACNT >> 31;
        if(IS_SOUND_DMA(dma->DMACNT) && dma->DMADAD == fifo_addr && enabled){
            int step = 0;
            switch((dma->DMACNT >> 17) & 0b11){
                case 0b00:
                step = 4;
                break;

                case 0b01:
                step = -4;
                break;
            }

            for(int j = 0; j < 4; j++){
                u32 word = cpu->readWord(cpu, dma->internal_source, true);
                dma->internal_source += step;
                cpu->writeWord(cpu, fifo_addr, word, true);
            }

            if((dma->DMACNT >> 0x1E) & 1){
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
        *sample = mixDmaSoundSample(apu);
        
        for(int i = 0; i < 4; i++){
            u16 dac_sample = apu->sound_channels[i].sample * apu->sound_channels[i].volume * 128;
            sample->left += dac_sample;
            sample->right += dac_sample;
        }

        sample->right += apu->audioSpec.silence;
        sample->left += apu->audioSpec.silence;


        buffer->w_idx = (buffer->w_idx + 1) % SAMPLE_BUFFER_SIZE; 
        buffer->size += 1;
    }

    scheduler_t* block = occupySchedulerBlock(gba->scheduler_pool, GBA_SCHEDULER_POOL_SIZE);
    block->remaining = gba->apu.samplePushRate;
    addEventToScheduler(&gba->scheduler_head, block);
}

void audioCallback(void* userdata, Uint8* stream, int len){
    atomic_fifo_t* fifo = userdata;
    int sample_len = len / sizeof(sample_t);

    for(int i = 0; i < sample_len; i++){
        ((sample_t*)stream)[i] = fifo->data[fifo->r_idx];
        if(fifo->size >= sample_len){
            fifo->r_idx = (fifo->r_idx + 1) % SAMPLE_BUFFER_SIZE; 
            fifo->size -= 1;
        }
    }
}

sample_t mixDmaSoundSample(apu_t* apu){
    sample_t sample = {0, 0};
    for(int i = 0; i < 2; i++){
        if(apu->dma_sound_enabled_right[i])
            sample.right += (((i16)(i8)apu->dma_sound_sample[i]) * 64) >> (1 - apu->dma_sound_volume[i]);
        if(apu->dma_sound_enabled_left[i])
            sample.left += (((i16)(i8)apu->dma_sound_sample[i]) * 64) >> (1 - apu->dma_sound_volume[i]);
    }
    return sample;
}

void event_lengthExpired(gba_t* gba, u32 idx, u32 dummy){
    sound_channel_t* ch = &gba->apu.sound_channels[idx];

    ch->enabled = false;
    removeEventToScheduler(&gba->scheduler_head, ch->freqUpdate);
    ch->freqUpdate = NULL;
    ch->lengthExpired = NULL;
}

void event_updateEnvelope(gba_t* gba, u32 idx, u32 dummy){
    sound_channel_t* ch = &gba->apu.sound_channels[idx];
    ch->volume += ch->envelope_dir ? +1 : -1;
    restartEnvelopeEvent(gba, ch, idx);
}

void event_updateLfsr(gba_t* gba, u32 dummy1, u32 dummy2){
    sound_channel_t* noise_channel = &gba->apu.sound_channels[3];
    u16* lfsr = &gba->apu.lfsr;
    bool carry = *lfsr & 1;
    noise_channel->sample = carry;
    *lfsr >>= 1;

    if(carry){
        if(gba->apu.SOUND4CNT_H & (1 << 3))
            *lfsr ^= 0x60;
        else
            *lfsr ^= 0x6000;
    }

    restartFreqEvent(gba, noise_channel, 3, event_updateLfsr);
}

void event_updateWave(gba_t* gba, u32 idx, u32 dummy2){
    sound_channel_t* ch = &gba->apu.sound_channels[idx];
    waveform_t* waveform = &gba->apu.waveforms[idx];   

    ch->sample = waveforms[waveform->selected][waveform->idx];
    waveform->idx = (waveform->idx + 1) % 8; 

    restartFreqEvent(gba, ch, idx, event_updateWave);
}