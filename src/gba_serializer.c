#include "gba_serializer.h"
#include "eeprom.h"
#include "flash.h"

#include <stdio.h>
#include <string.h>

#define GET_SCHEDULER_IDX(x) x ? x - gba->scheduler_pool : -1
#define SERIALIZE_VAR(x) vector_add(v, &x, sizeof(x))
#define SERIALIZE_ARRAY(x) vector_add(v, x, sizeof(x))

#define GET_SCHEDULER_PTR(x) x == -1 ? NULL : gba->scheduler_pool + x
#define DESERIALIZE_VAR(x) memcpy(&x, buf, sizeof(x)); buf += sizeof(x)
#define DESERIALIZE_ARRAY(x) memcpy(x, buf, sizeof(x)); buf += sizeof(x)

typedef enum EVENT_ENUM {
    EVENT_NULL = 0,
    EVENT_LENGTH_EXPIRED,
    EVENT_PUSH_SAMPLE_TO_AUDIO_DEVICE,
    EVENT_START_HBLANK,
    EVENT_START_SCANLINE,
    EVENT_TIMER_OVERFLOW,
    EVENT_UPDATE_ENVELOPE,
    EVENT_UPDATE_LFSR,
    EVENT_UPDATE_SWEEP,
    EVENT_UPDATE_TONE,
    EVENT_UPDATE_WAVE,
}  EVENT_ENUM;

typedef struct event_serializer_t {
    EVENT_ENUM type;
    eventFunc func_ptr;
} event_serializer_t;

event_serializer_t event_associations[] = {
    { EVENT_NULL,                        NULL                          },
    { EVENT_LENGTH_EXPIRED,              event_lengthExpired           },
    { EVENT_PUSH_SAMPLE_TO_AUDIO_DEVICE, event_pushSampleToAudioDevice },
    { EVENT_START_HBLANK,                event_startHBlank             },
    { EVENT_START_SCANLINE,              event_startScanline           },
    { EVENT_TIMER_OVERFLOW,              event_timerOverflow           },
    { EVENT_UPDATE_ENVELOPE,             event_updateEnvelope          },
    { EVENT_UPDATE_LFSR,                 event_updateLfsr              },
    { EVENT_UPDATE_SWEEP,                event_updateSweep             },
    { EVENT_UPDATE_TONE,                 event_updateTone              },
    { EVENT_UPDATE_WAVE,                 event_updateWave              }
};

EVENT_ENUM getEventEnum(eventFunc ptr){
    for(int i = 0; i < sizeof(event_associations)/sizeof(event_serializer_t); i++){
        event_serializer_t* es = &event_associations[i];
        if(es->func_ptr == ptr)
            return es->type;
    }

    printf("could not find event enum!\n");
    return 0;
}

eventFunc getEventFunc(EVENT_ENUM en){
    for(int i = 0; i < sizeof(event_associations)/sizeof(event_serializer_t); i++){
        event_serializer_t* es = &event_associations[i];
        if(es->type == en)
            return es->func_ptr;
    }

    printf("could not find event function!\n");
    return 0;
}

