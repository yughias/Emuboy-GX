#include "arm7tdmi/thumb.h"
#include "arm7tdmi/arm7tdmi.h"
#include "arm7tdmi/alu.h"
#include "arm7tdmi/arm.h"

#include <stdio.h>
#include <stdlib.h>

void thumb_pc_relative_load(arm7tdmi_t* cpu, u16 opcode);
void thumb_add_subtract(arm7tdmi_t* cpu, u16 opcode);
void thumb_move_shifted_register(arm7tdmi_t* cpu, u16 opcode);
void thumb_conditional_branch(arm7tdmi_t* cpu, u16 opcode);
void thumb_unconditional_branch(arm7tdmi_t* cpu, u16 opcode);
void thumb_misc_immediate(arm7tdmi_t* cpu, u16 opcode);
void thumb_long_branch_link(arm7tdmi_t* cpu, u16 opcode);
void thumb_alu_operations(arm7tdmi_t* cpu, u16 opcode);
void thumb_load_store_immediate_offset(arm7tdmi_t* cpu, u16 opcode);
void thumb_multiple_load_store(arm7tdmi_t* cpu, u16 opcode);
void thumb_hi_reg_op(arm7tdmi_t* cpu, u16 opcode);
void thumb_push_pop(arm7tdmi_t* cpu, u16 opcode);
void thumb_load_store_halfword(arm7tdmi_t* cpu, u16 opcode);
void thumb_load_store_sign_extended(arm7tdmi_t* cpu, u16 opcode);
void thumb_load_address(arm7tdmi_t* cpu, u16 opcode);
void thumb_load_store_register_offset(arm7tdmi_t* cpu, u16 opcode);
void thumb_add_offset_sp(arm7tdmi_t* cpu, u16 opcode);
void thumb_sp_relative_load_store(arm7tdmi_t* cpu, u16 opcode);
void thumb_software_interrupt(arm7tdmi_t* cpu, u16 opcode);

void thumb_step(arm7tdmi_t* cpu){
    if(!cpu->pipeline_valid){
        cpu->pipeline_opcode = readHalfWord(cpu, cpu->r[15]);
        cpu->r[15] += 2;
        cpu->pipeline_valid = true;
        return;
    }

    u16 opcode = cpu->pipeline_opcode;
    u32 decoded_opcode;
    cpu->pipeline_opcode = readHalfWord(cpu, cpu->r[15]);
    cpu->r[15] += 2;

    if((opcode >> 8) == 0b11011111){
        thumb_software_interrupt(cpu, opcode);
        return;
    }

    if((opcode >> 11) == 0b00011){
        thumb_add_subtract(cpu, opcode);
        return;
    }

    if(!(opcode >> 13)){
        thumb_move_shifted_register(cpu, opcode);
        return;
    }

    if((opcode >> 13) == 0b001){
        thumb_misc_immediate(cpu, opcode);
        return;
    }

    if((opcode >> 10) == 0b010000){
        thumb_alu_operations(cpu, opcode);
        return;
    }

    if(
        ((opcode >> 12) == 0b0101) &&
        !((opcode >> 9) & 1)
    ){
        thumb_load_store_register_offset(cpu, opcode);
        return;
    }

    if(
        ((opcode >> 12) == 0b0101) &&
        ((opcode >> 9) & 1)
    ){
        thumb_load_store_sign_extended(cpu, opcode);
        return;
    }

    if((opcode >> 10) == 0b010001){
        thumb_hi_reg_op(cpu, opcode);
        return;
    }

    if((opcode >> 11) == 0b01001){
        thumb_pc_relative_load(cpu, opcode);
        return;
    }
    
    if((opcode >> 13) == 0b011){
        thumb_load_store_immediate_offset(cpu, opcode);
        return;
    }

    if((opcode >> 12) == 0b1001){
        thumb_sp_relative_load_store(cpu, opcode);
        return;
    }

    if((opcode >> 12) == 0b1000){
        thumb_load_store_halfword(cpu, opcode);
        return;
    }

    if((opcode >> 12) == 0b1010){
        thumb_load_address(cpu, opcode);
        return;
    }

    if((opcode >> 8) == 0b10110000){
        thumb_add_offset_sp(cpu, opcode);
        return;
    }

    if(
        ((opcode >> 12) == 0b1011) &&
        (((opcode >> 9) & 0b11) == 0b10)
    ){
        thumb_push_pop(cpu, opcode);
        return;
    }

    if((opcode >> 12) == 0b1100){
        thumb_multiple_load_store(cpu, opcode);
        return;
    }

    if((opcode >> 12) == 0b1101){
        thumb_conditional_branch(cpu, opcode);
        return;
    }

    if((opcode >> 11) == 0b11100){
        thumb_unconditional_branch(cpu, opcode);
        return;
    }
    
    if((opcode >> 12) == 0b1111){
        thumb_long_branch_link(cpu, opcode);
        return;
    }

    printf("NOT DECODED THUMB %X %X!\n", opcode, cpu->r[15]);
    arm7tdmi_print(cpu);
    exit(0);
}

