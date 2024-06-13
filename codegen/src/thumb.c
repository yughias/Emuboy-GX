#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STR(x) #x "\n" 
#define GEN(x) printf(#x "\n")
#define RET printf("return;\n"); return

void thumb_pc_relative_load(int opcode);
void thumb_add_subtract(int opcode);
void thumb_move_shifted_register(int opcode);
void thumb_conditional_branch(int opcode);
void thumb_unconditional_branch(int opcode);
void thumb_misc_immediate(int opcode);
void thumb_long_branch_link(int opcode);
void thumb_alu_operations(int opcode);
void thumb_load_store_immediate_offset(int opcode);
void thumb_multiple_load_store(int opcode);
void thumb_hi_reg_op(int opcode);
void thumb_push_pop(int opcode);
void thumb_load_store_halfword(int opcode);
void thumb_load_store_sign_extended(int opcode);
void thumb_load_address(int opcode);
void thumb_load_store_register_offset(int opcode);
void thumb_add_offset_sp(int opcode);
void thumb_sp_relative_load_store(int opcode);
void thumb_software_interrupt(int opcode);

const char start_src[] = 
STR(#include "arm7tdmi/arm7tdmi.h")
STR(#include "arm7tdmi/thumb.h")
STR(#include "arm7tdmi/arm7tdmi_util.h")
STR()
STR(#include <stdio.h>)
STR(#include <stdlib.h>);

const char step_src[] =
STR(void thumb_step(arm7tdmi_t* cpu){)
STR(    u16 opcode = cpu->pipeline_opcode[0];)
STR(    cpu->pipeline_opcode[0] = cpu->pipeline_opcode[1];)
STR(    cpu->r[15] += 2;)
STR(    cpu->pipeline_opcode[1] = readHalfWordS(cpu, cpu->r[15]););

const char end_src[] =
STR(});

const char condFuncs[16][64] = {
    "cond_EQ(cpu)", "cond_NE(cpu)", "cond_CS(cpu)", "cond_CC(cpu)",
    "cond_MI(cpu)", "cond_PL(cpu)", "cond_VS(cpu)", "cond_VC(cpu)",
    "cond_HI(cpu)", "cond_LS(cpu)", "cond_GE(cpu)", "cond_LT(cpu)",
    "cond_GT(cpu)", "cond_LE(cpu)", "cond_AL(cpu)", "cond_Undefined(cpu)"
};

void generateLUT_gotoTable();
void generateLUT_data(int);

int main(int argv, char** argc){
    if(argv != 2){
        printf("<name.exe> <output_file>\n");
        exit(1);
    }

    freopen(argc[1], "w", stdout);
    
    printf("%s\n", start_src);  

    printf("%s\n", step_src);

    generateLUT_gotoTable();
    printf("\ngoto *thumb_table[opcode >> 6];\n");
    
    GEN(u32* rd;);
    GEN(u32 rs;);
    GEN(u32 addr;);
    GEN(u32 offset;);
    GEN(u32 old_r15;);
    GEN(u32 rb;);
    GEN(u32 ro;);
    GEN(u32 base;);
    GEN(u16 w9;);
    GEN(u8 w8;);
    GEN(u8 rd_idx;);
    GEN(u8 rs_idx;);
    GEN(u8 count;);
    GEN(u8 rlist;);
    GEN(u8 rlist_size;);
    GEN(bool should_transfer;);
    GEN(bool first_transfer;);

    for(int i = 0; i < 1 << 10; i++)
    generateLUT_data(i);

    printf("%s\n", end_src); 
}

void generateLUT_gotoTable(){
    printf("static void* thumb_table[1 << 10] = {");
    for(int i = 0; i < (1 << 10); i++){
        printf("&&thumb_op_%04X", i);
        if(i != (1 << 10) - 1)
            printf(", ");
    }
    printf("};\n");
}

void generateLUT_data(int idx){
    printf("thumb_op_%04X:\n", idx);
    int opcode = idx << 6;

    if((opcode >> 8) == 0b11011111){
        thumb_software_interrupt(opcode);
        RET;
    }

    if((opcode >> 11) == 0b00011){
        thumb_add_subtract(opcode);
        RET;
    }

    if(!(opcode >> 13)){
        thumb_move_shifted_register(opcode);
        RET;
    }

    if((opcode >> 13) == 0b001){
        thumb_misc_immediate(opcode);
        RET;
    }

    if((opcode >> 10) == 0b010000){
        thumb_alu_operations(opcode);
        RET;
    }

    if(
        ((opcode >> 12) == 0b0101) &&
        !((opcode >> 9) & 1)
    ){
        thumb_load_store_register_offset(opcode);
        RET;
    }

    if(
        ((opcode >> 12) == 0b0101) &&
        ((opcode >> 9) & 1)
    ){
        thumb_load_store_sign_extended(opcode);
        RET;
    }

    if((opcode >> 10) == 0b010001){
        thumb_hi_reg_op(opcode);
        RET;
    }

    if((opcode >> 11) == 0b01001){
        thumb_pc_relative_load(opcode);
        RET;
    }
    
    if((opcode >> 13) == 0b011){
        thumb_load_store_immediate_offset(opcode);
        RET;
    }

    if((opcode >> 12) == 0b1001){
        thumb_sp_relative_load_store(opcode);
        RET;
    }

    if((opcode >> 12) == 0b1000){
        thumb_load_store_halfword(opcode);
        RET;
    }

    if((opcode >> 12) == 0b1010){
        thumb_load_address(opcode);
        RET;
    }

    if((opcode >> 8) == 0b10110000){
        thumb_add_offset_sp(opcode);
        RET;
    }

    if(
        ((opcode >> 12) == 0b1011) &&
        (((opcode >> 9) & 0b11) == 0b10)
    ){
        thumb_push_pop(opcode);
        RET;
    }

    if((opcode >> 12) == 0b1100){
        thumb_multiple_load_store(opcode);
        RET;
    }

    if((opcode >> 12) == 0b1101){
        thumb_conditional_branch(opcode);
        RET;
    }

    if((opcode >> 11) == 0b11100){
        thumb_unconditional_branch(opcode);
        RET;
    }
    
    if((opcode >> 12) == 0b1111){
        thumb_long_branch_link(opcode);
        RET;
    }

    RET;
}


void thumb_move_shifted_register(int opcode){
    GEN(rd = &cpu->r[opcode & 0b111];);
    GEN(rs = cpu->r[(opcode >> 3) & 0b111];);
    int off5 = (opcode >> 6) & 0b11111;

    switch((opcode >> 11) & 0b11){
        case 0:
        printf("alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, %d, true), true);\n", off5);
        break;

        case 1:
        printf("alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, %d, true), true);\n", !off5 ? 32 : off5);
        break;

        case 2:
        printf("alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, %d, true), true);\n", !off5 ? 32 : off5);
        break;
    }
}

void thumb_pc_relative_load(int opcode){
    GEN(w8 = opcode & 0xFF;);
    printf("rd = &cpu->r[%d];\n", (opcode >> 8) & 0b111);
    GEN(addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2););
    GEN(*rd = readWordN(cpu, addr););
}


void thumb_conditional_branch(int opcode){
    GEN(w8 = opcode & 0xFF;);
    int cond = (opcode >> 8) & 0xF;
    printf("if(%s == false) return;\n", condFuncs[cond]);

    GEN(cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;);
    GEN(arm7tdmi_pipeline_refill(cpu););
}

void thumb_unconditional_branch(int opcode){
    GEN(offset = (opcode & 0b11111111111) << 1;);
    GEN(cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;);
    GEN(arm7tdmi_pipeline_refill(cpu););
}

void thumb_misc_immediate(int opcode){
    GEN(w8 = opcode & 0xFF;);
    printf("rd = &cpu->r[%d];\n", (opcode >> 8) & 0b111);

    switch((opcode >> 11) & 0b11){
        case 0b00:
        GEN(alu_MOV(cpu, rd, *rd, w8, true););
        break;

        case 0b01:
        GEN(alu_CMP(cpu, rd, *rd, w8, true););
        break;

        case 0b10:
        GEN(alu_ADD(cpu, rd, *rd, w8, true););
        break;

        case 0b11:
        GEN(alu_SUB(cpu, rd, *rd, w8, true););
        break;
    }
}

void thumb_long_branch_link(int opcode){
    bool h = (opcode >> 11) & 1;
    GEN(offset = (opcode & 0b11111111111););

    if(!h){
        GEN(offset <<= 1;);
        GEN(if(offset & 0x800));
        GEN(    offset |= 0xFFFFF000;);
        GEN(cpu->r[14] = cpu->r[15] + (offset << 11););
    } else {
        GEN(old_r15 = cpu->r[15];);
        GEN(cpu->r[15] = cpu->r[14] + (offset << 1););
        GEN(cpu->r[15] &= 0xFFFFFFFE;);
        GEN(cpu->r[14] = (old_r15 - 2) | 1;);
        GEN(arm7tdmi_pipeline_refill(cpu););
    }
}

void thumb_alu_operations(int opcode){
    GEN(rd = &cpu->r[opcode & 0b111];);
    GEN(rs = cpu->r[(opcode >> 3) & 0b111];);
    int op = (opcode >> 6) & 0xF;

    switch(op){
        case 0:
        GEN(alu_AND(cpu, rd, *rd, rs, true););
        break;
        
        case 1:
        GEN(alu_EOR(cpu, rd, *rd, rs, true););
        break;

        case 2:
        GEN(alu_MOV(cpu, rd, 0, alu_LSL(cpu, *rd, rs, true), true););
        break;

        case 3:
        GEN(alu_MOV(cpu, rd, 0, alu_LSR(cpu, *rd, rs, true), true););
        break;

        case 4:
        GEN(alu_MOV(cpu, rd, 0, alu_ASR(cpu, *rd, rs, true), true););
        break;

        case 5:
        GEN(alu_ADC(cpu, rd, *rd, rs, true););
        break;

        case 6:
        GEN(alu_SBC(cpu, rd, *rd, rs, true););
        break;

        case 7:
        GEN(alu_MOV(cpu, rd, 0, alu_ROR(cpu, *rd, rs, true), true););
        break;

        case 8:
        GEN(alu_TST(cpu, rd, *rd, rs, true););
        break;

        case 9:
        //NEG
        GEN(alu_SUB(cpu, rd, 0, rs, true););
        break;

        case 10:
        GEN(alu_CMP(cpu, rd, *rd, rs, true););
        break;

        case 11:
        GEN(alu_CMN(cpu, rd, *rd, rs, true););
        break;

        case 12:
        GEN(alu_ORR(cpu, rd, *rd, rs, true););
        break;

        case 13:
        // MUL
        GEN(*rd = ((i32)*rd) * ((i32)rs););
        GEN(cpu->Z_FLAG = !(*rd););
        GEN(cpu->N_FLAG = *rd >> 31;);
        break;

        case 14:
        GEN(alu_BIC(cpu, rd, *rd, rs, true););
        break;

        case 15:
        GEN(alu_MVN(cpu, rd, *rd, rs, true););
        break;
    }
}

void thumb_multiple_load_store(int opcode){
    int base_idx = (opcode >> 8) & 0b111;
    printf("base = cpu->r[%d];\n", base_idx);
    bool l = (opcode >> 11) & 1;
    GEN(rlist = opcode & 0xFF;);

    GEN(count = 0xFF;);
    GEN(if(!rlist){);
        if(l){
            GEN(cpu->r[15] = readWordN(cpu, base););
            GEN(arm7tdmi_pipeline_refill(cpu););
        } else {
            GEN(writeWordN(cpu, base, cpu->r[15] + 2););
        }
        printf("cpu->r[%d] += 0x40;\n", base_idx);
    GEN(} else{);
        GEN(rlist_size = __builtin_popcount(rlist););
        GEN(first_transfer = true;);
        GEN(while(rlist){);
            GEN(should_transfer = rlist & 1;);
            GEN(rlist >>= 1;);
            GEN(count += 1;);
            GEN(if(!should_transfer));
            GEN(    continue;);
            if(l)
                GEN(cpu->r[count] = readWordN(cpu, base););
            else {
                printf("if(count == %d && !first_transfer)", base_idx);
                    GEN(writeWordN(cpu, base, cpu->r[count] + (rlist_size << 2)););
                GEN(else);
                    GEN(writeWordN(cpu, base, cpu->r[count]););
            }
            GEN(base += 4;);
            GEN(first_transfer = false;);
        GEN(});

        printf("cpu->r[%d] = base;\n", base_idx);
    GEN(});
}

void thumb_hi_reg_op(int opcode){
    bool h1 = (opcode >> 7) & 1;
    bool h2 = (opcode >> 6) & 1;

    switch((opcode >> 8) & 0b11){
        case 0b00:
        printf("rd_idx = (opcode & 0b111) %s;\n", h1 ? "+ 8" : ""); 
        printf("rs_idx = ((opcode >> 3) & 0b111) %s;\n", h2 ? "+ 8" : "");
        GEN(rd = &cpu->r[rd_idx];);
        GEN(rs = cpu->r[rs_idx];);
        GEN(alu_ADD(cpu, rd, *rd, rs, false););
        GEN(if(rd_idx == 15){);
        GEN(    cpu->r[15] &= 0xFFFFFFFE;);
        GEN(    arm7tdmi_pipeline_refill(cpu););
        GEN(});
        break;

        case 0b01:
        printf("rd_idx = (opcode & 0b111) %s;\n", h1 ? "+ 8" : ""); 
        printf("rs_idx = ((opcode >> 3) & 0b111) %s;\n", h2 ? "+ 8" : "");
        GEN(rd = &cpu->r[rd_idx];);
        GEN(rs = cpu->r[rs_idx];);
        // CMP CAN'T CHANGE R15
        GEN(alu_CMP(cpu, rd, *rd, rs, true););
        break;

        case 0b10:
        printf("rd_idx = (opcode & 0b111) %s;\n", h1 ? "+ 8" : ""); 
        printf("rs_idx = ((opcode >> 3) & 0b111) %s;\n", h2 ? "+ 8" : "");
        GEN(rd = &cpu->r[rd_idx];);
        GEN(rs = cpu->r[rs_idx];);
        GEN(alu_MOV(cpu, rd, *rd, rs, false););
        GEN(if(rd_idx == 15){);
        GEN(    cpu->r[15] &= 0xFFFFFFFE;);
        GEN(    arm7tdmi_pipeline_refill(cpu););
        GEN(});
        break;

        case 0b11:
        printf("rs_idx = ((opcode >> 3) & 0b111) %s;\n", h2 ? "+ 8" : "");
        GEN(rs = cpu->r[rs_idx];);
        GEN(cpu->r[15] = rs;);
        GEN(cpu->thumb_mode = (cpu->r[15] & 0b1););
        GEN(cpu->r[15] &= 0xFFFFFFFE;);
        GEN(arm7tdmi_pipeline_refill(cpu););
        break;
    }
}

void thumb_add_subtract(int opcode){
    bool i = (opcode >> 10) & 1;
    bool op = (opcode >> 9) & 1;
    int idx = (opcode >> 6) & 0b111;
    GEN(rd = &cpu->r[opcode & 0b111];);
    GEN(rs = cpu->r[(opcode >> 3) & 0b111];);

    if(op){
        if(i)
            printf("alu_SUB(cpu, rd, rs, %d, true);\n", idx);
        else
            printf("alu_SUB(cpu, rd, rs, cpu->r[%d], true);\n", idx);
    } else {
        if(i)
            printf("alu_ADD(cpu, rd, rs, %d, true);\n", idx);
        else
            printf("alu_ADD(cpu, rd, rs, cpu->r[%d], true);\n", idx);
    }
}


void thumb_load_store_immediate_offset(int opcode){
    bool b = (opcode >> 12) & 1;
    bool l = (opcode >> 11) & 1;
    int off5 = (opcode >> 6) & 0b11111;
    GEN(rb = cpu->r[(opcode >> 3) & 0b111];);
    GEN(rd = &cpu->r[opcode & 0b111];);

    if(l){
        if(b)
            printf("*rd = readByteN(cpu, rb + %d);\n", off5);
        else {
            printf("addr = rb + (%d << 2);\n", off5);
            GEN(*rd = readWordN(cpu, addr););
            GEN(*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false););
        }
    } else {
        if(b)
            printf("writeByteN(cpu, rb + %d, *rd);\n", off5);
        else
            printf("writeWordN(cpu, rb + %d, *rd);\n", off5 << 2);
    }
}

void thumb_push_pop(int opcode){
    bool l = (opcode >> 11) & 1;
    bool r = (opcode >> 8) & 1;
    GEN(rlist = opcode & 0xFF;);

    GEN(count = __builtin_popcount(rlist););
    if(!l){
        printf("cpu->r[13] -= (count + %d) * 4;\n", r);
        GEN(rlist = opcode & 0xFF;);
    }

    GEN(for(int i = 0; i < 16 && rlist; i++){);
        GEN(should_transfer = rlist & 1;);
        GEN(rlist >>= 1;);
        GEN(if(!should_transfer));
        GEN(    continue;);

        if(l)
            GEN(cpu->r[i] = readWordN(cpu, cpu->r[13]););
        else
            GEN(writeWordN(cpu, cpu->r[13], cpu->r[i]););

        GEN(cpu->r[13] += 4;);
    GEN(});

    if(r){
        if(!l){
            GEN(writeWordN(cpu, cpu->r[13], cpu->r[14]););
        } else {
            GEN(cpu->r[15] = readWordN(cpu, cpu->r[13]););
            GEN(cpu->r[15] &= 0xFFFFFFFE;);
            GEN(arm7tdmi_pipeline_refill(cpu););
        }
        GEN(cpu->r[13] += 4;);
    }

    if(!l)
        printf("cpu->r[13] -= (count + %d) * 4;\n", r);
}

void thumb_load_store_halfword(int opcode){
    bool l = (opcode >> 11) & 1;
    GEN(rd = &cpu->r[opcode & 0b111];);
    GEN(rb = cpu->r[(opcode >> 3) & 0b111];);
    int off5 = ((opcode >> 6) & 0b11111) << 1;

    if(l) {
        printf("*rd = readHalfWordN(cpu, rb + %d);\n", off5);
        GEN(if(rb & 1));
            GEN(*rd = (*rd << 24) | (*rd >> 8););
    } else
        printf("writeHalfWordN(cpu, rb + %d, *rd);\n", off5);
}

void thumb_load_store_sign_extended(int opcode){
    bool h = (opcode >> 11) & 1;
    bool s = (opcode >> 10) & 1;
    printf("ro = cpu->r[%d];\n", (opcode >> 6) & 0b111);
    GEN(rb = cpu->r[(opcode >> 3) & 0b111];);
    GEN(rd = &cpu->r[opcode & 0b111];);
    GEN(addr = rb + ro;);

    if(!h){
        if(!s){
            GEN(writeHalfWordN(cpu, addr, *rd););
        } else {
            GEN(*rd = readByteN(cpu, addr););
            GEN(if(*rd & 0x80));
            GEN(    *rd |= 0xFFFFFF00;);
        }
    } else {
        GEN(*rd = readHalfWordN(cpu, addr););
        GEN(if(addr & 1){);
            if(!s){
                GEN(*rd = (*rd >> 8) | (*rd << 24););
            } else {
                GEN(*rd = readByteN(cpu, addr););
                GEN(if(*rd & 0x80));
                GEN(    *rd |= 0xFFFFFF00;);
            }
        GEN(} else {);
            if(s){
                GEN(if(*rd & 0xFFFF8000));
                GEN(    *rd |= 0xFFFF0000;);
            }
        GEN(});
    }
}

void thumb_load_address(int opcode){
    bool sp = (opcode >> 11) & 1;
    GEN(w8 = opcode & 0xFF;);
    printf("rd = &cpu->r[%d];\n", (opcode >> 8) & 0b111);
    if(sp)
        GEN(*rd = cpu->r[13];);
    else
        GEN(*rd = cpu->r[15] & 0xFFFFFFFC;);

    GEN(*rd += w8 << 2;);
}

void thumb_load_store_register_offset(int opcode){
    bool l = (opcode >> 11) & 1;
    bool b = (opcode >> 10) & 1;

    printf("ro = cpu->r[%d];\n", (opcode >> 6) & 0b111);
    GEN(rb = cpu->r[(opcode >> 3) & 0b111];);
    GEN(rd = &cpu->r[opcode & 0b111];);
    GEN(addr = rb + ro;);

    if(l){
        if(b)
            GEN(*rd = readByteN(cpu, addr););
        else {
            GEN(*rd = readWordN(cpu, addr););
            GEN(*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false););
        }
    } else {
        if(b)
            GEN(writeByteN(cpu, addr, *rd););
        else
            GEN(writeWordN(cpu, addr, *rd););
    }
}

void thumb_add_offset_sp(int opcode){
    bool s = (opcode >> 7) & 1;
    GEN(w9 = (opcode & 0b1111111) << 2;);
    if(s)
        GEN(cpu->r[13] -= w9;);
    else
        GEN(cpu->r[13] += w9;);
}

void thumb_sp_relative_load_store(int opcode){
    bool l = (opcode >> 11) & 1;
    printf("rd = &cpu->r[%d];\n", (opcode >> 8) & 0b111);
    GEN(w8 = opcode & 0xFF;);
    GEN(addr = cpu->r[13] + (w8 << 2););

    if(l) {
        GEN(*rd = readWordN(cpu, addr););
        GEN(*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false););
    } else
        GEN(writeWordN(cpu, addr, *rd););
}

void thumb_software_interrupt(int opcode){
    GEN(arm7tdmi_trigger_exception(cpu, 0x8, 0x13););
}