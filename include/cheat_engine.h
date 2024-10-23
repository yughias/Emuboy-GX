#ifndef __CHEAT_ENGINE_H__
#define __CHEAT_ENGINE_H__

#include "integer.h"

typedef struct gba_t gba_t;

void cheatEnginePrintAddresses();
void cheatEngineNewSearch(gba_t* gba, u32 value_to_find);
void cheatEngineContinueSearch(gba_t* gba, u32 value_to_find);
void cheatEngineWriteToFoundAddresses(gba_t* gba, u32 value_to_write);
void cheatEngineWriteToAddress(gba_t* gba, u32 address, u32 value_to_write, u8 type);

#endif