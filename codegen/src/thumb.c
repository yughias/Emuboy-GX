#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STR(x) #x "\n" 
#define GEN(x) printf(#x "\n")
#define RET printf("return; }\n")

#define LOOP(i, limit) for(int i = 0; i < (limit); i++)

void thumb_pc_relative_load(int off3);
void thumb_add_subtract(bool i, bool op, int off3);
void thumb_move_shifted_register(int off5, int switch2);
void thumb_conditional_branch(int cond4);
void thumb_unconditional_branch();
void thumb_misc_immediate(int off3, int switch2);
void thumb_long_branch_link(bool h);
void thumb_alu_operations(int op4);
void thumb_load_store_immediate_offset(bool b, bool l, int off5);
void thumb_multiple_load_store(int off3, bool l);
void thumb_hi_reg_op(bool h1, bool h2, int switch2);
void thumb_push_pop(bool l, bool r);
void thumb_load_store_halfword(bool l, int off5);
void thumb_load_store_sign_extended(bool h, bool s, int off3);
void thumb_load_address(bool sp, int off3);
void thumb_load_store_register_offset(bool l, bool b, int off3);
void thumb_add_offset_sp(bool s);
void thumb_sp_relative_load_store(bool l, int op3);
void thumb_software_interrupt();

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
    printf("\ngoto *thumb_table[opcode >> 6];\n");
    GEN();
    generateLUT_data();

    printf("%s\n", end_src); 
}

void generateLUT_gotoTable(){
    printf("static void* thumb_table[1 << 10] = {");
    for(int i = 0; i < (1 << 10); i++){
        int opcode = i << 6;
        if((opcode >> 8) == 0b11011111){
            printf("&&thumb_software_interrupt, ");
            continue;
        }

        if((opcode >> 11) == 0b00011){
            printf("&&thumb_add_subtract_%X_%X_%X, ", (opcode >> 10) & 1, (opcode >> 9) & 1, (opcode >> 6) & 0b111);
            continue;
        }

        if(!(opcode >> 13)){
            printf("&&thumb_move_shifted_register_%X_%X, ", (opcode >> 6) & 0b11111, (opcode >> 11) & 0b11);
            continue;
        }

        if((opcode >> 13) == 0b001){
            printf("&&thumb_misc_immediate_%X_%X, ", (opcode >> 8) & 0b111, (opcode >> 11) & 0b11);
            continue;
        }

        if((opcode >> 10) == 0b010000){
            printf("&&thumb_alu_operations_%X, ", (opcode >> 6) & 0xF);
            continue;
        }

        if(
            ((opcode >> 12) == 0b0101) &&
            !((opcode >> 9) & 1)
        ){
            printf("&&thumb_load_store_register_offset_%X_%X_%X, ", (opcode >> 11) & 1, (opcode >> 10) & 1, (opcode >> 6) & 0b111);
            continue;
        }

        if(
            ((opcode >> 12) == 0b0101) &&
            ((opcode >> 9) & 1)
        ){
            printf("&&thumb_load_store_sign_extended_%X_%X_%X, ", (opcode >> 11) & 1, (opcode >> 10) & 1, (opcode >> 6) & 0b111);
            continue;
        }

        if((opcode >> 10) == 0b010001){
            printf("&&thumb_hi_reg_op_%X_%X_%X, ", (opcode >> 7) & 1, (opcode >> 6) & 1, (opcode >> 8) & 0b11);
            continue;
        }

        if((opcode >> 11) == 0b01001){
            printf("&&thumb_pc_relative_load_%X, ", (opcode >> 8) & 0b111);
            continue;
        }
        
        if((opcode >> 13) == 0b011){
            printf("&&thumb_load_store_immediate_offset_%X_%X_%X, ", (opcode >> 12) & 1, (opcode >> 11) & 1, (opcode >> 6) & 0b11111);
            continue;
        }

        if((opcode >> 12) == 0b1001){
            printf("&&thumb_sp_relative_load_store_%X_%X, ", (opcode >> 11) & 1, (opcode >> 8) & 0b111);
            continue;
        }

        if((opcode >> 12) == 0b1000){
            printf("&&thumb_load_store_halfword_%X_%X, ", (opcode >> 11) & 1, ((opcode >> 6) & 0b11111) << 1);
            continue;
        }

        if((opcode >> 12) == 0b1010){
            printf("&&thumb_load_address_%X_%X, ", (opcode >> 11) & 1, (opcode >> 8) & 0b111);
            continue;
        }

        if((opcode >> 8) == 0b10110000){
            printf("&&thumb_add_offset_sp_%X, ", (opcode >> 7) & 1);
            continue;
        }

        if(
            ((opcode >> 12) == 0b1011) &&
            (((opcode >> 9) & 0b11) == 0b10)
        ){
            printf("&&thumb_push_pop_%X_%X, ", (opcode >> 11) & 1, (opcode >> 8) & 1);
            continue;
        }

        if((opcode >> 12) == 0b1100){
            printf("&&thumb_multiple_load_store_%X_%X, ", (opcode >> 8) & 0b111, (opcode >> 11) & 1);
            continue;
        }

        if((opcode >> 12) == 0b1101){
            printf("&&thumb_conditional_branch_%X, ", (opcode >> 8) & 0xF);
            continue;
        }

        if((opcode >> 11) == 0b11100){
            printf("&&thumb_unconditional_branch, ");
            continue;
        }
        
        if((opcode >> 12) == 0b1111){
            printf("&&thumb_long_branch_link_%X, ", (opcode >> 11) & 1);
            continue;
        }

        printf("&&thumb_not_encoded, ");
    }
    printf("};\n");
}

