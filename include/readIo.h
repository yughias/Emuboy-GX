u8 readIo8(arm7tdmi_t* cpu, u32 addr){
gba_t* gba = (gba_t*)cpu->master;
ppu_t* ppu = &gba->ppu;
apu_t* apu = &gba->apu;
switch(addr){
case 0x0:
return ((u8*)&ppu->DISPCNT)[0];
case 0x1:
return ((u8*)&ppu->DISPCNT)[1];
case 0x4:
composeDispstat(ppu);
return ((u8*)&ppu->DISPSTAT)[0];
case 0x5:
composeDispstat(ppu);
return ((u8*)&ppu->DISPSTAT)[1];
case 0x6:
return ((u8*)&ppu->VCOUNT)[0];
case 0x7:
return ((u8*)&ppu->VCOUNT)[1];
case 0x8:
return ((u8*)&ppu->BGCNT[0])[0];
case 0x9:
return ((u8*)&ppu->BGCNT[0])[1];
case 0xA:
return ((u8*)&ppu->BGCNT[1])[0];
case 0xB:
return ((u8*)&ppu->BGCNT[1])[1];
case 0xC:
return ((u8*)&ppu->BGCNT[2])[0];
case 0xD:
return ((u8*)&ppu->BGCNT[2])[1];
case 0xE:
return ((u8*)&ppu->BGCNT[3])[0];
case 0xF:
return ((u8*)&ppu->BGCNT[3])[1];
case 0x48:
return ((u8*)&ppu->WININ)[0];
case 0x49:
return ((u8*)&ppu->WININ)[1];
case 0x4A:
return ((u8*)&ppu->WINOUT)[0];
case 0x4B:
return ((u8*)&ppu->WINOUT)[1];
case 0x50:
return ((u8*)&ppu->BLDCNT)[0];
case 0x51:
return ((u8*)&ppu->BLDCNT)[1];
case 0x52:
return ((u8*)&ppu->BLDALPHA)[0];
case 0x53:
return ((u8*)&ppu->BLDALPHA)[1];
case 0x60:
{ u32 tmp = apu->SOUND1CNT_L & 0x7F; return ((u8*)&tmp)[0]; }
case 0x61:
{ u32 tmp = apu->SOUND1CNT_L & 0x7F; return ((u8*)&tmp)[1]; }
case 0x62:
{ u32 tmp = apu->SOUND1CNT_H & 0xFFC0; return ((u8*)&tmp)[0]; }
case 0x63:
{ u32 tmp = apu->SOUND1CNT_H & 0xFFC0; return ((u8*)&tmp)[1]; }
case 0x64:
{ u32 tmp = apu->SOUND1CNT_X & 0x4000; return ((u8*)&tmp)[0]; }
case 0x65:
{ u32 tmp = apu->SOUND1CNT_X & 0x4000; return ((u8*)&tmp)[1]; }
case 0x66:
{ u32 tmp = apu->SOUND1CNT_X & 0x4000; return ((u8*)&tmp)[2]; }
case 0x67:
{ u32 tmp = apu->SOUND1CNT_X & 0x4000; return ((u8*)&tmp)[3]; }
case 0x68:
{ u32 tmp = apu->SOUND2CNT_L & 0xFFC0; return ((u8*)&tmp)[0]; }
case 0x69:
{ u32 tmp = apu->SOUND2CNT_L & 0xFFC0; return ((u8*)&tmp)[1]; }
case 0x6A:
{ u32 tmp = apu->SOUND2CNT_L & 0xFFC0; return ((u8*)&tmp)[2]; }
case 0x6B:
{ u32 tmp = apu->SOUND2CNT_L & 0xFFC0; return ((u8*)&tmp)[3]; }
case 0x6C:
{ u32 tmp = apu->SOUND2CNT_H & 0x4000; return ((u8*)&tmp)[0]; }
case 0x6D:
{ u32 tmp = apu->SOUND2CNT_H & 0x4000; return ((u8*)&tmp)[1]; }
case 0x6E:
{ u32 tmp = apu->SOUND2CNT_H & 0x4000; return ((u8*)&tmp)[2]; }
case 0x6F:
{ u32 tmp = apu->SOUND2CNT_H & 0x4000; return ((u8*)&tmp)[3]; }
case 0x78:
{ u32 tmp = apu->SOUND4CNT_L & 0xFF00; return ((u8*)&tmp)[0]; }
case 0x79:
{ u32 tmp = apu->SOUND4CNT_L & 0xFF00; return ((u8*)&tmp)[1]; }
case 0x7A:
{ u32 tmp = apu->SOUND4CNT_L & 0xFF00; return ((u8*)&tmp)[2]; }
case 0x7B:
{ u32 tmp = apu->SOUND4CNT_L & 0xFF00; return ((u8*)&tmp)[3]; }
case 0x7C:
{ u32 tmp = apu->SOUND4CNT_H & 0x40FF; return ((u8*)&tmp)[0]; }
case 0x7D:
{ u32 tmp = apu->SOUND4CNT_H & 0x40FF; return ((u8*)&tmp)[1]; }
case 0x7E:
{ u32 tmp = apu->SOUND4CNT_H & 0x40FF; return ((u8*)&tmp)[2]; }
case 0x7F:
{ u32 tmp = apu->SOUND4CNT_H & 0x40FF; return ((u8*)&tmp)[3]; }
case 0x80:
return ((u8*)&apu->SOUNDCNT_L)[0];
case 0x81:
return ((u8*)&apu->SOUNDCNT_L)[1];
case 0x82:
return ((u8*)&apu->SOUNDCNT_H)[0];
case 0x83:
return ((u8*)&apu->SOUNDCNT_H)[1];
case 0x88:
return ((u8*)&apu->SOUNDBIAS)[0];
case 0x89:
return ((u8*)&apu->SOUNDBIAS)[1];
case 0xB8:
return 0;
case 0xB9:
return 0;
case 0xBA:
return ((u8*)&gba->dmas[0].DMACNT)[2];
case 0xBB:
return ((u8*)&gba->dmas[0].DMACNT)[3];
case 0xC4:
return 0;
case 0xC5:
return 0;
case 0xC6:
return ((u8*)&gba->dmas[1].DMACNT)[2];
case 0xC7:
return ((u8*)&gba->dmas[1].DMACNT)[3];
case 0xD0:
return 0;
case 0xD1:
return 0;
case 0xD2:
return ((u8*)&gba->dmas[2].DMACNT)[2];
case 0xD3:
return ((u8*)&gba->dmas[2].DMACNT)[3];
case 0xDC:
return 0;
case 0xDD:
return 0;
case 0xDE:
return ((u8*)&gba->dmas[3].DMACNT)[2];
case 0xDF:
return ((u8*)&gba->dmas[3].DMACNT)[3];
case 0x100:
updateTimerCounter(gba, 0);
return ((u8*)&gba->timers[0].counter)[0];
case 0x101:
updateTimerCounter(gba, 0);
return ((u8*)&gba->timers[0].counter)[1];
case 0x102:
return ((u8*)&gba->timers[0].TMCNT)[2];
case 0x103:
return ((u8*)&gba->timers[0].TMCNT)[3];
case 0x104:
updateTimerCounter(gba, 1);
return ((u8*)&gba->timers[1].counter)[0];
case 0x105:
updateTimerCounter(gba, 1);
return ((u8*)&gba->timers[1].counter)[1];
case 0x106:
return ((u8*)&gba->timers[1].TMCNT)[2];
case 0x107:
return ((u8*)&gba->timers[1].TMCNT)[3];
case 0x108:
updateTimerCounter(gba, 2);
return ((u8*)&gba->timers[2].counter)[0];
case 0x109:
updateTimerCounter(gba, 2);
return ((u8*)&gba->timers[2].counter)[1];
case 0x10A:
return ((u8*)&gba->timers[2].TMCNT)[2];
case 0x10B:
return ((u8*)&gba->timers[2].TMCNT)[3];
case 0x10C:
updateTimerCounter(gba, 3);
return ((u8*)&gba->timers[3].counter)[0];
case 0x10D:
updateTimerCounter(gba, 3);
return ((u8*)&gba->timers[3].counter)[1];
case 0x10E:
return ((u8*)&gba->timers[3].TMCNT)[2];
case 0x10F:
return ((u8*)&gba->timers[3].TMCNT)[3];
case 0x130:
return ((u8*)&gba->KEYINPUT)[0];
case 0x131:
return ((u8*)&gba->KEYINPUT)[1];
case 0x132:
return ((u8*)&gba->KEYCNT)[0];
case 0x133:
return ((u8*)&gba->KEYCNT)[1];
case 0x134:
return ((u8*)&gba->RCNT)[0];
case 0x135:
return ((u8*)&gba->RCNT)[1];
case 0x136:
return 0;
case 0x137:
return 0;
case 0x142:
return 0;
case 0x143:
return 0;
case 0x15A:
return 0;
case 0x15B:
return 0;
case 0x200:
return ((u8*)&gba->IE)[0];
case 0x201:
return ((u8*)&gba->IE)[1];
case 0x202:
return ((u8*)&gba->IF)[0];
case 0x203:
return ((u8*)&gba->IF)[1];
case 0x204:
return ((u8*)&gba->WAITCNT)[0];
case 0x205:
return ((u8*)&gba->WAITCNT)[1];
case 0x206:
return 0;
case 0x207:
return 0;
case 0x208:
return ((u8*)&gba->IME)[0];
case 0x209:
return ((u8*)&gba->IME)[1];
case 0x20A:
return 0;
case 0x20B:
return 0;
case 0x300:
return gba->POSTFLG;
case 0x302:
return 0;
case 0x303:
return 0;
default:
return readOpenBus(cpu) >> ((addr & 0b11) << 3);
};
}
