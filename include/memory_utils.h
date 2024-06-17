#include "integer.h"

#define unlikely(x) __builtin_expect(!!(x), 0)
#define INLINE static inline __attribute__ ((always_inline))

INLINE u8 readIo8(arm7tdmi_t* cpu, u16 addr);
INLINE void writeIo8(arm7tdmi_t* cpu, u16 addr, u8 val);

#define GET_POINTERS \
gba_t* gba = (gba_t*)cpu->master; \
ppu_t* ppu = &gba->ppu; \
gamepak_t* gamepak = &gba->gamepak \

#define GET_ARRAY_PTR(type, name) \
((u ## type*)&name)

#define WRITE_VRAM_8 \
ppu->VRAM[addr] = val; \
ppu->VRAM[(addr & ~0b1) + 1] = val \

#define WRITE_VRAM_16 WRITE_VRAM_DEFAULT(16)
#define WRITE_VRAM_32 WRITE_VRAM_DEFAULT(32)
#define WRITE_VRAM_DEFAULT(type) \
*GET_ARRAY_PTR(type, ppu->VRAM[addr]) = val

#define READ_IO_8(cpu, addr) readIo8(cpu, addr)
#define READ_IO_16(cpu, addr) (readIo8(cpu, addr) | (readIo8(cpu, (addr) + 1) << 8))
#define READ_IO_32(cpu, addr) (READ_IO_16(cpu, addr) | (READ_IO_16(cpu, (addr) + 2) << 16))

#define WRITE_IO_8(cpu, addr, val) writeIo8(cpu, addr, val)
#define WRITE_IO_16(cpu, addr, val) writeIo8(cpu, addr, val); writeIo8(cpu, (addr) + 1, (val) >> 8)
#define WRITE_IO_32(cpu, addr, val) WRITE_IO_16(cpu, addr, val); WRITE_IO_16(cpu, (addr) + 2, (val) >> 16)

#define MEMORY_READ_SAVE_DATA_32
#define MEMORY_READ_SAVE_DATA_16
#define MEMORY_READ_SAVE_DATA_8 \
case 0xE: \
case 0xF: \
return (*gamepak->readByte)(gamepak, addr);

#define MEMORY_WRITE_SAVE_DATA_32
#define MEMORY_WRITE_SAVE_DATA_16
#define MEMORY_WRITE_SAVE_DATA_8 \
case 0xE: \
case 0xF: \
(*gamepak->writeByte)(gamepak, addr, val); \
return; \

#define MEMORY_TABLE_READ(type) \
GET_POINTERS; \
switch((addr >> 24) & 0xF){ \
    case 0x0: \
    case 0x1: \
    return *GET_ARRAY_PTR(type, gba->BIOS[addr & (BIOS_SIZE - 1)]); \
\
    case 0x2: \
    return *GET_ARRAY_PTR(type, gba->WRAM_BOARD[addr & 0x3FFFF]); \
\
    case 0x3: \
    return *GET_ARRAY_PTR(type, gba->WRAM_CHIP[addr & 0x7FFF]); \
\
    case 0x4: \
    return READ_IO_ ## type (cpu, addr); \
\
    case 0x5: \
    return *GET_ARRAY_PTR(type, ppu->PALETTE_RAM[addr & 0x3FF]); \
\
    case 0x6: \
    return *GET_ARRAY_PTR(type, ppu->VRAM[(addr - 0x6000000) % VRAM_SIZE]); \
\
    case 0x7: \
    return *GET_ARRAY_PTR(type, ppu->OAM[addr & 0x3FF]); \
\
    case 0x8: \
    case 0x9: \
    case 0xA: \
    case 0xB: \
    case 0xC: \
    case 0xD: \
    addr -= 0x08000000; \
    if(unlikely(addr >= gamepak->ROM_SIZE)) \
            return 0x00; \
    return *GET_ARRAY_PTR(type, gba->gamepak.ROM[addr]); \
\
    MEMORY_READ_SAVE_DATA_ ## type \
\
    default: \
    return 0x00; \
} \

#define MEMORY_TABLE_WRITE(type) \
GET_POINTERS; \
switch((addr >> 24) & 0xF){ \
    case 0x2: \
    *GET_ARRAY_PTR(type, gba->WRAM_BOARD[addr & 0x3FFFF]) = val; \
    return; \
\
    case 0x3: \
    *GET_ARRAY_PTR(type, gba->WRAM_CHIP[addr & 0x7FFF]) = val; \
    return; \
\
    case 0x4: \
    WRITE_IO_ ## type (cpu, addr, val); \
    return; \
\
    case 0x5: \
    *GET_ARRAY_PTR(type, ppu->PALETTE_RAM[addr & 0x3FF]) = val; \
    return; \
\
    case 0x6: \
    addr -= 0x6000000; \
    addr %= VRAM_SIZE; \
    WRITE_VRAM_ ## type ; \
    return; \
\
    case 0x7: \
    *GET_ARRAY_PTR(type, ppu->OAM[addr & 0x3FF]) = val; \
    return; \
\
    MEMORY_WRITE_SAVE_DATA_ ## type \
} \

u8 readIo8(arm7tdmi_t* cpu, u16 addr){
gba_t* gba = (gba_t*)cpu->master;
ppu_t* ppu = &gba->ppu;
switch(addr){
case 0x0:
return ((u8*)&ppu->DISPCNT)[0];
case 0x1:
return ((u8*)&ppu->DISPCNT)[1];
case 0x4:
composeDispstat(ppu);
return ((u8*)&ppu->DISPSTAT)[0];
case 0x5:
composeDispstat(ppu);
return ((u8*)&ppu->DISPSTAT)[1];
case 0x6:
return ((u8*)&ppu->VCOUNT)[0];
case 0x7:
return ((u8*)&ppu->VCOUNT)[1];
case 0x8:
return ((u8*)&ppu->BGCNT[0])[0];
case 0x9:
return ((u8*)&ppu->BGCNT[0])[1];
case 0xA:
return ((u8*)&ppu->BGCNT[1])[0];
case 0xB:
return ((u8*)&ppu->BGCNT[1])[1];
case 0xC:
return ((u8*)&ppu->BGCNT[2])[0];
case 0xD:
return ((u8*)&ppu->BGCNT[2])[1];
case 0xE:
return ((u8*)&ppu->BGCNT[3])[0];
case 0xF:
return ((u8*)&ppu->BGCNT[3])[1];
case 0x48:
return ((u8*)&ppu->WININ)[0];
case 0x49:
return ((u8*)&ppu->WININ)[1];
case 0x4A:
return ((u8*)&ppu->WINOUT)[0];
case 0x4B:
return ((u8*)&ppu->WINOUT)[1];
case 0x50:
return ((u8*)&ppu->BLDCNT)[0];
case 0x51:
return ((u8*)&ppu->BLDCNT)[1];
case 0x52:
return ((u8*)&ppu->BLDALPHA)[0];
case 0x53:
return ((u8*)&ppu->BLDALPHA)[1];
case 0x88:
return ((u8*)&gba->SOUNDBIAS)[0];
case 0x89:
return ((u8*)&gba->SOUNDBIAS)[1];
case 0xBA:
return ((u8*)&gba->DMACNT[0])[0];
case 0xBB:
return ((u8*)&gba->DMACNT[0])[1];
case 0xC6:
return ((u8*)&gba->DMACNT[1])[0];
case 0xC7:
return ((u8*)&gba->DMACNT[1])[1];
case 0xD2:
return ((u8*)&gba->DMACNT[2])[0];
case 0xD3:
return ((u8*)&gba->DMACNT[2])[1];
case 0xDE:
return ((u8*)&gba->DMACNT[3])[0];
case 0xDF:
return ((u8*)&gba->DMACNT[3])[1];
case 0x100:
return ((u8*)&gba->timers[0].counter)[0];
case 0x101:
return ((u8*)&gba->timers[0].counter)[1];
case 0x102:
return ((u8*)&gba->timers[0].TMCNT)[2];
case 0x103:
return ((u8*)&gba->timers[0].TMCNT)[3];
case 0x104:
return ((u8*)&gba->timers[1].counter)[0];
case 0x105:
return ((u8*)&gba->timers[1].counter)[1];
case 0x106:
return ((u8*)&gba->timers[1].TMCNT)[2];
case 0x107:
return ((u8*)&gba->timers[1].TMCNT)[3];
case 0x108:
return ((u8*)&gba->timers[2].counter)[0];
case 0x109:
return ((u8*)&gba->timers[2].counter)[1];
case 0x10A:
return ((u8*)&gba->timers[2].TMCNT)[2];
case 0x10B:
return ((u8*)&gba->timers[2].TMCNT)[3];
case 0x10C:
return ((u8*)&gba->timers[3].counter)[0];
case 0x10D:
return ((u8*)&gba->timers[3].counter)[1];
case 0x10E:
return ((u8*)&gba->timers[3].TMCNT)[2];
case 0x10F:
return ((u8*)&gba->timers[3].TMCNT)[3];
case 0x130:
return ((u8*)&gba->KEYINPUT)[0];
case 0x131:
return ((u8*)&gba->KEYINPUT)[1];
case 0x132:
return ((u8*)&gba->KEYCNT)[0];
case 0x133:
return ((u8*)&gba->KEYCNT)[1];
case 0x134:
return ((u8*)&gba->RCNT)[0];
case 0x135:
return ((u8*)&gba->RCNT)[1];
case 0x200:
return ((u8*)&gba->IE)[0];
case 0x201:
return ((u8*)&gba->IE)[1];
case 0x202:
return ((u8*)&gba->IF)[0];
case 0x203:
return ((u8*)&gba->IF)[1];
case 0x204:
return ((u8*)&gba->WAITCNT)[0];
case 0x205:
return ((u8*)&gba->WAITCNT)[1];
case 0x208:
return ((u8*)&gba->IME)[0];
case 0x209:
return ((u8*)&gba->IME)[1];
case 0x300:
return gba->POSTFLG;
default:
return 0x00;
};
}

void writeIo8(arm7tdmi_t* cpu, u16 addr, u8 val){
gba_t* gba = (gba_t*)cpu->master;
ppu_t* ppu = &gba->ppu;
switch(addr){
case 0x0:
((u8*)&ppu->DISPCNT)[0] = val;
return;
case 0x1:
((u8*)&ppu->DISPCNT)[1] = val;
return;
case 0x4:
((u8*)&ppu->DISPSTAT)[0] = val;
return;
case 0x5:
((u8*)&ppu->DISPSTAT)[1] = val;
return;
case 0x8:
((u8*)&ppu->BGCNT[0])[0] = val;
return;
case 0x9:
((u8*)&ppu->BGCNT[0])[1] = val;
return;
case 0xA:
((u8*)&ppu->BGCNT[1])[0] = val;
return;
case 0xB:
((u8*)&ppu->BGCNT[1])[1] = val;
return;
case 0xC:
((u8*)&ppu->BGCNT[2])[0] = val;
return;
case 0xD:
((u8*)&ppu->BGCNT[2])[1] = val;
return;
case 0xE:
((u8*)&ppu->BGCNT[3])[0] = val;
return;
case 0xF:
((u8*)&ppu->BGCNT[3])[1] = val;
return;
case 0x10:
((u8*)&ppu->BGHOFS[0])[0] = val;
return;
case 0x11:
((u8*)&ppu->BGHOFS[0])[1] = val;
return;
case 0x12:
((u8*)&ppu->BGVOFS[0])[0] = val;
return;
case 0x13:
((u8*)&ppu->BGVOFS[0])[1] = val;
return;
case 0x14:
((u8*)&ppu->BGHOFS[1])[0] = val;
return;
case 0x15:
((u8*)&ppu->BGHOFS[1])[1] = val;
return;
case 0x16:
((u8*)&ppu->BGVOFS[1])[0] = val;
return;
case 0x17:
((u8*)&ppu->BGVOFS[1])[1] = val;
return;
case 0x18:
((u8*)&ppu->BGHOFS[2])[0] = val;
return;
case 0x19:
((u8*)&ppu->BGHOFS[2])[1] = val;
return;
case 0x1A:
((u8*)&ppu->BGVOFS[2])[0] = val;
return;
case 0x1B:
((u8*)&ppu->BGVOFS[2])[1] = val;
return;
case 0x1C:
((u8*)&ppu->BGHOFS[3])[0] = val;
return;
case 0x1D:
((u8*)&ppu->BGHOFS[3])[1] = val;
return;
case 0x1E:
((u8*)&ppu->BGVOFS[3])[0] = val;
return;
case 0x1F:
((u8*)&ppu->BGVOFS[3])[1] = val;
return;
case 0x20:
((u8*)&ppu->BGP[0])[0] = val;
return;
case 0x21:
((u8*)&ppu->BGP[0])[1] = val;
return;
case 0x22:
((u8*)&ppu->BGP[1])[0] = val;
return;
case 0x23:
((u8*)&ppu->BGP[1])[1] = val;
return;
case 0x24:
((u8*)&ppu->BGP[2])[0] = val;
return;
case 0x25:
((u8*)&ppu->BGP[2])[1] = val;
return;
case 0x26:
((u8*)&ppu->BGP[3])[0] = val;
return;
case 0x27:
((u8*)&ppu->BGP[3])[1] = val;
return;
case 0x28:
((u8*)&ppu->BGX[0])[0] = val;
ppu->INTERNAL_BGX[0] = ppu->BGX[0];
return;
case 0x29:
((u8*)&ppu->BGX[0])[1] = val;
ppu->INTERNAL_BGX[0] = ppu->BGX[0];
return;
case 0x2A:
((u8*)&ppu->BGX[0])[2] = val;
ppu->INTERNAL_BGX[0] = ppu->BGX[0];
return;
case 0x2B:
((u8*)&ppu->BGX[0])[3] = val;
ppu->INTERNAL_BGX[0] = ppu->BGX[0];
return;
case 0x2C:
((u8*)&ppu->BGY[0])[0] = val;
ppu->INTERNAL_BGY[0] = ppu->BGY[0];
return;
case 0x2D:
((u8*)&ppu->BGY[0])[1] = val;
ppu->INTERNAL_BGY[0] = ppu->BGY[0];
return;
case 0x2E:
((u8*)&ppu->BGY[0])[2] = val;
ppu->INTERNAL_BGY[0] = ppu->BGY[0];
return;
case 0x2F:
((u8*)&ppu->BGY[0])[3] = val;
ppu->INTERNAL_BGY[0] = ppu->BGY[0];
return;
case 0x30:
((u8*)&ppu->BGP[4])[0] = val;
return;
case 0x31:
((u8*)&ppu->BGP[4])[1] = val;
return;
case 0x32:
((u8*)&ppu->BGP[5])[0] = val;
return;
case 0x33:
((u8*)&ppu->BGP[5])[1] = val;
return;
case 0x34:
((u8*)&ppu->BGP[6])[0] = val;
return;
case 0x35:
((u8*)&ppu->BGP[6])[1] = val;
return;
case 0x36:
((u8*)&ppu->BGP[7])[0] = val;
return;
case 0x37:
((u8*)&ppu->BGP[7])[1] = val;
return;
case 0x38:
((u8*)&ppu->BGX[1])[0] = val;
ppu->INTERNAL_BGX[1] = ppu->BGX[1];
return;
case 0x39:
((u8*)&ppu->BGX[1])[1] = val;
ppu->INTERNAL_BGX[1] = ppu->BGX[1];
return;
case 0x3A:
((u8*)&ppu->BGX[1])[2] = val;
ppu->INTERNAL_BGX[1] = ppu->BGX[1];
return;
case 0x3B:
((u8*)&ppu->BGX[1])[3] = val;
ppu->INTERNAL_BGX[1] = ppu->BGX[1];
return;
case 0x3C:
((u8*)&ppu->BGY[1])[0] = val;
ppu->INTERNAL_BGY[1] = ppu->BGY[1];
return;
case 0x3D:
((u8*)&ppu->BGY[1])[1] = val;
ppu->INTERNAL_BGY[1] = ppu->BGY[1];
return;
case 0x3E:
((u8*)&ppu->BGY[1])[2] = val;
ppu->INTERNAL_BGY[1] = ppu->BGY[1];
return;
case 0x3F:
((u8*)&ppu->BGY[1])[3] = val;
ppu->INTERNAL_BGY[1] = ppu->BGY[1];
return;
case 0x40:
((u8*)&ppu->WINH[0])[0] = val;
return;
case 0x41:
((u8*)&ppu->WINH[0])[1] = val;
return;
case 0x42:
((u8*)&ppu->WINH[1])[0] = val;
return;
case 0x43:
((u8*)&ppu->WINH[1])[1] = val;
return;
case 0x44:
((u8*)&ppu->WINV[0])[0] = val;
return;
case 0x45:
((u8*)&ppu->WINV[0])[1] = val;
return;
case 0x46:
((u8*)&ppu->WINV[1])[0] = val;
return;
case 0x47:
((u8*)&ppu->WINV[1])[1] = val;
return;
case 0x48:
((u8*)&ppu->WININ)[0] = val;
return;
case 0x49:
((u8*)&ppu->WININ)[1] = val;
return;
case 0x4A:
((u8*)&ppu->WINOUT)[0] = val;
return;
case 0x4B:
((u8*)&ppu->WINOUT)[1] = val;
return;
case 0x50:
((u8*)&ppu->BLDCNT)[0] = val;
return;
case 0x51:
((u8*)&ppu->BLDCNT)[1] = val;
return;
case 0x52:
((u8*)&ppu->BLDALPHA)[0] = val;
return;
case 0x53:
((u8*)&ppu->BLDALPHA)[1] = val;
return;
case 0x54:
((u8*)&ppu->BLDY)[0] = val;
return;
case 0x55:
((u8*)&ppu->BLDY)[1] = val;
return;
case 0x88:
((u8*)&gba->SOUNDBIAS)[0] = val;
return;
case 0x89:
((u8*)&gba->SOUNDBIAS)[1] = val;
return;
case 0xB0:
((u8*)&gba->DMASAD[0])[0] = val;
return;
case 0xB1:
((u8*)&gba->DMASAD[0])[1] = val;
return;
case 0xB2:
((u8*)&gba->DMASAD[0])[2] = val;
return;
case 0xB3:
((u8*)&gba->DMASAD[0])[3] = val;
return;
case 0xB4:
((u8*)&gba->DMADAD[0])[0] = val;
return;
case 0xB5:
((u8*)&gba->DMADAD[0])[1] = val;
return;
case 0xB6:
((u8*)&gba->DMADAD[0])[2] = val;
return;
case 0xB7:
((u8*)&gba->DMADAD[0])[3] = val;
return;
case 0xB8:
((u8*)&gba->DMACNT[0])[0] = val;
if(gba->DMACNT[0] >> 31)
triggerDma(gba, 0);
else
gba->dma_enabled[0] = false;
return;
case 0xB9:
((u8*)&gba->DMACNT[0])[1] = val;
if(gba->DMACNT[0] >> 31)
triggerDma(gba, 0);
else
gba->dma_enabled[0] = false;
return;
case 0xBA:
((u8*)&gba->DMACNT[0])[2] = val;
if(gba->DMACNT[0] >> 31)
triggerDma(gba, 0);
else
gba->dma_enabled[0] = false;
return;
case 0xBB:
((u8*)&gba->DMACNT[0])[3] = val;
if(gba->DMACNT[0] >> 31)
triggerDma(gba, 0);
else
gba->dma_enabled[0] = false;
return;
case 0xBC:
((u8*)&gba->DMASAD[1])[0] = val;
return;
case 0xBD:
((u8*)&gba->DMASAD[1])[1] = val;
return;
case 0xBE:
((u8*)&gba->DMASAD[1])[2] = val;
return;
case 0xBF:
((u8*)&gba->DMASAD[1])[3] = val;
return;
case 0xC0:
((u8*)&gba->DMADAD[1])[0] = val;
return;
case 0xC1:
((u8*)&gba->DMADAD[1])[1] = val;
return;
case 0xC2:
((u8*)&gba->DMADAD[1])[2] = val;
return;
case 0xC3:
((u8*)&gba->DMADAD[1])[3] = val;
return;
case 0xC4:
((u8*)&gba->DMACNT[1])[0] = val;
if(gba->DMACNT[1] >> 31)
triggerDma(gba, 1);
else
gba->dma_enabled[1] = false;
return;
case 0xC5:
((u8*)&gba->DMACNT[1])[1] = val;
if(gba->DMACNT[1] >> 31)
triggerDma(gba, 1);
else
gba->dma_enabled[1] = false;
return;
case 0xC6:
((u8*)&gba->DMACNT[1])[2] = val;
if(gba->DMACNT[1] >> 31)
triggerDma(gba, 1);
else
gba->dma_enabled[1] = false;
return;
case 0xC7:
((u8*)&gba->DMACNT[1])[3] = val;
if(gba->DMACNT[1] >> 31)
triggerDma(gba, 1);
else
gba->dma_enabled[1] = false;
return;
case 0xC8:
((u8*)&gba->DMASAD[2])[0] = val;
return;
case 0xC9:
((u8*)&gba->DMASAD[2])[1] = val;
return;
case 0xCA:
((u8*)&gba->DMASAD[2])[2] = val;
return;
case 0xCB:
((u8*)&gba->DMASAD[2])[3] = val;
return;
case 0xCC:
((u8*)&gba->DMADAD[2])[0] = val;
return;
case 0xCD:
((u8*)&gba->DMADAD[2])[1] = val;
return;
case 0xCE:
((u8*)&gba->DMADAD[2])[2] = val;
return;
case 0xCF:
((u8*)&gba->DMADAD[2])[3] = val;
return;
case 0xD0:
((u8*)&gba->DMACNT[2])[0] = val;
if(gba->DMACNT[2] >> 31)
triggerDma(gba, 2);
else
gba->dma_enabled[2] = false;
return;
case 0xD1:
((u8*)&gba->DMACNT[2])[1] = val;
if(gba->DMACNT[2] >> 31)
triggerDma(gba, 2);
else
gba->dma_enabled[2] = false;
return;
case 0xD2:
((u8*)&gba->DMACNT[2])[2] = val;
if(gba->DMACNT[2] >> 31)
triggerDma(gba, 2);
else
gba->dma_enabled[2] = false;
return;
case 0xD3:
((u8*)&gba->DMACNT[2])[3] = val;
if(gba->DMACNT[2] >> 31)
triggerDma(gba, 2);
else
gba->dma_enabled[2] = false;
return;
case 0xD4:
((u8*)&gba->DMASAD[3])[0] = val;
return;
case 0xD5:
((u8*)&gba->DMASAD[3])[1] = val;
return;
case 0xD6:
((u8*)&gba->DMASAD[3])[2] = val;
return;
case 0xD7:
((u8*)&gba->DMASAD[3])[3] = val;
return;
case 0xD8:
((u8*)&gba->DMADAD[3])[0] = val;
return;
case 0xD9:
((u8*)&gba->DMADAD[3])[1] = val;
return;
case 0xDA:
((u8*)&gba->DMADAD[3])[2] = val;
return;
case 0xDB:
((u8*)&gba->DMADAD[3])[3] = val;
return;
case 0xDC:
((u8*)&gba->DMACNT[3])[0] = val;
if(gba->DMACNT[3] >> 31)
triggerDma(gba, 3);
else
gba->dma_enabled[3] = false;
return;
case 0xDD:
((u8*)&gba->DMACNT[3])[1] = val;
if(gba->DMACNT[3] >> 31)
triggerDma(gba, 3);
else
gba->dma_enabled[3] = false;
return;
case 0xDE:
((u8*)&gba->DMACNT[3])[2] = val;
if(gba->DMACNT[3] >> 31)
triggerDma(gba, 3);
else
gba->dma_enabled[3] = false;
return;
case 0xDF:
((u8*)&gba->DMACNT[3])[3] = val;
if(gba->DMACNT[3] >> 31)
triggerDma(gba, 3);
else
gba->dma_enabled[3] = false;
return;
case 0x100:
{
timer_t* timers = gba->timers;
u32 old_TMCNT = timers[0].TMCNT;
((u8*)&timers[0].TMCNT)[0] = val;
if(!((old_TMCNT >> 16) & 0x80) && ((timers[0].TMCNT >> 16) & 0x80))
triggerTimer(&timers[0]);
}
return;
case 0x101:
{
timer_t* timers = gba->timers;
u32 old_TMCNT = timers[0].TMCNT;
((u8*)&timers[0].TMCNT)[1] = val;
if(!((old_TMCNT >> 16) & 0x80) && ((timers[0].TMCNT >> 16) & 0x80))
triggerTimer(&timers[0]);
}
return;
case 0x102:
{
timer_t* timers = gba->timers;
u32 old_TMCNT = timers[0].TMCNT;
((u8*)&timers[0].TMCNT)[2] = val;
if(!((old_TMCNT >> 16) & 0x80) && ((timers[0].TMCNT >> 16) & 0x80))
triggerTimer(&timers[0]);
}
return;
case 0x103:
{
timer_t* timers = gba->timers;
u32 old_TMCNT = timers[0].TMCNT;
((u8*)&timers[0].TMCNT)[3] = val;
if(!((old_TMCNT >> 16) & 0x80) && ((timers[0].TMCNT >> 16) & 0x80))
triggerTimer(&timers[0]);
}
return;
case 0x104:
{
timer_t* timers = gba->timers;
u32 old_TMCNT = timers[1].TMCNT;
((u8*)&timers[1].TMCNT)[0] = val;
if(!((old_TMCNT >> 16) & 0x80) && ((timers[1].TMCNT >> 16) & 0x80))
triggerTimer(&timers[1]);
}
return;
case 0x105:
{
timer_t* timers = gba->timers;
u32 old_TMCNT = timers[1].TMCNT;
((u8*)&timers[1].TMCNT)[1] = val;
if(!((old_TMCNT >> 16) & 0x80) && ((timers[1].TMCNT >> 16) & 0x80))
triggerTimer(&timers[1]);
}
return;
case 0x106:
{
timer_t* timers = gba->timers;
u32 old_TMCNT = timers[1].TMCNT;
((u8*)&timers[1].TMCNT)[2] = val;
if(!((old_TMCNT >> 16) & 0x80) && ((timers[1].TMCNT >> 16) & 0x80))
triggerTimer(&timers[1]);
}
return;
case 0x107:
{
timer_t* timers = gba->timers;
u32 old_TMCNT = timers[1].TMCNT;
((u8*)&timers[1].TMCNT)[3] = val;
if(!((old_TMCNT >> 16) & 0x80) && ((timers[1].TMCNT >> 16) & 0x80))
triggerTimer(&timers[1]);
}
return;
case 0x108:
{
timer_t* timers = gba->timers;
u32 old_TMCNT = timers[2].TMCNT;
((u8*)&timers[2].TMCNT)[0] = val;
if(!((old_TMCNT >> 16) & 0x80) && ((timers[2].TMCNT >> 16) & 0x80))
triggerTimer(&timers[2]);
}
return;
case 0x109:
{
timer_t* timers = gba->timers;
u32 old_TMCNT = timers[2].TMCNT;
((u8*)&timers[2].TMCNT)[1] = val;
if(!((old_TMCNT >> 16) & 0x80) && ((timers[2].TMCNT >> 16) & 0x80))
triggerTimer(&timers[2]);
}
return;
case 0x10A:
{
timer_t* timers = gba->timers;
u32 old_TMCNT = timers[2].TMCNT;
((u8*)&timers[2].TMCNT)[2] = val;
if(!((old_TMCNT >> 16) & 0x80) && ((timers[2].TMCNT >> 16) & 0x80))
triggerTimer(&timers[2]);
}
return;
case 0x10B:
{
timer_t* timers = gba->timers;
u32 old_TMCNT = timers[2].TMCNT;
((u8*)&timers[2].TMCNT)[3] = val;
if(!((old_TMCNT >> 16) & 0x80) && ((timers[2].TMCNT >> 16) & 0x80))
triggerTimer(&timers[2]);
}
return;
case 0x10C:
{
timer_t* timers = gba->timers;
u32 old_TMCNT = timers[3].TMCNT;
((u8*)&timers[3].TMCNT)[0] = val;
if(!((old_TMCNT >> 16) & 0x80) && ((timers[3].TMCNT >> 16) & 0x80))
triggerTimer(&timers[3]);
}
return;
case 0x10D:
{
timer_t* timers = gba->timers;
u32 old_TMCNT = timers[3].TMCNT;
((u8*)&timers[3].TMCNT)[1] = val;
if(!((old_TMCNT >> 16) & 0x80) && ((timers[3].TMCNT >> 16) & 0x80))
triggerTimer(&timers[3]);
}
return;
case 0x10E:
{
timer_t* timers = gba->timers;
u32 old_TMCNT = timers[3].TMCNT;
((u8*)&timers[3].TMCNT)[2] = val;
if(!((old_TMCNT >> 16) & 0x80) && ((timers[3].TMCNT >> 16) & 0x80))
triggerTimer(&timers[3]);
}
return;
case 0x10F:
{
timer_t* timers = gba->timers;
u32 old_TMCNT = timers[3].TMCNT;
((u8*)&timers[3].TMCNT)[3] = val;
if(!((old_TMCNT >> 16) & 0x80) && ((timers[3].TMCNT >> 16) & 0x80))
triggerTimer(&timers[3]);
}
return;
case 0x134:
((u8*)&gba->RCNT)[0] = val;
return;
case 0x135:
((u8*)&gba->RCNT)[1] = val;
return;
case 0x200:
((u8*)&gba->IE)[0] = val;
checkInterrupts(gba);
return;
case 0x201:
((u8*)&gba->IE)[1] = val;
checkInterrupts(gba);
return;
case 0x202:
((u8*)&gba->IF)[0] &= ~(val);
return;
case 0x203:
((u8*)&gba->IF)[1] &= ~(val);
return;
case 0x204:
((u8*)&gba->WAITCNT)[0] = val;
return;
case 0x205:
((u8*)&gba->WAITCNT)[1] = val;
return;
case 0x208:
((u8*)&gba->IME)[0] = val;
return;
case 0x209:
((u8*)&gba->IME)[1] = val;
return;
case 0x300:
gba->POSTFLG = val;
return;
case 0x301:
gba->HALTCNT = true;
return;
default:
return;
};
}