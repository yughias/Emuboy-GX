#ifndef __GAMEPAK_H__
#define __GAMEPAK_H__

#include "db.h"
#include "integer.h"

#define GAMECODE_OFFSET 0xAC

#define N_WAIT_IDX 0
#define S_WAIT_IDX 1

typedef enum {NO_GAMEPAK = 0, GAMEPAK_ROM_ONLY, GAMEPAK_SRAM, GAMEPAK_FLASH, GAMEPAK_EEPROM} GAMEPAK_TYPE;

typedef struct gamepak_t gamepak_t;
typedef struct arm7tdmi_t arm7tdmi_t;

typedef struct gamepak_t {
    GAMEPAK_TYPE type;
    size_t ROM_SIZE;
    u8* ROM;
    u8* savMemory;
    size_t savMemorySize;
    u32 savSizeMask;

    void* internalData;

    uint8_t waitstates[3][2];
    u8 sram_wait;
} gamepak_t;


void getSavFilename(char* savFilename, const char* romFilename);
void loadGamePak(gamepak_t* gamepak, const char* romFilename);
void setupGamePakType(gamepak_t* gamepak);
void setupRomOnlyMemory(gamepak_t* gamepak);
void updateWaitStates(gamepak_t* gamepak, arm7tdmi_t* cpu, u16 waitcnt_reg);

void setupSaveMemoryWithDb(gamepak_t* gamepak, db_hash hash);
bool romContains(u8* rom, const char* string, size_t rom_size);
void freeGamePak(gamepak_t* gamepak);

#endif