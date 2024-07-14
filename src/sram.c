#include "sram.h"

#include <stdio.h>
#include <stdlib.h>

void setupSramMemory(gamepak_t* gamepak, size_t size){
    gamepak->type = GAMEPAK_SRAM;
    gamepak->savMemorySize = size;
    gamepak->savMemory = (u8*)malloc(size);
    gamepak->savSizeMask = size - 1;
    printf("SRAM DETECTED!\n");
}

u8 readSram(gamepak_t* gamepak, u16 addr){
    return gamepak->savMemory[addr & gamepak->savSizeMask];
}

void writeSram(gamepak_t* gamepak, u16 addr, u8 byte){
    gamepak->savMemory[addr & gamepak->savSizeMask] = byte;
}
