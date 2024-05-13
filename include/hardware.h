#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include "arm7tdmi/arm7tdmi.h"
#include "memory.h"
#include "ppu.h"
#include "keypad.h"
#include "dma.h"
#include "timer.h"

extern arm7tdmi_t cpu;
extern timer_t timers[4];

void emulateHardware();

#endif