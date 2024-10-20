#ifndef __CHEAT_ENGINE_H__
#define __CHEAT_ENGINE_H__

#include "integer.h"

typedef struct gba_t gba_t;

void cheatEnginePrintAddresses();
void cheatEngineNewSearch(gba_t* gba, u32 value_to_find);
void cheatEngineContinueSearch(gba_t* gba, u32 value_to_find);
void cheatEngineWrite(gba_t* gba, u32 value_to_write);

#endif