void serializeGba(vector_t* v, gba_t* gba){
    // SERIALIZE RAM
    SERIALIZE_ARRAY(gba->EWRAM);
    SERIALIZE_ARRAY(gba->IWRAM);

    // SERIALIZE GAMEPAK
    serializeGamePak(v, &gba->gamepak);

    // SERIALIZE BIOS
    SERIALIZE_VAR(gba->bios.last_fetched);

    // SERIALIZE INTERRUPT REGS
    SERIALIZE_VAR(gba->IE);
    SERIALIZE_VAR(gba->IF);
    SERIALIZE_VAR(gba->HALTCNT);

    // SERIALIZE INPUT REGS
    SERIALIZE_VAR(gba->KEYINPUT);
    
    // SERIALIZE MISC REGS
    SERIALIZE_VAR(gba->RCNT);
    SERIALIZE_VAR(gba->POSTFLG);
    SERIALIZE_VAR(gba->WAITCNT);

    // SERIALIZE COUNTERS
    SERIALIZE_VAR(gba->frame_clock);
    SERIALIZE_VAR(gba->clock_before_scheduling);

    // SERIALIZE CPU
    SERIALIZE_ARRAY(gba->cpu.r);
    SERIALIZE_ARRAY(gba->cpu.usr_r);
    SERIALIZE_ARRAY(gba->cpu.irq_r);
    SERIALIZE_ARRAY(gba->cpu.svc_r);
    SERIALIZE_ARRAY(gba->cpu.fiq_r);
    SERIALIZE_ARRAY(gba->cpu.und_r);
    SERIALIZE_VAR(gba->cpu.CPSR);
    SERIALIZE_VAR(gba->cpu.SPSR_fiq);
    SERIALIZE_VAR(gba->cpu.SPSR_svc);
    SERIALIZE_VAR(gba->cpu.SPSR_irq);
    SERIALIZE_ARRAY(gba->cpu.pipeline_opcode);
    SERIALIZE_VAR(gba->cpu.cycles);
    SERIALIZE_VAR(gba->cpu.fetch_seq);

    // SERIALIZE PPU
    serializePpu(v, &gba->ppu);

    // SERIALIZE APU
    serializeApu(v, gba, &gba->apu);

    // SERIALIZE PREFETCHER
    serializePrefetcher(v, &gba->prefetcher);

    // SERIALIZE TIMERS
    for(int i = 0; i < 4; i++)
        serializeTimer(v, gba, &gba->timers[i]);

    // SERIALIZE DMA
    serializeDmas(v, gba);

    // SERIALIZE SCHEDULER
    serializeScheduler(v, gba);
}

void serializePrefetcher(vector_t* v, prefetcher_t* prefetcher){
    SERIALIZE_VAR(prefetcher->enabled);
    SERIALIZE_VAR(prefetcher->size);
    SERIALIZE_VAR(prefetcher->address);
    SERIALIZE_VAR(prefetcher->cycle_counter);
}

void serializeTimer(vector_t* v, gba_t* gba, gba_tmr_t* timer){
    SERIALIZE_VAR(timer->started_clock);
    SERIALIZE_VAR(timer->started_value);
    SERIALIZE_VAR(timer->counter);
    SERIALIZE_VAR(timer->speed_shift);
    SERIALIZE_VAR(timer->TMCNT);
    
    int event_ptr = GET_SCHEDULER_IDX(timer->scheduled_event); 
    SERIALIZE_VAR(event_ptr);
    //printf("s %d %p\n", event_ptr, timer->scheduled_event);
}

void serializePpu(vector_t* v, ppu_t* ppu){
    SERIALIZE_ARRAY(ppu->PALETTE_RAM);
    SERIALIZE_ARRAY(ppu->VRAM);
    SERIALIZE_ARRAY(ppu->OAM);

    SERIALIZE_VAR(ppu->DISPCNT);
    SERIALIZE_VAR(ppu->DISPSTAT);
    SERIALIZE_VAR(ppu->VCOUNT);
    
    SERIALIZE_ARRAY(ppu->BGCNT);
    SERIALIZE_ARRAY(ppu->BGHOFS);
    SERIALIZE_ARRAY(ppu->BGVOFS);

    SERIALIZE_ARRAY(ppu->BGX);
    SERIALIZE_ARRAY(ppu->BGY);
    SERIALIZE_ARRAY(ppu->INTERNAL_BGX);
    SERIALIZE_ARRAY(ppu->INTERNAL_BGY);
    SERIALIZE_ARRAY(ppu->BGP);

    SERIALIZE_ARRAY(ppu->WINH);
    SERIALIZE_ARRAY(ppu->WINV);
    SERIALIZE_VAR(ppu->WININ);
    SERIALIZE_VAR(ppu->WINOUT);

    SERIALIZE_VAR(ppu->BLDCNT);
    SERIALIZE_VAR(ppu->BLDALPHA);
    SERIALIZE_VAR(ppu->BLDY);
    
    SERIALIZE_VAR(ppu->isHBlank);
    SERIALIZE_VAR(ppu->isVBlank);
    SERIALIZE_VAR(ppu->isVCount);
}

