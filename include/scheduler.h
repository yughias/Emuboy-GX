#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "integer.h"

typedef struct gba_t gba_t;

typedef void (*eventFunc)(gba_t* gba, u32 arg);
typedef struct scheduler_t scheduler_t;
typedef struct scheduler_t {
    bool used;
    u64 remaining;
    u32 arg;
    eventFunc event;
    scheduler_t* next;
} scheduler_t;

scheduler_t* occupySchedulerBlock(scheduler_t* scheduler_pool, size_t size);
void addEventToScheduler(scheduler_t** list, scheduler_t* event);
void removeEventToScheduler(scheduler_t** list, scheduler_t* event);
void stepScheduler(gba_t* gba, scheduler_t** list, u32 cycles_step);

void removeEventIfPresent(scheduler_t** list, scheduler_t** event);
scheduler_t* createAndAddEventWith0Args(scheduler_t** list, scheduler_t* pool, size_t pool_size, eventFunc event, u64 remaining);
scheduler_t* createAndAddEventWith1Arg(scheduler_t** list, scheduler_t* pool, size_t pool_size, eventFunc event, u32 arg, u64 remaining);

#endif