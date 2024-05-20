#include "arm7tdmi/arm.h"
#include "arm7tdmi/arm7tdmi.h"
#include "arm7tdmi/alu.h"

#include <stdio.h>
#include <stdlib.h>

void arm_mrs(arm7tdmi_t* cpu, u32 opcode);
void arm_msr(arm7tdmi_t* cpu, u32 opcode);
void arm_bx(arm7tdmi_t* cpu, u32 opcode);
void arm_b_bl(arm7tdmi_t* cpu, u32 opcode);
void arm_data_processing(arm7tdmi_t* cpu, u32 opcode);
void arm_halfword_data_transfer(arm7tdmi_t* cpu, u32 opcode);
void arm_single_data_transfer(arm7tdmi_t* cpu, u32 opcode);
void arm_block_data_transfer(arm7tdmi_t* cpu, u32 opcode);
void arm_multiply(arm7tdmi_t* cpu, u32 opcode);
void arm_multiply_long(arm7tdmi_t* cpu, u32 opcode);
u32 arm_shifter_reg(arm7tdmi_t* cpu, u32 opcode, bool s);
u32 arm_roller_imm(arm7tdmi_t* cpu, u32 opcode, bool s);

void arm_step(arm7tdmi_t* cpu){
    if(!cpu->pipeline_valid){
        cpu->pipeline_opcode = readWord(cpu, cpu->r[15]);
        cpu->r[15] += 4;
        cpu->pipeline_valid = true;
        return;
    }

    u32 opcode = cpu->pipeline_opcode;
    cpu->pipeline_opcode = readWord(cpu, cpu->r[15]);
    cpu->r[15] += 4;
    u8 cond = opcode >> 28;

    if((*condFuncs[cond])(cpu) == false)
        return;

    if(((opcode >> 24) & 0XF) == 0b1111){
        arm7tdmi_trigger_exception(cpu, 0x8, 0x13);
        return;
    }

    if(
        !((opcode >> 22) & 0b111111) &&
        (((opcode >> 4) & 0xF) == 0b1001)        
    ){
        arm_multiply(cpu, opcode);
        return;
    }

    if(
        (((opcode >> 23) & 0b11111) == 0b00001) &&
        (((opcode >> 4) & 0xF) == 0b1001)
    ){
        arm_multiply_long(cpu, opcode);
        return;
    }


    if(
        !(opcode & 0xFFF) &&
        (((opcode >> 16) & 0b111111) == 0b001111) &&
        (((opcode >> 23) & 0b11111) == 0b00010)
    ){
        arm_mrs(cpu, opcode);
        return;
    }

    if(
        (((opcode >> 23) & 0b11111) == 0b00110) && 
        (((opcode >> 20) & 0b11) == 0b10) && 
        (((opcode >> 12) & 0b1111) == 0b1111)
    ){
        arm_msr(cpu, opcode);
        return;
    }

    if(
        (((opcode >> 23) & 0b11111) == 0b00010) && 
        (((opcode >> 20) & 0b11) == 0b10) && 
        (((opcode >> 12) & 0b1111) == 0b1111) &&
        !(((opcode >> 4) & 0xFF))
    ){
        arm_msr(cpu, opcode);
        return;
    }
    

    if(((opcode >> 4) & 0xFFFFFF) == 0b000100101111111111110001){
        arm_bx(cpu, opcode);
        return;
    }

    if(((opcode >> 25) & 0b111) == 0b101){
        arm_b_bl(cpu, opcode);
        return;
    }

    if(
        ((opcode >> 26) & 0b11) == 0b01
    ){
        arm_single_data_transfer(cpu, opcode);
        return;
    }

    if(
        !((opcode >> 25) & 0b111)  &&
        ((opcode >> 7) & 1) &&
        ((opcode >> 4) & 1)
    ){
        arm_halfword_data_transfer(cpu, opcode);
        return;
    }

    if(((opcode >> 26) & 0b11) == 0b00){
        arm_data_processing(cpu, opcode);
        return;
    }

    if(((opcode >> 25) & 0b111) == 0b100){
        arm_block_data_transfer(cpu, opcode);
        return;
    }

    printf("UNKNOWN: PC: %X OPCODE: %X\n", cpu->r[15], opcode);
    exit(0);
}


