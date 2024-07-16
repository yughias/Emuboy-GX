#include <stdio.h>
#include <stdlib.h>

#define GEN(x) printf(#x "\n")
#define GEN_CASE printf("case 0x%X:\n", case_addr);

void generateSwitchCase(int addr);

int main(int argc, const char* argv[]){
    if(argc != 2){
        printf("<name.exe> <output_file>\n");
        exit(1);
    }

    freopen(argv[1], "w", stdout);

    GEN(u8 readIo8(arm7tdmi_t* cpu, u16 addr){);
    GEN(gba_t* gba = (gba_t*)cpu->master;);
    GEN(ppu_t* ppu = &gba->ppu;);
    GEN(apu_t* apu = &gba->apu;);

    GEN(switch(addr){);

    for(int i = 0; i <= 0xFFFF; i++){
        generateSwitchCase(i | 0x4000000);
    }

    GEN(default:);
    GEN(return readOpenBus(cpu) >> ((addr & 0b11) << 3););
    GEN(};);
    GEN(});
}

void generateSwitchCase(int addr){
    int case_addr = addr - 0x4000000;

    for(int i = 0; i < 4; i++){
        if(addr >= 0x4000008 + 0x2*i && addr < 0x4000008 + 0x2*(i+1)){
            addr -= 0x4000008 + 0x2*i;
            GEN_CASE;
            printf("return ((u8*)&ppu->BGCNT[%d])[%d];\n", i, addr);
            return;
        }
    }

    if(addr >= 0x4000048 && addr < 0x400004A){
        addr -= 0x4000048;
        GEN_CASE;
        printf("return ((u8*)&ppu->WININ)[%d];\n", addr);
        return;
    }

    if(addr >= 0x4000080 && addr < 0x4000082){
        addr -= 0x4000080;
        GEN_CASE;
        printf("return ((u8*)&apu->SOUNDCNT_L)[%d];\n", addr);
        return;
    }
    
    if(addr >= 0x4000082 && addr < 0x4000084){
        addr -= 0x4000082;
        GEN_CASE;
        printf("return ((u8*)&apu->SOUNDCNT_H)[%d];\n", addr);
        return;
    }

    if(addr >= 0x4000088 && addr < 0x400008A){
        addr -= 0x4000088;
        GEN_CASE;
        printf("return ((u8*)&apu->SOUNDBIAS)[%d];\n", addr);
        return;
    }

    if(addr >= 0x400004A && addr < 0x400004C){
        addr -= 0x400004A;
        GEN_CASE;
        printf("return ((u8*)&ppu->WINOUT)[%d];\n", addr);
        return;
    }

    for(int i = 0; i < 4; i++){
        if(addr >= 0x40000B8 + 0xC*i && addr < 0x40000B8 + 0xC*i + 4){    
            addr -= 0x40000B8 + 0xC*i;
            GEN_CASE;
            if(addr <= 1)
                GEN(return 0;);
            else
                printf("return ((u8*)&gba->dmas[%d].DMACNT)[%d];\n", i, addr);
            return;
        }
    }

    for(int i = 0; i < 4; i++){
        if(addr >= 0x4000100 + i*4 && addr < 0x4000100 + (i+1)*4){
            addr -=  0x4000100 + i*4;
            GEN_CASE;
            if(addr < 2){
                printf("updateTimerCounter(gba, %d);\n", i);
                printf("return ((u8*)&gba->timers[%d].counter)[%d];\n", i, addr);
            } else {
                printf("return ((u8*)&gba->timers[%d].TMCNT)[%d];\n", i, addr);
            } return;
        }
    }

    if(addr >= 0x4000130 && addr < 0x4000132){
        addr -= 0x4000130;
        GEN_CASE;
        printf("return ((u8*)&gba->KEYINPUT)[%d];\n", addr);
        return;
    }

    if(addr >= 0x4000132 && addr < 0x4000134){
        addr -= 0x4000132;
        GEN_CASE;
        printf("return ((u8*)&gba->KEYCNT)[%d];\n", addr);
        return;
    }

    if(addr >= 0x4000000 && addr < 0x4000002){
        addr -= 0x4000000;
        GEN_CASE;
        printf("return ((u8*)&ppu->DISPCNT)[%d];\n", addr);
        return;
    }

    if(addr >= 0x4000004 && addr < 0x4000006){
        addr -= 0x4000004;
        GEN_CASE;
        GEN(composeDispstat(ppu););
        printf("return ((u8*)&ppu->DISPSTAT)[%d];\n", addr);
        return;
    }

    if(addr >= 0x4000006 && addr < 0x4000008){
        addr -= 0x4000006;
        GEN_CASE;
        printf("return ((u8*)&ppu->VCOUNT)[%d];\n", addr);
        return;
    }

    
    if(addr >= 0x4000050 && addr < 0x4000052){
        addr -= 0x4000050;
        GEN_CASE;
        printf("return ((u8*)&ppu->BLDCNT)[%d];\n", addr);
        return;
    }

    if(addr >= 0x4000052 && addr < 0x4000054){
        addr -= 0x4000052;
        GEN_CASE;
        printf("return ((u8*)&ppu->BLDALPHA)[%d];\n", addr);
        return;
    }

    if(addr >= 0x4000134 && addr < 0x4000136){
        addr -= 0x4000134;
        GEN_CASE;
        printf("return ((u8*)&gba->RCNT)[%d];\n", addr);
        return;
    }

    if(addr >= 0x4000200 && addr < 0x4000202){
        addr -= 0x4000200;
        GEN_CASE;
        printf("return ((u8*)&gba->IE)[%d];\n", addr);
        return;
    }

    
    if(addr >= 0x4000202 && addr < 0x4000204){
        addr -= 0x4000202;
        GEN_CASE;
        printf("return ((u8*)&gba->IF)[%d];\n", addr);
        return;
    }

    if(addr >= 0x4000204 && addr < 0x4000206){
        addr -= 0x4000204;
        GEN_CASE;
        printf("return ((u8*)&gba->WAITCNT)[%d];\n", addr);
        return;
    }

    if(addr >= 0x4000208 && addr < 0x400020A){
        addr -= 0x4000208;
        GEN_CASE;
        printf("return ((u8*)&gba->IME)[%d];\n", addr);
        return;
    }

    if(addr == 0x4000300){
        GEN_CASE;
        GEN(return gba->POSTFLG;);
        return;
    }
}