void thumb_move_shifted_register(arm7tdmi_t* cpu, u16 opcode){
    u32* rd = &cpu->r[opcode & 0b111];
    u32 rs = cpu->r[(opcode >> 3) & 0b111];
    u8 off5 = (opcode >> 6) & 0b11111;

    switch((opcode >> 11) & 0b11){
        case 0:
        alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, off5, true), true);
        break;

        case 1:
        alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, !off5 ? 32 : off5, true), true);
        break;

        case 2:
        alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, !off5 ? 32: off5, true), true);
        break;
    }
}

void thumb_pc_relative_load(arm7tdmi_t* cpu, u16 opcode){
    u8 w8 = opcode & 0xFF;
    u32* rd = &cpu->r[(opcode >> 8) & 0b111];
    u32 addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2); 
    *rd = readWord(cpu, addr);
}


void thumb_conditional_branch(arm7tdmi_t* cpu, u16 opcode){
    u8 sOff8 = opcode & 0xFF;
    u8 cond = (opcode >> 8) & 0xF;
    if((*condFuncs[cond])(cpu) == false)
        return;

    cpu->r[15] += sOff8 & 0x80 ? (0xFFFFFF00 | sOff8) << 1 : sOff8 << 1;
    cpu->pipeline_valid = false;
}

void thumb_unconditional_branch(arm7tdmi_t* cpu, u16 opcode){
    u32 offset = (opcode & 0b11111111111) << 1;
    cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
    cpu->pipeline_valid = false;
}

void thumb_misc_immediate(arm7tdmi_t* cpu, u16 opcode){
    u8 offset = opcode & 0xFF;
    u32* rd = &cpu->r[(opcode >> 8) & 0b111];

    switch((opcode >> 11) & 0b11){
        case 0b00:
        alu_MOV(cpu, rd, *rd, offset, true);
        break;

        case 0b01:
        alu_CMP(cpu, rd, *rd, offset, true);
        break;

        case 0b10:
        alu_ADD(cpu, rd, *rd, offset, true);
        break;

        case 0b11:
        alu_SUB(cpu, rd, *rd, offset, true);
        break;
    }
}

void thumb_long_branch_link(arm7tdmi_t* cpu, u16 opcode){
    bool h = (opcode >> 11) & 1;
    u32 off = (opcode & 0b11111111111);

    if(!h){
        off <<= 1;
        if(off & 0x800)
            off |= 0xFFFFF000;
        cpu->r[14] = cpu->r[15] + (off << 11);
    } else {
        u32 old_r15 = cpu->r[15];
        cpu->r[15] = cpu->r[14] + (off << 1);
        cpu->r[15] &= 0xFFFFFFFE;
        cpu->r[14] = (old_r15 - 2) | 1;
        cpu->pipeline_valid = false;
    }
}

void thumb_alu_operations(arm7tdmi_t* cpu, u16 opcode){
    u32* rd = &cpu->r[opcode & 0b111];
    u32 rs = cpu->r[(opcode >> 3) & 0b111];
    u8 op = (opcode >> 6) & 0xF;

    switch(op){
        case 0:
        alu_AND(cpu, rd, *rd, rs, true);
        break;
        
        case 1:
        alu_EOR(cpu, rd, *rd, rs, true);
        break;

        case 2:
        alu_MOV(cpu, rd, 0, alu_LSL(cpu, *rd, rs, true), true);
        break;

        case 3:
        alu_MOV(cpu, rd, 0, alu_LSR(cpu, *rd, rs, true), true);
        break;

        case 4:
        alu_MOV(cpu, rd, 0, alu_ASR(cpu, *rd, rs, true), true);
        break;

        case 5:
        alu_ADC(cpu, rd, *rd, rs, true);
        break;

        case 6:
        alu_SBC(cpu, rd, *rd, rs, true);
        break;

        case 7:
        alu_MOV(cpu, rd, 0, alu_ROR(cpu, *rd, rs, true), true);
        break;

        case 8:
        alu_TST(cpu, rd, *rd, rs, true);
        break;

        case 9:
        //NEG
        alu_SUB(cpu, rd, 0, rs, true);
        break;

        case 10:
        alu_CMP(cpu, rd, *rd, rs, true);
        break;

        case 11:
        alu_CMN(cpu, rd, *rd, rs, true);
        break;

        case 12:
        alu_ORR(cpu, rd, *rd, rs, true);
        break;

        case 13:
        // MUL
        *rd = ((i32)*rd) * ((i32)rs);
        cpu->Z_FLAG = !(*rd);
        cpu->N_FLAG = *rd >> 31;
        break;

        case 14:
        alu_BIC(cpu, rd, *rd, rs, true);
        break;

        case 15:
        alu_MVN(cpu, rd, *rd, rs, true);
        break;
    }
}

