#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "integer.h"

typedef struct gba_t gba_t;
typedef struct arm7tdmi_t arm7tdmi_t;

#define BIOS_SIZE 0x4000
#define WRAM_BOARD_SIZE (1 << 18)
#define WRAM_CHIP_SIZE (1 << 15)

u8 readByte(arm7tdmi_t* cpu, u32 addr);
u16 readHalfWord(arm7tdmi_t* cpu, u32 addr);
u32 readWord(arm7tdmi_t* cpu, u32 addr);

void writeByte(arm7tdmi_t* cpu, u32 addr, u8 val);
void writeHalfWord(arm7tdmi_t* cpu, u32 addr, u16 val);
void writeWord(arm7tdmi_t* cpu, u32 addr, u32 val);

void loadBios(const char * filename, u8** bios);

#endif