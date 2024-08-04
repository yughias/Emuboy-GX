#include "integer.h"

#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#define INLINE static inline __attribute__ ((always_inline))

#define THUMB_OPENBUS(idx1, idx2) (cpu->pipeline_opcode[idx1] & 0xFFFF) | (cpu->pipeline_opcode[idx2] << 16)

INLINE u32 readOpenBus(arm7tdmi_t* cpu){
    if(cpu->thumb_mode) {
        switch((cpu->r[15] >> 24) & 0xFF){
            // MAIN RAM | PALETTE RAM | VRAM | ROM
            case 0x2: case 0x5: case 0x6:
            case 0x8: case 0x9: case 0xA: 
            case 0xB: case 0xC: case 0xD: 
            return THUMB_OPENBUS(1, 1);

            // BIOS | OAM
            case 0x0: case 0x7:
            return THUMB_OPENBUS(0, 1);

            // OTHERWISE
            default:
            return THUMB_OPENBUS(1, 0);
        } 
    }
    return cpu->pipeline_opcode[1]; 
}

#include "readIo.h"
#include "writeIo.h"

#define DEFINE_READ_FUNC(name, n_bits, mask) \
u ## n_bits read ## name (arm7tdmi_t* cpu, u32 not_aligned_addr, bool seq){ \
    u32 addr = not_aligned_addr & ~mask; \
    MEMORY_TABLE_READ(n_bits); \
}

#define DEFINE_WRITE_FUNC(name, n_bits, mask) \
void write ## name (arm7tdmi_t* cpu, u32 not_aligned_addr, u ## n_bits val, bool seq){ \
    u32 addr = not_aligned_addr & ~mask; \
    MEMORY_TABLE_WRITE(n_bits); \
}

#define GET_POINTERS \
gba_t* gba = (gba_t*)cpu->master; \
ppu_t* ppu = &gba->ppu; \
gamepak_t* gamepak = &gba->gamepak; \
bios_t* bios = &gba->bios

#define EXTRA_CYCLE_32 cpu->cycles += 1
#define EXTRA_CYCLE_16
#define EXTRA_CYCLE_8

