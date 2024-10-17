#include "prefetcher.h"
#include "gamepak.h"
#include "arm7tdmi/arm7tdmi.h"

#define UPDATE_PREFETCH(prefetch) \
while(elapsed >= wt + 1){ \
    prefetch->size += prefetch->size < 16; \
    prefetch->cycle_counter += (wt + 1); \
    elapsed -= (wt + 1); \
}

#define RESET_PREFETCH(prefetch) \
prefetch->size = 0; \
prefetch->cycle_counter = cpu->cycles

void addDelayHalfWordWithPrefetcher(prefetcher_t* prefetch, gamepak_t* gamepak, arm7tdmi_t* cpu, u32 addr, bool seq){
    u32 elapsed = cpu->cycles - prefetch->cycle_counter;
    u8 wt = gamepak->waitstates[0][true];

    UPDATE_PREFETCH(prefetch);

    if(addr == prefetch->address){
        if(prefetch->size >= 1){
            prefetch->size -= 1;
        } else {
            cpu->cycles += wt + 1 - elapsed;
            prefetch->cycle_counter = cpu->cycles;
        }
    } else {
        if(!(addr & 0x1FFFF) && !elapsed)
            cpu->cycles += 1;
        cpu->cycles += gamepak->waitstates[0][seq];
        RESET_PREFETCH(prefetch);
    }
    prefetch->address = addr + 2;
}

void addDelayWordWithPrefetcher(prefetcher_t* prefetch, gamepak_t* gamepak, arm7tdmi_t* cpu, u32 addr, bool seq){
    u32 elapsed = cpu->cycles - prefetch->cycle_counter;
    u8 wt = gamepak->waitstates[0][true];
    
    UPDATE_PREFETCH(prefetch);

    if(addr == prefetch->address){
        if(prefetch->size >= 2){
            prefetch->size -= 2;
        } else {
            cpu->cycles += wt + 1 - elapsed;
            if(!prefetch->size)
                cpu->cycles += wt + 1;
            RESET_PREFETCH(prefetch);
        }
    } else {
        if(!(addr & 0x1FFFF) && !elapsed)
            cpu->cycles += 1;
        cpu->cycles += gamepak->waitstates[0][seq] + 1 + gamepak->waitstates[0][true];
        RESET_PREFETCH(prefetch);
    }
    prefetch->address = addr + 4;
}