void arm_bx(arm7tdmi_t* cpu, u32 opcode){
    cpu->r[15] = cpu->r[opcode & 0xF];
    cpu->thumb_mode = (cpu->r[15] & 0b1);
    cpu->r[15] &= 0xFFFFFFFE;
    cpu->pipeline_valid = false;
}

void arm_b_bl(arm7tdmi_t* cpu, u32 opcode){
    bool link_bit = (opcode >> 24) & 1;

    if(link_bit){
        cpu->r[14] = cpu->r[15] - 4;
    }

    u32 offset = opcode & 0xFFFFFF;
    if(offset & 0x800000)
        offset |= 0xFF000000;
    offset <<= 2;

    cpu->r[15] += offset;
    cpu->pipeline_valid = false;
}

void arm_mrs(arm7tdmi_t* cpu, u32 opcode){
    bool p_bit = (opcode >> 22) & 1;

    if(p_bit)
        cpu->r[(opcode >> 12) & 0xF] = *getSPSR(cpu);
    else
        cpu->r[(opcode >> 12) & 0xF] = cpu->CPSR;
}


void arm_msr(arm7tdmi_t* cpu, u32 opcode){
    u32 operand;
    u8 field_mask = (opcode >> 16) & 0xF;
    bool p = (opcode >> 22) & 1;
    bool i_bit = (opcode >> 25) & 1;
    u32 mask = 0;
    if(field_mask & 0b1000)
        mask |= 0xFF000000;
    if(field_mask & 0b1)
        mask |= 0xFF;

    if(!i_bit) 
        operand = cpu->r[opcode & 0xF];
    else
        operand = arm_roller_imm(cpu, opcode, false);

    if(p){
        u32* spsr = getSPSR(cpu);
        *spsr = (*spsr & ~mask) | (operand & mask);
    } else {
        saveBankedReg(cpu);
        cpu->CPSR = (cpu->CPSR & ~mask) | (operand & mask);
        loadBankedReg(cpu);
    }
}

void arm_data_processing(arm7tdmi_t* cpu, u32 opcode){
    bool s_bit = (opcode >> 20) & 1;
    bool i_bit = (opcode >> 25) & 1;

    u8 rd_idx = (opcode >> 12) & 0xF;
    u8 rn_idx = (opcode >> 16) & 0xF;
    u32 rn = cpu->r[rn_idx];
    u32* rd = &cpu->r[rd_idx];
    u32 op2;
    dataProcessingFunc alu_op = dataProcFuncs[(opcode >> 21) & 0xF];
    
    bool old_carry = cpu->C_FLAG;
    if(i_bit){
        op2 = arm_roller_imm(cpu, opcode, s_bit);
    } else {
        op2 = arm_shifter_reg(cpu, opcode, s_bit);
        if(rn_idx == 15 && ((opcode >> 4) & 1))
            rn += 4;
    }

    if(alu_op == alu_ADC || alu_op == alu_SBC || alu_op == alu_RSB)
        cpu->C_FLAG = old_carry;

    (*alu_op)(cpu, rd, rn, op2, s_bit);

    if(rd_idx == 15 && rn_idx != 15)
        cpu->pipeline_valid = false;

    if(s_bit && rd_idx == 15){
        saveBankedReg(cpu);
        cpu->CPSR = *getSPSR(cpu);
        loadBankedReg(cpu);
    }
}

