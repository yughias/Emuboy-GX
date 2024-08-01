#include <stdio.h>
#include <stdlib.h>

#define GEN(x) printf(#x "\n")
#define GEN_CASE printf("case 0x%X:\n", case_addr);
#define RET GEN(return;)

void generateSwitchCase(int addr);

int main(int argc, const char* argv[]){
    if(argc != 2){
        printf("<name.exe> <output_file>\n");
        exit(1);
    }

    freopen(argv[1], "w", stdout);

    GEN(void writeIo8(arm7tdmi_t* cpu, u32 addr, u8 val){);
    GEN(gba_t* gba = (gba_t*)cpu->master;);
    GEN(ppu_t* ppu = &gba->ppu;);
    GEN(apu_t* apu = &gba->apu;);

    GEN(switch(addr){);

    for(int i = 0; i <= 0xFFFF; i++){
        generateSwitchCase(i | 0x4000000);
    }

    GEN(default:);
    RET;
    GEN(};);
    GEN(});
}

void generateSwitchCase(int addr){
    int case_addr = addr - 0x4000000;

     if(addr >= 0x4000000 && addr < 0x4000002){
        addr -= 0x4000000;
        GEN_CASE;
        printf("((u8*)&ppu->DISPCNT)[%d] = val;\n", addr);
        RET;
        return;
    }

    for(int i = 0; i < 4; i++){
        if(addr >= 0x4000008 + 0x2*i && addr < 0x4000008 + 0x2*(i+1)){
            addr -= 0x4000008 + 0x2*i;
            GEN_CASE;
            if(i <= 1 && addr == 1)
                printf("((u8*)&ppu->BGCNT[%d])[%d] = val & 0xDF;\n", i, addr);
            else 
                printf("((u8*)&ppu->BGCNT[%d])[%d] = val;\n", i, addr);
            RET;
            return;
        }
    }

    if(addr >= 0x4000004 && addr < 0x4000006){
        addr -= 0x4000004;
        GEN_CASE;
        printf("((u8*)&ppu->DISPSTAT)[%d] = val;\n", addr);
        if(addr == 1)
            printf("checkVCount(gba);\n");
        RET;
        return;
    }

    for(int i = 0; i < 4; i++){
        if(addr >= 0x4000010 + 0x4*i && addr < 0x4000010 + 0x4*i + 2){
            addr -= 0x4000010 + 0x4*i;
            GEN_CASE;
            printf("((u8*)&ppu->BGHOFS[%d])[%d] = val;\n", i, addr);
            RET;
            return;    
        }
    }


    for(int i = 0; i < 4; i++){
        if(addr >= 0x4000012 + 0x4*i && addr < 0x4000012 + 0x4*i + 2){
            addr -= 0x4000012 + 0x4*i;
            GEN_CASE;
            printf("((u8*)&ppu->BGVOFS[%d])[%d] = val;\n", i, addr);
            RET;
            return;    
        }
    }

    for(int i = 0; i < 2; i++){
        if(addr >= 0x4000028 + 0x10*i && addr < 0x4000028 + 0x10*i + 4){
            addr -= 0x4000028 + 0x10*i;
            GEN_CASE;
            printf("((u8*)&ppu->BGX[%d])[%d] = val;\n", i, addr);
            printf("ppu->INTERNAL_BGX[%d] = ppu->BGX[%d];\n", i, i);
            RET;
            return; 
        }
    }

    for(int i = 0; i < 2; i++){
        if(addr >= 0x400002C + 0x10*i && addr < 0x400002C + 0x10*i + 4){
            addr -= 0x400002C + 0x10*i;
            GEN_CASE;
            printf("((u8*)&ppu->BGY[%d])[%d] = val;\n", i, addr);
            printf("ppu->INTERNAL_BGY[%d] = ppu->BGY[%d];\n", i, i);
            RET;
            return; 
        }
    }

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            if(addr >= 0x4000020 + 0x10*i + 0x02*j && addr < 0x4000020 + 0x10*i + 0x02*j + 2){
                addr -= 0x4000020 + 0x10*i + 0x02*j;
                GEN_CASE;
                printf("((u8*)&ppu->BGP[%d])[%d] = val;\n", i*4 + j, addr);
                RET;
                return;
            }
        }
    }


    for(int i = 0; i < 2; i++){
        if(addr >= 0x4000040 + 0x2*i && addr < 0x4000040 + 0x2*(i+1)){
            addr -= 0x4000040 + 0x2*i;
            GEN_CASE;
            printf("((u8*)&ppu->WINH[%d])[%d] = val;\n", i, addr);
            RET;
            return;
        }
    }

    for(int i = 0; i < 2; i++){
        if(addr >= 0x4000044 + 0x2*i && addr < 0x4000044 + 0x2*(i+1)){
            addr -= 0x4000044 + 0x2*i;
            GEN_CASE;
            printf("((u8*)&ppu->WINV[%d])[%d] = val;\n", i, addr);
            RET;
            return;
        }
    }

    if(addr >= 0x4000048 && addr < 0x400004A){
        addr -= 0x4000048;
        GEN_CASE;
        printf("((u8*)&ppu->WININ)[%d] = val & 0x3F;\n", addr);
        RET;
        return;
    }

    if(addr >= 0x400004A && addr < 0x400004C){
        addr -= 0x400004A;
        GEN_CASE;
        printf("((u8*)&ppu->WINOUT)[%d] = val & 0x3F;\n", addr);
        RET;
        return;
    }

    if(addr >= 0x4000050 && addr < 0x4000052){
        addr -= 0x4000050;
        GEN_CASE;
        if(addr == 1)
            printf("((u8*)&ppu->BLDCNT)[%d] = val & 0x3F;\n", addr);
        else
            printf("((u8*)&ppu->BLDCNT)[%d] = val;\n", addr);
        RET;
        return;
    }

    if(addr >= 0x4000052 && addr < 0x4000054){
        addr -= 0x4000052;
        GEN_CASE;
        printf("((u8*)&ppu->BLDALPHA)[%d] = val & 0x1F;\n", addr);
        RET;
        return;
    }

    if(addr >= 0x4000054 && addr < 0x4000056){
        addr -= 0x4000054;
        GEN_CASE;
        printf("((u8*)&ppu->BLDY)[%d] = val;\n", addr);
        RET;
        return;
    }

    if(addr >= 0x4000080 && addr < 0x4000082){
        addr -= 0x4000080;
        GEN_CASE;
        if(addr == 0)
            printf("((u8*)&apu->SOUNDCNT_L)[%d] = val & 0x77;\n", addr);
        else
            printf("((u8*)&apu->SOUNDCNT_L)[%d] = val;\n", addr);
        RET;
        return;
    }

    if(addr >= 0x4000082 && addr < 0x4000084){
        addr -= 0x4000082;
        GEN_CASE;
        printf("((u8*)&apu->SOUNDCNT_H)[%d] = val;\n", addr);
        GEN(updateChannelMixing(apu););
        RET;
        return;
    }

    if(addr >= 0x4000088 && addr < 0x400008A){
        addr -= 0x4000088;
        GEN_CASE;
        printf("((u8*)&apu->SOUNDBIAS)[%d] = val;\n", addr);
        RET;
        return;
    }

    if(addr >= 0x40000A0 && addr < 0x40000A4){
        GEN_CASE;
        printf("pushIntoFifo(&apu->fifo[0], val);\n");
        RET;
        return;
    }

    if(addr >= 0x40000A4 && addr < 0x40000A8){
        GEN_CASE;
        printf("pushIntoFifo(&apu->fifo[1], val);\n");
        RET;
        return;
    }

    for(int i = 0; i < 4; i++){
        if(addr >= 0x40000B0 + 0xC*i && addr < 0x40000B0 + 0xC*(i+1)){
            addr -= 0x40000B0 + 0xC*i;
            if(addr < 0x4){
                GEN_CASE;
                printf("((u8*)&gba->dmas[%d].DMASAD)[%d] = val;\n", i, addr);
                RET;
                return;
            }

            if(addr < 0x8){
                GEN_CASE;
                printf("((u8*)&gba->dmas[%d].DMADAD)[%d] = val;\n", i, addr - 0x4);
                RET;
                return;
            }

            if(addr < 0xC){
                GEN_CASE;
                printf("{");
                printf("bool old_trigger = gba->dmas[%d].DMACNT >> 31;\n", i);
                if(addr - 0x8 == 2)
                    printf("((u8*)&gba->dmas[%d].DMACNT)[%d] = val & 0xE0;\n", i, addr - 0x8);
                else if(addr - 0x8 == 3 && i != 3)
                    printf("((u8*)&gba->dmas[%d].DMACNT)[%d] = val & 0xF7;\n", i, addr - 0x8);
                else
                    printf("((u8*)&gba->dmas[%d].DMACNT)[%d] = val;\n", i, addr - 0x8);

                printf("bool new_trigger = gba->dmas[%d].DMACNT >> 31;\n", i);
                GEN(if(!old_trigger && new_trigger));
                printf("triggerDma(gba, %d);\n", i);
                printf("}");
                RET;
                return;
            }          
        }
    }

    for(int i = 0; i < 4; i++){
        if(addr >= 0x4000100 + i*4 && addr < 0x4000100 + (i+1)*4){
            addr -=  0x4000100 + i*4;
            GEN_CASE;
            GEN({);
            GEN(gba_tmr_t* timers = gba->timers;);
            printf("u32 old_TMCNT = timers[%d].TMCNT;\n", i);
            printf("((u8*)&timers[%d].TMCNT)[%d] = val;\n", i, addr);
            GEN(bool old_enabled = (old_TMCNT >> 16) & 0x80;);
            GEN(bool old_cascade = (old_TMCNT >> 16) & 0b100;);
            printf("bool new_enabled = (timers[%d].TMCNT >> 16) & 0x80;\n", i);
            printf("bool new_cascade = ((timers[%d].TMCNT >> 16) & 0b100);\n", i);
            printf("if(!old_enabled && new_enabled) triggerTimer(gba, %d);\n", i);
            printf("else if((old_enabled && !new_enabled) || (new_enabled && !old_cascade && new_cascade)) descheduleTimer(gba, %d);\n", i);
            printf("else if(new_enabled && old_cascade && !new_cascade) disableCascadeModeTimer(gba, %d);\n", i);
            GEN(});
            RET;
            return;
        }
    }

    if(addr >= 0x4000134 && addr < 0x4000136){
        addr -= 0x4000134;
        GEN_CASE;
        printf("((u8*)&gba->RCNT)[%d] = val;\n", addr);
        RET;
        return;
    }

    if(addr >= 0x4000200 && addr < 0x4000202){
        addr -= 0x4000200;
        GEN_CASE;
        printf("((u8*)&gba->IE)[%d] = val;\n", addr);
        GEN(checkInterrupts(gba););
        RET;
        return;
    }

    
    if(addr >= 0x4000202 && addr < 0x4000204){
        addr -= 0x4000202;
        GEN_CASE;
        printf("((u8*)&gba->IF)[%d] &= ~(val);\n", addr);
        RET;
        return;
    }

    if(addr >= 0x4000204 && addr < 0x4000206){
        addr -= 0x4000204;
        GEN_CASE;
        printf("((u8*)&gba->WAITCNT)[%d] = val;\n", addr);
        RET;
        return;
    }

    if(addr >= 0x4000208 && addr < 0x400020A){
        addr -= 0x4000208;
        GEN_CASE;
        printf("((u8*)&gba->IME)[%d] = val;\n", addr);
        GEN(checkInterrupts(gba););
        RET;
        return;
    }

    if(addr == 0x4000300){
        GEN_CASE;
        GEN(gba->POSTFLG = val;);
        RET;
        return;
    }

    if(addr == 0x4000301){
        GEN_CASE;
        GEN(gba->HALTCNT = true;);
        RET;
        return;
    }
}

