#ifndef __SRAM_H__
#define __SRAM_H__

#include "gamepak.h"
#include "integer.h"

#define SRAM_SIZE (1 << 15)

void setupSramMemory(gamepak_t* gamepak, size_t size);
u8 readSram(gamepak_t* gamepak, u16 addr);
void writeSram(gamepak_t* gamepak, u16 addr, u8 byte);

#endif