void serializeGamePak(vector_t* v, gamepak_t* gamepak){
    SERIALIZE_ARRAY(gamepak->waitstates);
    SERIALIZE_VAR(gamepak->sram_wait);
    SERIALIZE_VAR(gamepak->type);

    if(gamepak->type != GAMEPAK_ROM_ONLY && gamepak->type != NO_GAMEPAK){
        SERIALIZE_VAR(gamepak->savMemorySize);
        SERIALIZE_VAR(gamepak->savSizeMask);
        vector_add(v, gamepak->savMemory, gamepak->savMemorySize);
        switch(gamepak->type){
            case GAMEPAK_EEPROM:
            serializeEeprom(v, gamepak);
            break;

            case GAMEPAK_FLASH:
            serializeFlash(v, gamepak);
            break;

            default:
            break;
        }
    }
}

void serializeFlash(vector_t* v, gamepak_t* gamepak){
    flash_t* flash = gamepak->internalData;

    SERIALIZE_VAR(flash->bank);
    SERIALIZE_ARRAY(flash->id_byte);
    SERIALIZE_VAR(flash->state);
}

void serializeEeprom(vector_t* v, gamepak_t* gamepak){
    eeprom_t* eeprom = gamepak->internalData;

    SERIALIZE_VAR(eeprom->address);
    SERIALIZE_VAR(eeprom->bit_counter);
    SERIALIZE_VAR(eeprom->buffer);
    SERIALIZE_VAR(eeprom->n);
    SERIALIZE_VAR(eeprom->state);
}

void serializeApu(vector_t* v, gba_t* gba, apu_t* apu){
    SERIALIZE_VAR(apu->SOUNDBIAS);
    SERIALIZE_VAR(apu->SOUNDCNT_L);
    SERIALIZE_VAR(apu->SOUNDCNT_H);
    SERIALIZE_VAR(apu->SOUNDCNT_X);

    SERIALIZE_VAR(apu->SOUND1CNT_L);
    SERIALIZE_VAR(apu->SOUND1CNT_H);
    SERIALIZE_VAR(apu->SOUND1CNT_X);

    SERIALIZE_VAR(apu->SOUND2CNT_L);
    SERIALIZE_VAR(apu->SOUND2CNT_H);

    SERIALIZE_VAR(apu->SOUND3CNT_L);
    SERIALIZE_VAR(apu->SOUND3CNT_H);
    SERIALIZE_VAR(apu->SOUND3CNT_X);

    SERIALIZE_VAR(apu->SOUND4CNT_L);
    SERIALIZE_VAR(apu->SOUND4CNT_H);

    for(int i = 0; i < 4; i++){
        sound_channel_t* sc = &apu->sound_channels[i];
        SERIALIZE_VAR(sc->length_enabled);
        SERIALIZE_VAR(sc->length);
        SERIALIZE_VAR(sc->envelope_dir);
        SERIALIZE_VAR(sc->envelope_time);
        SERIALIZE_VAR(sc->sample);
        SERIALIZE_VAR(sc->volume);
        SERIALIZE_VAR(sc->freq);
        SERIALIZE_VAR(sc->enabled);

        int ptr;
        ptr = GET_SCHEDULER_IDX(sc->lengthExpired);
        SERIALIZE_VAR(ptr);
        ptr = GET_SCHEDULER_IDX(sc->freqUpdate);
        SERIALIZE_VAR(ptr);
        ptr = GET_SCHEDULER_IDX(sc->envUpdate);
        SERIALIZE_VAR(ptr);
    }

    for(int i = 0; i < 2; i++){
        waveform_t* wf = &apu->waveforms[i];
        SERIALIZE_VAR(wf->selected);
        SERIALIZE_VAR(wf->idx);
    }

    SERIALIZE_VAR(apu->lfsr);
    SERIALIZE_ARRAY(apu->wave_ram);
    SERIALIZE_VAR(apu->wave_idx);
    SERIALIZE_VAR(apu->sound_channels_volume);
    SERIALIZE_VAR(apu->sound_channels_amplifier_right);
    SERIALIZE_VAR(apu->sound_channels_amplifier_left);
    SERIALIZE_ARRAY(apu->sound_channels_enabled_right);
    SERIALIZE_ARRAY(apu->sound_channels_enabled_left);

    int ptr = GET_SCHEDULER_IDX(apu->updateSweep);
    SERIALIZE_VAR(ptr);

    for(int i = 0; i < 2; i++){
        fifo_t* f = &apu->fifo[i];
        SERIALIZE_ARRAY(f->data);
        SERIALIZE_VAR(f->size);
        SERIALIZE_VAR(f->r_idx);
        SERIALIZE_VAR(f->w_idx);
    }

    SERIALIZE_ARRAY(apu->timer_idx);
    SERIALIZE_ARRAY(apu->dma_sound_sample);
    SERIALIZE_ARRAY(apu->dma_sound_enabled_left);
    SERIALIZE_ARRAY(apu->dma_sound_enabled_right);
    SERIALIZE_ARRAY(apu->dma_sound_volume);
}