void arm_halfword_data_transfer(arm7tdmi_t* cpu, u32 opcode){
    bool load_bit = (opcode >> 20) & 1;
    bool up_bit = (opcode >> 23) & 1;
    bool pre_bit = (opcode >> 24) & 1;
    bool write_bit = (opcode >> 21) & 1;
    u8 operation = (opcode >> 5) & 0b11;
    u32 offset;
    u32* rd = &cpu->r[(opcode >> 12) & 0xF];
    u32* rn = &cpu->r[(opcode >> 16) & 0xF];

    if((opcode >> 22) & 1)
        offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
    else {
        offset = cpu->r[opcode & 0xF]; 
    }

    u32 addr = *rn;

    if(pre_bit)
        addr += up_bit ? offset : -offset;

    switch (operation){
        case 0x00:
        alu_SWP(cpu, opcode);
        return;

        case 0x01:
        if(load_bit) {
            *rd = readHalfWord(cpu, addr);
            if(addr & 1)
                *rd = (*rd >> 8) | (*rd << 24);
        } else
            writeHalfWord(cpu, addr, *rd);
        break;

        case 0x02:
        if(load_bit){
            *rd = cpu->readByte(cpu, addr);
            if(*rd & 0x80)
                *rd |= 0xFFFFFF00; 
        } else
            cpu->writeByte(cpu, addr, *rd);
        break;

        case 0x03:
        if(load_bit){
            *rd = readHalfWord(cpu, addr);
            if(*rd & 0x8000)
                *rd |= 0xFFFF0000;  
            if(addr & 1)
            *rd = (*rd >> 8) | (*rd & 0x00800000 ? 0xFF000000 : 0);
        } else
            writeHalfWord(cpu, addr, *rd);
        break;
    }

    if(!pre_bit)
        addr += up_bit ? offset : -offset;

    if(write_bit || !pre_bit){
        if(!load_bit || rn != rd)
            *rn = addr;
    }

}

void arm_single_data_transfer(arm7tdmi_t* cpu, u32 opcode){
    bool i_bit = (opcode >> 25) & 1;
    bool p_bit = (opcode >> 24) & 1;
    bool u_bit = (opcode >> 23) & 1;
    bool b_bit = (opcode >> 22) & 1;
    bool w_bit = (opcode >> 21) & 1;
    bool l_bit = (opcode >> 20) & 1;

    u32 rn_idx = (opcode >> 16) & 0xF;
    u32 rd_idx = (opcode >> 12) & 0xF;
    u32* rn = &cpu->r[rn_idx];
    u32* rd = &cpu->r[rd_idx];
    u32 addr = *rn;
    u32 offset;

    if(i_bit)
        offset = arm_shifter_reg(cpu, opcode, false);
    else
        offset = opcode & 0xFFF;

    if(p_bit)
        addr += u_bit ? offset : -offset;

    if(l_bit){
        if(b_bit)
            *rd = cpu->readByte(cpu, addr);
        else{
            if(((opcode >> 12) & 0xF) == 15)
                cpu->pipeline_valid = false;
            *rd = readWord(cpu, addr);
            *rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
        }
    } else {
        u32 val = *rd;
        if(rd_idx == 15)
            val += 4;
        if(b_bit)
            cpu->writeByte(cpu, addr, val);
        else
            writeWord(cpu, addr, val);
    }

    if(!p_bit)
        addr += u_bit ? offset : -offset;

    if(w_bit || !p_bit){
        if(!l_bit || rn != rd)
            *rn = addr;
    }
}

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

u32 arm_roller_imm(arm7tdmi_t* cpu, u32 opcode, bool s){
    u32 val = opcode & 0xFF;
    u8 rot_amnt = (opcode >> 8) & 0xF;
    rot_amnt <<= 1;

    return alu_ROR(cpu, val, rot_amnt, s);
}