#define GET_ARRAY_PTR(n_bits, name) \
((u ## n_bits*)&name)

#define MASK_VRAM_ADDRESS(x) \
x &= (1 << 17) - 1; \
if(x >= (1 << 16)) x = (x & 0x7FFF) | (1 << 16)

#define WRITE_VRAM_DEFAULT(n_bits) \
*GET_ARRAY_PTR(n_bits, ppu->VRAM[addr]) = val

#define WRITE_VRAM_16 WRITE_VRAM_DEFAULT(16)
#define WRITE_VRAM_32 WRITE_VRAM_DEFAULT(32)
#define WRITE_VRAM_8 \
if(addr < 0x14000) *GET_ARRAY_PTR(16, ppu->VRAM[addr & (~0b1)]) = val | (val << 8) \

#define WRITE_PALETTE_RAM_DEFAULT(n_bits) \
*GET_ARRAY_PTR(n_bits, ppu->PALETTE_RAM[addr & 0x3FF]) = val

#define WRITE_PALETTE_RAM_32 WRITE_PALETTE_RAM_DEFAULT(32)
#define WRITE_PALETTE_RAM_16 WRITE_PALETTE_RAM_DEFAULT(16)
#define WRITE_PALETTE_RAM_8 \
*GET_ARRAY_PTR(16, ppu->PALETTE_RAM[addr & 0x3FE]) = val | (val << 8) \

#define WRITE_OAM_DEFAULT(n_bits) \
*GET_ARRAY_PTR(n_bits, ppu->OAM[addr & 0x3FF]) = val

#define WRITE_OAM_32 WRITE_OAM_DEFAULT(32)
#define WRITE_OAM_16 WRITE_OAM_DEFAULT(16)
#define WRITE_OAM_8

#define READ_IO_8(cpu, addr) readIo8(cpu, addr)
#define READ_IO_16(cpu, addr) (readIo8(cpu, addr) | (readIo8(cpu, (addr) + 1) << 8))
#define READ_IO_32(cpu, addr) (READ_IO_16(cpu, addr) | (READ_IO_16(cpu, (addr) + 2) << 16))

#define WRITE_IO_8(cpu, addr, val) writeIo8(cpu, addr, val)
#define WRITE_IO_16(cpu, addr, val) writeIo8(cpu, addr, val); writeIo8(cpu, (addr) + 1, (val) >> 8)
#define WRITE_IO_32(cpu, addr, val) WRITE_IO_16(cpu, addr, val); WRITE_IO_16(cpu, (addr) + 2, (val) >> 16)

#define EWRAM_TIMING_32 cpu->cycles += 5;
#define EWRAM_TIMING_16 EWRAM_TIMING_DEFAULT
#define EWRAM_TIMING_8 EWRAM_TIMING_DEFAULT
#define EWRAM_TIMING_DEFAULT cpu->cycles += 2;

#define ROM_OOB_8(x) (((x) >> 1) & 0xFF)
#define ROM_OOB_16(x) (((x) >> 1) & 0xFFFF)
#define ROM_OOB_32(x) (ROM_OOB_16(addr + 2) << 16) | ROM_OOB_16(addr)

#define READ_SRAM_32 { u8 byte = readSram(gamepak, not_aligned_addr); return byte | (byte << 8) | (byte << 16) | (byte << 24); }
#define READ_SRAM_16 { u8 byte = readSram(gamepak, not_aligned_addr); return byte | (byte << 8); }
#define READ_SRAM_8 return readSram(gamepak, not_aligned_addr)

#define WRITE_SRAM_32 writeSram(gamepak, not_aligned_addr, val); writeSram(gamepak, not_aligned_addr+1, val); writeSram(gamepak, not_aligned_addr+2, val);  writeSram(gamepak, not_aligned_addr+3, val)  
#define WRITE_SRAM_16 writeSram(gamepak, not_aligned_addr, val); writeSram(gamepak, not_aligned_addr+1, val) 
#define WRITE_SRAM_8 writeSram(gamepak, not_aligned_addr, val)

#define READ_ROM(n_bits) \
if(unlikely(addr >= gamepak->ROM_SIZE)) \
            return ROM_OOB_ ## n_bits (addr); \
return *GET_ARRAY_PTR(n_bits, gba->gamepak.ROM[addr]) 

#define DEFAULT_WAIT_STATE(zone, seq) cpu->cycles += gamepak->waitstates[zone][seq]

#define WAIT_STATE_32(zone, seq) DEFAULT_WAIT_STATE(zone, seq); cpu->cycles += 1; DEFAULT_WAIT_STATE(zone, true)
#define WAIT_STATE_16(zone, seq) DEFAULT_WAIT_STATE(zone, seq)
#define WAIT_STATE_8(zone, seq) DEFAULT_WAIT_STATE(zone, seq)

#define FORCE_N_CYCLE if(!(addr & 0x1FFFF)) seq = false

// add open bus for bios to fix fzero climax
// it sufficient to return 0xFF
// also konami collector relies on this!
// metal slug depends on openbus, returning 0xFF
// make things even worse!
// kirby breaks on level intro with 0xFF open bug fix!

#define MEMORY_TABLE_READ(n_bits) \
GET_POINTERS; \
switch((addr >> 24) & 0xFF){ \
    case 0x0: \
    if(likely(addr < BIOS_SIZE)){ \
        if((cpu->r[15] >> 24) & 0xFF) \
            return bios->last_fetched; \
        bios->last_fetched = *GET_ARRAY_PTR(32, bios->data[addr & (BIOS_SIZE - 1)]); \
        return bios->last_fetched; \
    } \
    return readOpenBus(cpu); \
\
    case 0x2: \
    EWRAM_TIMING_ ## n_bits \
    return *GET_ARRAY_PTR(n_bits, gba->EWRAM[addr & 0x3FFFF]); \
\
    case 0x3: \
    return *GET_ARRAY_PTR(n_bits, gba->IWRAM[addr & 0x7FFF]); \
\
    case 0x4: \
    addr -= 0x4000000; \
    return READ_IO_ ## n_bits (cpu, addr); \
\
    case 0x5: \
    EXTRA_CYCLE_ ## n_bits ; \
    return *GET_ARRAY_PTR(n_bits, ppu->PALETTE_RAM[addr & 0x3FF]); \
\
    case 0x6: \
    EXTRA_CYCLE_ ## n_bits ; \
    MASK_VRAM_ADDRESS(addr); \
    return *GET_ARRAY_PTR(n_bits, ppu->VRAM[addr]); \
\
    case 0x7: \
    return *GET_ARRAY_PTR(n_bits, ppu->OAM[addr & 0x3FF]); \
\
    case 0x8: \
    case 0x9: \
    FORCE_N_CYCLE; \
    WAIT_STATE_ ## n_bits (0, seq); \
    addr -= 0x08000000; \
    READ_ROM(n_bits); \
\
    case 0xA: \
    case 0xB: \
    FORCE_N_CYCLE; \
    WAIT_STATE_ ## n_bits (1, seq); \
    addr -= 0x0A000000; \
    READ_ROM(n_bits); \
\
    case 0xC: \
    FORCE_N_CYCLE; \
    WAIT_STATE_ ## n_bits (2, seq); \
    addr -= 0x0C000000; \
    READ_ROM(n_bits); \
\
    case 0xD: \
    FORCE_N_CYCLE; \
    WAIT_STATE_ ## n_bits (2, seq); \
    addr -= 0x0C000000; \
    switch(gamepak->type){ \
        case GAMEPAK_EEPROM: \
        return readEeprom(gamepak); \
\
        default: \
        READ_ROM(n_bits); \
    } \
\
    case 0xE: \
    switch(gamepak->type){ \
        case GAMEPAK_SRAM: \
        READ_SRAM_ ## n_bits ; \
\
        case GAMEPAK_FLASH: \
        return readFlash(gamepak, addr); \
\
        default: \
        return readOpenBus(cpu); \
    } \
\
    default: \
    return readOpenBus(cpu); \
}

#define MEMORY_TABLE_WRITE(n_bits) \
GET_POINTERS; \
switch((addr >> 24) & 0xFF){ \
    case 0x2: \
    EWRAM_TIMING_ ## n_bits \
    *GET_ARRAY_PTR(n_bits, gba->EWRAM[addr & 0x3FFFF]) = val; \
    return; \
\
    case 0x3: \
    *GET_ARRAY_PTR(n_bits, gba->IWRAM[addr & 0x7FFF]) = val; \
    return; \
\
    case 0x4: \
    addr -= 0x4000000; \
    WRITE_IO_ ## n_bits (cpu, addr, val); \
    return; \
\
    case 0x5: \
    EXTRA_CYCLE_ ## n_bits ; \
    WRITE_PALETTE_RAM_ ## n_bits; \
    return; \
\
    case 0x6: \
    EXTRA_CYCLE_ ## n_bits; \
    MASK_VRAM_ADDRESS(addr); \
    WRITE_VRAM_ ## n_bits ; \
    return; \
\
    case 0x7: \
    WRITE_OAM_ ## n_bits ; \
    return; \
\
    case 0xD: \
    switch(gamepak->type){ \
        case GAMEPAK_EEPROM: \
        writeEeprom(gamepak, val); \
        return; \
\
        default: \
        return; \
    } \
\
    case 0xE: \
    case 0xF: \
    switch(gamepak->type){ \
        case GAMEPAK_SRAM: \
        WRITE_SRAM_ ## n_bits ;  \
        return; \
\
        case GAMEPAK_FLASH: \
        writeFlash(gamepak, addr, val); \
        return; \
\
        default: \
        return; \
    } \
}
