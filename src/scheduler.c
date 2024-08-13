#include "scheduler.h"
#include "gba.h"
#include "timer.h"

#include <stdio.h>

scheduler_t* occupySchedulerBlock(scheduler_t* scheduler_pool, size_t size){
    for(int i = 0; i < size; i++){
        if(!scheduler_pool[i].used){
            scheduler_pool[i].used = true;
            scheduler_pool[i].next = NULL;
            return &scheduler_pool[i];
        }
    }

    printf("CANNOT FIND FREE SCHEDULER!\n");
}


void addEventToScheduler(scheduler_t** list, scheduler_t* event){
    if(*list == NULL){
        *list = event;
        return;
    }

    if(event->remaining < (*list)->remaining){
        (*list)->remaining -= event->remaining;
        event->next = *list;
        (*list) = event;
        return;
    }
    
    event->remaining -= (*list)->remaining;

    scheduler_t* p = (*list)->next;
    scheduler_t* q = *list;
    while(p && event->remaining > p->remaining){
        event->remaining -= p->remaining;
        q = p;
        p = p->next;
    }

    q->next = event;
    event->next = p;
    if(p)
        p->remaining -= event->remaining;
}

void removeEventToScheduler(scheduler_t** list, scheduler_t* event){
    event->used = false;

    if(event->next)
        event->next->remaining += event->remaining;

    if((*list) == event){
        *list = (*list)->next;
        return;
    }

    scheduler_t* p = *list;
    while(p && p->next != event)
        p = p->next;

    p->next = event->next;
}

void stepScheduler(gba_t* gba, scheduler_t** scheduler, u32 cycles_step){
    if(*scheduler == NULL)
        printf("SCHEDULER HEAD CANNOT BE EMPTY!\n");
    
    gba->clock_before_scheduling = gba->cpu.cycles;

    scheduler_t* closest_event = (*scheduler);
    while(cycles_step || !closest_event->remaining){
        u32 to_subtract = cycles_step < closest_event->remaining ? cycles_step : closest_event->remaining;
        closest_event->remaining -= to_subtract;
        cycles_step -= to_subtract;
        if(!closest_event->remaining){
            closest_event->used = false;
            *scheduler = closest_event->next;
            (closest_event->event)(gba, closest_event->arg);
        }
        closest_event = (*scheduler);
    }
}

void removeEventIfPresent(scheduler_t** list, scheduler_t** event){
    if(*event){
        removeEventToScheduler(list, *event);
        *event = NULL;
    }
}


scheduler_t* createAndAddEventWith0Args(scheduler_t** list, scheduler_t* pool, size_t pool_size, eventFunc event, u64 remaining){
    scheduler_t* block = occupySchedulerBlock(pool, pool_size);
    block->event = event;
    block->remaining = remaining;
    addEventToScheduler(list, block);
    return block;
}


scheduler_t* createAndAddEventWith1Arg(scheduler_t** list, scheduler_t* pool, size_t pool_size, eventFunc event, u32 arg, u64 remaining){
    scheduler_t* block = createAndAddEventWith0Args(list, pool, pool_size, event, remaining);
    block->arg = arg;
    return block;
}