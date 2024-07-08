void writeIo8(arm7tdmi_t* cpu, u16 addr, u8 val){
gba_t* gba = (gba_t*)cpu->master;
ppu_t* ppu = &gba->ppu;
apu_t* apu = &gba->apu;
switch(addr){
case 0x0:
((u8*)&ppu->DISPCNT)[0] = val;
return;
case 0x1:
((u8*)&ppu->DISPCNT)[1] = val;
return;
case 0x4:
((u8*)&ppu->DISPSTAT)[0] = val;
return;
case 0x5:
((u8*)&ppu->DISPSTAT)[1] = val;
checkVCount(gba);
return;
case 0x8:
((u8*)&ppu->BGCNT[0])[0] = val;
return;
case 0x9:
((u8*)&ppu->BGCNT[0])[1] = val;
return;
case 0xA:
((u8*)&ppu->BGCNT[1])[0] = val;
return;
case 0xB:
((u8*)&ppu->BGCNT[1])[1] = val;
return;
case 0xC:
((u8*)&ppu->BGCNT[2])[0] = val;
return;
case 0xD:
((u8*)&ppu->BGCNT[2])[1] = val;
return;
case 0xE:
((u8*)&ppu->BGCNT[3])[0] = val;
return;
case 0xF:
((u8*)&ppu->BGCNT[3])[1] = val;
return;
case 0x10:
((u8*)&ppu->BGHOFS[0])[0] = val;
return;
case 0x11:
((u8*)&ppu->BGHOFS[0])[1] = val;
return;
case 0x12:
((u8*)&ppu->BGVOFS[0])[0] = val;
return;
case 0x13:
((u8*)&ppu->BGVOFS[0])[1] = val;
return;
case 0x14:
((u8*)&ppu->BGHOFS[1])[0] = val;
return;
case 0x15:
((u8*)&ppu->BGHOFS[1])[1] = val;
return;
case 0x16:
((u8*)&ppu->BGVOFS[1])[0] = val;
return;
case 0x17:
((u8*)&ppu->BGVOFS[1])[1] = val;
return;
case 0x18:
((u8*)&ppu->BGHOFS[2])[0] = val;
return;
case 0x19:
((u8*)&ppu->BGHOFS[2])[1] = val;
return;
case 0x1A:
((u8*)&ppu->BGVOFS[2])[0] = val;
return;
case 0x1B:
((u8*)&ppu->BGVOFS[2])[1] = val;
return;
case 0x1C:
((u8*)&ppu->BGHOFS[3])[0] = val;
return;
case 0x1D:
((u8*)&ppu->BGHOFS[3])[1] = val;
return;
case 0x1E:
((u8*)&ppu->BGVOFS[3])[0] = val;
return;
case 0x1F:
((u8*)&ppu->BGVOFS[3])[1] = val;
return;
case 0x20:
((u8*)&ppu->BGP[0])[0] = val;
return;
case 0x21:
((u8*)&ppu->BGP[0])[1] = val;
return;
case 0x22:
((u8*)&ppu->BGP[1])[0] = val;
return;
case 0x23:
((u8*)&ppu->BGP[1])[1] = val;
return;
case 0x24:
((u8*)&ppu->BGP[2])[0] = val;
return;
case 0x25:
((u8*)&ppu->BGP[2])[1] = val;
return;
case 0x26:
((u8*)&ppu->BGP[3])[0] = val;
return;
case 0x27:
((u8*)&ppu->BGP[3])[1] = val;
return;
case 0x28:
((u8*)&ppu->BGX[0])[0] = val;
ppu->INTERNAL_BGX[0] = ppu->BGX[0];
return;
case 0x29:
((u8*)&ppu->BGX[0])[1] = val;
ppu->INTERNAL_BGX[0] = ppu->BGX[0];
return;
case 0x2A:
((u8*)&ppu->BGX[0])[2] = val;
ppu->INTERNAL_BGX[0] = ppu->BGX[0];
return;
case 0x2B:
((u8*)&ppu->BGX[0])[3] = val;
ppu->INTERNAL_BGX[0] = ppu->BGX[0];
return;
case 0x2C:
((u8*)&ppu->BGY[0])[0] = val;
ppu->INTERNAL_BGY[0] = ppu->BGY[0];
return;
case 0x2D:
((u8*)&ppu->BGY[0])[1] = val;
ppu->INTERNAL_BGY[0] = ppu->BGY[0];
return;
case 0x2E:
((u8*)&ppu->BGY[0])[2] = val;
ppu->INTERNAL_BGY[0] = ppu->BGY[0];
return;
case 0x2F:
((u8*)&ppu->BGY[0])[3] = val;
ppu->INTERNAL_BGY[0] = ppu->BGY[0];
return;
case 0x30:
((u8*)&ppu->BGP[4])[0] = val;
return;
case 0x31:
((u8*)&ppu->BGP[4])[1] = val;
return;
case 0x32:
((u8*)&ppu->BGP[5])[0] = val;
return;
case 0x33:
((u8*)&ppu->BGP[5])[1] = val;
return;
case 0x34:
((u8*)&ppu->BGP[6])[0] = val;
return;
case 0x35:
((u8*)&ppu->BGP[6])[1] = val;
return;
case 0x36:
((u8*)&ppu->BGP[7])[0] = val;
return;
case 0x37:
((u8*)&ppu->BGP[7])[1] = val;
return;
case 0x38:
((u8*)&ppu->BGX[1])[0] = val;
ppu->INTERNAL_BGX[1] = ppu->BGX[1];
return;
case 0x39:
((u8*)&ppu->BGX[1])[1] = val;
ppu->INTERNAL_BGX[1] = ppu->BGX[1];
return;
case 0x3A:
((u8*)&ppu->BGX[1])[2] = val;
ppu->INTERNAL_BGX[1] = ppu->BGX[1];
return;
case 0x3B:
((u8*)&ppu->BGX[1])[3] = val;
ppu->INTERNAL_BGX[1] = ppu->BGX[1];
return;
case 0x3C:
((u8*)&ppu->BGY[1])[0] = val;
ppu->INTERNAL_BGY[1] = ppu->BGY[1];
return;
case 0x3D:
((u8*)&ppu->BGY[1])[1] = val;
ppu->INTERNAL_BGY[1] = ppu->BGY[1];
return;
case 0x3E:
((u8*)&ppu->BGY[1])[2] = val;
ppu->INTERNAL_BGY[1] = ppu->BGY[1];
return;
case 0x3F:
((u8*)&ppu->BGY[1])[3] = val;
ppu->INTERNAL_BGY[1] = ppu->BGY[1];
return;
case 0x40:
((u8*)&ppu->WINH[0])[0] = val;
return;
case 0x41:
((u8*)&ppu->WINH[0])[1] = val;
return;
case 0x42:
((u8*)&ppu->WINH[1])[0] = val;
return;
case 0x43:
((u8*)&ppu->WINH[1])[1] = val;
return;
case 0x44:
((u8*)&ppu->WINV[0])[0] = val;
return;
case 0x45:
((u8*)&ppu->WINV[0])[1] = val;
return;
case 0x46:
((u8*)&ppu->WINV[1])[0] = val;
return;
case 0x47:
((u8*)&ppu->WINV[1])[1] = val;
return;
case 0x48:
((u8*)&ppu->WININ)[0] = val;
return;
case 0x49:
((u8*)&ppu->WININ)[1] = val;
return;
case 0x4A:
((u8*)&ppu->WINOUT)[0] = val;
return;
case 0x4B:
((u8*)&ppu->WINOUT)[1] = val;
return;
case 0x50:
((u8*)&ppu->BLDCNT)[0] = val;
return;
case 0x51:
((u8*)&ppu->BLDCNT)[1] = val;
return;
case 0x52:
((u8*)&ppu->BLDALPHA)[0] = val;
return;
case 0x53:
((u8*)&ppu->BLDALPHA)[1] = val;
return;
case 0x54:
((u8*)&ppu->BLDY)[0] = val;
return;
case 0x55:
((u8*)&ppu->BLDY)[1] = val;
return;
case 0x80:
((u8*)&apu->SOUNDCNT_L)[0] = val;
return;
case 0x81:
((u8*)&apu->SOUNDCNT_L)[1] = val;
return;
case 0x82:
((u8*)&apu->SOUNDCNT_H)[0] = val;
updateChannelMixing(apu);
return;
case 0x83:
((u8*)&apu->SOUNDCNT_H)[1] = val;
updateChannelMixing(apu);
return;
case 0x88:
((u8*)&apu->SOUNDBIAS)[0] = val;
return;
case 0x89:
((u8*)&apu->SOUNDBIAS)[1] = val;
return;
case 0xA0:
pushIntoFifo(&apu->fifo[0], val);
return;
case 0xA1:
pushIntoFifo(&apu->fifo[0], val);
return;
case 0xA2:
pushIntoFifo(&apu->fifo[0], val);
return;
case 0xA3:
pushIntoFifo(&apu->fifo[0], val);
return;
case 0xA4:
pushIntoFifo(&apu->fifo[1], val);
return;
case 0xA5:
pushIntoFifo(&apu->fifo[1], val);
return;
case 0xA6:
pushIntoFifo(&apu->fifo[1], val);
return;
case 0xA7:
pushIntoFifo(&apu->fifo[1], val);
return;
case 0xB0:
((u8*)&gba->dmas[0].DMASAD)[0] = val;
return;
case 0xB1:
((u8*)&gba->dmas[0].DMASAD)[1] = val;
return;
case 0xB2:
((u8*)&gba->dmas[0].DMASAD)[2] = val;
return;
case 0xB3:
((u8*)&gba->dmas[0].DMASAD)[3] = val;
return;
case 0xB4:
((u8*)&gba->dmas[0].DMADAD)[0] = val;
return;
case 0xB5:
((u8*)&gba->dmas[0].DMADAD)[1] = val;
return;
case 0xB6:
((u8*)&gba->dmas[0].DMADAD)[2] = val;
return;
case 0xB7:
((u8*)&gba->dmas[0].DMADAD)[3] = val;
return;
case 0xB8:
{bool old_trigger = gba->dmas[0].DMACNT >> 31;
((u8*)&gba->dmas[0].DMACNT)[0] = val;
bool new_trigger = gba->dmas[0].DMACNT >> 31;
if(!old_trigger && new_trigger)
triggerDma(gba, 0);
}return;
case 0xB9:
{bool old_trigger = gba->dmas[0].DMACNT >> 31;
((u8*)&gba->dmas[0].DMACNT)[1] = val;
bool new_trigger = gba->dmas[0].DMACNT >> 31;
if(!old_trigger && new_trigger)
triggerDma(gba, 0);
}return;
case 0xBA:
{bool old_trigger = gba->dmas[0].DMACNT >> 31;
((u8*)&gba->dmas[0].DMACNT)[2] = val;
bool new_trigger = gba->dmas[0].DMACNT >> 31;
if(!old_trigger && new_trigger)
triggerDma(gba, 0);
}return;
case 0xBB:
{bool old_trigger = gba->dmas[0].DMACNT >> 31;
((u8*)&gba->dmas[0].DMACNT)[3] = val;
bool new_trigger = gba->dmas[0].DMACNT >> 31;
if(!old_trigger && new_trigger)
triggerDma(gba, 0);
}return;
case 0xBC:
((u8*)&gba->dmas[1].DMASAD)[0] = val;
return;
case 0xBD:
((u8*)&gba->dmas[1].DMASAD)[1] = val;
return;
case 0xBE:
((u8*)&gba->dmas[1].DMASAD)[2] = val;
return;
case 0xBF:
((u8*)&gba->dmas[1].DMASAD)[3] = val;
return;
case 0xC0:
((u8*)&gba->dmas[1].DMADAD)[0] = val;
return;
case 0xC1:
((u8*)&gba->dmas[1].DMADAD)[1] = val;
return;
case 0xC2:
((u8*)&gba->dmas[1].DMADAD)[2] = val;
return;
case 0xC3:
((u8*)&gba->dmas[1].DMADAD)[3] = val;
return;
case 0xC4:
{bool old_trigger = gba->dmas[1].DMACNT >> 31;
((u8*)&gba->dmas[1].DMACNT)[0] = val;
bool new_trigger = gba->dmas[1].DMACNT >> 31;
if(!old_trigger && new_trigger)
triggerDma(gba, 1);
}return;
case 0xC5:
{bool old_trigger = gba->dmas[1].DMACNT >> 31;
((u8*)&gba->dmas[1].DMACNT)[1] = val;
bool new_trigger = gba->dmas[1].DMACNT >> 31;
if(!old_trigger && new_trigger)
triggerDma(gba, 1);
}return;
case 0xC6:
{bool old_trigger = gba->dmas[1].DMACNT >> 31;
((u8*)&gba->dmas[1].DMACNT)[2] = val;
bool new_trigger = gba->dmas[1].DMACNT >> 31;
if(!old_trigger && new_trigger)
triggerDma(gba, 1);
}return;
case 0xC7:
{bool old_trigger = gba->dmas[1].DMACNT >> 31;
((u8*)&gba->dmas[1].DMACNT)[3] = val;
bool new_trigger = gba->dmas[1].DMACNT >> 31;
if(!old_trigger && new_trigger)
triggerDma(gba, 1);
}return;
case 0xC8:
((u8*)&gba->dmas[2].DMASAD)[0] = val;
return;
case 0xC9:
((u8*)&gba->dmas[2].DMASAD)[1] = val;
return;
case 0xCA:
((u8*)&gba->dmas[2].DMASAD)[2] = val;
return;
case 0xCB:
((u8*)&gba->dmas[2].DMASAD)[3] = val;
return;
case 0xCC:
((u8*)&gba->dmas[2].DMADAD)[0] = val;
return;
case 0xCD:
((u8*)&gba->dmas[2].DMADAD)[1] = val;
return;
case 0xCE:
((u8*)&gba->dmas[2].DMADAD)[2] = val;
return;
case 0xCF:
((u8*)&gba->dmas[2].DMADAD)[3] = val;
return;
case 0xD0:
{bool old_trigger = gba->dmas[2].DMACNT >> 31;
((u8*)&gba->dmas[2].DMACNT)[0] = val;
bool new_trigger = gba->dmas[2].DMACNT >> 31;
if(!old_trigger && new_trigger)
triggerDma(gba, 2);
}return;
case 0xD1:
{bool old_trigger = gba->dmas[2].DMACNT >> 31;
((u8*)&gba->dmas[2].DMACNT)[1] = val;
bool new_trigger = gba->dmas[2].DMACNT >> 31;
if(!old_trigger && new_trigger)
triggerDma(gba, 2);
}return;
case 0xD2:
{bool old_trigger = gba->dmas[2].DMACNT >> 31;
((u8*)&gba->dmas[2].DMACNT)[2] = val;
bool new_trigger = gba->dmas[2].DMACNT >> 31;
if(!old_trigger && new_trigger)
triggerDma(gba, 2);
}return;
case 0xD3:
{bool old_trigger = gba->dmas[2].DMACNT >> 31;
((u8*)&gba->dmas[2].DMACNT)[3] = val;
bool new_trigger = gba->dmas[2].DMACNT >> 31;
if(!old_trigger && new_trigger)
triggerDma(gba, 2);
}return;
case 0xD4:
((u8*)&gba->dmas[3].DMASAD)[0] = val;
return;
case 0xD5:
((u8*)&gba->dmas[3].DMASAD)[1] = val;
return;
case 0xD6:
((u8*)&gba->dmas[3].DMASAD)[2] = val;
return;
case 0xD7:
((u8*)&gba->dmas[3].DMASAD)[3] = val;
return;
case 0xD8:
((u8*)&gba->dmas[3].DMADAD)[0] = val;
return;
case 0xD9:
((u8*)&gba->dmas[3].DMADAD)[1] = val;
return;
case 0xDA:
((u8*)&gba->dmas[3].DMADAD)[2] = val;
return;
case 0xDB:
((u8*)&gba->dmas[3].DMADAD)[3] = val;
return;
case 0xDC:
{bool old_trigger = gba->dmas[3].DMACNT >> 31;
((u8*)&gba->dmas[3].DMACNT)[0] = val;
bool new_trigger = gba->dmas[3].DMACNT >> 31;
if(!old_trigger && new_trigger)
triggerDma(gba, 3);
}return;
case 0xDD:
{bool old_trigger = gba->dmas[3].DMACNT >> 31;
((u8*)&gba->dmas[3].DMACNT)[1] = val;
bool new_trigger = gba->dmas[3].DMACNT >> 31;
if(!old_trigger && new_trigger)
triggerDma(gba, 3);
}return;
case 0xDE:
{bool old_trigger = gba->dmas[3].DMACNT >> 31;
((u8*)&gba->dmas[3].DMACNT)[2] = val;
bool new_trigger = gba->dmas[3].DMACNT >> 31;
if(!old_trigger && new_trigger)
triggerDma(gba, 3);
}return;
case 0xDF:
{bool old_trigger = gba->dmas[3].DMACNT >> 31;
((u8*)&gba->dmas[3].DMACNT)[3] = val;
bool new_trigger = gba->dmas[3].DMACNT >> 31;
if(!old_trigger && new_trigger)
triggerDma(gba, 3);
}return;
case 0x100:
{
gba_tmr_t* timers = gba->timers;
u32 old_TMCNT = timers[0].TMCNT;
((u8*)&timers[0].TMCNT)[0] = val;
bool old_enabled = (old_TMCNT >> 16) & 0x80;
bool old_cascade = (old_TMCNT >> 16) & 0b100;
bool new_enabled = (timers[0].TMCNT >> 16) & 0x80;
bool new_cascade = ((timers[0].TMCNT >> 16) & 0b100);
if(!old_enabled && new_enabled) triggerTimer(gba, 0);
else if((old_enabled && !new_enabled) || (new_enabled && !old_cascade && new_cascade)) descheduleTimer(gba, 0);
else if(new_enabled && old_cascade && !new_cascade) disableCascadeModeTimer(gba, 0);
}
return;
case 0x101:
{
gba_tmr_t* timers = gba->timers;
u32 old_TMCNT = timers[0].TMCNT;
((u8*)&timers[0].TMCNT)[1] = val;
bool old_enabled = (old_TMCNT >> 16) & 0x80;
bool old_cascade = (old_TMCNT >> 16) & 0b100;
bool new_enabled = (timers[0].TMCNT >> 16) & 0x80;
bool new_cascade = ((timers[0].TMCNT >> 16) & 0b100);
if(!old_enabled && new_enabled) triggerTimer(gba, 0);
else if((old_enabled && !new_enabled) || (new_enabled && !old_cascade && new_cascade)) descheduleTimer(gba, 0);
else if(new_enabled && old_cascade && !new_cascade) disableCascadeModeTimer(gba, 0);
}
return;
case 0x102:
{
gba_tmr_t* timers = gba->timers;
u32 old_TMCNT = timers[0].TMCNT;
((u8*)&timers[0].TMCNT)[2] = val;
bool old_enabled = (old_TMCNT >> 16) & 0x80;
bool old_cascade = (old_TMCNT >> 16) & 0b100;
bool new_enabled = (timers[0].TMCNT >> 16) & 0x80;
bool new_cascade = ((timers[0].TMCNT >> 16) & 0b100);
if(!old_enabled && new_enabled) triggerTimer(gba, 0);
else if((old_enabled && !new_enabled) || (new_enabled && !old_cascade && new_cascade)) descheduleTimer(gba, 0);
else if(new_enabled && old_cascade && !new_cascade) disableCascadeModeTimer(gba, 0);
}
return;
case 0x103:
{
gba_tmr_t* timers = gba->timers;
u32 old_TMCNT = timers[0].TMCNT;
((u8*)&timers[0].TMCNT)[3] = val;
bool old_enabled = (old_TMCNT >> 16) & 0x80;
bool old_cascade = (old_TMCNT >> 16) & 0b100;
bool new_enabled = (timers[0].TMCNT >> 16) & 0x80;
bool new_cascade = ((timers[0].TMCNT >> 16) & 0b100);
if(!old_enabled && new_enabled) triggerTimer(gba, 0);
else if((old_enabled && !new_enabled) || (new_enabled && !old_cascade && new_cascade)) descheduleTimer(gba, 0);
else if(new_enabled && old_cascade && !new_cascade) disableCascadeModeTimer(gba, 0);
}
return;
case 0x104:
{
gba_tmr_t* timers = gba->timers;
u32 old_TMCNT = timers[1].TMCNT;
((u8*)&timers[1].TMCNT)[0] = val;
bool old_enabled = (old_TMCNT >> 16) & 0x80;
bool old_cascade = (old_TMCNT >> 16) & 0b100;
bool new_enabled = (timers[1].TMCNT >> 16) & 0x80;
bool new_cascade = ((timers[1].TMCNT >> 16) & 0b100);
if(!old_enabled && new_enabled) triggerTimer(gba, 1);
else if((old_enabled && !new_enabled) || (new_enabled && !old_cascade && new_cascade)) descheduleTimer(gba, 1);
else if(new_enabled && old_cascade && !new_cascade) disableCascadeModeTimer(gba, 1);
}
return;
case 0x105:
{
gba_tmr_t* timers = gba->timers;
u32 old_TMCNT = timers[1].TMCNT;
((u8*)&timers[1].TMCNT)[1] = val;
bool old_enabled = (old_TMCNT >> 16) & 0x80;
bool old_cascade = (old_TMCNT >> 16) & 0b100;
bool new_enabled = (timers[1].TMCNT >> 16) & 0x80;
bool new_cascade = ((timers[1].TMCNT >> 16) & 0b100);
if(!old_enabled && new_enabled) triggerTimer(gba, 1);
else if((old_enabled && !new_enabled) || (new_enabled && !old_cascade && new_cascade)) descheduleTimer(gba, 1);
else if(new_enabled && old_cascade && !new_cascade) disableCascadeModeTimer(gba, 1);
}
return;
case 0x106:
{
gba_tmr_t* timers = gba->timers;
u32 old_TMCNT = timers[1].TMCNT;
((u8*)&timers[1].TMCNT)[2] = val;
bool old_enabled = (old_TMCNT >> 16) & 0x80;
bool old_cascade = (old_TMCNT >> 16) & 0b100;
bool new_enabled = (timers[1].TMCNT >> 16) & 0x80;
bool new_cascade = ((timers[1].TMCNT >> 16) & 0b100);
if(!old_enabled && new_enabled) triggerTimer(gba, 1);
else if((old_enabled && !new_enabled) || (new_enabled && !old_cascade && new_cascade)) descheduleTimer(gba, 1);
else if(new_enabled && old_cascade && !new_cascade) disableCascadeModeTimer(gba, 1);
}
return;
case 0x107:
{
gba_tmr_t* timers = gba->timers;
u32 old_TMCNT = timers[1].TMCNT;
((u8*)&timers[1].TMCNT)[3] = val;
bool old_enabled = (old_TMCNT >> 16) & 0x80;
bool old_cascade = (old_TMCNT >> 16) & 0b100;
bool new_enabled = (timers[1].TMCNT >> 16) & 0x80;
bool new_cascade = ((timers[1].TMCNT >> 16) & 0b100);
if(!old_enabled && new_enabled) triggerTimer(gba, 1);
else if((old_enabled && !new_enabled) || (new_enabled && !old_cascade && new_cascade)) descheduleTimer(gba, 1);
else if(new_enabled && old_cascade && !new_cascade) disableCascadeModeTimer(gba, 1);
}
return;
case 0x108:
{
gba_tmr_t* timers = gba->timers;
u32 old_TMCNT = timers[2].TMCNT;
((u8*)&timers[2].TMCNT)[0] = val;
bool old_enabled = (old_TMCNT >> 16) & 0x80;
bool old_cascade = (old_TMCNT >> 16) & 0b100;
bool new_enabled = (timers[2].TMCNT >> 16) & 0x80;
bool new_cascade = ((timers[2].TMCNT >> 16) & 0b100);
if(!old_enabled && new_enabled) triggerTimer(gba, 2);
else if((old_enabled && !new_enabled) || (new_enabled && !old_cascade && new_cascade)) descheduleTimer(gba, 2);
else if(new_enabled && old_cascade && !new_cascade) disableCascadeModeTimer(gba, 2);
}
return;
case 0x109:
{
gba_tmr_t* timers = gba->timers;
u32 old_TMCNT = timers[2].TMCNT;
((u8*)&timers[2].TMCNT)[1] = val;
bool old_enabled = (old_TMCNT >> 16) & 0x80;
bool old_cascade = (old_TMCNT >> 16) & 0b100;
bool new_enabled = (timers[2].TMCNT >> 16) & 0x80;
bool new_cascade = ((timers[2].TMCNT >> 16) & 0b100);
if(!old_enabled && new_enabled) triggerTimer(gba, 2);
else if((old_enabled && !new_enabled) || (new_enabled && !old_cascade && new_cascade)) descheduleTimer(gba, 2);
else if(new_enabled && old_cascade && !new_cascade) disableCascadeModeTimer(gba, 2);
}
return;
case 0x10A:
{
gba_tmr_t* timers = gba->timers;
u32 old_TMCNT = timers[2].TMCNT;
((u8*)&timers[2].TMCNT)[2] = val;
bool old_enabled = (old_TMCNT >> 16) & 0x80;
bool old_cascade = (old_TMCNT >> 16) & 0b100;
bool new_enabled = (timers[2].TMCNT >> 16) & 0x80;
bool new_cascade = ((timers[2].TMCNT >> 16) & 0b100);
if(!old_enabled && new_enabled) triggerTimer(gba, 2);
else if((old_enabled && !new_enabled) || (new_enabled && !old_cascade && new_cascade)) descheduleTimer(gba, 2);
else if(new_enabled && old_cascade && !new_cascade) disableCascadeModeTimer(gba, 2);
}
return;
case 0x10B:
{
gba_tmr_t* timers = gba->timers;
u32 old_TMCNT = timers[2].TMCNT;
((u8*)&timers[2].TMCNT)[3] = val;
bool old_enabled = (old_TMCNT >> 16) & 0x80;
bool old_cascade = (old_TMCNT >> 16) & 0b100;
bool new_enabled = (timers[2].TMCNT >> 16) & 0x80;
bool new_cascade = ((timers[2].TMCNT >> 16) & 0b100);
if(!old_enabled && new_enabled) triggerTimer(gba, 2);
else if((old_enabled && !new_enabled) || (new_enabled && !old_cascade && new_cascade)) descheduleTimer(gba, 2);
else if(new_enabled && old_cascade && !new_cascade) disableCascadeModeTimer(gba, 2);
}
return;
case 0x10C:
{
gba_tmr_t* timers = gba->timers;
u32 old_TMCNT = timers[3].TMCNT;
((u8*)&timers[3].TMCNT)[0] = val;
bool old_enabled = (old_TMCNT >> 16) & 0x80;
bool old_cascade = (old_TMCNT >> 16) & 0b100;
bool new_enabled = (timers[3].TMCNT >> 16) & 0x80;
bool new_cascade = ((timers[3].TMCNT >> 16) & 0b100);
if(!old_enabled && new_enabled) triggerTimer(gba, 3);
else if((old_enabled && !new_enabled) || (new_enabled && !old_cascade && new_cascade)) descheduleTimer(gba, 3);
else if(new_enabled && old_cascade && !new_cascade) disableCascadeModeTimer(gba, 3);
}
return;
case 0x10D:
{
gba_tmr_t* timers = gba->timers;
u32 old_TMCNT = timers[3].TMCNT;
((u8*)&timers[3].TMCNT)[1] = val;
bool old_enabled = (old_TMCNT >> 16) & 0x80;
bool old_cascade = (old_TMCNT >> 16) & 0b100;
bool new_enabled = (timers[3].TMCNT >> 16) & 0x80;
bool new_cascade = ((timers[3].TMCNT >> 16) & 0b100);
if(!old_enabled && new_enabled) triggerTimer(gba, 3);
else if((old_enabled && !new_enabled) || (new_enabled && !old_cascade && new_cascade)) descheduleTimer(gba, 3);
else if(new_enabled && old_cascade && !new_cascade) disableCascadeModeTimer(gba, 3);
}
return;
case 0x10E:
{
gba_tmr_t* timers = gba->timers;
u32 old_TMCNT = timers[3].TMCNT;
((u8*)&timers[3].TMCNT)[2] = val;
bool old_enabled = (old_TMCNT >> 16) & 0x80;
bool old_cascade = (old_TMCNT >> 16) & 0b100;
bool new_enabled = (timers[3].TMCNT >> 16) & 0x80;
bool new_cascade = ((timers[3].TMCNT >> 16) & 0b100);
if(!old_enabled && new_enabled) triggerTimer(gba, 3);
else if((old_enabled && !new_enabled) || (new_enabled && !old_cascade && new_cascade)) descheduleTimer(gba, 3);
else if(new_enabled && old_cascade && !new_cascade) disableCascadeModeTimer(gba, 3);
}
return;
case 0x10F:
{
gba_tmr_t* timers = gba->timers;
u32 old_TMCNT = timers[3].TMCNT;
((u8*)&timers[3].TMCNT)[3] = val;
bool old_enabled = (old_TMCNT >> 16) & 0x80;
bool old_cascade = (old_TMCNT >> 16) & 0b100;
bool new_enabled = (timers[3].TMCNT >> 16) & 0x80;
bool new_cascade = ((timers[3].TMCNT >> 16) & 0b100);
if(!old_enabled && new_enabled) triggerTimer(gba, 3);
else if((old_enabled && !new_enabled) || (new_enabled && !old_cascade && new_cascade)) descheduleTimer(gba, 3);
else if(new_enabled && old_cascade && !new_cascade) disableCascadeModeTimer(gba, 3);
}
return;
case 0x134:
((u8*)&gba->RCNT)[0] = val;
return;
case 0x135:
((u8*)&gba->RCNT)[1] = val;
return;
case 0x200:
((u8*)&gba->IE)[0] = val;
checkInterrupts(gba);
return;
case 0x201:
((u8*)&gba->IE)[1] = val;
checkInterrupts(gba);
return;
case 0x202:
((u8*)&gba->IF)[0] &= ~(val);
return;
case 0x203:
((u8*)&gba->IF)[1] &= ~(val);
return;
case 0x204:
((u8*)&gba->WAITCNT)[0] = val;
return;
case 0x205:
((u8*)&gba->WAITCNT)[1] = val;
return;
case 0x208:
((u8*)&gba->IME)[0] = val;
checkInterrupts(gba);
return;
case 0x209:
((u8*)&gba->IME)[1] = val;
checkInterrupts(gba);
return;
case 0x300:
gba->POSTFLG = val;
return;
case 0x301:
gba->HALTCNT = true;
return;
default:
return;
};
}
