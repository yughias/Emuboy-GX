#include "gamepak.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {FLASH_READY, FLASH_ID_MODE, FLASH_SET_BANK, FLASH_WRITE_MODE, FLASH_ERASE_MODE} FLASH_STATE;

typedef struct flash_t {
    FLASH_STATE state;    
    bool bank;
    u8 id_byte[2];
} flash_t;

u8 gamePakEmptySaveRead(gamepak_t* gamepak, u16 addr){ return 0x00; }
void gamePakEmptySaveWrite(gamepak_t* gamepak, u16 addr, u8 byte){ return; }

u8 gamePakSramRead(gamepak_t* gamepak, u16 addr){
    return gamepak->savMemory[addr & gamepak->savSizeMask];
}

void gamePakSramWrite(gamepak_t* gamepak, u16 addr, u8 byte){
    gamepak->savMemory[addr & gamepak->savSizeMask] = byte;
}

u8 gamePakReadFlash(gamepak_t* gamepak, u16 addr){
    flash_t* flash = gamepak->internalData;
    if(flash->state == FLASH_ID_MODE && addr <= 1)
        return flash->id_byte[addr];

    int banked_addr = (addr + flash->bank * (1 << 16));
    return gamepak->savMemory[banked_addr & gamepak->savSizeMask]; 
}

void gamePakWriteFlash(gamepak_t* gamepak, u16 addr, u8 byte){
    flash_t* flash = gamepak->internalData;

    if(flash->state == FLASH_WRITE_MODE){
        int banked_addr = (addr + flash->bank * (1 << 16));
        gamepak->savMemory[banked_addr & gamepak->savSizeMask] = byte;
        flash->state = FLASH_READY;
        return;
    }

    if(flash->state == FLASH_ERASE_MODE){
        if(addr == 0x5555 && byte == 0x10){
            memset(gamepak->savMemory, 0xFF, gamepak->savMemorySize);
            flash->state = FLASH_READY;
            return;
        }

        if(byte == 0x30){
            int bank = addr & 0xF000;
            int banked_addr = (bank + flash->bank * (1 << 16));
            banked_addr &= gamepak->savSizeMask;
            memset(&gamepak->savMemory[banked_addr], 0xFF, 0x1000);
            flash->state = FLASH_READY;
            return;
        }
    }

    if(flash->state == FLASH_SET_BANK && addr == 0){
        flash->bank = byte & 1;
        flash->state = FLASH_READY;
        return;
    }

    if(addr == 0x5555){
        if(flash->state == FLASH_ID_MODE && byte == 0xF0){
            flash->state = FLASH_READY;
            return;
        }

        if(flash->state == FLASH_READY){
            switch(byte){
                case 0xAA:
                return;

                case 0xA0:
                flash->state = FLASH_WRITE_MODE;
                break;

                case 0x90:
                flash->state = FLASH_ID_MODE;
                return;

                case 0x80:
                flash->state = FLASH_ERASE_MODE;
                return;

                case 0xF0:
                flash->state = FLASH_READY;
                return;

                case 0xB0:
                flash->state = FLASH_SET_BANK;
                return;

                default:
                printf("UNKNOWN! %x\n", byte);
                return;
            }
        }
    }
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
        gamepak->internalData = NULL;
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
            fread(gamepak->savMemory, 1, gamepak->savMemorySize, fptr);
            fclose(fptr);
        }
    }
}

