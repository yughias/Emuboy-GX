#include "gba.h"

#define IS_ENABLED(x) ((timer->TMCNT >> 16) & 0x80)
#define IS_IRQ(x) ((timer->TMCNT >> 16) & (1 << 6))
#define IS_CASCADE(x) ((x->TMCNT >> 16) & 0b100)
#define GET_RELOAD(x) (x->TMCNT & 0xFFFF)
#define GET_SPEED_SHIFT(x) (timerSpeedShift[(x->TMCNT >> 16) & 0b11])

#define TIMER_TRIGGER_DELAY 2

const u32 timerSpeedShift[4] = {0, 6, 8, 10};

void triggerTimer(gba_t* gba, int i){
    gba_tmr_t* timer = &gba->timers[i];

    bool cascade = IS_CASCADE(timer);
    if(cascade){
        timer->counter = GET_RELOAD(timer);
        timer->scheduled_event = NULL;
        return;
    }

    timer->speed_shift = GET_SPEED_SHIFT(timer); 
    u32 duration = 0x10000 - GET_RELOAD(timer);
    duration <<= timer->speed_shift;

    // delay occurs only if timer was disabled 
    u8 delay = timer->scheduled_event ? 0 : TIMER_TRIGGER_DELAY;

    timer->started_clock = gba->frame_clock + gba->cpu.cycles + delay;
    timer->started_value = GET_RELOAD(timer);

    u64 remaining = duration + (gba->cpu.cycles - gba->clock_before_scheduling) + delay;
    timer->scheduled_event = createAndAddEventWith1Arg(&gba->scheduler_head, gba->scheduler_pool, GBA_SCHEDULER_POOL_SIZE, event_timerOverflow, i, remaining);
}

void disableCascadeModeTimer(gba_t* gba, int i){
    gba_tmr_t* timer = &gba->timers[i];

    timer->speed_shift = GET_SPEED_SHIFT(timer); 
    u32 duration = 0x10000 - timer->counter;
    duration <<= timer->speed_shift;

    timer->started_clock = gba->frame_clock + gba->cpu.cycles;
    timer->started_value = timer->counter;

    u64 remaining = duration + (gba->cpu.cycles - gba->clock_before_scheduling);
    timer->scheduled_event = createAndAddEventWith1Arg(&gba->scheduler_head, gba->scheduler_pool, GBA_SCHEDULER_POOL_SIZE, event_timerOverflow, i, remaining);
}

void descheduleTimer(gba_t* gba, int i){
    gba_tmr_t* timer = &gba->timers[i];
    bool cascade = IS_CASCADE(timer);

    if(!cascade)
        updateTimerCounter(gba, i);
    
    removeEventIfPresent(&gba->scheduler_head, &timer->scheduled_event);
}

void updateTimerCounter(gba_t* gba, int i){
    gba_tmr_t* timer = &gba->timers[i];
    bool enabled = IS_ENABLED(timer);
    bool cascade = IS_CASCADE(timer);

    if(!enabled || cascade)
        return;

    u64 elapsed = gba->frame_clock + gba->cpu.cycles - timer->started_clock;
    elapsed >>= timer->speed_shift;

    timer->counter = (timer->started_value + elapsed) & 0xFFFF;
}

void event_timerOverflow(gba_t* gba, u32 i){
    gba_tmr_t* timer = &gba->timers[i];

    apuCheckTimer(gba, i);
    bool irq_enabled = IS_IRQ(timer);
    if(irq_enabled){
        gba->IF |= 1 << (3+i);
        checkInterrupts(gba);
    }

    for(int j = i+1; j < 4; j++){
        gba_tmr_t* timer = &gba->timers[j];
        bool enabled = IS_ENABLED(timer);
        bool cascade = IS_CASCADE(timer);
        if(!enabled || !cascade)
            break;
        
        timer->counter += 1;
        if(timer->counter == 0x10000)
            timer->counter = GET_RELOAD(timer);
        else
            break;

        apuCheckTimer(gba, j);
        bool irq_enabled = IS_IRQ(timer);
        if(irq_enabled){
            gba->IF |= 1 << (3+j);
            checkInterrupts(gba);
        }
    }

    triggerTimer(gba, i);
}