#include "sram.h"

u8 readSram(gamepak_t* gamepak, u16 addr){
    return gamepak->savMemory[addr & gamepak->savSizeMask];
}

void writeSram(gamepak_t* gamepak, u16 addr, u8 byte){
    gamepak->savMemory[addr & gamepak->savSizeMask] = byte;
}
