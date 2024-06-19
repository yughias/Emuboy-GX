#ifndef __GAMEPAK_H__
#define __GAMEPAK_H__

#include "integer.h"

#define SRAM_SIZE (1 << 16)
#define FLASH_64K_SIZE (1 << 16)
#define FLASH_128K_SIZE (1 << 17)

typedef enum {NO_GAMEPAK, GAMEPAK_ROM_ONLY, GAMEPAK_SRAM, GAMEPAK_FLASH_64K, GAMEPAK_FLASH_128K} GAMEPAK_TYPE;

typedef struct gamepak_t gamepak_t;
typedef u8 (*readSramFunc)(gamepak_t*, u16);
typedef void (*writeSramFunc)(gamepak_t*, u16, u8);

typedef struct gamepak_t {
    GAMEPAK_TYPE type;
    size_t ROM_SIZE;
    u8* ROM;
    u8* savMemory;
    size_t savMemorySize;
    u32 sizeMask;

    void* internalData;
    
    readSramFunc readByte;
    writeSramFunc writeByte;
} gamepak_t;


void getSavFilename(char* savFilename, const char* romFilename);
void loadGamePak(gamepak_t* gamepak, const char* romFilename);
void setupGamePakType(gamepak_t* gamepak);
void setupFlashMemory(gamepak_t* gamepak, size_t size);
void freeGamePak(gamepak_t* gamepak);
bool romContains(u8* rom, const char* string, size_t rom_size);

#endif