void serializeDmas(vector_t* v, gba_t* gba){
    SERIALIZE_VAR(gba->active_dma);
    
    for(int i = 0; i < 4; i++){
        dma_t* dma = &gba->dmas[i];
        SERIALIZE_VAR(dma->internal_source);
        SERIALIZE_VAR(dma->internal_dest);
        SERIALIZE_VAR(dma->bus);
        SERIALIZE_VAR(dma->DMASAD);
        SERIALIZE_VAR(dma->DMADAD);
        SERIALIZE_VAR(dma->DMACNT);
    }
}

void serializeScheduler(vector_t* v, gba_t* gba){
    int pool_size = GBA_SCHEDULER_POOL_SIZE;
    int ptr = GET_SCHEDULER_IDX(gba->scheduler_head);

    SERIALIZE_VAR(ptr);
    SERIALIZE_VAR(pool_size);

    for(int i = 0; i < GBA_SCHEDULER_POOL_SIZE; i++){
        scheduler_t* s = &gba->scheduler_pool[i];
        SERIALIZE_VAR(s->used);
        SERIALIZE_VAR(s->remaining);
        SERIALIZE_VAR(s->arg);
        EVENT_ENUM en = getEventEnum(s->event);
        SERIALIZE_VAR(en);
        int ptr = GET_SCHEDULER_IDX(s->next);
        SERIALIZE_VAR(ptr);
    }
}

