#ifndef __ALU_H__
#define __ALU_H__

#include "arm7tdmi/arm7tdmi.h"
#include "integer.h"

#include <stdio.h>

#define INLINE static inline __attribute__ ((always_inline))

typedef bool (*condFunc)(arm7tdmi_t* cpu);
typedef void (*dataProcessingFunc)(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s);  

INLINE u8 readByteS(arm7tdmi_t* cpu, u32 addr){
    cpu->cycles += S_CYCLES;
    return cpu->readByte(cpu, addr);
}

INLINE u16 readHalfWordS(arm7tdmi_t* cpu, u32 addr){
    cpu->cycles += S_CYCLES;
    return cpu->readHalfWord(cpu, addr);
}

INLINE u32 readWordS(arm7tdmi_t* cpu, u32 addr){
    cpu->cycles += S_CYCLES;
    return cpu->readWord(cpu, addr);
}

INLINE u8 readByteN(arm7tdmi_t* cpu, u32 addr){
    cpu->cycles += N_CYCLES;
    return cpu->readByte(cpu, addr);
}

INLINE u16 readHalfWordN(arm7tdmi_t* cpu, u32 addr){
    cpu->cycles += N_CYCLES;
    return cpu->readHalfWord(cpu, addr);
}

INLINE u32 readWordN(arm7tdmi_t* cpu, u32 addr){
    cpu->cycles += N_CYCLES;
    return cpu->readWord(cpu, addr);
}

INLINE void writeByteS(arm7tdmi_t* cpu, u32 addr, u8 val){
    cpu->cycles += S_CYCLES;
    cpu->writeByte(cpu, addr, val);
}

INLINE void writeHalfWordS(arm7tdmi_t* cpu, u32 addr, u16 val){
    cpu->cycles += S_CYCLES;
    cpu->writeHalfWord(cpu, addr, val);
}

INLINE void writeWordS(arm7tdmi_t* cpu, u32 addr, u32 val){
    cpu->cycles += S_CYCLES;
    cpu->writeWord(cpu, addr, val);
}

INLINE void writeByteN(arm7tdmi_t* cpu, u32 addr, u8 val){
    cpu->cycles += N_CYCLES;
    cpu->writeByte(cpu, addr, val);
}

INLINE void writeHalfWordN(arm7tdmi_t* cpu, u32 addr, u16 val){
    cpu->cycles += N_CYCLES;
    cpu->writeHalfWord(cpu, addr, val);
}

INLINE void writeWordN(arm7tdmi_t* cpu, u32 addr, u32 val){
    cpu->cycles += N_CYCLES;
    cpu->writeWord(cpu, addr, val);
}

INLINE bool cond_EQ(arm7tdmi_t* cpu){ return cpu->Z_FLAG; }
INLINE bool cond_NE(arm7tdmi_t* cpu){ return !cpu->Z_FLAG; }
INLINE bool cond_CS(arm7tdmi_t* cpu){ return cpu->C_FLAG; }
INLINE bool cond_CC(arm7tdmi_t* cpu){ return !cpu->C_FLAG; }
INLINE bool cond_MI(arm7tdmi_t* cpu){ return cpu->N_FLAG; }
INLINE bool cond_PL(arm7tdmi_t* cpu){ return !cpu->N_FLAG; }
INLINE bool cond_VS(arm7tdmi_t* cpu){ return cpu->V_FLAG; }
INLINE bool cond_VC(arm7tdmi_t* cpu){ return !cpu->V_FLAG; }
INLINE bool cond_HI(arm7tdmi_t* cpu){ return cpu->C_FLAG && !cpu->Z_FLAG; }
INLINE bool cond_LS(arm7tdmi_t* cpu){ return !cpu->C_FLAG || cpu->Z_FLAG; }
INLINE bool cond_GE(arm7tdmi_t* cpu){ return cpu->N_FLAG == cpu->V_FLAG; }
INLINE bool cond_LT(arm7tdmi_t* cpu){ return cpu->N_FLAG != cpu->V_FLAG; }
INLINE bool cond_GT(arm7tdmi_t* cpu){ return !cpu->Z_FLAG && (cpu->N_FLAG == cpu->V_FLAG); }
INLINE bool cond_LE(arm7tdmi_t* cpu){ return cpu->Z_FLAG || (cpu->N_FLAG != cpu->V_FLAG); }
INLINE bool cond_AL(arm7tdmi_t* cpu){ return true; }
INLINE bool cond_Undefined(arm7tdmi_t* cpu){ printf("undefined cond!\n"); arm7tdmi_print(cpu); return true; }