void thumb_multiple_load_store(arm7tdmi_t* cpu, u16 opcode){
    u8 base_idx = (opcode >> 8) & 0b111;
    u32 base = cpu->r[base_idx];
    bool l = (opcode >> 11) & 1;
    u8 rlist = opcode & 0xFF;

    u8 count = 0xFF;
    if(!rlist){
        if(l){
            cpu->r[15] = readWord(cpu, base);
            cpu->pipeline_valid = false;
        } else {
            writeWord(cpu, base, cpu->r[15] + 2);
        }
        cpu->r[base_idx] += 0x40;
    } else{
        u8 rlist_size = 0;
        while(rlist){
            bool should_transfer = rlist & 1;
            rlist >>= 1;
            if(!should_transfer)
                continue;
            rlist_size += 1;
        }
        rlist = opcode & 0xFF;
        bool first_transfer = true;
        while(rlist){
            bool should_transfer = rlist & 1;
            rlist >>= 1;
            count += 1;
            if(!should_transfer)
                continue;
            if(l)
                cpu->r[count] = readWord(cpu, base);
            else {
                if(count == base_idx && !first_transfer)
                    writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
                else 
                    writeWord(cpu, base, cpu->r[count]);
            }
            base += 4;
            first_transfer = false;
        }

        cpu->r[base_idx] = base;
    }
}

void thumb_hi_reg_op(arm7tdmi_t* cpu, u16 opcode){
    bool h1 = (opcode >> 7) & 1;
    bool h2 = (opcode >> 6) & 1;
    
    u8 rd_idx = (opcode & 0b111) + h1*8;
    u8 rs_idx = ((opcode >> 3) & 0b111) + h2*8;

    u32* rd = &cpu->r[rd_idx];
    u32 rs = cpu->r[rs_idx];

    switch((opcode >> 8) & 0b11){
        case 0b00:
        alu_ADD(cpu, rd, *rd, rs, false);
        cpu->pipeline_valid = rd_idx != 15;
        cpu->r[15] &= 0xFFFFFFFE;
        break;

        case 0b01:
        // CMP CAN'T CHANGE R15
        alu_CMP(cpu, rd, *rd, rs, true);   
        break;

        case 0b10:
        alu_MOV(cpu, rd, *rd, rs, false);
        cpu->pipeline_valid = rd_idx != 15;
        if(rd_idx == 15)
            cpu->r[15] &= 0xFFFFFFFE;
        break;

        case 0b11:
        cpu->r[15] = rs;
        cpu->thumb_mode = (cpu->r[15] & 0b1);
        cpu->r[15] &= 0xFFFFFFFE;
        cpu->pipeline_valid = false;
        break;
    }
}

void thumb_add_subtract(arm7tdmi_t* cpu, u16 opcode){
    bool i = (opcode >> 10) & 1;
    bool op = (opcode >> 9) & 1;
    u8 idx = (opcode >> 6) & 0b111;
    u32* rd = &cpu->r[opcode & 0b111];
    u32 rs = cpu->r[(opcode >> 3) & 0b111];

    if(op){
        alu_SUB(cpu, rd, rs, i ? idx : cpu->r[idx], true);
    } else {
        alu_ADD(cpu, rd, rs, i ? idx : cpu->r[idx], true);
    }
}


void thumb_load_store_immediate_offset(arm7tdmi_t* cpu, u16 opcode){
    bool b = (opcode >> 12) & 1;
    bool l = (opcode >> 11) & 1;
    u8 off5 = (opcode >> 6) & 0b11111;
    u32 rb = cpu->r[(opcode >> 3) & 0b111];
    u32* rd = &cpu->r[opcode & 0b111];

    if(l){
        if(b)
            *rd = cpu->readByte(rb + off5);
        else {
            u32 addr = rb + (off5 << 2);
            *rd = readWord(cpu, addr);
            *rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
        }
    } else {
        if(b)
            cpu->writeByte(rb + off5, *rd);
        else
            writeWord(cpu, rb + (off5 << 2), *rd);
    }
}

