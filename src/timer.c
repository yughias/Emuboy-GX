#include "hardware.h"

void updateTimers(int ticks, timer_t* timers){
    static u32 timerSpeed[4] = {1, 64, 256, 1024};
    bool prev_overflow = false;
    for(int i = 0; i < 4; i++){
        timer_t* timer = &timers[i];
        bool enabled = (timer->TMCNT >> 16) & 0x80;
        if(!enabled){
            prev_overflow = false;
            continue;
        }
        bool cascade_mode = (timer->TMCNT >> 16) & 0b100;
        bool irq_enabled = (timer->TMCNT >> 16) & (1 << 6);
        if(cascade_mode){
            if(prev_overflow)
                timer->counter += 1;
        } else {
            u32 speed = timerSpeed[(timer->TMCNT >> 16) & 0b11];
            timer->internal_clock += ticks;
            if(timer->internal_clock >= speed){
                timer->counter += timer->internal_clock / speed;
                timer->internal_clock = timer->internal_clock % speed; 
            }
        }
        if(timer->counter > 0xFFFF){
            timer->counter %= 0x10000;
            prev_overflow = true;
            timer->counter += timer->TMCNT & 0xFFFF;
            if(irq_enabled)
                IF |= 1 << (3+i);
        } else
            prev_overflow = false;
    }
}

void triggerTimer(timer_t* timer){
    timer->internal_clock = timer->TMCNT & 0xFFFF;
    timer->counter = 0;
}