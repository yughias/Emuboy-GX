#include "gba.h"
#include "arm7tdmi/arm7tdmi.h"
#include "memory_utils.h"

#include <stdio.h>
#include <stdlib.h>

u8 readByte(arm7tdmi_t* cpu, u32 addr){
    MEMORY_TABLE_READ(8);
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