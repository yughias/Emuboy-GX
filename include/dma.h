#ifndef __DMA_H__
#define __DMA_H__

#include "integer.h"

typedef struct gba_t gba_t;

typedef struct dma_t {
    bool enabled;
    u32 internal_source;
    u32 internal_dest;
    u32 DMASAD;
    u32 DMADAD;
    u32 DMACNT;
} dma_t;

void triggerDma(gba_t* gba, int i);
void transferDma(gba_t* gba, int i);
void updateHblankDma(gba_t* gba);
void updateVblankDma(gba_t* gba);

#endif