void generateLUT_data(){
    LOOP(off3, 1 << 3)
        thumb_pc_relative_load(off3);

    LOOP(i, 2)
    LOOP(op, 2)
    LOOP(off3, 1 << 3)
        thumb_add_subtract(i, op, off3);

    LOOP(off5, 1 << 5)
    LOOP(switch2, 1 << 2)  
        thumb_move_shifted_register(off5, switch2);
        
    LOOP(cond4, 1 << 4)
        thumb_conditional_branch(cond4);
        
    thumb_unconditional_branch();
        
    LOOP(off3, 1 << 3)
    LOOP(switch2, 1 << 2)
        thumb_misc_immediate(off3, switch2);
        
    LOOP(h, 2)
        thumb_long_branch_link(h);
        
    LOOP(op4, 1 << 4)
        thumb_alu_operations(op4);
        
    LOOP(b, 2)
    LOOP(l, 2)
    LOOP(off5, 1 << 5)
        thumb_load_store_immediate_offset(b, l, off5);
        
    LOOP(off3, 1 << 3)
    LOOP(l, 2)
        thumb_multiple_load_store(off3, l);
        
    LOOP(h1, 2)
    LOOP(h2, 2)
    LOOP(switch2, 1 << 2)
        thumb_hi_reg_op(h1, h2, switch2);
    
    LOOP(l, 2)
    LOOP(r, 2)
        thumb_push_pop(l, r);
        
    LOOP(l, 2)
    LOOP(off5, 1 << 5)
        thumb_load_store_halfword(l, off5 << 1);
    
    LOOP(h, 2)
    LOOP(s, 2)
    LOOP(off3, 1 << 3)
        thumb_load_store_sign_extended(h, s, off3);
        
    LOOP(sp, 2)
    LOOP(off3, 1 << 3)
        thumb_load_address(sp, off3);

    LOOP(l, 2)
    LOOP(b, 2)
    LOOP(off3, 1 << 3)
        thumb_load_store_register_offset(l, b, off3);
        
    LOOP(s, 2)
        thumb_add_offset_sp(s);
        
    LOOP(l, 2)
    LOOP(op3, 1 << 3)
        thumb_sp_relative_load_store(l, op3);
    
    thumb_software_interrupt();

    GEN(thumb_not_encoded:{);
    GEN(printf("THUMB ILLEGAL OPCODE!\n"););
    GEN(});
}


void thumb_move_shifted_register(int off5, int switch2){
    printf("thumb_move_shifted_register_%X_%X:{\n", off5, switch2);
    GEN(u32* rd = &cpu->r[opcode & 0b111];);
    GEN(u32 rs = cpu->r[(opcode >> 3) & 0b111];);

    switch(switch2){
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

    RET;
}

void thumb_pc_relative_load(int off3){
    printf("thumb_pc_relative_load_%X:{\n", off3);
    GEN(u8 w8 = opcode & 0xFF;);
    printf("u32* rd = &cpu->r[%d];\n", off3);
    GEN(u32 addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2););
    GEN(cpu->cycles += I_CYCLES;);
    GEN(*rd = readWordN(cpu, addr););
    RET;
}

void thumb_conditional_branch(int cond4){
    printf("thumb_conditional_branch_%X:{\n", cond4);
    GEN(u8 w8 = opcode & 0xFF;);
    printf("if(%s == false) return;\n", condFuncs[cond4]);

    GEN(cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;);
    GEN(thumb_pipeline_refill(cpu););
    RET;
}

