#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define STR(x) #x "\n" 
#define GEN(x) printf(#x "\n")
#define RET printf("return; }\n");

#define LOOP(x, limit) for(int x = 0; x < (limit); x++)

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

void arm_mrs(bool p_bit);
void arm_msr(bool p, bool i_bit);
void arm_bx();
void arm_b_bl(bool link_bit, bool sign);
void arm_data_processing(bool s_bit, bool i_bit, int op4, int bit456);
void arm_halfword_data_transfer(bool load_bit, bool up_bit, bool pre_bit, bool write_bit, int op2, bool opcodeBit22);
void arm_single_data_transfer(bool i_bit, bool p_bit, bool u_bit, bool b_bit, bool w_bit, bool l_bit, int bit456);
void arm_block_data_transfer(bool p_bit, bool u_bit, bool s_bit, bool w_bit, bool l_bit, bool bit15);
void arm_multiply(bool a, bool s);
void arm_multiply_long(bool u, bool a, bool s);

#define ROLLER_IMM(operand, opcode, s) \
{ \
    GEN({); \
    GEN(u32 val = opcode & 0xFF;); \
    GEN(u8 rot_amnt = (opcode >> 8) & 0xF;); \
    GEN(rot_amnt <<= 1;); \
    printf("%s = alu_ROR(cpu, val, rot_amnt, %d);\n", #operand, s); \
    GEN(}); \
} \

#define SHIFTER_REG(operand, bit456, s) \
{ \
    GEN({); \
    GEN(u8 shift_amnt;); \
    GEN(u32 val = cpu->r[opcode & 0xF];); \
    bool use_reg = (bit456) & 1; \
    if(use_reg){ \
        GEN(shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;); \
        GEN(cpu->cycles += I_CYCLES;); \
    } else { \
        GEN(shift_amnt = (opcode >> 7) & 0x1F; ); \
    } \
    if(use_reg){ \
        GEN(if((opcode & 0xF) == 15)); \
        GEN(    val += 4;); \
    } \
    switch((bit456 >> 1) & 0b11){ \
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
void generateLUT_data();

int main(int argv, char** argc){
    if(argv != 2){
        printf("<name.exe> <output_file>\n");
        exit(1);
    }

    freopen(argc[1], "w", stdout);
    
    printf("%s\n", start_src);  

    printf("%s\n", step_src);

    generateLUT_gotoTable();
    printf("\ngoto *arm_table[(((opcode >> 20) & 0xFF) << 4) | ((opcode >> 4) & 0xF)];\n");
    GEN();
    generateLUT_data();
    
    printf("%s\n", end_src); 
}

void generateLUT_gotoTable(){
    printf("static void* arm_table[1 << 12] = {");
    for(int high = 0; high < 256; high++){
        for(int low = 0; low < 16; low++){
            int opcode = (high << 20) | (low << 4);
        
            printf("&&");

            if(((opcode >> 24) & 0XF) == 0b1111){
                printf("swi, ");
                continue;
            }

            if(
                !((opcode >> 22) & 0b111111) &&
                (((opcode >> 4) & 0xF) == 0b1001)        
            ){
                printf("arm_multiply_%X_%X, ", (opcode >> 21) & 1, (opcode >> 20) & 1);
                continue;
            }

            if(
                (((opcode >> 23) & 0b11111) == 0b00001) &&
                (((opcode >> 4) & 0xF) == 0b1001)
            ){
                printf("arm_multiply_long_%X_%X_%X, ", (opcode >> 22) & 1, (opcode >> 21) & 1, (opcode >> 20) & 1);
                continue;
            }


            if(
                !(opcode & 0xFFF) &&
                (((opcode >> 20) & 0b11) == 0b00) &&
                (((opcode >> 23) & 0b11111) == 0b00010)
            ){
                printf("arm_mrs_%X, ", (opcode >> 22) & 1);
                continue;
            }

            if(
                (((opcode >> 23) & 0b11111) == 0b00110) && 
                (((opcode >> 20) & 0b11) == 0b10)
            ){
                printf("arm_msr_%X_%X, ", (opcode >> 22) & 1, (opcode >> 25) & 1);
                continue;
            }

            if(
                (((opcode >> 23) & 0b11111) == 0b00010) && 
                (((opcode >> 20) & 0b11) == 0b10) && 
                !(((opcode >> 4) & 0xF))
            ){
                printf("arm_msr_%X_%X, ", (opcode >> 22) & 1, (opcode >> 25) & 1);
                continue;
            }
            

            if(
                (((opcode >> 20) & 0xFF) == 0b00010010) &&
                (((opcode >> 4) & 0xF) == 0b0001)
            ){
                printf("arm_bx, ");
                continue;
            }

            if(((opcode >> 25) & 0b111) == 0b101){
                printf("arm_b_bl_%X_%X, ", (opcode >> 24) & 1, (opcode >> 23) & 1);
                continue;
            }

            if(
                ((opcode >> 26) & 0b11) == 0b01
            ){
                printf("arm_single_data_transfer_%X_%X_%X_%X_%X_%X_%X, ",
                    (opcode >> 25) & 1,
                    (opcode >> 24) & 1,
                    (opcode >> 23) & 1,
                    (opcode >> 22) & 1,
                    (opcode >> 21) & 1,
                    (opcode >> 20) & 1,
                    (opcode >> 4) & 0b111
                );
                continue;
            }

            if(
                !((opcode >> 25) & 0b111)  &&
                ((opcode >> 7) & 1) &&
                ((opcode >> 4) & 1)
            ){
                printf("arm_halfword_data_transfer_%X_%X_%X_%X_%X_%X, ",
                    (opcode >> 20) & 1,
                    (opcode >> 23) & 1,
                    (opcode >> 24) & 1,
                    (opcode >> 21) & 1,
                    (opcode >> 5) & 0b11,
                    (opcode >> 22) & 0b1
                );
                continue;
            }

            if(((opcode >> 26) & 0b11) == 0b00){
                printf("arm_data_processing_%X_%X_%X_%X, ",
                    (opcode >> 20) & 1,
                    (opcode >> 25) & 1,
                    (opcode >> 21) & 0xF,
                    (opcode >> 4) & 0b111
                );
                continue;
            }

            if(((opcode >> 25) & 0b111) == 0b100){
                printf("arm_block_data_transfer_%X_%X_%X_%X_%X_%X, ",
                    (opcode >> 24) & 1,
                    (opcode >> 23) & 1,
                    (opcode >> 22) & 1,
                    (opcode >> 21) & 1,
                    (opcode >> 20) & 1,  
                    (opcode >> 15) & 1
                );
                continue;
            }

            printf("arm_not_decoded, ");
        }
    }
    printf("};\n");
}

void generateLUT_data(){
    GEN(swi:{);
    GEN(arm7tdmi_trigger_exception(cpu, 0x8, 0x13););
    RET;

    LOOP(p_bit, 2)
        arm_mrs(p_bit);
    
    LOOP(p, 2)
    LOOP(i_bit, 2)
        arm_msr(p, i_bit);
    
    arm_bx();
    
    LOOP(link_bit, 2)
    LOOP(sign, 2)
        arm_b_bl(link_bit, sign);
    
    LOOP(s_bit, 2)
    LOOP(i_bit, 2)
    LOOP(op4, 1 << 4)
    LOOP(bit456, 1 << 3)
        arm_data_processing(s_bit, i_bit, op4, bit456);
    
    LOOP(load_bit, 2)
    LOOP(up_bit, 2)
    LOOP(pre_bit, 2)
    LOOP(write_bit, 2)
    LOOP(op2, 1 << 2)
    LOOP(opcodeBit22, 2)
        arm_halfword_data_transfer(load_bit, up_bit, pre_bit, write_bit, op2, opcodeBit22);
    
    LOOP(i_bit, 2)
    LOOP(p_bit, 2)
    LOOP(u_bit, 2)
    LOOP(b_bit, 2)
    LOOP(w_bit, 2)
    LOOP(l_bit, 2)
    LOOP(bit456, 1 << 3)
        arm_single_data_transfer(i_bit, p_bit, u_bit, b_bit, w_bit, l_bit, bit456);
    
    LOOP(p_bit, 2)
    LOOP(u_bit, 2)
    LOOP(s_bit, 2)
    LOOP(w_bit, 2)
    LOOP(l_bit, 2)
    LOOP(bit15, 2)
        arm_block_data_transfer(p_bit, u_bit, s_bit, w_bit, l_bit, bit15);
    
    LOOP(a, 2)
    LOOP(s, 2)
        arm_multiply(a, s);
    
    LOOP(u, 2)
    LOOP(a, 2)
    LOOP(s, 2)
        arm_multiply_long(u, a, s);

    GEN(arm_not_decoded:{);
    GEN(printf("ARM OPCODE NOT DECODED!\n"););
    GEN(});
}


void arm_bx(){
    printf("arm_bx:{\n");
    GEN(cpu->r[15] = cpu->r[opcode & 0xF];);
    GEN(cpu->thumb_mode = (cpu->r[15] & 0b1););
    GEN(cpu->r[15] &= 0xFFFFFFFE;);
    GEN(arm7tdmi_pipeline_refill(cpu););
    RET;
}

void arm_b_bl(bool link_bit, bool sign){
    printf("arm_b_bl_%X_%X:{\n", link_bit, sign);

    if(link_bit){
        GEN(cpu->r[14] = cpu->r[15] - 4;);
    }

    GEN(u32 offset = opcode & 0xFFFFFF;);
    if(sign)
        GEN(offset |= 0xFF000000;);
    GEN(offset <<= 2;);

    GEN(cpu->r[15] += offset;);
    GEN(arm7tdmi_pipeline_refill(cpu););
    RET;
}

void arm_mrs(bool p_bit){
    printf("arm_mrs_%X:{\n", p_bit);

    if(p_bit)
        GEN(cpu->r[(opcode >> 12) & 0xF] = *getSPSR(cpu););
    else
        GEN(cpu->r[(opcode >> 12) & 0xF] = cpu->CPSR;);
    RET;
}


void arm_msr(bool p, bool i_bit){
    printf("arm_msr_%X_%X:{\n", p, i_bit);
    GEN(u32 operand;);
    GEN(u8 field_mask = (opcode >> 16) & 0xF;);
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
    RET;
}

void arm_data_processing(bool s_bit, bool i_bit, int op4, int bit456){
    printf("arm_data_processing_%X_%X_%X_%X:{\n", s_bit, i_bit, op4, bit456);

    GEN(u8 rd_idx = (opcode >> 12) & 0xF;);
    GEN(u8 rn_idx = (opcode >> 16) & 0xF;);
    GEN(u32 rn = cpu->r[rn_idx];);
    GEN(u32* rd = &cpu->r[rd_idx];);
    GEN(u32 op2;);
    const char* alu_op = dataProcessingFuncs[op4];
    
    if(!strcmp(alu_op, "alu_ADD") || !strcmp(alu_op, "alu_SUB") || !strcmp(alu_op, "alu_ADC") || !strcmp(alu_op, "alu_SBC") || !strcmp(alu_op, "alu_RSB") || !strcmp(alu_op, "alu_RSC"))
        GEN(bool old_carry = cpu->C_FLAG;);
    
    if(i_bit){
        ROLLER_IMM(op2, opcode, s_bit);
    } else {
        SHIFTER_REG(op2, bit456, s_bit);
        if(bit456 & 1){
            GEN(if(rn_idx == 15));
            GEN(    rn += 4;);
        }
    }

    if(!strcmp(alu_op, "alu_ADD") || !strcmp(alu_op, "alu_SBC") || !strcmp(alu_op, "alu_ADC") || !strcmp(alu_op, "alu_SBC") || !strcmp(alu_op, "alu_RSB") || !strcmp(alu_op, "alu_RSC"))
        GEN(cpu->C_FLAG = old_carry;);

    printf("%s(cpu, rd, rn, op2, %d);\n", alu_op, s_bit);

    if(s_bit){
        GEN(if(rd_idx == 15){);
        GEN(    saveBankedReg(cpu););
        GEN(    cpu->CPSR = *getSPSR(cpu););
        GEN(    loadBankedReg(cpu););
        GEN(});
    }
    
    if(strcmp(alu_op, "alu_CMP") && strcmp(alu_op, "alu_CMN") && strcmp(alu_op, "alu_TST") && strcmp(alu_op, "alu_TEQ")){
        GEN(if(rd_idx == 15));
            GEN(arm7tdmi_pipeline_refill(cpu););
    }
    
    RET;
}

void arm_halfword_data_transfer(bool load_bit, bool up_bit, bool pre_bit, bool write_bit, int op2, bool opcodeBit22){
    printf("arm_halfword_data_transfer_%X_%X_%X_%X_%X_%X:{\n", load_bit, up_bit, pre_bit, write_bit, op2, opcodeBit22);

    GEN(u32 offset;);
    GEN(u32* rd = &cpu->r[(opcode >> 12) & 0xF];);
    GEN(u32* rn = &cpu->r[(opcode >> 16) & 0xF];);

    if(opcodeBit22)
        GEN(offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4););
    else {
        GEN(offset = cpu->r[opcode & 0xF];);
    }

    GEN(u32 addr = *rn;);

    if(pre_bit)
        printf("addr += %s;\n", up_bit ? "offset" : "-offset");

    switch (op2){
        case 0x00:
        GEN(alu_SWP(cpu, opcode););
        RET;
        return;

        case 0x01:
        if(load_bit) {
            GEN(cpu->cycles += I_CYCLES;);
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
        if(!load_bit)
            GEN(*rn = addr;);
        else {
            GEN(if(rn != rd));
                GEN(*rn = addr;);
        }
    }
    RET;
}

void arm_single_data_transfer(bool i_bit, bool p_bit, bool u_bit, bool b_bit, bool w_bit, bool l_bit, int bit456){
    printf("arm_single_data_transfer_%X_%X_%X_%X_%X_%X_%X:{\n", i_bit, p_bit, u_bit, b_bit, w_bit, l_bit, bit456);
    GEN(u32 rn_idx = (opcode >> 16) & 0xF;);
    GEN(u32 rd_idx = (opcode >> 12) & 0xF;);
    GEN(u32* rn = &cpu->r[rn_idx];);
    GEN(u32* rd = &cpu->r[rd_idx];);
    GEN(u32 addr = *rn;);
    GEN(u32 offset;);

    if(i_bit) {
        SHIFTER_REG(offset, bit456, false);
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
            GEN(if(rd_idx == 15));
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
        if(!l_bit)
            GEN(*rn = addr;);
        else {
            GEN(if(rn != rd));
            GEN(    *rn = addr;);
        }
    }
    RET;
}

void arm_block_data_transfer(bool p_bit, bool u_bit, bool s_bit, bool w_bit, bool l_bit, bool bit15){
    printf("arm_block_data_transfer_%X_%X_%X_%X_%X_%X:{\n", p_bit, u_bit, s_bit, w_bit, l_bit, bit15);
    GEN(u8 base_idx = (opcode >> 16) & 0xF;);
    GEN(u32* rn = &cpu->r[base_idx];);
    GEN(u16 reg_list = opcode & 0xFFFF;);
    GEN(u32* regs = cpu->r;);
    GEN(u32 addr = *rn;);

    if(!bit15 && s_bit){
        GEN(saveBankedReg(cpu););
        GEN(regs = cpu->usr_r;);
    }

    GEN(u32 reg_count = __builtin_popcount(reg_list););
    if(!u_bit){
        GEN(addr -= reg_count*4;);
        p_bit ^= 1;
    }

    if(l_bit)
        GEN(cpu->cycles += I_CYCLES;);

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
        if(!(bit15) && s_bit)
            GEN(loadBankedReg(cpu););

        
        if(w_bit){
            if(!l_bit)
                GEN(*rn = addr;);
            else{
                GEN(if(!(reg_list & (1 << base_idx))));
                GEN(    *rn = addr;);
            }
        }
    GEN(});
    RET;
}

void arm_multiply(bool a, bool s){
    printf("arm_multiply_%X_%X:{\n", a, s);

    GEN(u32 rm = cpu->r[opcode & 0xF];);
    GEN(u32 rs = cpu->r[(opcode >> 8) & 0xF];);
    GEN(u32 rn = cpu->r[(opcode >> 12) & 0xF];);
    GEN(u32* rd = &cpu->r[(opcode >> 16) & 0xF];);
    
    GEN(*rd = ((i32)rm) * ((i32)rs););
    
    if(a){
        GEN(*rd += rn;);
    }

    GEN(if(!(rs & 0xFFFFFF00) || !((~rs) & 0xFFFFFF00)));
        printf("cpu->cycles += %d;\n", a ? 2 : 1);
    GEN(else if(!(rs & 0xFFFF0000) || !((~rs) & 0xFFFF0000)));
    	printf("cpu->cycles += %d;\n", a ? 3: 2);
    GEN(else if(!(rs & 0xFF000000) || !((~rs) & 0xFF000000)));
        printf("cpu->cycles += %d;\n", a ? 4: 3);
    GEN(else);
        printf("cpu->cycles += %d;\n", a ? 5: 4);

    if(s){
        GEN(cpu->Z_FLAG = !(*rd););
        GEN(cpu->N_FLAG = *rd >> 31;);
    }
    RET;
}

void arm_multiply_long(bool u, bool a, bool s){
    printf("arm_multiply_long_%X_%X_%X:{\n", u, a, s);    

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

        GEN(if(!(rs & 0xFFFFFF00) || !((~rs) & 0xFFFFFF00)));
            printf("cpu->cycles += %d;\n", a ? 3: 2);
        GEN(else if(!(rs & 0xFFFF0000) || !((~rs) & 0xFFFF0000)));
            printf("cpu->cycles += %d;\n", a ? 4: 3);
        GEN(else if(!(rs & 0xFF000000) || !((~rs) & 0xFF000000)));
            printf("cpu->cycles += %d;\n", a ? 5: 4);
        GEN(else);
            printf("cpu->cycles += %d;\n", a ? 6: 5);   
    } else {
        GEN(if(!(rs & 0xFFFFFF00)));
            printf("cpu->cycles += %d;\n", a ? 3: 2);
        GEN(else if(!(rs & 0xFFFF0000)));
            printf("cpu->cycles += %d;\n", a ? 4: 3);
        GEN(else if(!(rs & 0xFF000000)));
            printf("cpu->cycles += %d;\n", a ? 5: 4);
        GEN(else);
            printf("cpu->cycles += %d;\n", a ? 6: 5);  
    }


    RET;
}