#include "gba.h"
#include "arm7tdmi/arm7tdmi.h"

#include <stdio.h>
#include <stdlib.h>

u8 readIo8(arm7tdmi_t* cpu, u32 addr);
u16 readIo16(arm7tdmi_t* cpu, u32 addr);
u32 readIo32(arm7tdmi_t* cpu, u32 addr);

void writeIo8(arm7tdmi_t* cpu, u32 addr, u8 val);
void writeIo16(arm7tdmi_t* cpu, u32 addr, u16 val);
void writeIo32(arm7tdmi_t* cpu, u32 addr, u32 val);

#define GET_POINTERS \
gba_t* gba = (gba_t*)cpu->master; \
ppu_t* ppu = &gba->ppu; \

#define WRITE_VRAM_8 \
ppu->VRAM[addr] = val; \
ppu->VRAM[(addr & ~0b1) + 1] = val; \

#define WRITE_VRAM_16 WRITE_VRAM_NORMAL(16)
#define WRITE_VRAM_32 WRITE_VRAM_NORMAL(32)
#define WRITE_VRAM_NORMAL(type) \
*((u ## type*)&ppu->VRAM[addr]) = val;

#define MEMORY_TABLE_READ(type) \
GET_POINTERS \
switch((addr >> 24) & 0xF){ \
    case 0x0: \
    case 0x1: \
    return *((u ## type*)&gba->BIOS[addr & (BIOS_SIZE - 1)]); \
\
    case 0x2: \
    return *((u ## type*)&gba->WRAM_BOARD[addr & 0x3FFFF]); \
\
    case 0x3: \
    return *((u ## type*)&gba->WRAM_CHIP[addr & 0x7FFF]); \
\
    case 0x4: \
    return readIo ## type (cpu, addr); \
\
    case 0x5: \
    return *((u ## type*)&ppu->PALETTE_RAM[addr & 0x3FF]); \
\
    case 0x6: \
    return *((u ## type*)&ppu->VRAM[(addr - 0x6000000) % VRAM_SIZE]); \
\
    case 0x7: \
    return *((u ## type*)&ppu->OAM[addr & 0x3FF]); \
\
    case 0x8: \
    case 0x9: \
    case 0xA: \
    case 0xB: \
    case 0xC: \
    case 0xD: \
    addr -= 0x08000000; \
    if(addr >= gba->ROM_SIZE) \
            return 0x00; \
    return *((u ## type*)&gba->ROM[addr]); \
\
    case 0xE: \
    case 0xF: \
    if(addr == 0x0E000000) \
        return 0x62; \
\
    if(addr == 0x0E000001) \
        return 0x13; \
\
    if(addr >= 0xE000000 && addr < 0xE010000) \
        return *((u ## type*)&gba->SRAM[(addr - 0xE000000) & 0xFFFF]); \
    return 0x00; \
\
    default: \
    return 0x00; \
} \

#define MEMORY_TABLE_WRITE(type) \
GET_POINTERS \
switch((addr >> 24) & 0xF){ \
    case 0x2: \
    *((u ## type*)&gba->WRAM_BOARD[addr & 0x3FFFF]) = val; \
    return; \
\
    case 0x3: \
    *((u ## type*)&gba->WRAM_CHIP[addr & 0x7FFF]) = val; \
    return; \
\
    case 0x4: \
    writeIo ## type (cpu, addr, val); \
    return; \
\
    case 0x5: \
    *((u ## type*)&ppu->PALETTE_RAM[addr & 0x3FF]) = val; \
    return; \
\
    case 0x6: \
    addr -= 0x6000000; \
    addr %= VRAM_SIZE; \
    WRITE_VRAM_ ## type \
    return; \
\
    case 0x7: \
    *((u ## type*)&ppu->OAM[addr & 0x3FF]) = val; \
    return; \
\
    case 0xE: \
    case 0xF: \
    if(addr >= 0xE000000 && addr < 0xE010000) \
        *((u ## type*)&gba->SRAM[(addr - 0xE000000) & 0xFFFF]) = val; \
} \

u8 readByte(arm7tdmi_t* cpu, u32 addr){
    MEMORY_TABLE_READ(8);
}

u16 get16(arm7tdmi_t* cpu, u32 addr){
    MEMORY_TABLE_READ(16);
}

u16 readHalfWord(arm7tdmi_t* cpu, u32 addr){
    addr &= ~0b1;

    MEMORY_TABLE_READ(16);
}

u32 readWord(arm7tdmi_t* cpu, u32 addr){
    addr &= ~0b11;

    MEMORY_TABLE_READ(32);
}

void writeByte(arm7tdmi_t* cpu, u32 addr, u8 val){
    MEMORY_TABLE_WRITE(8);
}

void writeHalfWord(arm7tdmi_t* cpu, u32 addr, u16 val){
    addr &= ~0b1;
    
    MEMORY_TABLE_WRITE(16);
}

void writeWord(arm7tdmi_t* cpu, u32 addr, u32 val){
    addr &= ~0b11;
    
    MEMORY_TABLE_WRITE(32);
}

void writeIo8(arm7tdmi_t* cpu, u32 addr, u8 val){
    gba_t* gba = (gba_t*)cpu->master;
    ppu_t* ppu = (ppu_t*)&gba->ppu;

    if(addr >= 0x4000000 && addr < 0x4000002){
        addr -= 0x4000000;
        ((u8*)&ppu->DISPCNT)[addr] = val;
        return;
    }

    if(addr >= 0x4000002 && addr < 0x4000004){
        return;
    }

    for(int i = 0; i < 4; i++){
        if(addr >= 0x4000008 + 0x2*i && addr < 0x4000008 + 0x2*(i+1)){
            addr -= 0x4000008 + 0x2*i;
            ((u8*)&ppu->BGCNT[i])[addr] = val;
            return;
        }
    }

    if(addr >= 0x4000004 && addr < 0x4000006){
        addr -= 0x4000004;
        ((u8*)&ppu->DISPSTAT)[addr] = val;
        return;
    }

    for(int i = 0; i < 4; i++){
        if(addr >= 0x4000010 + 0x4*i && addr < 0x4000010 + 0x4*i + 2){
            addr -= 0x4000010 + 0x4*i;
            ((u8*)&ppu->BGHOFS[i])[addr] = val;
            return;    
        }
    }


    for(int i = 0; i < 4; i++){
        if(addr >= 0x4000012 + 0x4*i && addr < 0x4000012 + 0x4*i + 2){
            addr -= 0x4000012 + 0x4*i;
            ((u8*)&ppu->BGVOFS[i])[addr] = val;
            return;    
        }
    }

    for(int i = 0; i < 2; i++){
        if(addr >= 0x4000028 + 0x10*i && addr < 0x4000028 + 0x10*i + 4){
            addr -= 0x4000028 + 0x10*i;
            ((u8*)&ppu->BGX[i])[addr] = val;
            ppu->INTERNAL_BGX[i] = ppu->BGX[i];
            return; 
        }
    }

    for(int i = 0; i < 2; i++){
        if(addr >= 0x400002C + 0x10*i && addr < 0x400002C + 0x10*i + 4){
            addr -= 0x400002C + 0x10*i;
            ((u8*)&ppu->BGY[i])[addr] = val;
            ppu->INTERNAL_BGY[i] = ppu->BGY[i];
            return; 
        }
    }

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            if(addr >= 0x4000020 + 0x10*i + 0x02*j && addr < 0x4000020 + 0x10*i + 0x02*j + 2){
                addr -= 0x4000020 + 0x10*i + 0x02*j;
                ((u8*)&ppu->BGP[i*4 + j])[addr] = val;
                return;
            }
        }
    }


    for(int i = 0; i < 2; i++){
        if(addr >= 0x4000040 + 0x2*i && addr < 0x4000040 + 0x2*(i+1)){
            addr -= 0x4000040 + 0x2*i;
            ((u8*)&ppu->WINH[i])[addr] = val;
            return;
        }
    }

    for(int i = 0; i < 2; i++){
        if(addr >= 0x4000044 + 0x2*i && addr < 0x4000044 + 0x2*(i+1)){
            addr -= 0x4000044 + 0x2*i;
            ((u8*)&ppu->WINV[i])[addr] = val;
            return;
        }
    }

    if(addr >= 0x4000048 && addr < 0x400004A){
        addr -= 0x4000048;
        ((u8*)&ppu->WININ)[addr] = val;
        return;
    }

    if(addr >= 0x400004A && addr < 0x400004C){
        addr -= 0x400004A;
        ((u8*)&ppu->WINOUT)[addr] = val;
        return;
    }

    if(addr >= 0x4000050 && addr < 0x4000052){
        addr -= 0x4000050;
        ((u8*)&ppu->BLDCNT)[addr] = val;
        return;
    }

    if(addr >= 0x4000052 && addr < 0x4000054){
        addr -= 0x4000052;
        ((u8*)&ppu->BLDALPHA)[addr] = val;
        return;
    }

    if(addr >= 0x4000054 && addr < 0x4000056){
        addr -= 0x4000054;
        ((u8*)&ppu->BLDY)[addr] = val;
        return;
    }

    if(addr >= 0x4000088 && addr < 0x400008A){
        addr -= 0x4000088;
        ((u8*)&gba->SOUNDBIAS)[addr] = val;
        return;
    }

    for(int i = 0; i < 4; i++){
        if(addr >= 0x40000B0 + 0xC*i && addr < 0x40000B0 + 0xC*(i+1)){
            addr -= 0x40000B0 + 0xC*i;
           
            if(addr < 0x4){
                ((u8*)&gba->DMASAD[i])[addr] = val;
                return;
            }

            if(addr < 0x8){
                ((u8*)&gba->DMADAD[i])[addr - 0x4] = val;
                return;
            }

            if(addr < 0xC){
                ((u8*)&gba->DMACNT[i])[addr - 0x8] = val;
                if(gba->DMACNT[i] >> 31)
                    triggerDma(gba, i);
                return;
            }          
        }
    }

    for(int i = 0; i < 4; i++){
        if(addr >= 0x4000100 + i*4 && addr < 0x4000100 + (i+1)*4){
            addr -=  0x4000100 + i*4;
            timer_t* timers = gba->timers;
            u32 old_TMCNT = timers[i].TMCNT;
            ((u8*)&timers[i].TMCNT)[addr] = val;
            if(!((old_TMCNT >> 16) & 0x80) && ((timers[i].TMCNT >> 16) & 0x80)){
                triggerTimer(&timers[i]);
            }
            return;
        }
    }

    if(addr >= 0x4000134 && addr < 0x4000136){
        addr -= 0x4000134;
        ((u8*)&gba->RCNT)[addr] = val;
        return;
    }

    if(addr >= 0x4000200 && addr < 0x4000202){
        addr -= 0x4000200;
        ((u8*)&gba->IE)[addr] = val;
        checkInterrupts(gba);
        return;
    }

    
    if(addr >= 0x4000202 && addr < 0x4000204){
        addr -= 0x4000202;
        ((u8*)&gba->IF)[addr] &= ~(val);
        return;
    }

    if(addr >= 0x4000204 && addr < 0x4000206){
        addr -= 0x4000204;
        ((u8*)&gba->WAITCNT)[addr] = val;
        return;
    }

    if(addr >= 0x4000208 && addr < 0x400020A){
        addr -= 0x4000208;
        ((u8*)&gba->IME)[addr] = val;
        return;
    }

    if(addr == 0x4000300){
        gba->POSTFLG = val;
        return;
    }

    if(addr == 0x4000301){
        gba->HALTCNT = true;
        return;
    }

    //printf("WRONG WRITE %X %X\n", addr, cpu.r[15]);
    //arm7tdmi_print(&cpu);
    //exit(0);
}

void writeIo16(arm7tdmi_t* cpu, u32 addr, u16 val){
    writeIo8(cpu, addr, val);
    writeIo8(cpu, addr + 1, val >> 8);  
}

void writeIo32(arm7tdmi_t* cpu, u32 addr, u32 val){
    writeIo16(cpu, addr, val);
    writeIo16(cpu, addr + 2, val >> 16);  
}

u8 readIo8(arm7tdmi_t* cpu, u32 addr){
    gba_t* gba = (gba_t*)cpu->master;
    ppu_t* ppu = &gba->ppu;

    for(int i = 0; i < 4; i++){
        if(addr >= 0x4000008 + 0x2*i && addr < 0x4000008 + 0x2*(i+1)){
            addr -= 0x4000008 + 0x2*i;
            return ((u8*)&ppu->BGCNT[i])[addr];
        }
    }

    if(addr >= 0x4000048 && addr < 0x400004A){
        addr -= 0x4000048;
        return ((u8*)&ppu->WININ)[addr];
    }

    if(addr >= 0x4000088 && addr < 0x400008A){
        addr -= 0x4000088;
        return ((u8*)&gba->SOUNDBIAS)[addr];
    }

    if(addr >= 0x400004A && addr < 0x400004C){
        addr -= 0x400004A;
        return ((u8*)&ppu->WINOUT)[addr];
    }

    for(int i = 0; i < 4; i++){
        if(addr >= 0x40000BA + 0xC*i && addr < 0x40000BA + 0xC*i + 2){    
            addr -= 0x40000BA + 0xC*i;
            return ((u8*)&gba->DMACNT[i])[addr];
        }
    }

    for(int i = 0; i < 4; i++){
        if(addr >= 0x4000100 + i*4 && addr < 0x4000100 + (i+1)*4){
            addr -=  0x4000100 + i*4;
            timer_t* timers = gba->timers;
            if(addr < 2)
                return ((u8*)&timers[i].counter)[addr];
            else
                return ((u8*)&timers[i].TMCNT)[addr];
        }
    }

    if(addr >= 0x4000130 && addr < 0x4000132){
        addr -= 0x4000130;
        return ((u8*)&gba->KEYINPUT)[addr];
    }

    if(addr >= 0x4000132 && addr < 0x4000134){
        addr -= 0x4000132;
        return ((u8*)&gba->KEYCNT)[addr];
    }

    if(addr >= 0x4000000 && addr < 0x4000002){
        addr -= 0x4000000;
        return ((u8*)&ppu->DISPCNT)[addr];
    }

    if(addr >= 0x4000004 && addr < 0x4000006){
        addr -= 0x4000004;
        composeDispstat(ppu);
        return ((u8*)&ppu->DISPSTAT)[addr];
    }

    if(addr >= 0x4000006 && addr < 0x4000008){
        addr -= 0x4000006;
        return ((u8*)&ppu->VCOUNT)[addr];
    }

    
    if(addr >= 0x4000050 && addr < 0x4000052){
        addr -= 0x4000050;
        return ((u8*)&ppu->BLDCNT)[addr];
    }

    if(addr >= 0x4000052 && addr < 0x4000054){
        addr -= 0x4000052;
        return ((u8*)&ppu->BLDALPHA)[addr];
    }

    if(addr >= 0x4000134 && addr < 0x4000136){
        addr -= 0x4000134;
        return ((u8*)&gba->RCNT)[addr];
    }

    if(addr >= 0x4000200 && addr < 0x4000202){
        addr -= 0x4000200;
        return ((u8*)&gba->IE)[addr];
    }

    
    if(addr >= 0x4000202 && addr < 0x4000204){
        addr -= 0x4000202;
        return ((u8*)&gba->IF)[addr];
    }

    if(addr >= 0x4000204 && addr < 0x4000206){
        addr -= 0x4000204;
        return ((u8*)&gba->WAITCNT)[addr];
    }

    if(addr >= 0x4000208 && addr < 0x400020A){
        addr -= 0x4000208;
        return ((u8*)&gba->IME)[addr];
    }

    if(addr == 0x4000300){
        return gba->POSTFLG;
    }

    return 0x00;
}

u16 readIo16(arm7tdmi_t* cpu, u32 addr){
    return readIo8(cpu, addr) | (readIo8(cpu, addr + 1) << 8);
}

u32 readIo32(arm7tdmi_t* cpu, u32 addr){
    return readIo16(cpu, addr) | (readIo16(cpu, addr + 2) << 16);
}

void loadBios(const char* filename, u8** bios){
    FILE* fptr = fopen(filename, "rb");
    if(!fptr){
        printf("can't open bios\n");
        return;
    }

    *bios = (u8*)malloc(BIOS_SIZE);

    fread(*bios, 1, BIOS_SIZE, fptr);

    fclose(fptr);
}

size_t loadRom(const char* filename, u8** rom){
    FILE* fptr = fopen(filename, "rb");
    if(!fptr){
        printf("can't open rom\n");
        return 0;
    }

    fseek(fptr, 0, SEEK_END);
    size_t size = ftell(fptr);
    rewind(fptr);

    *rom = (u8*)malloc(size);

    fread(*rom, 1, size, fptr);

    fclose(fptr);

    return size;
}