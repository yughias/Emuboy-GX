#ifndef __TIMER_H__
#define __TIMER_H__

#include "integer.h"

typedef struct gba_t gba_t;

typedef struct
{
    u32 counter;
    u32 internal_clock;
    u32 TMCNT;
} timer_t;

void triggerTimer(timer_t* timer);
void updateTimers(gba_t* gba, int ticks);


#endif