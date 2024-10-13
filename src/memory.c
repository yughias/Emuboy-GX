#include "gba.h"

#include "sram.h"
#include "flash.h"
#include "eeprom.h"

#include "memory_utils.h"

#include <stdio.h>
#include <stdlib.h>

DEFINE_READ_FUNC(Byte, 8, 0)
DEFINE_READ_FUNC(HalfWord, 16, 0b1)
DEFINE_READ_FUNC(Word, 32, 0b11)

DEFINE_WRITE_FUNC(Byte, 8, 0)
DEFINE_WRITE_FUNC(HalfWord, 16, 0b1)
DEFINE_WRITE_FUNC(Word, 32, 0b11)

void loadBios(const char* filename, u8** bios){
    FILE* fptr = fopen(filename, "rb");
    if(!fptr){
        printf("can't open bios\n");
        return;
    }

    *bios = (u8*)malloc(BIOS_SIZE);

    fread(*bios, 1, BIOS_SIZE, fptr);

    fclose(fptr);
}

u16 readHalfWordWithPrefetcher(arm7tdmi_t* cpu, gamepak_t* gamepak, u32 addr, bool seq){
    u32 elapsed = cpu->cycles - cpu->prefetch_counter;
    u8 wt = gamepak->waitstates[0][true];

    while(cpu->prefetch_n < 16 && elapsed >= wt + 1){
        cpu->prefetch_n += 1;
        cpu->prefetch_counter += (wt + 1);
        elapsed -= (wt + 1);
    }

    if(addr == cpu->prefetch_addr){
        if(cpu->prefetch_n >= 1){
            cpu->prefetch_n -= 1;
        } else {
            cpu->cycles += wt + 1 - elapsed;
            cpu->prefetch_counter = cpu->cycles;
        }
    } else {
        if(!(addr & 0x1FFFF) && !elapsed)
            cpu->cycles += 1;
        cpu->cycles += gamepak->waitstates[0][seq];
        cpu->prefetch_n = 0;
        cpu->prefetch_counter = cpu->cycles;
    }
    cpu->prefetch_addr = addr + 2;
    return *(u16*)(&gamepak->ROM[addr-0x08000000]);
}

u32 readWordWithPrefetcher(arm7tdmi_t* cpu, gamepak_t* gamepak, u32 addr, bool seq){
    u32 elapsed = cpu->cycles - cpu->prefetch_counter;
    u8 wt = gamepak->waitstates[0][true];
    
    while(cpu->prefetch_n < 16 && elapsed >= wt + 1){
        cpu->prefetch_n += 1;
        cpu->prefetch_counter += (wt + 1);
        elapsed -= (wt + 1);
    }

    if(addr == cpu->prefetch_addr){
        if(cpu->prefetch_n >= 2){
            cpu->prefetch_n -= 2;
        } else {
            cpu->cycles += wt + 1 - elapsed;
            if(!cpu->prefetch_n)
                cpu->cycles += wt + 1;
            cpu->prefetch_n = 0;
            cpu->prefetch_counter = cpu->cycles;
        }
    } else {
        if(!(addr & 0x1FFFF) && !elapsed)
            cpu->cycles += 1;
        cpu->cycles += gamepak->waitstates[0][seq] + 1 + gamepak->waitstates[0][true];
        cpu->prefetch_n = 0;
        cpu->prefetch_counter = cpu->cycles;
    }
    cpu->prefetch_addr = addr + 4;
    return *(u32*)(&gamepak->ROM[addr-0x08000000]);
}