#include "integer.h"

#define unlikely(x) __builtin_expect(!!(x), 0)
#define INLINE static inline __attribute__ ((always_inline))

#include "readIo.h"
#include "writeIo.h"

#define GET_POINTERS \
gba_t* gba = (gba_t*)cpu->master; \
ppu_t* ppu = &gba->ppu; \
gamepak_t* gamepak = &gba->gamepak; \
bios_t* bios = &gba->bios;

#define GET_ARRAY_PTR(type, name) \
((u ## type*)&name)

#define WRITE_VRAM_8 \
*GET_ARRAY_PTR(16, ppu->VRAM[addr & (~0b1)]) = val | (val << 8) \

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

#define MEMORY_READ_SAVE_DATA_ZONE(zone) \
case 0x ## zone: \
return (*gamepak->readByte_ ## zone)(gamepak, addr)

#define MEMORY_WRITE_SAVE_DATA_ZONE(zone) \
case 0x ## zone: \
(*gamepak->writeByte_ ## zone)(gamepak, addr, val); return

#define MEMORY_READ_SAVE_DATA_32 MEMORY_READ_SAVE_DATA_ZONE(D)
#define MEMORY_READ_SAVE_DATA_16 MEMORY_READ_SAVE_DATA_ZONE(D)
#define MEMORY_READ_SAVE_DATA_8 \
MEMORY_READ_SAVE_DATA_ZONE(D); \
MEMORY_READ_SAVE_DATA_ZONE(E)

#define MEMORY_WRITE_SAVE_DATA_32 MEMORY_WRITE_SAVE_DATA_ZONE(D)
#define MEMORY_WRITE_SAVE_DATA_16 MEMORY_WRITE_SAVE_DATA_ZONE(D)
#define MEMORY_WRITE_SAVE_DATA_8 \
MEMORY_WRITE_SAVE_DATA_ZONE(D); \
MEMORY_WRITE_SAVE_DATA_ZONE(E)

#define WRAM_BOARD_TIMING_32 cpu->cycles += 5;
#define WRAM_BOARD_TIMING_16 WRAM_BOARD_TIMING_DEFAULT
#define WRAM_BOARD_TIMING_8 WRAM_BOARD_TIMING_DEFAULT
#define WRAM_BOARD_TIMING_DEFAULT cpu->cycles += 2;

// add open bus for bios to fix fzero climax
// it sufficient to return 0xFF
// also konami collector relies on this!
// metal slug depends on openbus, returning 0xFF
// make things even worse!
// kirby breaks on level intro with 0xFF open bug fix!

#define MEMORY_TABLE_READ(type) \
GET_POINTERS; \
switch((addr >> 24) & 0xF){ \
    case 0x0: \
    case 0x1: \
    if((cpu->r[15] >> 24) & 0xF) \
        return bios->last_fetched; \
    bios->last_fetched = *GET_ARRAY_PTR(32, bios->data[addr & (BIOS_SIZE - 1)]); \
    return bios->last_fetched; \
\
    case 0x2: \
    WRAM_BOARD_TIMING_ ## type \
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
    addr -= 0x08000000; \
    if(unlikely(addr >= gamepak->ROM_SIZE)) \
            return 0x00; \
    return *GET_ARRAY_PTR(type, gba->gamepak.ROM[addr]); \
\
    MEMORY_READ_SAVE_DATA_ ## type ; \
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
    MEMORY_WRITE_SAVE_DATA_ ## type ; \
}