void deserializeGba(u8* buf, gba_t* gba){
    // DESERIALIZE RAM
    DESERIALIZE_ARRAY(gba->EWRAM);
    DESERIALIZE_ARRAY(gba->IWRAM);

    // DESERIALIZE GAMEPAK
    buf = deserializeGamePak(buf, &gba->gamepak);

    // DESERIALIZE BIOS
    DESERIALIZE_VAR(gba->bios.last_fetched);

    // DESERIALIZE INTERRUPT REGS
    DESERIALIZE_VAR(gba->IE);
    DESERIALIZE_VAR(gba->IF);
    DESERIALIZE_VAR(gba->HALTCNT);

    // DESERIALIZE INPUT REGS
    DESERIALIZE_VAR(gba->KEYINPUT);

    // DESERIALIZE MISC REGS
    DESERIALIZE_VAR(gba->RCNT);
    DESERIALIZE_VAR(gba->POSTFLG);
    DESERIALIZE_VAR(gba->WAITCNT);

    // DESERIALIZE COUNTERS
    DESERIALIZE_VAR(gba->frame_clock);
    DESERIALIZE_VAR(gba->clock_before_scheduling);

    // DESERIALIZE CPU
    DESERIALIZE_ARRAY(gba->cpu.r);
    DESERIALIZE_ARRAY(gba->cpu.usr_r);
    DESERIALIZE_ARRAY(gba->cpu.irq_r);
    DESERIALIZE_ARRAY(gba->cpu.svc_r);
    DESERIALIZE_ARRAY(gba->cpu.fiq_r);
    DESERIALIZE_ARRAY(gba->cpu.und_r);
    DESERIALIZE_VAR(gba->cpu.CPSR);
    DESERIALIZE_VAR(gba->cpu.SPSR_fiq);
    DESERIALIZE_VAR(gba->cpu.SPSR_svc);
    DESERIALIZE_VAR(gba->cpu.SPSR_irq);
    DESERIALIZE_ARRAY(gba->cpu.pipeline_opcode);
    DESERIALIZE_VAR(gba->cpu.cycles);
    DESERIALIZE_VAR(gba->cpu.fetch_seq);

    // DESERIALIZE PPU
    buf = deserializePpu(buf, &gba->ppu);

    // DESERIALIZE APU
    buf = deserializeApu(buf, gba, &gba->apu);

    // DESERIALIZE PREFETCHER
    buf = deserializePrefetcher(buf, &gba->prefetcher);

    // DESERIALIZE TIMERS
    for(int i = 0; i < 4; i++)
        buf = deserializeTimer(buf, gba, &gba->timers[i]);

    // DESERIALIZE DMA
    buf = deserializeDmas(buf, gba);

    // DESERIALIZE SCHEDULER
    buf = deserializeScheduler(buf, gba);
}

u8* deserializePrefetcher(u8* buf, prefetcher_t* prefetcher){
    DESERIALIZE_VAR(prefetcher->enabled);
    DESERIALIZE_VAR(prefetcher->size);
    DESERIALIZE_VAR(prefetcher->address);
    DESERIALIZE_VAR(prefetcher->cycle_counter);

    return buf;
}

u8* deserializeTimer(u8* buf, gba_t* gba, gba_tmr_t* timer){
    DESERIALIZE_VAR(timer->started_clock);
    DESERIALIZE_VAR(timer->started_value);
    DESERIALIZE_VAR(timer->counter);
    DESERIALIZE_VAR(timer->speed_shift);
    DESERIALIZE_VAR(timer->TMCNT);
    
    int event_ptr;
    DESERIALIZE_VAR(event_ptr);
    timer->scheduled_event = GET_SCHEDULER_PTR(event_ptr); 

    return buf;
}

u8* deserializePpu(u8* buf, ppu_t* ppu){
    DESERIALIZE_ARRAY(ppu->PALETTE_RAM);
    DESERIALIZE_ARRAY(ppu->VRAM);
    DESERIALIZE_ARRAY(ppu->OAM);

    DESERIALIZE_VAR(ppu->DISPCNT);
    DESERIALIZE_VAR(ppu->DISPSTAT);
    DESERIALIZE_VAR(ppu->VCOUNT);
    
    DESERIALIZE_ARRAY(ppu->BGCNT);
    DESERIALIZE_ARRAY(ppu->BGHOFS);
    DESERIALIZE_ARRAY(ppu->BGVOFS);

    DESERIALIZE_ARRAY(ppu->BGX);
    DESERIALIZE_ARRAY(ppu->BGY);
    DESERIALIZE_ARRAY(ppu->INTERNAL_BGX);
    DESERIALIZE_ARRAY(ppu->INTERNAL_BGY);
    DESERIALIZE_ARRAY(ppu->BGP);

    DESERIALIZE_ARRAY(ppu->WINH);
    DESERIALIZE_ARRAY(ppu->WINV);
    DESERIALIZE_VAR(ppu->WININ);
    DESERIALIZE_VAR(ppu->WINOUT);

    DESERIALIZE_VAR(ppu->BLDCNT);
    DESERIALIZE_VAR(ppu->BLDALPHA);
    DESERIALIZE_VAR(ppu->BLDY);
    
    DESERIALIZE_VAR(ppu->isHBlank);
    DESERIALIZE_VAR(ppu->isVBlank);
    DESERIALIZE_VAR(ppu->isVCount);

    return buf;
}