void thumb_unconditional_branch(){
    printf("thumb_unconditional_branch:{\n");
    GEN(u32 offset = (opcode & 0b11111111111) << 1;);
    GEN(cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;);
    GEN(thumb_pipeline_refill(cpu););
    RET;
}

void thumb_misc_immediate(int off3, int switch2){
    printf("thumb_misc_immediate_%X_%X:{\n", off3, switch2);
    GEN(u8 w8 = opcode & 0xFF;);
    printf("u32* rd = &cpu->r[%d];\n", off3);

    switch(switch2){
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

    RET;
}

void thumb_long_branch_link(bool h){
    printf("thumb_long_branch_link_%X:{\n", h);
    GEN(u32 offset = (opcode & 0b11111111111););

    if(!h){
        GEN(offset <<= 1;);
        GEN(if(offset & 0x800));
        GEN(    offset |= 0xFFFFF000;);
        GEN(cpu->r[14] = cpu->r[15] + (offset << 11););
    } else {
        GEN(u32 old_r15 = cpu->r[15];);
        GEN(cpu->r[15] = cpu->r[14] + (offset << 1););
        GEN(cpu->r[15] &= 0xFFFFFFFE;);
        GEN(cpu->r[14] = (old_r15 - 2) | 1;);
        GEN(thumb_pipeline_refill(cpu););
    }
    RET;
}

void thumb_alu_operations(int op4){
    printf("thumb_alu_operations_%X:{\n", op4);
    GEN(u32* rd = &cpu->r[opcode & 0b111];);
    GEN(u32 rs = cpu->r[(opcode >> 3) & 0b111];);

    switch(op4){
        case 0:
        GEN(alu_AND(cpu, rd, *rd, rs, true););
        break;
        
        case 1:
        GEN(alu_EOR(cpu, rd, *rd, rs, true););
        break;

        case 2:
        GEN(cpu->cycles += I_CYCLES;);
        GEN(alu_MOV(cpu, rd, 0, alu_LSL(cpu, *rd, rs, true), true););
        break;

        case 3:
        GEN(cpu->cycles += I_CYCLES;);
        GEN(alu_MOV(cpu, rd, 0, alu_LSR(cpu, *rd, rs, true), true););
        break;

        case 4:
        GEN(cpu->cycles += I_CYCLES;);
        GEN(alu_MOV(cpu, rd, 0, alu_ASR(cpu, *rd, rs, true), true););
        break;

        case 5:
        GEN(alu_ADC(cpu, rd, *rd, rs, true););
        break;

        case 6:
        GEN(alu_SBC(cpu, rd, *rd, rs, true););
        break;

        case 7:
        GEN(cpu->cycles += I_CYCLES;);
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

        GEN(if(!(rs & 0xFFFFFF00) || !((~rs) & 0xFFFFFF00)));
            GEN(cpu->cycles += 1*I_CYCLES;);
        GEN(else if(!(rs & 0xFFFF0000) || !((~rs) & 0xFFFF0000)));
            GEN(cpu->cycles += 2*I_CYCLES;);
        GEN(else if(!(rs & 0xFF000000) || !((~rs) & 0xFF000000)));
            GEN(cpu->cycles += 3*I_CYCLES;);
        GEN(else);
            GEN(cpu->cycles += 4*I_CYCLES;);

        break;

        case 14:
        GEN(alu_BIC(cpu, rd, *rd, rs, true););
        break;

        case 15:
        GEN(alu_MVN(cpu, rd, *rd, rs, true););
        break;
    }
    RET;
}

void thumb_multiple_load_store(int off3, bool l){
    printf("thumb_multiple_load_store_%X_%X:{\n", off3, l);
    int base_idx = off3;
    printf("u32 base = cpu->r[%d];\n", base_idx);
    GEN(u8 rlist = opcode & 0xFF;);

    if(l)
        GEN(cpu->cycles += I_CYCLES;);

    GEN(u8 count = 0xFF;);
    GEN(if(!rlist){);
        if(l){
            GEN(cpu->r[15] = readWordN(cpu, base););
            GEN(thumb_pipeline_refill(cpu););
        } else {
            GEN(writeWordN(cpu, base, cpu->r[15] + 2););
        }
        printf("cpu->r[%d] += 0x40;\n", base_idx);
    GEN(} else{);
        GEN(u8 rlist_size = __builtin_popcount(rlist););
        GEN(bool first_transfer = true;);
        GEN(while(rlist){);
            GEN(bool should_transfer = rlist & 1;);
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
    RET;
}

void thumb_hi_reg_op(bool h1, bool h2, int switch2){
    printf("thumb_hi_reg_op_%X_%X_%X:{\n", h1, h2, switch2);

    switch(switch2){
        case 0b00:
        printf("u8 rd_idx = (opcode & 0b111) %s;\n", h1 ? "+ 8" : ""); 
        printf("u8 rs_idx = ((opcode >> 3) & 0b111) %s;\n", h2 ? "+ 8" : "");
        GEN(u32* rd = &cpu->r[rd_idx];);
        GEN(u32 rs = cpu->r[rs_idx];);
        GEN(alu_ADD(cpu, rd, *rd, rs, false););
        GEN(if(rd_idx == 15){);
        GEN(    cpu->r[15] &= 0xFFFFFFFE;);
        GEN(    thumb_pipeline_refill(cpu););
        GEN(});
        break;

        case 0b01:
        printf("u8 rd_idx = (opcode & 0b111) %s;\n", h1 ? "+ 8" : ""); 
        printf("u8 rs_idx = ((opcode >> 3) & 0b111) %s;\n", h2 ? "+ 8" : "");
        GEN(u32* rd = &cpu->r[rd_idx];);
        GEN(u32 rs = cpu->r[rs_idx];);
        // CMP CAN'T CHANGE R15
        GEN(alu_CMP(cpu, rd, *rd, rs, true););
        break;

        case 0b10:
        printf("u8 rd_idx = (opcode & 0b111) %s;\n", h1 ? "+ 8" : ""); 
        printf("u8 rs_idx = ((opcode >> 3) & 0b111) %s;\n", h2 ? "+ 8" : "");
        GEN(u32* rd = &cpu->r[rd_idx];);
        GEN(u32 rs = cpu->r[rs_idx];);
        GEN(alu_MOV(cpu, rd, *rd, rs, false););
        GEN(if(rd_idx == 15){);
        GEN(    cpu->r[15] &= 0xFFFFFFFE;);
        GEN(    thumb_pipeline_refill(cpu););
        GEN(});
        break;

        case 0b11:
        printf("u8 rs_idx = ((opcode >> 3) & 0b111) %s;\n", h2 ? "+ 8" : "");
        GEN(u32 rs = cpu->r[rs_idx];);
        GEN(cpu->r[15] = rs;);
        GEN(cpu->thumb_mode = (cpu->r[15] & 0b1););
        GEN(cpu->r[15] &= 0xFFFFFFFE;);
        GEN(arm7tdmi_pipeline_refill(cpu););
        break;
    }
    RET;
}

void thumb_add_subtract(bool i, bool op, int off3){
    printf("thumb_add_subtract_%X_%X_%X:{\n", i, op, off3);

    GEN(u32* rd = &cpu->r[opcode & 0b111];);
    GEN(u32 rs = cpu->r[(opcode >> 3) & 0b111];);

    if(op){
        if(i)
            printf("alu_SUB(cpu, rd, rs, %d, true);\n", off3);
        else
            printf("alu_SUB(cpu, rd, rs, cpu->r[%d], true);\n", off3);
    } else {
        if(i)
            printf("alu_ADD(cpu, rd, rs, %d, true);\n", off3);
        else
            printf("alu_ADD(cpu, rd, rs, cpu->r[%d], true);\n", off3);
    }
    RET;
}


void thumb_load_store_immediate_offset(bool b, bool l, int off5){
    printf("thumb_load_store_immediate_offset_%X_%X_%X:{\n", b, l, off5);

    GEN(u32 rb = cpu->r[(opcode >> 3) & 0b111];);
    GEN(u32* rd = &cpu->r[opcode & 0b111];);

    if(l){
        GEN(cpu->cycles += I_CYCLES;);
        if(b)
            printf("*rd = readByteN(cpu, rb + %d);\n", off5);
        else {
            printf("u32 addr = rb + (%d << 2);\n", off5);
            GEN(*rd = readWordN(cpu, addr););
            GEN(*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false););
        }
    } else {
        if(b)
            printf("writeByteN(cpu, rb + %d, *rd);\n", off5);
        else
            printf("writeWordN(cpu, rb + %d, *rd);\n", off5 << 2);
    }
    RET;
}

void thumb_push_pop(bool l, bool r){
    printf("thumb_push_pop_%X_%X:{\n", l, r);
    GEN(u8 rlist = opcode & 0xFF;);

    GEN(u8 count = __builtin_popcount(rlist););
    if(!l){
        printf("cpu->r[13] -= (count + %d) * 4;\n", r);
        GEN(rlist = opcode & 0xFF;);
    } else {
        GEN(cpu->cycles += I_CYCLES;);
    }

    GEN(for(int i = 0; i < 16 && rlist; i++){);
        GEN(bool should_transfer = rlist & 1;);
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
            GEN(thumb_pipeline_refill(cpu););
        }
        GEN(cpu->r[13] += 4;);
    }

    if(!l)
        printf("cpu->r[13] -= (count + %d) * 4;\n", r);

    RET;
}

void thumb_load_store_halfword(bool l, int off5){
    printf("thumb_load_store_halfword_%X_%X:{\n", l, off5);

    GEN(u32* rd = &cpu->r[opcode & 0b111];);
    GEN(u32 rb = cpu->r[(opcode >> 3) & 0b111];);

    if(l) {
        GEN(cpu->cycles += I_CYCLES;);
        printf("*rd = readHalfWordN(cpu, rb + %d);\n", off5);
        GEN(if(rb & 1));
            GEN(*rd = (*rd << 24) | (*rd >> 8););
    } else
        printf("writeHalfWordN(cpu, rb + %d, *rd);\n", off5);

    RET;
}

void thumb_load_store_sign_extended(bool h, bool s, int off3){
    printf("thumb_load_store_sign_extended_%X_%X_%X:{\n", h, s, off3);

    printf("u32 ro = cpu->r[%d];\n", off3);
    GEN(u32 rb = cpu->r[(opcode >> 3) & 0b111];);
    GEN(u32* rd = &cpu->r[opcode & 0b111];);
    GEN(u32 addr = rb + ro;);

    if(!h){
        if(!s){
            GEN(writeHalfWordN(cpu, addr, *rd););
        } else {
            GEN(cpu->cycles += I_CYCLES;);
            GEN(*rd = readByteN(cpu, addr););
            GEN(if(*rd & 0x80));
            GEN(    *rd |= 0xFFFFFF00;);
        }
    } else {
        GEN(cpu->cycles += I_CYCLES;);
        GEN(if(addr & 1){);
            if(!s){
                GEN(*rd = readHalfWordN(cpu, addr););
                GEN(*rd = (*rd >> 8) | (*rd << 24););
            } else {
                GEN(*rd = readByteN(cpu, addr););
                GEN(if(*rd & 0x80));
                GEN(    *rd |= 0xFFFFFF00;);
            }
        GEN(} else {);
            GEN(*rd = readHalfWordN(cpu, addr););
            if(s){
                GEN(if(*rd & 0xFFFF8000));
                GEN(    *rd |= 0xFFFF0000;);
            }
        GEN(});
    }

    RET;
}

void thumb_load_address(bool sp, int off3){
    printf("thumb_load_address_%X_%X:{\n", sp, off3);
    GEN(u8 w8 = opcode & 0xFF;);
    printf("u32* rd = &cpu->r[%d];\n", off3);
    if(sp)
        GEN(*rd = cpu->r[13];);
    else
        GEN(*rd = cpu->r[15] & 0xFFFFFFFC;);

    GEN(*rd += w8 << 2;);

    RET;
}

void thumb_load_store_register_offset(bool l, bool b, int off3){
    printf("thumb_load_store_register_offset_%X_%X_%X:{\n", l, b, off3);

    printf("u32 ro = cpu->r[%d];\n", off3);
    GEN(u32 rb = cpu->r[(opcode >> 3) & 0b111];);
    GEN(u32* rd = &cpu->r[opcode & 0b111];);
    GEN(u32 addr = rb + ro;);

    if(l){
        GEN(cpu->cycles += I_CYCLES;);
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

    RET;
}

void thumb_add_offset_sp(bool s){
    printf("thumb_add_offset_sp_%X:{\n", s);

    GEN(u16 w9 = (opcode & 0b1111111) << 2;);
    if(s)
        GEN(cpu->r[13] -= w9;);
    else
        GEN(cpu->r[13] += w9;);

    RET;
}

void thumb_sp_relative_load_store(bool l, int op3){
    printf("thumb_sp_relative_load_store_%X_%X:{\n", l, op3);

    printf("u32* rd = &cpu->r[%d];\n", op3);
    GEN(u8 w8 = opcode & 0xFF;);
    GEN(u32 addr = cpu->r[13] + (w8 << 2););

    if(l) {
        GEN(cpu->cycles += I_CYCLES;);
        GEN(*rd = readWordN(cpu, addr););
        GEN(*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false););
    } else
        GEN(writeWordN(cpu, addr, *rd););
    
    RET;
}

void thumb_software_interrupt(){
    printf("thumb_software_interrupt:{\n");
    GEN(arm7tdmi_trigger_exception(cpu, 0x8, 0x13););
    RET;
}