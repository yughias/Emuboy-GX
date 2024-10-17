#ifndef __PREFETCHER_H__
#define __PREFETCHER_H__

#include "integer.h"

typedef struct arm7tdmi_t arm7tdmi_t;
typedef struct gamepak_t gamepak_t;

typedef struct prefetcher_t {
    bool enabled;
    int size;
    u32 address;
    u32 cycle_counter;
} prefetcher_t;

void addDelayWordWithPrefetcher(prefetcher_t* prefetch, gamepak_t* gamepak, arm7tdmi_t* cpu, u32 addr, bool seq);
void addDelayHalfWordWithPrefetcher(prefetcher_t* prefetch, gamepak_t* gamepak, arm7tdmi_t* cpu, u32 addr, bool seq);

#endif