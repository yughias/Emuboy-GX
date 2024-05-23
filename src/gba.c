#include "gba.h"

#include <string.h>

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

    for(int i = 0; i < CYCLES_PER_FRAME; i++){
        if(gba->HALTCNT)
            gba->HALTCNT = !(gba->IF & gba->IE & 0x3FFF); 
        else
            arm7tdmi_step(&gba->cpu);
        updatePPU(gba, i);
        updateTimers(gba, 1);
    }
}

void initGba(gba_t* gba){
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
}