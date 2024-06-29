#include "gba.h"
#include "gamepak.h"

#include <SDL2/SDL.h>

#include <string.h>
#include <stdlib.h>
#include <time.h>

void checkInterrupts(gba_t* gba){
    if(!(gba->IME & 1) || gba->cpu.irq_disable)
        return;
    bool irq_mask = gba->IE & gba->IF & 0x3FFF;
    if(irq_mask == 0)
        return;

    arm7tdmi_trigger_exception(&gba->cpu, 0x18, 0x12);
}

void emulateGba(gba_t* gba){
    gba->KEYINPUT = update_keypad();

    u32 prev_cycles = gba->cpu.cycles;
    while(gba->cpu.cycles < CYCLES_PER_FRAME){
        u32 elapsed = 0;

        while(elapsed < gba->scheduler_head->remaining){
            if(gba->HALTCNT){
                gba->HALTCNT = !(gba->IF & gba->IE & 0x3FFF); 
                gba->cpu.cycles += gba->scheduler_head->remaining;
            } else
                arm7tdmi_step(&gba->cpu);
            elapsed = gba->cpu.cycles - prev_cycles;
        }
 
        stepScheduler(gba, &gba->scheduler_head, elapsed);
        prev_cycles = gba->cpu.cycles;
    }

    gba->cpu.cycles -= CYCLES_PER_FRAME;
    gba->clock_before_scheduling -= CYCLES_PER_FRAME;
    gba->frame_clock += CYCLES_PER_FRAME;
}

void initGba(gba_t* gba, const char* biosFilename, const char* romFilename){
    memset(gba, 0, sizeof(gba_t));
    #ifdef EMSCRIPTEN
    gba->cpu.r[13] = 0x3007F00;
    gba->cpu.r[15] = 0x8000000;
    gba->cpu.irq_r[1] = 0x0;
    gba->cpu.irq_r[0] = 0x03007FA0;
    gba->cpu.usr_r[13] = 0x03007F00;
    gba->cpu.svc_r[0] = 0x03007FE0;
    gba->cpu.mode_bits = 0x1F;
    #else
    gba->cpu.mode_bits = 0x13;
    gba->cpu.fiq_disable = true,
    gba->cpu.irq_disable = true,
    #endif
    gba->cpu.readByte = readByte;
    gba->cpu.readHalfWord = readHalfWord;
    gba->cpu.readWord = readWord;
    gba->cpu.writeByte = writeByte;
    gba->cpu.writeHalfWord = writeHalfWord;
    gba->cpu.writeWord = writeWord;
    gba->cpu.master = gba;

    gba->KEYINPUT = 0xFFFF;
    gba->RCNT = 0x8000;

    loadBios(biosFilename, &gba->BIOS);
    loadGamePak(&gba->gamepak, romFilename);

    arm7tdmi_pipeline_refill(&gba->cpu);

    scheduler_t* block = occupySchedulerBlock(gba->scheduler_pool, GBA_SCHEDULER_POOL_SIZE);
    block->remaining = DRAW_CYCLES;
    block->event = event_startHBlank;
    addEventToScheduler(&gba->scheduler_head, block);

    apu_t* apu = &gba->apu;
    apu->audioSpec.freq = 44100;
    apu->audioSpec.channels = 1;
    apu->audioSpec.format = AUDIO_S16;
    apu->audioSpec.callback = NULL;
    apu->audioSpec.userdata = NULL;
    apu->audioDev = SDL_OpenAudioDevice(0, 0, &apu->audioSpec, &apu->audioSpec, 0);
    apu->samplePushRate = CYCLES_PER_FRAME * REFRESH_RATE / apu->audioSpec.freq;

    block = occupySchedulerBlock(gba->scheduler_pool, GBA_SCHEDULER_POOL_SIZE);
    block->remaining = gba->apu.samplePushRate;
    block->event = event_pushSampleToAudioDevice;
    addEventToScheduler(&gba->scheduler_head, block);

    SDL_PauseAudioDevice(gba->apu.audioDev, 0);
}

void freeGba(gba_t* gba){
    if(gba->BIOS)
        free(gba->BIOS);

    freeGamePak(&gba->gamepak);
}