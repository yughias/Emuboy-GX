#ifndef __GAMEPAK_H__
#define __GAMEPAK_H__

#include "db.h"
#include "integer.h"

#define SRAM_SIZE (1 << 16)
#define FLASH_64K_SIZE (1 << 16)
#define FLASH_128K_SIZE (1 << 17)

#define GAMECODE_OFFSET 0xAC
#define DEFAULT_64K_ID_CODE 0x1B32
#define DEFAULT_128K_ID_CODE 0x1362

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
    
    readSramFunc readByte;
    writeSramFunc writeByte;
} gamepak_t;


void getSavFilename(char* savFilename, const char* romFilename);
void loadGamePak(gamepak_t* gamepak, const char* romFilename);
void setupGamePakType(gamepak_t* gamepak);
void setupRomOnlyMemory(gamepak_t* gamepak);
void setupSramMemory(gamepak_t* gamepak, size_t size);
void setupFlashMemory(gamepak_t* gamepak, size_t size, u16 id_code);
void setupSaveMemoryWithDb(gamepak_t* gamepak, db_hash hash);
bool romContains(u8* rom, const char* string, size_t rom_size);
void freeGamePak(gamepak_t* gamepak);

#endif