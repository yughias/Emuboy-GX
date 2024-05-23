#ifndef __DMA_H__
#define __DMA_H__

typedef struct gba_t gba_t;

void triggerDma(gba_t* gba, int i);
void transferDma(gba_t* gba, int i);
void updateHblankDma(gba_t* gba);
void updateVblankDma(gba_t* gba);

#endif