u8* deserializeGamePak(u8* buf, gamepak_t* gamepak){
    DESERIALIZE_ARRAY(gamepak->waitstates);
    DESERIALIZE_VAR(gamepak->sram_wait);
    DESERIALIZE_VAR(gamepak->type);

    if(gamepak->type != GAMEPAK_ROM_ONLY && gamepak->type != NO_GAMEPAK){
        DESERIALIZE_VAR(gamepak->savMemorySize);
        DESERIALIZE_VAR(gamepak->savSizeMask);
        memcpy(gamepak->savMemory, buf, gamepak->savMemorySize);
        buf += gamepak->savMemorySize;
        switch(gamepak->type){
            case GAMEPAK_EEPROM:
            buf = deserializeEeprom(buf, gamepak);
            break;

            case GAMEPAK_FLASH:
            buf = deserializeFlash(buf, gamepak);
            break;

            default:
            break;
        }
    }

    return buf;
}

u8* deserializeFlash(u8* buf, gamepak_t* gamepak){
    flash_t* flash = gamepak->internalData;

    DESERIALIZE_VAR(flash->bank);
    DESERIALIZE_ARRAY(flash->id_byte);
    DESERIALIZE_VAR(flash->state);

    return buf;
}

u8* deserializeEeprom(u8* buf, gamepak_t* gamepak){
    eeprom_t* eeprom = gamepak->internalData;

    DESERIALIZE_VAR(eeprom->address);
    DESERIALIZE_VAR(eeprom->bit_counter);
    DESERIALIZE_VAR(eeprom->buffer);
    DESERIALIZE_VAR(eeprom->n);
    DESERIALIZE_VAR(eeprom->state);

    return buf;
}