INLINE void alu_AND(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s){
    *rd = op1 & op2;
    if(s){
        cpu->Z_FLAG = (*rd) == 0;
        cpu->N_FLAG = *rd >> 31;
    }
}

INLINE void alu_EOR(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s){
    *rd = op1 ^ op2;
    if(s){
        cpu->N_FLAG = *rd >> 31;
        cpu->Z_FLAG = !(*rd);
    }
}

INLINE void alu_SUB(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s){
    *rd = op1 - op2;
    if(s){
        cpu->Z_FLAG = !(*rd);
        cpu->N_FLAG = *rd >> 31;
        cpu->C_FLAG = !(op1 < op2);
        cpu->V_FLAG = ((op1>>31) != (op2>>31)) && ((op1>>31) != (*rd>>31));
    }
}

INLINE void alu_RSB(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s){
    alu_SUB(cpu, rd, op2, op1, s);
}

INLINE void alu_ADD(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s){
    *rd = op1 + op2;
    if(s){
        cpu->Z_FLAG = !(*rd);
        cpu->C_FLAG = (((u32) (op1) >> 31) + ((u32) (op2) >> 31) > ((u32) (*rd) >> 31));
        cpu->N_FLAG = *rd >> 31;
        cpu->V_FLAG = ((op1>>31) == (op2>>31)) && ((op1>>31) != (*rd>>31));
    }
}

INLINE void alu_ADC(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s){
    *rd = op1 + op2 + cpu->C_FLAG;
    if(s){
        cpu->Z_FLAG = !(*rd);
        cpu->C_FLAG = (((u32) (op1) >> 31) + ((u32) (op2) >> 31) > ((u32) (*rd) >> 31));
        cpu->N_FLAG = *rd >> 31;
        cpu->V_FLAG = ((op1>>31) == (op2>>31)) && ((op1>>31) != (*rd>>31));
    }
}

INLINE void alu_SBC(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s){
    *rd = op1 - op2 - !cpu->C_FLAG;
    if(s){
        cpu->Z_FLAG = !(*rd);
        cpu->N_FLAG = *rd >> 31;
        cpu->C_FLAG = (u64)op1 >= (u64)op2 + (u64)!cpu->C_FLAG;
        cpu->V_FLAG = ((op1>>31) != (op2>>31)) && ((op1>>31) != (*rd>>31));
    }
}

INLINE void alu_RSC(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s){
    alu_SBC(cpu, rd, op2, op1, s);
}

INLINE void alu_TST(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s){
    u32 copy = *rd;
    alu_AND(cpu, rd, op1, op2, true);
    *rd = copy;
}

INLINE void alu_TEQ(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s){
    u32 copy = *rd;
    alu_EOR(cpu, rd, op1, op2, true);
    *rd = copy;
}

INLINE void alu_CMP(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s){
    u32 copy = *rd;
    alu_SUB(cpu, rd, op1, op2, true);
    *rd = copy;
}

INLINE void alu_CMN(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s){
    u32 copy = *rd;
    alu_ADD(cpu, rd, op1, op2, s);
    *rd = copy;
}

INLINE void alu_ORR(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s){    
    *rd = op1 | op2;
     if(s){
        cpu->Z_FLAG = !(*rd);
        cpu->N_FLAG = *rd >> 31;
    }
}

INLINE void alu_MOV(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s){
    *rd = op2;
    if(s){
        cpu->Z_FLAG = !(*rd);
        cpu->N_FLAG = *rd >> 31;
    }    
}

INLINE void alu_BIC(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s){
    alu_AND(cpu, rd, op1, ~op2, s);
}

INLINE void alu_MVN(arm7tdmi_t* cpu, u32* rd, u32 op1, u32 op2, bool s){
    alu_MOV(cpu, rd, op1, ~op2, s);
}

