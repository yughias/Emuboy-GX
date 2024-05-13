#include "hardware.h"

arm7tdmi_t cpu = {
    /*
    .r[13] = 0x3007F00,
    .r[15] = 0x8000000,
    .irq_r[1] = 0x0,
    .irq_r[0] = 0x03007FA0,
    .usr_r[13] = 0x03007F00,
    .svc_r[0] = 0x03007FE0,
    .mode_bits = 0x1F,
    */
    
    .mode_bits = 0x13,
    .fiq_disable = true,
    .irq_disable = true,
    

    .readByte = readByte,
    .writeByte = writeByte  
};

timer_t timers[4];

void checkInterrupts(arm7tdmi_t* cpu){
    if(!(IME & 1) || cpu->irq_disable)
        return;
    bool irq_mask = IE & IF & 0x3FFF;
    if(irq_mask == 0)
        return;

    arm7tdmi_trigger_exception(cpu, 0x18, 0x12);
}

void emulateHardware(){
    update_keypad();

    for(int i = 0; i < CYCLES_PER_FRAME; i++){
        checkInterrupts(&cpu);
        if(HALTCNT)
            HALTCNT = !(IF & IE & 0x3FFF); 
        else
            arm7tdmi_step(&cpu);
        updatePPU(i);
        updateTimers(1, timers);
    }
}