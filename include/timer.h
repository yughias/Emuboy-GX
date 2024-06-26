#ifndef __TIMER_H__
#define __TIMER_H__

#include "integer.h"

typedef struct gba_t gba_t;
typedef struct scheduler_t scheduler_t;

typedef struct
{
    u64 started_clock;
    u32 started_value;
    u32 counter;
    u32 TMCNT;

    scheduler_t* scheduled_event;
} timer_t;

void triggerTimer(gba_t* gba, int i);
void updateTimerCounter(gba_t* gba, int i);
void descheduleTimer(gba_t* gba, int i);

void event_timerOverflow(gba_t* gba, u32 i, u32 dummy);

#endif