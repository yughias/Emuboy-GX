#ifndef __ALU_H__
#define __ALU_H__

#include "arm7tdmi/arm7tdmi.h"
#include "integer.h"

#include <stdio.h>

typedef bool (*condFunc)(arm7tdmi_t* cpu);
typedef void (*dataProcessingFunc)(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s);  

bool cond_EQ(arm7tdmi_t*);
bool cond_NE(arm7tdmi_t*);
bool cond_CS(arm7tdmi_t*);
bool cond_CC(arm7tdmi_t*);
bool cond_MI(arm7tdmi_t*);
bool cond_PL(arm7tdmi_t*);
bool cond_VS(arm7tdmi_t*);
bool cond_VC(arm7tdmi_t*);
bool cond_HI(arm7tdmi_t*);
bool cond_LS(arm7tdmi_t*);
bool cond_GE(arm7tdmi_t*);
bool cond_LT(arm7tdmi_t*);
bool cond_GT(arm7tdmi_t*);
bool cond_LE(arm7tdmi_t*);
bool cond_AL(arm7tdmi_t*);
bool cond_Undefined(arm7tdmi_t*);

void alu_AND(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s);
void alu_EOR(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s);
void alu_SUB(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s);
void alu_RSB(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s);
void alu_ADD(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s);
void alu_ADC(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s);
void alu_SBC(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s);
void alu_RSC(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s);
void alu_TST(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s);
void alu_TEQ(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s);
void alu_CMP(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s);
void alu_CMN(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s);
void alu_ORR(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s);
void alu_MOV(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s);
void alu_BIC(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s);
void alu_MVN(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s);
void alu_SWP(arm7tdmi_t* cpu, u32 opcode);

u32 alu_LSL(arm7tdmi_t* cpu, u32 val, u8 shift_amnt, bool s);
u32 alu_LSR(arm7tdmi_t* cpu, u32 val, u8 shift_amnt, bool s);
u32 alu_ASR(arm7tdmi_t* cpu, u32 val, u8 shift_amnt, bool s);
u32 alu_ROR(arm7tdmi_t* cpu, u32 val, u8 shift_amnt, bool s);
u32 alu_RRX(arm7tdmi_t* cpu, u32 val, u8 shift_amnt, bool s);

extern condFunc condFuncs[16];
extern dataProcessingFunc dataProcFuncs[16];

#endif