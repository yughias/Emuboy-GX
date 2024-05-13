#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "integer.h"

#define BIOS_SIZE 0x4000

extern u8 WRAM_BOARD[1 << 18];
extern u8 WRAM_CHIP[1 << 15];

extern u8 PALETTE_RAM[1 << 10];
extern u8 VRAM[0x18000];
extern u8 OAM[1 << 10];

extern u8 SRAM[1 << 16];

extern u16 DISPCNT;
extern u16 DISPSTAT;
extern u16 VCOUNT;

extern u16 KEYINPUT;
extern u16 KEYCNT;

extern u16 BGCNT[4];
extern u16 BGHOFS[4];
extern u16 BGVOFS[4];

extern u32 BGX[2];
extern u32 BGY[2];
extern u32 INTERNAL_BGX[2];
extern u32 INTERNAL_BGY[2];
extern u16 BGP[2*4];

extern u8* BIOS;
extern u8* ROM;
extern size_t ROM_SIZE;

extern u32 DMASAD[4];
extern u32 DMADAD[4];
extern u32 DMACNT[4];

extern u16 WINH[2];
extern u16 WINV[2];
extern u16 WININ;
extern u16 WINOUT;

extern u16 BLDCNT;
extern u16 BLDALPHA;
extern u16 BLDY;     

extern u16 IE;
extern u16 IF;
extern u16 IME;

extern u16 RCNT;
extern u8 POSTFLG;
extern u16 WAITCNT;
extern u16 SOUNDBIAS;

extern bool HALTCNT;

void writeByte(u32 addr, u8 val);
u8 readByte(u32 addr);

void loadBios(const char * filename);
void loadRom(const char* filename);

#endif