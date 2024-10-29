#ifndef __GBA_SERIALIZER_H__
#define __GBA_SERIALIZER_H__

#include "gba.h"
#include "vector.h"

void serializeGba(vector_t* v, gba_t* gba);
void serializeApu(vector_t* v, gba_t* gba, apu_t* apu);
void serializeGamePak(vector_t* v, gamepak_t* gamepak);
void serializeEeprom(vector_t* v, gamepak_t* gamepak);
void serializeFlash(vector_t* v, gamepak_t* gamepak);
void serializeTimer(vector_t* v, gba_t* gba, gba_tmr_t* timer);
void serializePpu(vector_t* v, ppu_t* ppu);
void serializePrefetcher(vector_t* v, prefetcher_t* prefetcher);
void serializeDmas(vector_t* v, gba_t* gba);
void serializeScheduler(vector_t* v, gba_t* gba);

void deserializeGba(u8* data, gba_t* gba);
u8* deserializeApu(u8* data, gba_t* gba, apu_t* apu);
u8* deserializeGamePak(u8* data, gamepak_t* gamepak);
u8* deserializeEeprom(u8* data, gamepak_t* gamepak);
u8* deserializeFlash(u8* data, gamepak_t* gamepak);
u8* deserializeTimer(u8* data, gba_t* gba, gba_tmr_t* timer);
u8* deserializePpu(u8* data, ppu_t* ppu);
u8* deserializePrefetcher(u8* data, prefetcher_t* prefetcher);
u8* deserializeDmas(u8* data, gba_t* gba);
u8* deserializeScheduler(u8* data, gba_t* gba);

#endif