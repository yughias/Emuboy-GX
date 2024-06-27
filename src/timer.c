#include "gba.h"
#include "scheduler.h"

#define IS_ENABLED(x) ((timer->TMCNT >> 16) & 0x80)
#define IS_IRQ(x) ((timer->TMCNT >> 16) & (1 << 6))
#define IS_CASCADE(x) ((x->TMCNT >> 16) & 0b100)
#define GET_RELOAD(x) (x->TMCNT & 0xFFFF)

const u32 timerSpeedSfhit[4] = {0, 6, 8, 10};

/*
void updateTimers(gba_t* gba, int ticks){
    timer_t* timers = gba->timers;
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
            if(irq_enabled){
                gba->IF |= 1 << (3+i);
                checkInterrupts(gba);
            }
        } else
            prev_overflow = false;
    }
}
*/

void triggerTimer(gba_t* gba, int i){
    timer_t* timer = &gba->timers[i];

    bool cascade = IS_CASCADE(timer);
    if(cascade){
        timer->counter = GET_RELOAD(timer);
        timer->scheduled_event = NULL;
        return;
    }

    u32 duration = 0x10000 - GET_RELOAD(timer);
    duration <<= timerSpeedSfhit[(timer->TMCNT >> 16) & 0b11];

    scheduler_t* block = occupySchedulerBlock(gba->scheduler_pool, GBA_SCHEDULER_POOL_SIZE);
    timer->scheduled_event = block;
    timer->started_clock = gba->frame_clock + gba->cpu.cycles;
    timer->started_value = GET_RELOAD(timer);

    block->remaining = duration;
    block->arg1 = i;
    block->event = event_timerOverflow;
    addEventToScheduler(&gba->scheduler_head, block);
}

void descheduleTimer(gba_t* gba, int i){
    timer_t* timer = &gba->timers[i];
    bool cascade = IS_CASCADE(timer);

    if(!cascade)
        updateTimerCounter(gba, i);
    
    if(!timer->scheduled_event)
        return;

    removeEventToScheduler(&gba->scheduler_head, timer->scheduled_event);
    timer->scheduled_event = NULL;
}

void updateTimerCounter(gba_t* gba, int i){
    timer_t* timer = &gba->timers[i];
    bool enabled = IS_ENABLED(timer);
    bool cascade = IS_CASCADE(timer);

    if(!enabled || cascade)
        return;

    u64 elapsed = gba->frame_clock + gba->cpu.cycles - timer->started_clock;
    elapsed >>= timerSpeedSfhit[(timer->TMCNT >> 16) & 0b11];

    timer->counter = timer->started_value + elapsed;
}

void event_timerOverflow(gba_t* gba, u32 i, u32 dummy){
    timer_t* timer = &gba->timers[i];

    bool irq_enabled = IS_IRQ(timer);
    if(irq_enabled){
        gba->IF |= 1 << (3+i);
        checkInterrupts(gba);
    }

    for(int j = i+1; j < 4; j++){
        timer_t* timer = &gba->timers[j];
        bool enabled = IS_ENABLED(timer);
        bool cascade = IS_CASCADE(timer);
        if(!enabled || !cascade)
            break;
        
        timer->counter += 1;
        if(timer->counter == 0x10000)
            timer->counter = GET_RELOAD(timer);
        else
            break;

        bool irq_enabled = IS_IRQ(timer);
        if(irq_enabled){
            gba->IF |= 1 << (3+j);
            checkInterrupts(gba);
        }
    }

    triggerTimer(gba, i);
}