#ifndef __DMA_H__
#define __DMA_H__

#include "gba.h"

void triggerDma(gba_t* gba, int i);
void transferDma(gba_t* gba, int i);
void updateHblankDma();
void updateVblankDma();

#endif