void thumb_push_pop(arm7tdmi_t* cpu, u16 opcode){
    bool l = (opcode >> 11) & 1;
    bool r = (opcode >> 8) & 1;
    u8 rlist = opcode & 0xFF;

    // INEFFICIENT
    u8 rcount = 0;
    if(!l){
        for(int i = 0; i < 16 && rlist; i++){ 
            bool should_transfer = rlist & 1;
            rlist >>= 1;
            if(should_transfer)
                rcount++;
        }
        cpu->r[13] -= (rcount + r) *4;
        rlist = opcode & 0xFF;
    }

    for(int i = 0; i < 16 && rlist; i++){ 
        bool should_transfer = rlist & 1;
        rlist >>= 1;
        if(!should_transfer)
            continue;

        if(l)
            cpu->r[i] = readWord(cpu, cpu->r[13]);
        else
            writeWord(cpu, cpu->r[13], cpu->r[i]);

        cpu->r[13] += 4;
    }

    if(r){
        if(!l){
            writeWord(cpu, cpu->r[13], cpu->r[14]);
        } else {
            cpu->r[15] = readWord(cpu, cpu->r[13]);
            cpu->r[15] &= 0xFFFFFFFE;
            cpu->pipeline_valid = false;
        }
        cpu->r[13] += 4;
    }

    if(!l)
        cpu->r[13] -= (rcount + r) * 4;
}

void thumb_load_store_halfword(arm7tdmi_t* cpu, u16 opcode){
    bool l = (opcode >> 11) & 1;
    u32* rd = &cpu->r[opcode & 0b111];
    u32 rb = cpu->r[(opcode >> 3) & 0b111];
    u8 off5 = ((opcode >> 6) & 0b11111) << 1;

    if(l) {
        *rd = readHalfWord(cpu, rb + off5);
        if(rb & 1)
            *rd = (*rd << 24) | (*rd >> 8);
    } else
        writeHalfWord(cpu, rb + off5, *rd);
}

void thumb_load_store_sign_extended(arm7tdmi_t* cpu, u16 opcode){
    bool h = (opcode >> 11) & 1;
    bool s = (opcode >> 10) & 1;
    u32 ro = cpu->r[(opcode >> 6) & 0b111];
    u32 rb = cpu->r[(opcode >> 3) & 0b111];
    u32* rd = &cpu->r[opcode & 0b111];
    u32 addr = rb + ro;

    if(!h){
        if(!s){
            writeHalfWord(cpu, addr, *rd);
        } else {
            *rd = cpu->readByte(addr);
            if(*rd & 0x80)
                *rd |= 0xFFFFFF00;
        }
    } else {
        *rd = readHalfWord(cpu, addr);
        if(addr & 1){
            if(!s){
                *rd = (*rd >> 8) | (*rd << 24);
            } else {
                *rd = cpu->readByte(addr);
                if(*rd & 0x80)
                    *rd |= 0xFFFFFF00;
            }
        } else {
            if(s && (*rd & 0xFFFF8000))
                *rd |= 0xFFFF0000;
        }
    }
}

void thumb_load_address(arm7tdmi_t* cpu, u16 opcode){
    bool sp = (opcode >> 11) & 1;
    u8 w8 = opcode & 0xFF;
    u32* rd = &cpu->r[(opcode >> 8) & 0b111];
    if(sp)
        *rd = cpu->r[13];
    else
        *rd = cpu->r[15] & 0xFFFFFFFC;

    *rd += w8 << 2;
}

void thumb_load_store_register_offset(arm7tdmi_t* cpu, u16 opcode){
    bool l = (opcode >> 11) & 1;
    bool b = (opcode >> 10) & 1;

    u32 ro = cpu->r[(opcode >> 6) & 0b111];
    u32 rb = cpu->r[(opcode >> 3) & 0b111];
    u32* rd = &cpu->r[opcode & 0b111];
    u32 addr = rb + ro;

    if(l){
        if(b)
            *rd = cpu->readByte(addr);
        else {
            *rd = readWord(cpu, addr);
            *rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
        }
    } else {
        if(b)
            cpu->writeByte(addr, *rd);
        else
            writeWord(cpu, addr, *rd);
    }
}

void thumb_add_offset_sp(arm7tdmi_t* cpu, u16 opcode){
    bool s = (opcode >> 7) & 1;
    u32 w9 = (opcode & 0b1111111) << 2;
    if(s)
        cpu->r[13] -= w9;
    else
        cpu->r[13] += w9;
}

void thumb_sp_relative_load_store(arm7tdmi_t* cpu, u16 opcode){
    bool l = (opcode >> 11) & 1;
    u32* rd = &cpu->r[(opcode >> 8) & 0b111];
    u8 w8 = opcode & 0xFF;
    u32 addr = cpu->r[13] + (w8 << 2);

    if(l) {
        *rd = readWord(cpu, addr);
        if(addr & 0b11){
            int rot_amnt = (addr & 0b11) << 3;
            for(int i = 0; i < rot_amnt; i++)
                *rd = (*rd >> 1) | (*rd << 31);
        }
    } else
        writeWord(cpu, addr, *rd);
}

void thumb_software_interrupt(arm7tdmi_t* cpu, u16 opcode){
    arm7tdmi_trigger_exception(cpu, 0x8, 0x13);
}