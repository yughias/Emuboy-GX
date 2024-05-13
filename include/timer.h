#ifndef __TIMER_H__
#define __TIMER_H__

#include "integer.h"

typedef struct
{
    u32 counter;
    u32 internal_clock;
    u32 TMCNT;
} timer_t;

void triggerTimer(timer_t* timer);
void updateTimers(int ticks, timer_t* timers);


#endif