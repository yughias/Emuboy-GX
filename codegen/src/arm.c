#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define STR(x) #x "\n" 
#define GEN(x) printf(#x "\n")
#define RET printf("return; }\n"); return

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

void arm_mrs(u32 opcode);
void arm_msr(u32 opcode);
void arm_bx(u32 opcode);
void arm_b_bl(u32 opcode);
void arm_data_processing(u32 opcode);
void arm_halfword_data_transfer(u32 opcode);
void arm_single_data_transfer(u32 opcode);
void arm_block_data_transfer(u32 opcode);
void arm_multiply(u32 opcode);
void arm_multiply_long(u32 opcode);

#define ROLLER_IMM(operand, opcode, s) \
{ \
    GEN({); \
    GEN(u32 val = opcode & 0xFF;); \
    GEN(u8 rot_amnt = (opcode >> 8) & 0xF;); \
    GEN(rot_amnt <<= 1;); \
    printf("%s = alu_ROR(cpu, val, rot_amnt, %d);\n", #operand, s); \
    GEN(}); \
} \

#define SHIFTER_REG(operand, opcode, s) \
{ \
    GEN({); \
    GEN(u8 shift_amnt;); \
    GEN(u32 val = cpu->r[opcode & 0xF];); \
    bool use_reg = (opcode >> 4) & 1; \
    if(use_reg){ \
        GEN(shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;); \
    } else { \
        GEN(shift_amnt = (opcode >> 7) & 0x1F; ); \
    } \
    if(use_reg){ \
        GEN(if((opcode & 0xF) == 15)); \
        GEN(    val += 4;); \
    } \
    switch((opcode >> 5) & 0b11){ \
        case 0: \
        printf("%s = alu_LSL(cpu, val, shift_amnt, %d);\n", #operand, s); \
        break; \
\
        case 1: \
        if(!use_reg) \
            GEN(shift_amnt = !shift_amnt ? 32 : shift_amnt;); \
        printf("%s = alu_LSR(cpu, val ,shift_amnt, %d);\n", #operand, s); \
        break; \
\
        case 2: \
        if(!use_reg) \
            GEN(shift_amnt = !shift_amnt ? 32 : shift_amnt;); \
        printf("%s = alu_ASR(cpu, val, shift_amnt, %d);\n", #operand, s); \
        break; \
\
        case 3: \
        if(!use_reg) \
            printf("%s = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, %d) : alu_ROR(cpu, val, shift_amnt, %d);\n", #operand, s, s); \
        else \
            printf("%s = alu_ROR(cpu, val, shift_amnt, %d);\n", #operand, s); \
        break; \
    } \
    GEN(}); \
} \
 

const char start_src[] = 
STR(#include "arm7tdmi/arm7tdmi.h")
STR(#include "arm7tdmi/arm.h")
STR(#include "arm7tdmi/arm7tdmi_util.h")
STR()
STR(#include <stdio.h>)
STR(#include <stdlib.h>);

const char step_src[] =
STR(void arm_step(arm7tdmi_t* cpu){)
STR(    u32 opcode = cpu->pipeline_opcode[0];)
STR(    cpu->pipeline_opcode[0] = cpu->pipeline_opcode[1];)
STR(    cpu->r[15] += 4;)
STR(    cpu->pipeline_opcode[1] = readWordS(cpu, cpu->r[15]);)
STR()
STR(    u8 cond = opcode >> 28;)
STR(    if((*condFuncs[cond])(cpu) == false))
STR(        return;);


const char end_src[] =
STR(});

const char dataProcessingFuncs[][64] = {
    "alu_AND", "alu_EOR", "alu_SUB", "alu_RSB",
    "alu_ADD", "alu_ADC", "alu_SBC", "alu_RSC",
    "alu_TST", "alu_TEQ", "alu_CMP", "alu_CMN",
    "alu_ORR", "alu_MOV", "alu_BIC", "alu_MVN"
};

void generateLUT_gotoTable();
void generateLUT_data(u32 opcode);

int main(int argv, char** argc){
    if(argv != 2){
        printf("<name.exe> <output_file>\n");
        exit(1);
    }

    freopen(argc[1], "w", stdout);
    
    printf("%s\n", start_src);  

    printf("%s\n", step_src);

    generateLUT_gotoTable();
    printf("\ngoto *thumb_table[(((opcode >> 20) & 0xFF) << 4) | ((opcode >> 4) & 0xF)];\n");

    for(int high = 0; high < 256; high++)
        for(int low = 0; low < 16; low++){
            u32 opcode = (high << 20) | (low << 4);
            generateLUT_data(opcode);
        }

    printf("%s\n", end_src); 
}

void generateLUT_gotoTable(){
    printf("static void* thumb_table[1 << 12] = {");
    for(int high = 0; high < 256; high++){
        for(int low = 0; low < 16; low++){
            printf("&&arm_op_%08X", (high << 20) | (low << 4));
            if(!(high == 256 && low == 16))
                printf(", ");
        }
    }
    printf("};\n");
}

void generateLUT_data(u32 opcode){
    printf("arm_op_%08X: {\n", opcode);

    if(((opcode >> 24) & 0XF) == 0b1111){
        GEN(arm7tdmi_trigger_exception(cpu, 0x8, 0x13););
        RET;
    }

    if(
        !((opcode >> 22) & 0b111111) &&
        (((opcode >> 4) & 0xF) == 0b1001)        
    ){
        arm_multiply(opcode);
        RET;
    }

    if(
        (((opcode >> 23) & 0b11111) == 0b00001) &&
        (((opcode >> 4) & 0xF) == 0b1001)
    ){
        arm_multiply_long(opcode);
        RET;
    }


    if(
        !(opcode & 0xFFF) &&
        (((opcode >> 20) & 0b11) == 0b00) &&
        (((opcode >> 23) & 0b11111) == 0b00010)
    ){
        arm_mrs(opcode);
        RET;
    }

    if(
        (((opcode >> 23) & 0b11111) == 0b00110) && 
        (((opcode >> 20) & 0b11) == 0b10)
    ){
        arm_msr(opcode);
        RET;
    }

    if(
        (((opcode >> 23) & 0b11111) == 0b00010) && 
        (((opcode >> 20) & 0b11) == 0b10) && 
        !(((opcode >> 4) & 0xF))
    ){
        arm_msr(opcode);
        RET;
    }
    

    if(
        (((opcode >> 20) & 0xFF) == 0b00010010) &&
        (((opcode >> 4) & 0xF) == 0b0001)
    ){
        arm_bx(opcode);
        RET;
    }

    if(((opcode >> 25) & 0b111) == 0b101){
        arm_b_bl(opcode);
        RET;
    }

    if(
        ((opcode >> 26) & 0b11) == 0b01
    ){
        arm_single_data_transfer(opcode);
        RET;
    }

    if(
        !((opcode >> 25) & 0b111)  &&
        ((opcode >> 7) & 1) &&
        ((opcode >> 4) & 1)
    ){
        arm_halfword_data_transfer(opcode);
        RET;
    }

    if(((opcode >> 26) & 0b11) == 0b00){
        arm_data_processing(opcode);
        RET;
    }

    if(((opcode >> 25) & 0b111) == 0b100){
        arm_block_data_transfer(opcode);
        RET;
    }

    RET;
}


void arm_bx(u32 opcode){
    GEN(cpu->r[15] = cpu->r[opcode & 0xF];);
    GEN(cpu->thumb_mode = (cpu->r[15] & 0b1););
    GEN(cpu->r[15] &= 0xFFFFFFFE;);
    GEN(arm7tdmi_pipeline_refill(cpu););
}

void arm_b_bl(u32 opcode){
    bool link_bit = (opcode >> 24) & 1;

    if(link_bit){
        GEN(cpu->r[14] = cpu->r[15] - 4;);
    }

    GEN(u32 offset = opcode & 0xFFFFFF;);
    if(opcode & 0x800000)
        GEN(offset |= 0xFF000000;);
    GEN(offset <<= 2;);

    GEN(cpu->r[15] += offset;);
    GEN(arm7tdmi_pipeline_refill(cpu););
}

void arm_mrs(u32 opcode){
    bool p_bit = (opcode >> 22) & 1;

    if(p_bit)
        GEN(cpu->r[(opcode >> 12) & 0xF] = *getSPSR(cpu););
    else
        GEN(cpu->r[(opcode >> 12) & 0xF] = cpu->CPSR;);
}


void arm_msr(u32 opcode){
    GEN(u32 operand;);
    GEN(u8 field_mask = (opcode >> 16) & 0xF;);
    bool p = (opcode >> 22) & 1;
    bool i_bit = (opcode >> 25) & 1;
    GEN(u32 mask = 0;);
    GEN(if(field_mask & 0b1000));
    GEN(    mask |= 0xFF000000;);
    GEN(if(field_mask & 0b1));
    GEN(    mask |= 0xFF;);

    if(!i_bit) 
        GEN(operand = cpu->r[opcode & 0xF];);
    else
        ROLLER_IMM(operand, opcode, false);

    if(p){
        GEN(u32* spsr = getSPSR(cpu););
        GEN(*spsr = (*spsr & ~mask) | (operand & mask););
    } else {
        GEN(saveBankedReg(cpu););
        GEN(cpu->CPSR = (cpu->CPSR & ~mask) | (operand & mask););
        GEN(loadBankedReg(cpu););
    }
}

void arm_data_processing(u32 opcode){
    bool s_bit = (opcode >> 20) & 1;
    bool i_bit = (opcode >> 25) & 1;

    GEN(u8 rd_idx = (opcode >> 12) & 0xF;);
    GEN(u8 rn_idx = (opcode >> 16) & 0xF;);
    GEN(u32 rn = cpu->r[rn_idx];);
    GEN(u32* rd = &cpu->r[rd_idx];);
    GEN(u32 op2;);
    const char* alu_op = dataProcessingFuncs[(opcode >> 21) & 0xF];
    
    GEN(bool old_carry = cpu->C_FLAG;);
    if(i_bit){
        ROLLER_IMM(op2, opcode, s_bit);
    } else {
        SHIFTER_REG(op2, opcode, s_bit);
        if((opcode >> 4) & 1){
            GEN(if(rn_idx == 15));
            GEN(    rn += 4;);
        }
    }

    if(!strcmp(alu_op, "alu_ADC") || !strcmp(alu_op, "alu_SBC") || !strcmp(alu_op, "alu_RSB"))
        GEN(cpu->C_FLAG = old_carry;);

    printf("%s(cpu, rd, rn, op2, %d);\n", alu_op, s_bit);

    if(s_bit){
        GEN(if(rd_idx == 15){);
        GEN(    saveBankedReg(cpu););
        GEN(    cpu->CPSR = *getSPSR(cpu););
        GEN(    loadBankedReg(cpu););
        GEN(});
    }

    GEN(if(rd_idx == 15 && rn_idx != 15));
        GEN(arm7tdmi_pipeline_refill(cpu););
}

void arm_halfword_data_transfer(u32 opcode){
    bool load_bit = (opcode >> 20) & 1;
    bool up_bit = (opcode >> 23) & 1;
    bool pre_bit = (opcode >> 24) & 1;
    bool write_bit = (opcode >> 21) & 1;
    u8 operation = (opcode >> 5) & 0b11;
    GEN(u32 offset;);
    GEN(u32* rd = &cpu->r[(opcode >> 12) & 0xF];);
    GEN(u32* rn = &cpu->r[(opcode >> 16) & 0xF];);

    if((opcode >> 22) & 1)
        GEN(offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4););
    else {
        GEN(offset = cpu->r[opcode & 0xF];);
    }

    GEN(u32 addr = *rn;);

    if(pre_bit)
        printf("addr += %s;\n", up_bit ? "offset" : "-offset");

    switch (operation){
        case 0x00:
        GEN(alu_SWP(cpu, opcode););
        return;

        case 0x01:
        if(load_bit) {
            GEN(*rd = readHalfWordN(cpu, addr););
            GEN(if(addr & 1));
                GEN(*rd = (*rd >> 8) | (*rd << 24););
        } else
            GEN(writeHalfWordN(cpu, addr, *rd););
        break;

        case 0x02:
        if(load_bit){
            GEN(*rd = readByteN(cpu, addr););
            GEN(if(*rd & 0x80));
            GEN(    *rd |= 0xFFFFFF00;); 
        } else
            GEN(writeByteN(cpu, addr, *rd););
        break;

        case 0x03:
        if(load_bit){
            GEN(*rd = readHalfWordN(cpu, addr););
            GEN(if(*rd & 0x8000));
            GEN(    *rd |= 0xFFFF0000;);
            GEN(if(addr & 1));
            GEN(*rd = (*rd >> 8) | (*rd & 0x00800000 ? 0xFF000000 : 0););
        } else
            GEN(writeHalfWordN(cpu, addr, *rd););
        break;
    }

    if(!pre_bit)
        printf("addr += %s;\n", up_bit ? "offset" : "-offset");

    if(write_bit || !pre_bit){
        GEN(if(!((opcode >> 20) & 1) || rn != rd));
            GEN(*rn = addr;);
    }

}

void arm_single_data_transfer(u32 opcode){
    bool i_bit = (opcode >> 25) & 1;
    bool p_bit = (opcode >> 24) & 1;
    bool u_bit = (opcode >> 23) & 1;
    bool b_bit = (opcode >> 22) & 1;
    bool w_bit = (opcode >> 21) & 1;
    bool l_bit = (opcode >> 20) & 1;

    GEN(u32 rn_idx = (opcode >> 16) & 0xF;);
    GEN(u32 rd_idx = (opcode >> 12) & 0xF;);
    GEN(u32* rn = &cpu->r[rn_idx];);
    GEN(u32* rd = &cpu->r[rd_idx];);
    GEN(u32 addr = *rn;);
    GEN(u32 offset;);

    if(i_bit) {
        SHIFTER_REG(offset, opcode, false);
    } else
        GEN(offset = opcode & 0xFFF;);

    if(p_bit)
        printf("addr += %s;\n", u_bit ? "offset" : "-offset");

    if(l_bit){
        GEN(cpu->cycles += I_CYCLES;);
        if(b_bit)
            GEN(*rd = readByteN(cpu, addr););
        else{
            GEN(*rd = readWordN(cpu, addr););
            GEN(*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false););
            GEN(if(((opcode >> 12) & 0xF) == 15));
            GEN(    arm7tdmi_pipeline_refill(cpu););
        }
    } else {
        GEN(u32 val = *rd;);
        GEN(if(rd_idx == 15));
        GEN(    val += 4;);
        if(b_bit)
            GEN(writeByteN(cpu, addr, val););
        else
            GEN(writeWordN(cpu, addr, val););
    }

    if(!p_bit)
        printf("addr += %s;\n", u_bit ? "offset" : "-offset");

    if(w_bit || !p_bit){
        GEN(if(!((opcode >> 20) & 1) || rn != rd));
        GEN(    *rn = addr;);
    }
}

void arm_block_data_transfer(u32 opcode){
    bool p_bit = (opcode >> 24) & 1;
    bool u_bit = (opcode >> 23) & 1;
    bool s_bit = (opcode >> 22) & 1;
    bool w_bit = (opcode >> 21) & 1;
    bool l_bit = (opcode >> 20) & 1;
    GEN(u8 base_idx = (opcode >> 16) & 0xF;);
    GEN(u32* rn = &cpu->r[base_idx];);
    GEN(u16 reg_list = opcode & 0xFFFF;);
    GEN(u32* regs = cpu->r;);
    GEN(u32 addr = *rn;);

    if(!(opcode & (1 << 15)) && s_bit){
        GEN(saveBankedReg(cpu););
        GEN(regs = cpu->usr_r;);
    }

    GEN(u32 reg_count = __builtin_popcount(reg_list););
    if(!u_bit){
        GEN(addr -= reg_count*4;);
        p_bit ^= 1;
    }

    GEN(if(!reg_count){);
        if(l_bit){
            GEN(cpu->r[15] = readWordN(cpu, *rn););
            GEN(arm7tdmi_pipeline_refill(cpu););
        } else {
            if(!u_bit)
                printf("writeWordN(cpu, *rn - %s, cpu->r[15] + 4);\n", p_bit ? "0x3C" : "0x40");
            else
                printf("writeWordN(cpu, *rn + %s, cpu->r[15] + 4);\n", p_bit ? "0x04" : "0x00");
        }
        if(!u_bit)
            GEN(cpu->r[base_idx] -= 0x40;);
        else
            GEN(cpu->r[base_idx] += 0x40;);
    GEN(} else {);
        GEN(bool first_transfer = true;);
        GEN(for(int i = 0; i < 16 && reg_list; i++){);
        GEN(    bool should_transfer = reg_list & 1;);
        GEN(    reg_list >>= 1;);
        GEN(    if(!should_transfer));
        GEN(        continue;);

            if(p_bit)
                GEN(addr += 4;);

            if(l_bit){
                GEN(regs[i] = readWordN(cpu, addr););
                GEN(if(i == 15){);
                GEN(    arm7tdmi_pipeline_refill(cpu););
                    if(s_bit){
                GEN(        printf("S BIT ON ARM PUSH/POP NOT IMPLEMENTED\n"););
                    }
                GEN(});
            } else {
                GEN(if(i == base_idx && !first_transfer) {);
                    if(!u_bit)
                        GEN(writeWordN(cpu, addr, *rn - (reg_count << 2)););
                    else
                        GEN(writeWordN(cpu, addr, *rn + (reg_count << 2)););
                GEN(} else);
                    GEN(writeWordN(cpu, addr, i == 15 ? regs[i] + 4 : regs[i]););
            }

            if(!p_bit)
                GEN(addr += 4;);
            
            GEN(first_transfer = false;);
        GEN(});

        if(!u_bit)
            GEN(addr -= reg_count*4;);

        
        GEN(reg_list = opcode & 0xFFFF;);
        if(!(opcode & (1 << 15)) && s_bit)
            GEN(loadBankedReg(cpu););

        
        if(w_bit){
            if(!((opcode >> 20) & 1))
                GEN(*rn = addr;);
            else{
                GEN(if(!(reg_list & (1 << base_idx))));
                GEN(    *rn = addr;);
            }
        }
    GEN(});
}

void arm_multiply(u32 opcode){
    bool a = (opcode >> 21) & 1;
    bool s = (opcode >> 20) & 1;

    GEN(u32 rm = cpu->r[opcode & 0xF];);
    GEN(u32 rs = cpu->r[(opcode >> 8) & 0xF];);
    GEN(u32 rn = cpu->r[(opcode >> 12) & 0xF];);
    GEN(u32* rd = &cpu->r[(opcode >> 16) & 0xF];);
    
    GEN(*rd = ((i32)rm) * ((i32)rs););
    
    if(a)
        GEN(*rd += rn;);

    if(s){
        GEN(cpu->Z_FLAG = !(*rd););
        GEN(cpu->N_FLAG = *rd >> 31;);
    }
}

void arm_multiply_long(u32 opcode){
    bool u = (opcode >> 22) & 1;
    bool a = (opcode >> 21) & 1;
    bool s = (opcode >> 20) & 1;

    GEN(u32 rm = cpu->r[opcode & 0xF];);
    GEN(u32 rs = cpu->r[(opcode >> 8) & 0xF];);
    GEN(u32* rd_lo = &cpu->r[(opcode >> 12) & 0xF];);
    GEN(u32* rd_hi = &cpu->r[(opcode >> 16) & 0xF];);
    GEN(u64 result;);

    if(u)
        GEN(result = ((i64)(i32)rm) * ((i64)(i32)rs););
    else
        GEN(result = ((u64)rm) * ((u64)rs););

    if(a)
        GEN(result += (((u64)*rd_hi) << 32) | (u64)(*rd_lo););

    GEN(*rd_hi = result >> 32;);
    GEN(*rd_lo = result;);

    if(s){
        GEN(cpu->Z_FLAG = !result;);
        GEN(cpu->N_FLAG = result >> 63;);
    }
}

/*
u32 arm_shifter_reg(arm7tdmi_t* cpu, u32 opcode, bool s){
    u8 shift_amnt;
    u32 val = cpu->r[opcode & 0xF];  
    bool use_reg = (opcode >> 4) & 1;

    if(use_reg){
        shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
    } else {
        shift_amnt = (opcode >> 7) & 0x1F;
    }

    if((opcode & 0xF) == 15 && use_reg){
        // pipeline edge case
        val += 4;
    }

    switch((opcode >> 5) & 0b11){
        case 0:
        return alu_LSL(cpu, val, shift_amnt, s);

        case 1:
        shift_amnt = !shift_amnt && !use_reg ? 32 : shift_amnt;
        return alu_LSR(cpu, val ,shift_amnt, s);

        case 2:
        shift_amnt = !shift_amnt && !use_reg ? 32 : shift_amnt;
        return alu_ASR(cpu, val, shift_amnt, s);

        case 3:
        return !shift_amnt && !use_reg ? alu_RRX(cpu, val, shift_amnt, s) : alu_ROR(cpu, val, shift_amnt, s);
        break;
    }
}
*/