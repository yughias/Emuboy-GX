#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "integer.h"

typedef struct gba_t gba_t;
typedef struct arm7tdmi_t arm7tdmi_t;
typedef struct gamepak_t gamepak_t;

#define BIOS_SIZE 0x4000
#define EWRAM_SIZE (1 << 18)
#define IWRAM_SIZE (1 << 15)

typedef struct bios_t {
    u8* data;
    u32 last_fetched;
} bios_t;

u8 readByte(arm7tdmi_t* cpu, u32 addr, bool seq);
u16 readHalfWord(arm7tdmi_t* cpu, u32 addr, bool seq);
u32 readWord(arm7tdmi_t* cpu, u32 addr, bool seq);

void writeByte(arm7tdmi_t* cpu, u32 addr, u8 val, bool seq);
void writeHalfWord(arm7tdmi_t* cpu, u32 addr, u16 val, bool seq);
void writeWord(arm7tdmi_t* cpu, u32 addr, u32 val, bool seq);

void loadBios(const char * filename, u8** bios);

u16 readHalfWordWithPrefetcher(arm7tdmi_t* cpu, gamepak_t* gamepak, u32 addr, bool seq);
u32 readWordWithPrefetcher(arm7tdmi_t* cpu, gamepak_t* gamepak, u32 addr, bool seq);

#endif