void setupGamePakType(gamepak_t* gamepak){
    const char sram_tags[2][32] = {"SRAM_V", "SRAM_F_V"};
    const char flash64k_tags[2][32] = { "FLASH_V", "FLASH512_V"};
    const char flash128k_tag[32] = "FLASH1M_V";

    db_hash db_result = db_search(&gamepak->ROM[GAMECODE_OFFSET]);
    if(db_result != DB_NOT_FOUND){
        setupSaveMemoryWithDb(gamepak, db_result);
        return;
    }
    
    for(int i = 0; i < 2; i++)
        if(romContains(gamepak->ROM, flash64k_tags[i], gamepak->ROM_SIZE)){
            setupFlashMemory(gamepak, FLASH_64K_SIZE, DEFAULT_64K_ID_CODE);
            return;
        }

    if(romContains(gamepak->ROM, flash128k_tag, gamepak->ROM_SIZE)){
        setupFlashMemory(gamepak, FLASH_128K_SIZE, DEFAULT_128K_ID_CODE);
        return;
    }

    for(int i = 0; i < 2; i++)
        if(romContains(gamepak->ROM, sram_tags[i], gamepak->ROM_SIZE)){
            setupSramMemory(gamepak, SRAM_SIZE);
            return;
        }

    setupRomOnlyMemory(gamepak);
}

bool romContains(u8* rom, const char* string, size_t rom_size){
    size_t offset = 0;
    size_t str_len = strlen(string);
    while(offset + str_len < rom_size){
        if(!memcmp(rom + offset, string, str_len))
            return true;
        offset += 1;
    }

    return false;
}

void setupRomOnlyMemory(gamepak_t* gamepak){
    gamepak->type = GAMEPAK_ROM_ONLY;
    gamepak->readByte = gamePakEmptySaveRead;
    gamepak->writeByte = gamePakEmptySaveWrite;
    printf("ROM ONLY!\n");
}

void setupSramMemory(gamepak_t* gamepak, size_t size){
    gamepak->type = GAMEPAK_SRAM;
    gamepak->savMemorySize = size;
    gamepak->savMemory = (u8*)malloc(size);
    gamepak->readByte = gamePakSramRead;
    gamepak->writeByte = gamePakSramWrite;
    gamepak->savSizeMask = size - 1;
    printf("SRAM DETECTED!\n");
}

void setupFlashMemory(gamepak_t* gamepak, size_t size, u16 id_code){
    gamepak->type = GAMEPAK_FLASH;
    gamepak->savMemorySize = size;
    gamepak->savMemory = malloc(size);
    gamepak->internalData = malloc(sizeof(flash_t));
    flash_t* flash = gamepak->internalData;
    flash->bank = 0;
    flash->state = FLASH_READY;
    flash->id_byte[0] = id_code & 0xFF;
    flash->id_byte[1] = id_code >> 8;
    memset(gamepak->savMemory, 0xFF, gamepak->savMemorySize);
    gamepak->readByte = gamePakReadFlash;
    gamepak->writeByte = gamePakWriteFlash;
    gamepak->savSizeMask = size - 1;

    if(size == FLASH_64K_SIZE) printf("FLASH 64K DETECTED!\n");
    if(size == FLASH_128K_SIZE) printf("FLASH 128K DETECTED!\n");
}

void freeGamePak(gamepak_t* gamepak){
    if(gamepak->ROM)
        free(gamepak->ROM);
    if(gamepak->savMemory)
        free(gamepak->savMemory);
    if(gamepak->internalData)
        free(gamepak->internalData);
}

void setupSaveMemoryWithDb(gamepak_t* gamepak, db_hash hash){
    switch(hash){
        case 0xF:
        setupRomOnlyMemory(gamepak);
        break;

        case 0xE:
        setupSramMemory(gamepak, SRAM_SIZE);
        break;

        case 0xD: case 0xC: case 0xB: case 0xA:
        case 0x9: case 0x8: case 0x7: case 0x6:
        case 0x5: case 0x4:
        setupFlashMemory(gamepak, db_get_size(hash), db_get_id_code(hash));
        break;
    
        case 0x0: case 0x1: case 0x2: case 0x3:
        printf("EEPROM NOT SUPPORTED YET!\n");
        setupRomOnlyMemory(gamepak);
        break;

        default:
        printf("UNKNOWN DB HASH!\n");
        setupRomOnlyMemory(gamepak);
        break;
    }
}