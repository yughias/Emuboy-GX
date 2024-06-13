#ifndef __ARM7TDMI_H__
#define __ARM7TDMI_H__

#include "integer.h"

typedef struct arm7tdmi_t arm7tdmi_t;
typedef u8 (*readByteFunc)(arm7tdmi_t*, u32);
typedef u16 (*readHalfWordFunc)(arm7tdmi_t*, u32);
typedef u32 (*readWordFunc)(arm7tdmi_t*, u32);
typedef void (*writeByteFunc)(arm7tdmi_t*, u32, u8);
typedef void (*writeHalfWordFunc)(arm7tdmi_t*, u32, u16);
typedef void (*writeWordFunc)(arm7tdmi_t*, u32, u32);

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

    u32 pipeline_opcode[2];

    readByteFunc readByte;
    readHalfWordFunc readHalfWord;
    readWordFunc readWord;

    writeByteFunc writeByte;
    writeHalfWordFunc writeHalfWord;
    writeWordFunc writeWord;

    u32 cycles;

    void* master;
} arm7tdmi_t;

void arm7tdmi_step(arm7tdmi_t* cpu);
void arm7tdmi_print(arm7tdmi_t* cpu);
void arm7tdmi_trigger_exception(arm7tdmi_t* cpu, u32 addr, u8 mode);
void arm7tdmi_pipeline_refill(arm7tdmi_t* cpu);

void saveBankedReg(arm7tdmi_t* cpu);
void loadBankedReg(arm7tdmi_t* cpu);
u32* getSPSR(arm7tdmi_t* cpu);


#endif