void arm_block_data_transfer(arm7tdmi_t* cpu, u32 opcode){
    bool p_bit = (opcode >> 24) & 1;
    bool u_bit = (opcode >> 23) & 1;
    bool s_bit = (opcode >> 22) & 1;
    bool w_bit = (opcode >> 21) & 1;
    bool l_bit = (opcode >> 20) & 1;
    u8 base_idx = (opcode >> 16) & 0xF;
    u32* rn = &cpu->r[base_idx];
    u16 reg_list = opcode & 0xFFFF;
    u32* regs = cpu->r;
    u32 addr = *rn;

    if(!(reg_list & (1 << 15)) && s_bit){
        saveBankedReg(cpu);
        regs = cpu->usr_r;
    }

    u32 reg_count = regcount_LUT[reg_list & 0xFF] + regcount_LUT[reg_list >> 8];
    if(!u_bit){
        addr -= reg_count*4;
        p_bit ^= 1;
    }

    if(!reg_count){
        if(l_bit){
            cpu->r[15] = readWord(cpu, *rn);
            cpu->pipeline_valid = false;
        } else {
            if(!u_bit)
                writeWord(cpu, *rn - (p_bit ? 0x3C : 0x40), cpu->r[15] + 4);
            else
                writeWord(cpu, *rn + (p_bit ? 0x04 : 0x00), cpu->r[15] + 4);
        }
        if(!u_bit)
            cpu->r[base_idx] -= 0x40;
        else
            cpu->r[base_idx] += 0x40;
    } else {
        bool first_transfer = true;
        for(int i = 0; i < 16 && reg_list; i++){ 
            bool should_transfer = reg_list & 1;
            reg_list >>= 1;
            if(!should_transfer)
                continue;

            if(p_bit)
                addr += 4;

            if(l_bit){
                if(i == 15){
                    cpu->pipeline_valid = false;
                    if(s_bit){
                        getSPSR(cpu);
                        printf("NOT SUPPORTED!\n");
                    }
                }
                regs[i] = readWord(cpu, addr);
            } else {
                if(i == base_idx && !first_transfer) {
                    if(!u_bit)
                        writeWord(cpu, addr, *rn - (reg_count << 2));
                    else
                        writeWord(cpu, addr, *rn + (reg_count << 2));
                } else
                    writeWord(cpu, addr, i == 15 ? regs[i] + 4 : regs[i]);
            }

            if(!p_bit)
                addr += 4;
            
            first_transfer = false;
        }

        if(!u_bit)
            addr -= reg_count*4; 

        
        reg_list = opcode & 0xFFFF;
        if(!(reg_list & (1 << 15)) && s_bit)
            loadBankedReg(cpu);

        
        if(w_bit){
            if(!(reg_list & (1 << base_idx)) || !l_bit)
                *rn = addr;
        }
    }
}

void arm_multiply(arm7tdmi_t* cpu, u32 opcode){
    bool a = (opcode >> 21) & 1;
    bool s = (opcode >> 20) & 1;

    u32 rm = cpu->r[opcode & 0xF];
    u32 rs = cpu->r[(opcode >> 8) & 0xF];
    u32 rn = cpu->r[(opcode >> 12) & 0xF];
    u32* rd = &cpu->r[(opcode >> 16) & 0xF];
    
    *rd = ((i32)rm) * ((i32)rs);
    
    if(a)
        *rd += rn;

    if(s){
        cpu->Z_FLAG = !(*rd);
        cpu->N_FLAG = *rd >> 31;
    }
}

void arm_multiply_long(arm7tdmi_t* cpu, u32 opcode){
    bool u = (opcode >> 22) & 1;
    bool a = (opcode >> 21) & 1;
    bool s = (opcode >> 20) & 1;

    u32 rm = cpu->r[opcode & 0xF];
    u32 rs = cpu->r[(opcode >> 8) & 0xF];
    u32* rd_lo = &cpu->r[(opcode >> 12) & 0xF];
    u32* rd_hi = &cpu->r[(opcode >> 16) & 0xF];
    u64 result;

    if(u)
        result = ((i64)(i32)rm) * ((i64)(i32)rs);
    else
        result = ((u64)rm) * ((u64)rs);

    if(a)
        result += (((u64)*rd_hi) << 32) | (u64)(*rd_lo);

    *rd_hi = result >> 32;
    *rd_lo = result;

    if(s){
        cpu->Z_FLAG = !result;
        cpu->N_FLAG = result >> 63;
    }
}