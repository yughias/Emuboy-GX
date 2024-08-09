#include "gamepak.h"

#include "sram.h"
#include "flash.h"
#include "eeprom.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

u8 gamePakEmptySaveRead(gamepak_t* gamepak, u16 addr){ return 0x00; }
void gamePakEmptySaveWrite(gamepak_t* gamepak, u16 addr, u8 byte){ return; }

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

    bool nes_mirror = gamepak->ROM_SIZE == 1 << 20;

    if(nes_mirror){
        // classic nes games that are 1Mb in size requires mirror!
        const int n_mirror = 4;
        gamepak->ROM = malloc(gamepak->ROM_SIZE*n_mirror);
        fread(gamepak->ROM, 1, gamepak->ROM_SIZE, fptr);
        fclose(fptr);
        for(int i = 1; i < n_mirror; i++){
            memcpy(gamepak->ROM + gamepak->ROM_SIZE*i, gamepak->ROM, gamepak->ROM_SIZE);
        }
        gamepak->ROM_SIZE *= n_mirror;
    } else {
        gamepak->ROM = malloc(gamepak->ROM_SIZE);
        fread(gamepak->ROM, 1, gamepak->ROM_SIZE, fptr);
        fclose(fptr);
    }

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
    printf("ROM ONLY!\n");
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
        printf("EEPROM %zu DETECTED!\n", db_get_size(hash));
        setupEepromMemory(gamepak, db_get_size(hash));
        break;

        default:
        printf("UNKNOWN DB HASH!\n");
        setupRomOnlyMemory(gamepak);
        break;
    }
}

void updateWaitStates(gamepak_t* gamepak, u16 waitcnt_reg){
    static const u8 wait_n[4] = {4, 3, 2, 8};
    static const u8 wait0_s[2] = {2, 1};
    static const u8 wait1_s[2] = {4, 1};
    static const u8 wait2_s[2] = {8, 1};

    gamepak->sram_wait = wait_n[waitcnt_reg & 0b11];
    gamepak->prefetch_enabled = (waitcnt_reg >> 14) & 0b1;

    if(!gamepak->prefetch_enabled){
        gamepak->waitstates[0][N_WAIT_IDX] = wait_n[(waitcnt_reg >> 2) & 0b11];
        gamepak->waitstates[0][S_WAIT_IDX] = wait0_s[(waitcnt_reg >> 4) & 0b1];

        gamepak->waitstates[1][N_WAIT_IDX] = wait_n[(waitcnt_reg >> 5) & 0b11];
        gamepak->waitstates[1][S_WAIT_IDX] = wait1_s[(waitcnt_reg >> 7) & 0b1];

        gamepak->waitstates[2][N_WAIT_IDX] = wait_n[(waitcnt_reg >> 8) & 0b11];
        gamepak->waitstates[2][S_WAIT_IDX] = wait2_s[(waitcnt_reg >> 10) & 0b1];
    } else {
        gamepak->waitstates[0][N_WAIT_IDX] = wait_n[(waitcnt_reg >> 2) & 0b11];
        gamepak->waitstates[0][S_WAIT_IDX] = 0;

        gamepak->waitstates[1][N_WAIT_IDX] = wait_n[(waitcnt_reg >> 5) & 0b11];
        gamepak->waitstates[1][S_WAIT_IDX] = 0;

        gamepak->waitstates[2][N_WAIT_IDX] = wait_n[(waitcnt_reg >> 8) & 0b11];
        gamepak->waitstates[2][S_WAIT_IDX] = 0;
    }
}