INLINE u32 alu_LSL(arm7tdmi_t* cpu, u32 val, u8 shift_amnt, bool s){
    if(s){
        if(shift_amnt > 32)
            cpu->C_FLAG = false;
        else if(shift_amnt == 32)
            cpu->C_FLAG = val & 1;
        else if(shift_amnt)
            cpu->C_FLAG = val & (1 << (32 - shift_amnt));
    }
    
    if(shift_amnt >= 32)
        return 0;
    else
        return val << shift_amnt;
}

INLINE u32 alu_LSR(arm7tdmi_t* cpu, u32 val, u8 shift_amnt, bool s){
    if(s){
        if(shift_amnt > 32)
            cpu->C_FLAG = false;
        else if(shift_amnt == 32)
            cpu->C_FLAG = val >> 31;
        else if(shift_amnt)
            cpu->C_FLAG = val & (1 << (shift_amnt - 1));
    }
    
    if(shift_amnt >= 32)
        return 0;
    else
        return val >> shift_amnt;
}

INLINE u32 alu_ASR(arm7tdmi_t* cpu, u32 val, u8 shift_amnt, bool s){
    if(s){
        if(shift_amnt >= 32)
            cpu->C_FLAG = val >> 31;
        else if(shift_amnt)
            cpu->C_FLAG = val & (1 << (shift_amnt - 1));
    }

    if(shift_amnt >= 32)
        return val >> 31 ? 0xFFFFFFFF : 0;
    else
        return (i32)val >> shift_amnt;
}

INLINE u32 alu_ROR(arm7tdmi_t* cpu, u32 val, u8 shift_amnt, bool s){
    while(shift_amnt > 32)
        shift_amnt -= 32;

    if(s){
        if(shift_amnt == 32)
            cpu->C_FLAG = val >> 31;
        else if(shift_amnt)
            cpu->C_FLAG = val & (1 << (shift_amnt - 1));
    }

    if(shift_amnt == 32)
        return val;
    else
        return val >> shift_amnt | (val & ((1 << shift_amnt) - 1)) << (32 - shift_amnt);
}

INLINE u32 alu_RRX(arm7tdmi_t* cpu, u32 val, u8 shift_amnt, bool s){
    bool new_flag = val & 1;
    val = (cpu->C_FLAG << 31) | (val >> 1);
    if(s)
        cpu->C_FLAG = new_flag;
    return val;
}

INLINE void alu_SWP(arm7tdmi_t* cpu, u32 opcode){
    bool b = (opcode >> 22) & 1;
    u32* rd = &cpu->r[(opcode >> 12) & 0xF];
    u32 rn = cpu->r[(opcode >> 16) & 0xF];
    u32 rm = cpu->r[opcode & 0xF];

    if(b){
        u8 byte = readByteN(cpu, rn);
        writeByteN(cpu, rn, rm);
        *rd = byte;
    } else {
        u32 word = readWordN(cpu, rn & ~(0b11));
        writeWordN(cpu, rn & ~(0b11), rm);
        *rd = word;
        *rd = alu_ROR(cpu, *rd, (rn & 0b11) << 3, false);
    }
}

static const condFunc condFuncs[16] = {
    &cond_EQ, &cond_NE, &cond_CS, &cond_CC,
    &cond_MI, &cond_PL, &cond_VS, &cond_VC,
    &cond_HI, &cond_LS, &cond_GE, &cond_LT,
    &cond_GT, &cond_LE, &cond_AL, &cond_Undefined
};

INLINE void arm_pipeline_refill(arm7tdmi_t* cpu){
    cpu->pipeline_opcode[0] = readWordN(cpu, cpu->r[15]);
    cpu->pipeline_opcode[1] = readWordS(cpu, cpu->r[15] + 4);
    cpu->r[15] += 4;
}

INLINE void thumb_pipeline_refill(arm7tdmi_t* cpu){
    cpu->pipeline_opcode[0] = readHalfWordN(cpu, cpu->r[15]);
    cpu->pipeline_opcode[1] = readHalfWordS(cpu, cpu->r[15] + 2);
    cpu->r[15] += 2;
}

#endif