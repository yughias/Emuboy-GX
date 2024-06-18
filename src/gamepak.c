#include "gamepak.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

u8 gamePakEmptySaveRead(gamepak_t* gamepak, u32 addr){ return 0x00; }
void gamePakEmptySaveWrite(gamepak_t* gamepak, u32 addr, u8 byte){ return; }

u8 gamePakSramRead(gamepak_t* gamepak, u32 addr){
    if(addr >= 0xE000000 && addr < 0xE010000)
        return gamepak->savMemory[addr - 0xE000000];
    return 0x00;
}

void gamePakSramWrite(gamepak_t* gamepak, u32 addr, u8 byte){
    if(addr >= 0xE000000 && addr < 0xE010000)
        gamepak->savMemory[addr - 0xE000000] = byte;
}

void getSavFilename(char* savFilename, const char* romFilename){
    strcpy(savFilename, romFilename);
    char *dot = strrchr(savFilename, '.');

    if(dot != NULL)
        strcpy(dot, ".sav");
    else
        strcat(savFilename, ".sav");
}

void loadGamePak(gamepak_t* gamepak, const char* romFilename){
    FILE* fptr = fopen(romFilename, "rb");
    if(!fptr){
        printf("can't open rom\n");
        gamepak->ROM_SIZE = 0;
        gamepak->ROM = NULL;
        gamepak->savMemory = NULL;
        gamepak->type = NO_GAMEPAK;
        return;
    }

    fseek(fptr, 0, SEEK_END);
    gamepak->ROM_SIZE = ftell(fptr);
    rewind(fptr);

    gamepak->ROM = (u8*)malloc(gamepak->ROM_SIZE);

    fread(gamepak->ROM, 1, gamepak->ROM_SIZE, fptr);
    fclose(fptr);

    setupGamePakType(gamepak);

    if(gamepak->type != GAMEPAK_ROM_ONLY){
        char savFilename[FILENAME_MAX];
        getSavFilename(savFilename, romFilename);

        fptr = fopen(savFilename, "rb");
        if(fptr){
            fread(gamepak->savMemory, 1, SRAM_SIZE, fptr);
            fclose(fptr);
        }
    }
}

void setupGamePakType(gamepak_t* gamepak){
    static const char sram_tag[32] = "SRAM";
    
    if(romContains(gamepak->ROM, sram_tag, gamepak->ROM_SIZE)){
        gamepak->type = GAMEPAK_SRAM;
        gamepak->savMemory = (u8*)malloc(SRAM_SIZE);
        gamepak->readByte = gamePakSramRead;
        gamepak->writeByte = gamePakSramWrite;
        printf("SRAM DETECTED!\n");
        return;
    }

    gamepak->readByte = gamePakEmptySaveRead;
    gamepak->writeByte = gamePakEmptySaveWrite;
    printf("ROM ONLY DETECTED!\n");
}

bool romContains(u8* rom, const char* string, size_t rom_size){
    size_t offset = 0;
    size_t str_len = strlen(string);
    while(offset + str_len < rom_size){
        if(!memcmp(rom + offset, string, str_len))
            return true;
        offset += str_len;
    }

    return false;
}