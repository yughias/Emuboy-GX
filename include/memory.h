#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "integer.h"

typedef struct gba_t gba_t;
typedef struct arm7tdmi_t arm7tdmi_t;

#define BIOS_SIZE 0x4000

extern u8 PALETTE_RAM[1 << 10];
extern u8 VRAM[0x18000];
extern u8 OAM[1 << 10];

extern u16 DISPCNT;
extern u16 DISPSTAT;
extern u16 VCOUNT;

extern u16 BGCNT[4];
extern u16 BGHOFS[4];
extern u16 BGVOFS[4];

extern u32 BGX[2];
extern u32 BGY[2];
extern u32 INTERNAL_BGX[2];
extern u32 INTERNAL_BGY[2];
extern u16 BGP[2*4];

extern u16 WINH[2];
extern u16 WINV[2];
extern u16 WININ;
extern u16 WINOUT;

extern u16 BLDCNT;
extern u16 BLDALPHA;
extern u16 BLDY;     

void writeByte(arm7tdmi_t* cpu, u32 addr, u8 val);
u8 readByte(arm7tdmi_t* cpu, u32 addr);

void loadBios(const char * filename, u8** bios);
size_t loadRom(const char* filename, u8** rom);

#endif