#include "arm7tdmi/arm7tdmi.h"
#include "arm7tdmi/arm.h"
#include "arm7tdmi/thumb.h"
#include "integer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void arm7tdmi_print(arm7tdmi_t* cpu){
    for(int i = 0; i < 16; i++){
        printf("r[%d]: %08X\n", i, cpu->r[i]);
    }

    u32 pc = cpu->r[15];
    if(cpu->pipeline_valid){
        if(cpu->thumb_mode)
            pc -= 2;
        else
            pc -= 4;
    }

    printf("CPSR: %08X\n", cpu->CPSR);
    printf("SPSR: %08X\n", *getSPSR(cpu));
    printf("PC: %08X\n", pc);
    printf("\n");
}

void arm7tdmi_step(arm7tdmi_t* cpu){
    static bool debug = false;    
    
    if(debug)
        arm7tdmi_print(cpu);

    if(cpu->thumb_mode)
        thumb_step(cpu);
    else
        arm_step(cpu);
}

void saveBankedReg(arm7tdmi_t* cpu){
    switch(cpu->mode_bits){
        case 0x10:
        case 0x1F:
        memcpy(cpu->usr_r, cpu->r, sizeof(u32)*16);
        break;

        case 0x11:
        memcpy(cpu->usr_r, cpu->r, sizeof(u32)*8);;
        memcpy(cpu->fiq_r, &cpu->r[8], sizeof(u32)*7);
        memcpy(&cpu->usr_r[15], &cpu->r[15], sizeof(u32)*1);
        break;

        case 0x12:
        memcpy(cpu->usr_r, cpu->r, sizeof(u32)*13);;
        memcpy(cpu->irq_r, &cpu->r[13], sizeof(u32)*2);
        memcpy(&cpu->usr_r[15], &cpu->r[15], sizeof(u32)*1);
        break;

        case 0x13:
        memcpy(cpu->usr_r, cpu->r, sizeof(u32)*13);;
        memcpy(cpu->svc_r, &cpu->r[13], sizeof(u32)*2);
        memcpy(&cpu->usr_r[15], &cpu->r[15], sizeof(u32)*1);
        break;

        default:
        printf("CANNOT DECODE MODE! 0x%X\n", cpu->mode_bits);
        exit(0);
        break;
    }
}

void loadBankedReg(arm7tdmi_t* cpu){
    switch(cpu->mode_bits){
        case 0x10:
        case 0x1F:
        memcpy(cpu->r, cpu->usr_r, sizeof(u32)*16);
        break;

        case 0x11:
        memcpy(cpu->r, cpu->usr_r, sizeof(u32)*8);
        memcpy(&cpu->r[8], cpu->fiq_r, sizeof(u32)*7);
        memcpy(&cpu->r[15], &cpu->usr_r[15], sizeof(u32)*1);
        break;

        case 0x12:
        memcpy(cpu->r, cpu->usr_r, sizeof(u32)*13);
        memcpy(&cpu->r[13], cpu->irq_r, sizeof(u32)*2);
        memcpy(&cpu->r[15], &cpu->usr_r[15], sizeof(u32)*1);
        break;

        case 0x13:
        memcpy(cpu->r, cpu->usr_r, sizeof(u32)*13);
        memcpy(&cpu->r[13], cpu->svc_r, sizeof(u32)*2);
        memcpy(&cpu->r[15], &cpu->usr_r[15], sizeof(u32)*1);
        break;

        default:
        printf("CANNOT DECODE MODE! 0x%X\n", cpu->mode_bits);
        exit(0);
        break;
    }
}

u32* getSPSR(arm7tdmi_t* cpu){
    switch(cpu->mode_bits){
        case 0x11:
        return &cpu->SPSR_fiq;

        case 0x12:
        return &cpu->SPSR_irq;

        case 0x13:
        return &cpu->SPSR_svc;

        default:
        return &cpu->CPSR;
    }
}


void arm7tdmi_trigger_exception(arm7tdmi_t* cpu, u32 addr, u8 mode){
    u8 old_mode = cpu->mode_bits;
    saveBankedReg(cpu);
    cpu->mode_bits = mode;
    *getSPSR(cpu) = (cpu->CPSR & ~(0x1F)) |  old_mode;
    loadBankedReg(cpu);
    u32 ret_addr = cpu->r[15];
    if(cpu->pipeline_valid)
        ret_addr -= cpu->thumb_mode ? 2 : 4;
    if(mode == 0x13)
        cpu->r[14] = ret_addr;
    if(mode == 0x12)
        cpu->r[14] = ret_addr + 4;
    cpu->r[15] = addr;
    saveBankedReg(cpu);
    cpu->pipeline_valid = false;
    cpu->thumb_mode = false;
    cpu->irq_disable = true;
}