u8* deserializeApu(u8* buf, gba_t* gba, apu_t* apu){
    DESERIALIZE_VAR(apu->SOUNDBIAS);
    DESERIALIZE_VAR(apu->SOUNDCNT_L);
    DESERIALIZE_VAR(apu->SOUNDCNT_H);
    DESERIALIZE_VAR(apu->SOUNDCNT_X);

    DESERIALIZE_VAR(apu->SOUND1CNT_L);
    DESERIALIZE_VAR(apu->SOUND1CNT_H);
    DESERIALIZE_VAR(apu->SOUND1CNT_X);

    DESERIALIZE_VAR(apu->SOUND2CNT_L);
    DESERIALIZE_VAR(apu->SOUND2CNT_H);

    DESERIALIZE_VAR(apu->SOUND3CNT_L);
    DESERIALIZE_VAR(apu->SOUND3CNT_H);
    DESERIALIZE_VAR(apu->SOUND3CNT_X);

    DESERIALIZE_VAR(apu->SOUND4CNT_L);
    DESERIALIZE_VAR(apu->SOUND4CNT_H);

    for(int i = 0; i < 4; i++){
        sound_channel_t* sc = &apu->sound_channels[i];
        DESERIALIZE_VAR(sc->length_enabled);
        DESERIALIZE_VAR(sc->length);
        DESERIALIZE_VAR(sc->envelope_dir);
        DESERIALIZE_VAR(sc->envelope_time);
        DESERIALIZE_VAR(sc->sample);
        DESERIALIZE_VAR(sc->volume);
        DESERIALIZE_VAR(sc->freq);
        DESERIALIZE_VAR(sc->enabled);

        int ptr;
        DESERIALIZE_VAR(ptr);
        sc->lengthExpired = GET_SCHEDULER_PTR(ptr);
        DESERIALIZE_VAR(ptr);
        sc->freqUpdate = GET_SCHEDULER_PTR(ptr);
        DESERIALIZE_VAR(ptr);
        sc->envUpdate = GET_SCHEDULER_PTR(ptr);
    }

    for(int i = 0; i < 2; i++){
        waveform_t* wf = &apu->waveforms[i];
        DESERIALIZE_VAR(wf->selected);
        DESERIALIZE_VAR(wf->idx);
    }

    DESERIALIZE_VAR(apu->lfsr);
    DESERIALIZE_ARRAY(apu->wave_ram);
    DESERIALIZE_VAR(apu->wave_idx);
    DESERIALIZE_VAR(apu->sound_channels_volume);
    DESERIALIZE_VAR(apu->sound_channels_amplifier_right);
    DESERIALIZE_VAR(apu->sound_channels_amplifier_left);
    DESERIALIZE_ARRAY(apu->sound_channels_enabled_right);
    DESERIALIZE_ARRAY(apu->sound_channels_enabled_left);

    int ptr;
    DESERIALIZE_VAR(ptr);
    apu->updateSweep = GET_SCHEDULER_PTR(ptr);

    for(int i = 0; i < 2; i++){
        fifo_t* f = &apu->fifo[i];
        DESERIALIZE_ARRAY(f->data);
        DESERIALIZE_VAR(f->size);
        DESERIALIZE_VAR(f->r_idx);
        DESERIALIZE_VAR(f->w_idx);
    }

    DESERIALIZE_ARRAY(apu->timer_idx);
    DESERIALIZE_ARRAY(apu->dma_sound_sample);
    DESERIALIZE_ARRAY(apu->dma_sound_enabled_left);
    DESERIALIZE_ARRAY(apu->dma_sound_enabled_right);
    DESERIALIZE_ARRAY(apu->dma_sound_volume);

    return buf;
}

u8* deserializeDmas(u8* buf, gba_t* gba){
    DESERIALIZE_VAR(gba->active_dma);
    
    for(int i = 0; i < 4; i++){
        dma_t* dma = &gba->dmas[i];
        DESERIALIZE_VAR(dma->internal_source);
        DESERIALIZE_VAR(dma->internal_dest);
        DESERIALIZE_VAR(dma->bus);
        DESERIALIZE_VAR(dma->DMASAD);
        DESERIALIZE_VAR(dma->DMADAD);
        DESERIALIZE_VAR(dma->DMACNT);
    }

    return buf;
}

u8* deserializeScheduler(u8* buf, gba_t* gba){
    int pool_size;

    int ptr;
    DESERIALIZE_VAR(ptr);
    gba->scheduler_head = GET_SCHEDULER_PTR(ptr);

    DESERIALIZE_VAR(pool_size);
    if(pool_size != GBA_SCHEDULER_POOL_SIZE)
        printf("different scheduler pool size from previous savestate!\n");

    for(int i = 0; i < GBA_SCHEDULER_POOL_SIZE; i++){
        scheduler_t* s = &gba->scheduler_pool[i];
        DESERIALIZE_VAR(s->used);
        DESERIALIZE_VAR(s->remaining);
        DESERIALIZE_VAR(s->arg);
        EVENT_ENUM en;
        DESERIALIZE_VAR(en);
        s->event = getEventFunc(en);
        int ptr;
        DESERIALIZE_VAR(ptr);
        s->next = GET_SCHEDULER_PTR(ptr);
    }

    return buf;
}