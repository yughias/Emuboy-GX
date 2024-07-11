#ifndef __GAMEPAK_H__
#define __GAMEPAK_H__

#include "db.h"
#include "integer.h"

#define GAMECODE_OFFSET 0xAC

typedef enum {NO_GAMEPAK, GAMEPAK_ROM_ONLY, GAMEPAK_SRAM, GAMEPAK_FLASH, GAMEPAK_EEPROM} GAMEPAK_TYPE;

typedef struct gamepak_t gamepak_t;
typedef u8 (*readSramFunc)(gamepak_t*, u16);
typedef void (*writeSramFunc)(gamepak_t*, u16, u8);

typedef struct gamepak_t {
    GAMEPAK_TYPE type;
    size_t ROM_SIZE;
    u8* ROM;
    u8* savMemory;
    size_t savMemorySize;
    u32 savSizeMask;

    void* internalData;
    
    readSramFunc readByte_D;
    writeSramFunc writeByte_D;
    readSramFunc readByte_E;
    writeSramFunc writeByte_E;
} gamepak_t;


void getSavFilename(char* savFilename, const char* romFilename);
void loadGamePak(gamepak_t* gamepak, const char* romFilename);
void setupGamePakType(gamepak_t* gamepak);
void setupRomOnlyMemory(gamepak_t* gamepak);
void setupSramMemory(gamepak_t* gamepak, size_t size);
void setupFlashMemory(gamepak_t* gamepak, size_t size, u16 id_code);
void setupEepromMemory(gamepak_t* gampepak, size_t size);
void setupSaveMemoryWithDb(gamepak_t* gamepak, db_hash hash);
bool romContains(u8* rom, const char* string, size_t rom_size);
void freeGamePak(gamepak_t* gamepak);

#endif