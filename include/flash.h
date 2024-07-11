#ifndef __FLASH_H__
#define __FLASH_H__

#include "gamepak.h"
#include "integer.h"

#define FLASH_64K_SIZE (1 << 16)
#define FLASH_128K_SIZE (1 << 17)
#define DEFAULT_64K_ID_CODE 0x1B32
#define DEFAULT_128K_ID_CODE 0x1362

typedef enum {FLASH_READY, FLASH_ID_MODE, FLASH_SET_BANK, FLASH_WRITE_MODE, FLASH_ERASE_MODE} FLASH_STATE;

typedef struct flash_t {
    FLASH_STATE state;    
    bool bank;
    u8 id_byte[2];
} flash_t;

u8 readFlash(gamepak_t* gamepak, u16 addr);
void writeFlash(gamepak_t* gamepak, u16 addr, u8 byte);

#endif