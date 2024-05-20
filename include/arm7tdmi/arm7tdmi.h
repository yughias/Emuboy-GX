#ifndef __ARM7TDMI_H__
#define __ARM7TDMI_H__

#include "integer.h"

typedef struct arm7tdmi_t arm7tdmi_t;
typedef u8 (*readFunc)(arm7tdmi_t*, u32);
typedef void (*writeFunc)(arm7tdmi_t*, u32, u8);

typedef struct arm7tdmi_t {
    u32 r[16];
    u32 usr_r[16];
    u32 irq_r[2];
    u32 svc_r[2];
    u32 fiq_r[7];
    
    union {
        u32 CPSR;
        struct {
            u8 mode_bits : 5;
            bool thumb_mode : 1;
            bool fiq_disable : 1;
            bool irq_disable : 1;
            u8 not_used2 : 8;
            u8 not_used3 : 8;
            u8 not_used4: 4;
            bool V_FLAG : 1;
            bool C_FLAG : 1;
            bool Z_FLAG : 1;
            bool N_FLAG : 1;
        };
    };

    u32 SPSR_fiq;
    u32 SPSR_svc;
    u32 SPSR_irq;

    bool pipeline_valid;
    u32 pipeline_opcode;

    readFunc readByte;
    writeFunc writeByte;

    void* master;
} arm7tdmi_t;

void arm7tdmi_step(arm7tdmi_t* cpu);
void arm7tdmi_print(arm7tdmi_t* cpu);
void arm7tdmi_trigger_exception(arm7tdmi_t* cpu, u32 addr, u8 mode);

u32 readWord(arm7tdmi_t* cpu, u32 addr);
u16 readHalfWord(arm7tdmi_t* cpu, u32 addr);
void writeWord(arm7tdmi_t* cpu, u32 addr, u32 word);
void writeHalfWord(arm7tdmi_t* cpu, u32 addr, u16 halfword);

void saveBankedReg(arm7tdmi_t* cpu);
void loadBankedReg(arm7tdmi_t* cpu);
u32* getSPSR(arm7tdmi_t* cpu);

#endif