#include "arm7tdmi/arm7tdmi.h"
#include "arm7tdmi/arm.h"
#include "arm7tdmi/arm7tdmi_util.h"

#include <stdio.h>
#include <stdlib.h>

void arm_step(arm7tdmi_t* cpu){
u32 opcode = cpu->pipeline_opcode[0];
cpu->pipeline_opcode[0] = cpu->pipeline_opcode[1];
cpu->r[15] += 4;
cpu->pipeline_opcode[1] = readWordAndTick(cpu, cpu->r[15], cpu->fetch_seq);
cpu->fetch_seq = true;

u8 cond = opcode >> 28;
if((*condFuncs[cond])(cpu) == false)
return;

static void* arm_table[1 << 12] = {&&arm_data_processing_0_0_0_0, &&arm_data_processing_0_0_0_1, &&arm_data_processing_0_0_0_2, &&arm_data_processing_0_0_0_3, &&arm_data_processing_0_0_0_4, &&arm_data_processing_0_0_0_5, &&arm_data_processing_0_0_0_6, &&arm_data_processing_0_0_0_7, &&arm_data_processing_0_0_0_0, &&arm_multiply_0_0, &&arm_data_processing_0_0_0_2, &&arm_halfword_data_transfer_0_0_0_0_1_0, &&arm_data_processing_0_0_0_4, &&arm_halfword_data_transfer_0_0_0_0_2_0, &&arm_data_processing_0_0_0_6, &&arm_halfword_data_transfer_0_0_0_0_3_0, &&arm_data_processing_1_0_0_0, &&arm_data_processing_1_0_0_1, &&arm_data_processing_1_0_0_2, &&arm_data_processing_1_0_0_3, &&arm_data_processing_1_0_0_4, &&arm_data_processing_1_0_0_5, &&arm_data_processing_1_0_0_6, &&arm_data_processing_1_0_0_7, &&arm_data_processing_1_0_0_0, &&arm_multiply_0_1, &&arm_data_processing_1_0_0_2, &&arm_halfword_data_transfer_1_0_0_0_1_0, &&arm_data_processing_1_0_0_4, &&arm_halfword_data_transfer_1_0_0_0_2_0, &&arm_data_processing_1_0_0_6, &&arm_halfword_data_transfer_1_0_0_0_3_0, &&arm_data_processing_0_0_1_0, &&arm_data_processing_0_0_1_1, &&arm_data_processing_0_0_1_2, &&arm_data_processing_0_0_1_3, &&arm_data_processing_0_0_1_4, &&arm_data_processing_0_0_1_5, &&arm_data_processing_0_0_1_6, &&arm_data_processing_0_0_1_7, &&arm_data_processing_0_0_1_0, &&arm_multiply_1_0, &&arm_data_processing_0_0_1_2, &&arm_halfword_data_transfer_0_0_0_1_1_0, &&arm_data_processing_0_0_1_4, &&arm_halfword_data_transfer_0_0_0_1_2_0, &&arm_data_processing_0_0_1_6, &&arm_halfword_data_transfer_0_0_0_1_3_0, &&arm_data_processing_1_0_1_0, &&arm_data_processing_1_0_1_1, &&arm_data_processing_1_0_1_2, &&arm_data_processing_1_0_1_3, &&arm_data_processing_1_0_1_4, &&arm_data_processing_1_0_1_5, &&arm_data_processing_1_0_1_6, &&arm_data_processing_1_0_1_7, &&arm_data_processing_1_0_1_0, &&arm_multiply_1_1, &&arm_data_processing_1_0_1_2, &&arm_halfword_data_transfer_1_0_0_1_1_0, &&arm_data_processing_1_0_1_4, &&arm_halfword_data_transfer_1_0_0_1_2_0, &&arm_data_processing_1_0_1_6, &&arm_halfword_data_transfer_1_0_0_1_3_0, &&arm_data_processing_0_0_2_0, &&arm_data_processing_0_0_2_1, &&arm_data_processing_0_0_2_2, &&arm_data_processing_0_0_2_3, &&arm_data_processing_0_0_2_4, &&arm_data_processing_0_0_2_5, &&arm_data_processing_0_0_2_6, &&arm_data_processing_0_0_2_7, &&arm_data_processing_0_0_2_0, &&arm_halfword_data_transfer_0_0_0_0_0_1, &&arm_data_processing_0_0_2_2, &&arm_halfword_data_transfer_0_0_0_0_1_1, &&arm_data_processing_0_0_2_4, &&arm_halfword_data_transfer_0_0_0_0_2_1, &&arm_data_processing_0_0_2_6, &&arm_halfword_data_transfer_0_0_0_0_3_1, &&arm_data_processing_1_0_2_0, &&arm_data_processing_1_0_2_1, &&arm_data_processing_1_0_2_2, &&arm_data_processing_1_0_2_3, &&arm_data_processing_1_0_2_4, &&arm_data_processing_1_0_2_5, &&arm_data_processing_1_0_2_6, &&arm_data_processing_1_0_2_7, &&arm_data_processing_1_0_2_0, &&arm_halfword_data_transfer_1_0_0_0_0_1, &&arm_data_processing_1_0_2_2, &&arm_halfword_data_transfer_1_0_0_0_1_1, &&arm_data_processing_1_0_2_4, &&arm_halfword_data_transfer_1_0_0_0_2_1, &&arm_data_processing_1_0_2_6, &&arm_halfword_data_transfer_1_0_0_0_3_1, &&arm_data_processing_0_0_3_0, &&arm_data_processing_0_0_3_1, &&arm_data_processing_0_0_3_2, &&arm_data_processing_0_0_3_3, &&arm_data_processing_0_0_3_4, &&arm_data_processing_0_0_3_5, &&arm_data_processing_0_0_3_6, &&arm_data_processing_0_0_3_7, &&arm_data_processing_0_0_3_0, &&arm_halfword_data_transfer_0_0_0_1_0_1, &&arm_data_processing_0_0_3_2, &&arm_halfword_data_transfer_0_0_0_1_1_1, &&arm_data_processing_0_0_3_4, &&arm_halfword_data_transfer_0_0_0_1_2_1, &&arm_data_processing_0_0_3_6, &&arm_halfword_data_transfer_0_0_0_1_3_1, &&arm_data_processing_1_0_3_0, &&arm_data_processing_1_0_3_1, &&arm_data_processing_1_0_3_2, &&arm_data_processing_1_0_3_3, &&arm_data_processing_1_0_3_4, &&arm_data_processing_1_0_3_5, &&arm_data_processing_1_0_3_6, &&arm_data_processing_1_0_3_7, &&arm_data_processing_1_0_3_0, &&arm_halfword_data_transfer_1_0_0_1_0_1, &&arm_data_processing_1_0_3_2, &&arm_halfword_data_transfer_1_0_0_1_1_1, &&arm_data_processing_1_0_3_4, &&arm_halfword_data_transfer_1_0_0_1_2_1, &&arm_data_processing_1_0_3_6, &&arm_halfword_data_transfer_1_0_0_1_3_1, &&arm_data_processing_0_0_4_0, &&arm_data_processing_0_0_4_1, &&arm_data_processing_0_0_4_2, &&arm_data_processing_0_0_4_3, &&arm_data_processing_0_0_4_4, &&arm_data_processing_0_0_4_5, &&arm_data_processing_0_0_4_6, &&arm_data_processing_0_0_4_7, &&arm_data_processing_0_0_4_0, &&arm_multiply_long_0_0_0, &&arm_data_processing_0_0_4_2, &&arm_halfword_data_transfer_0_1_0_0_1_0, &&arm_data_processing_0_0_4_4, &&arm_halfword_data_transfer_0_1_0_0_2_0, &&arm_data_processing_0_0_4_6, &&arm_halfword_data_transfer_0_1_0_0_3_0, &&arm_data_processing_1_0_4_0, &&arm_data_processing_1_0_4_1, &&arm_data_processing_1_0_4_2, &&arm_data_processing_1_0_4_3, &&arm_data_processing_1_0_4_4, &&arm_data_processing_1_0_4_5, &&arm_data_processing_1_0_4_6, &&arm_data_processing_1_0_4_7, &&arm_data_processing_1_0_4_0, &&arm_multiply_long_0_0_1, &&arm_data_processing_1_0_4_2, &&arm_halfword_data_transfer_1_1_0_0_1_0, &&arm_data_processing_1_0_4_4, &&arm_halfword_data_transfer_1_1_0_0_2_0, &&arm_data_processing_1_0_4_6, &&arm_halfword_data_transfer_1_1_0_0_3_0, &&arm_data_processing_0_0_5_0, &&arm_data_processing_0_0_5_1, &&arm_data_processing_0_0_5_2, &&arm_data_processing_0_0_5_3, &&arm_data_processing_0_0_5_4, &&arm_data_processing_0_0_5_5, &&arm_data_processing_0_0_5_6, &&arm_data_processing_0_0_5_7, &&arm_data_processing_0_0_5_0, &&arm_multiply_long_0_1_0, &&arm_data_processing_0_0_5_2, &&arm_halfword_data_transfer_0_1_0_1_1_0, &&arm_data_processing_0_0_5_4, &&arm_halfword_data_transfer_0_1_0_1_2_0, &&arm_data_processing_0_0_5_6, &&arm_halfword_data_transfer_0_1_0_1_3_0, &&arm_data_processing_1_0_5_0, &&arm_data_processing_1_0_5_1, &&arm_data_processing_1_0_5_2, &&arm_data_processing_1_0_5_3, &&arm_data_processing_1_0_5_4, &&arm_data_processing_1_0_5_5, &&arm_data_processing_1_0_5_6, &&arm_data_processing_1_0_5_7, &&arm_data_processing_1_0_5_0, &&arm_multiply_long_0_1_1, &&arm_data_processing_1_0_5_2, &&arm_halfword_data_transfer_1_1_0_1_1_0, &&arm_data_processing_1_0_5_4, &&arm_halfword_data_transfer_1_1_0_1_2_0, &&arm_data_processing_1_0_5_6, &&arm_halfword_data_transfer_1_1_0_1_3_0, &&arm_data_processing_0_0_6_0, &&arm_data_processing_0_0_6_1, &&arm_data_processing_0_0_6_2, &&arm_data_processing_0_0_6_3, &&arm_data_processing_0_0_6_4, &&arm_data_processing_0_0_6_5, &&arm_data_processing_0_0_6_6, &&arm_data_processing_0_0_6_7, &&arm_data_processing_0_0_6_0, &&arm_multiply_long_1_0_0, &&arm_data_processing_0_0_6_2, &&arm_halfword_data_transfer_0_1_0_0_1_1, &&arm_data_processing_0_0_6_4, &&arm_halfword_data_transfer_0_1_0_0_2_1, &&arm_data_processing_0_0_6_6, &&arm_halfword_data_transfer_0_1_0_0_3_1, &&arm_data_processing_1_0_6_0, &&arm_data_processing_1_0_6_1, &&arm_data_processing_1_0_6_2, &&arm_data_processing_1_0_6_3, &&arm_data_processing_1_0_6_4, &&arm_data_processing_1_0_6_5, &&arm_data_processing_1_0_6_6, &&arm_data_processing_1_0_6_7, &&arm_data_processing_1_0_6_0, &&arm_multiply_long_1_0_1, &&arm_data_processing_1_0_6_2, &&arm_halfword_data_transfer_1_1_0_0_1_1, &&arm_data_processing_1_0_6_4, &&arm_halfword_data_transfer_1_1_0_0_2_1, &&arm_data_processing_1_0_6_6, &&arm_halfword_data_transfer_1_1_0_0_3_1, &&arm_data_processing_0_0_7_0, &&arm_data_processing_0_0_7_1, &&arm_data_processing_0_0_7_2, &&arm_data_processing_0_0_7_3, &&arm_data_processing_0_0_7_4, &&arm_data_processing_0_0_7_5, &&arm_data_processing_0_0_7_6, &&arm_data_processing_0_0_7_7, &&arm_data_processing_0_0_7_0, &&arm_multiply_long_1_1_0, &&arm_data_processing_0_0_7_2, &&arm_halfword_data_transfer_0_1_0_1_1_1, &&arm_data_processing_0_0_7_4, &&arm_halfword_data_transfer_0_1_0_1_2_1, &&arm_data_processing_0_0_7_6, &&arm_halfword_data_transfer_0_1_0_1_3_1, &&arm_data_processing_1_0_7_0, &&arm_data_processing_1_0_7_1, &&arm_data_processing_1_0_7_2, &&arm_data_processing_1_0_7_3, &&arm_data_processing_1_0_7_4, &&arm_data_processing_1_0_7_5, &&arm_data_processing_1_0_7_6, &&arm_data_processing_1_0_7_7, &&arm_data_processing_1_0_7_0, &&arm_multiply_long_1_1_1, &&arm_data_processing_1_0_7_2, &&arm_halfword_data_transfer_1_1_0_1_1_1, &&arm_data_processing_1_0_7_4, &&arm_halfword_data_transfer_1_1_0_1_2_1, &&arm_data_processing_1_0_7_6, &&arm_halfword_data_transfer_1_1_0_1_3_1, &&arm_mrs_0, &&arm_data_processing_0_0_8_1, &&arm_data_processing_0_0_8_2, &&arm_data_processing_0_0_8_3, &&arm_data_processing_0_0_8_4, &&arm_data_processing_0_0_8_5, &&arm_data_processing_0_0_8_6, &&arm_data_processing_0_0_8_7, &&arm_data_processing_0_0_8_0, &&arm_halfword_data_transfer_0_0_1_0_0_0, &&arm_data_processing_0_0_8_2, &&arm_halfword_data_transfer_0_0_1_0_1_0, &&arm_data_processing_0_0_8_4, &&arm_halfword_data_transfer_0_0_1_0_2_0, &&arm_data_processing_0_0_8_6, &&arm_halfword_data_transfer_0_0_1_0_3_0, &&arm_data_processing_1_0_8_0, &&arm_data_processing_1_0_8_1, &&arm_data_processing_1_0_8_2, &&arm_data_processing_1_0_8_3, &&arm_data_processing_1_0_8_4, &&arm_data_processing_1_0_8_5, &&arm_data_processing_1_0_8_6, &&arm_data_processing_1_0_8_7, &&arm_data_processing_1_0_8_0, &&arm_halfword_data_transfer_1_0_1_0_0_0, &&arm_data_processing_1_0_8_2, &&arm_halfword_data_transfer_1_0_1_0_1_0, &&arm_data_processing_1_0_8_4, &&arm_halfword_data_transfer_1_0_1_0_2_0, &&arm_data_processing_1_0_8_6, &&arm_halfword_data_transfer_1_0_1_0_3_0, &&arm_msr_0_0, &&arm_bx, &&arm_data_processing_0_0_9_2, &&arm_data_processing_0_0_9_3, &&arm_data_processing_0_0_9_4, &&arm_data_processing_0_0_9_5, &&arm_data_processing_0_0_9_6, &&arm_data_processing_0_0_9_7, &&arm_data_processing_0_0_9_0, &&arm_halfword_data_transfer_0_0_1_1_0_0, &&arm_data_processing_0_0_9_2, &&arm_halfword_data_transfer_0_0_1_1_1_0, &&arm_data_processing_0_0_9_4, &&arm_halfword_data_transfer_0_0_1_1_2_0, &&arm_data_processing_0_0_9_6, &&arm_halfword_data_transfer_0_0_1_1_3_0, &&arm_data_processing_1_0_9_0, &&arm_data_processing_1_0_9_1, &&arm_data_processing_1_0_9_2, &&arm_data_processing_1_0_9_3, &&arm_data_processing_1_0_9_4, &&arm_data_processing_1_0_9_5, &&arm_data_processing_1_0_9_6, &&arm_data_processing_1_0_9_7, &&arm_data_processing_1_0_9_0, &&arm_halfword_data_transfer_1_0_1_1_0_0, &&arm_data_processing_1_0_9_2, &&arm_halfword_data_transfer_1_0_1_1_1_0, &&arm_data_processing_1_0_9_4, &&arm_halfword_data_transfer_1_0_1_1_2_0, &&arm_data_processing_1_0_9_6, &&arm_halfword_data_transfer_1_0_1_1_3_0, &&arm_mrs_1, &&arm_data_processing_0_0_A_1, &&arm_data_processing_0_0_A_2, &&arm_data_processing_0_0_A_3, &&arm_data_processing_0_0_A_4, &&arm_data_processing_0_0_A_5, &&arm_data_processing_0_0_A_6, &&arm_data_processing_0_0_A_7, &&arm_data_processing_0_0_A_0, &&arm_halfword_data_transfer_0_0_1_0_0_1, &&arm_data_processing_0_0_A_2, &&arm_halfword_data_transfer_0_0_1_0_1_1, &&arm_data_processing_0_0_A_4, &&arm_halfword_data_transfer_0_0_1_0_2_1, &&arm_data_processing_0_0_A_6, &&arm_halfword_data_transfer_0_0_1_0_3_1, &&arm_data_processing_1_0_A_0, &&arm_data_processing_1_0_A_1, &&arm_data_processing_1_0_A_2, &&arm_data_processing_1_0_A_3, &&arm_data_processing_1_0_A_4, &&arm_data_processing_1_0_A_5, &&arm_data_processing_1_0_A_6, &&arm_data_processing_1_0_A_7, &&arm_data_processing_1_0_A_0, &&arm_halfword_data_transfer_1_0_1_0_0_1, &&arm_data_processing_1_0_A_2, &&arm_halfword_data_transfer_1_0_1_0_1_1, &&arm_data_processing_1_0_A_4, &&arm_halfword_data_transfer_1_0_1_0_2_1, &&arm_data_processing_1_0_A_6, &&arm_halfword_data_transfer_1_0_1_0_3_1, &&arm_msr_1_0, &&arm_data_processing_0_0_B_1, &&arm_data_processing_0_0_B_2, &&arm_data_processing_0_0_B_3, &&arm_data_processing_0_0_B_4, &&arm_data_processing_0_0_B_5, &&arm_data_processing_0_0_B_6, &&arm_data_processing_0_0_B_7, &&arm_data_processing_0_0_B_0, &&arm_halfword_data_transfer_0_0_1_1_0_1, &&arm_data_processing_0_0_B_2, &&arm_halfword_data_transfer_0_0_1_1_1_1, &&arm_data_processing_0_0_B_4, &&arm_halfword_data_transfer_0_0_1_1_2_1, &&arm_data_processing_0_0_B_6, &&arm_halfword_data_transfer_0_0_1_1_3_1, &&arm_data_processing_1_0_B_0, &&arm_data_processing_1_0_B_1, &&arm_data_processing_1_0_B_2, &&arm_data_processing_1_0_B_3, &&arm_data_processing_1_0_B_4, &&arm_data_processing_1_0_B_5, &&arm_data_processing_1_0_B_6, &&arm_data_processing_1_0_B_7, &&arm_data_processing_1_0_B_0, &&arm_halfword_data_transfer_1_0_1_1_0_1, &&arm_data_processing_1_0_B_2, &&arm_halfword_data_transfer_1_0_1_1_1_1, &&arm_data_processing_1_0_B_4, &&arm_halfword_data_transfer_1_0_1_1_2_1, &&arm_data_processing_1_0_B_6, &&arm_halfword_data_transfer_1_0_1_1_3_1, &&arm_data_processing_0_0_C_0, &&arm_data_processing_0_0_C_1, &&arm_data_processing_0_0_C_2, &&arm_data_processing_0_0_C_3, &&arm_data_processing_0_0_C_4, &&arm_data_processing_0_0_C_5, &&arm_data_processing_0_0_C_6, &&arm_data_processing_0_0_C_7, &&arm_data_processing_0_0_C_0, &&arm_halfword_data_transfer_0_1_1_0_0_0, &&arm_data_processing_0_0_C_2, &&arm_halfword_data_transfer_0_1_1_0_1_0, &&arm_data_processing_0_0_C_4, &&arm_halfword_data_transfer_0_1_1_0_2_0, &&arm_data_processing_0_0_C_6, &&arm_halfword_data_transfer_0_1_1_0_3_0, &&arm_data_processing_1_0_C_0, &&arm_data_processing_1_0_C_1, &&arm_data_processing_1_0_C_2, &&arm_data_processing_1_0_C_3, &&arm_data_processing_1_0_C_4, &&arm_data_processing_1_0_C_5, &&arm_data_processing_1_0_C_6, &&arm_data_processing_1_0_C_7, &&arm_data_processing_1_0_C_0, &&arm_halfword_data_transfer_1_1_1_0_0_0, &&arm_data_processing_1_0_C_2, &&arm_halfword_data_transfer_1_1_1_0_1_0, &&arm_data_processing_1_0_C_4, &&arm_halfword_data_transfer_1_1_1_0_2_0, &&arm_data_processing_1_0_C_6, &&arm_halfword_data_transfer_1_1_1_0_3_0, &&arm_data_processing_0_0_D_0, &&arm_data_processing_0_0_D_1, &&arm_data_processing_0_0_D_2, &&arm_data_processing_0_0_D_3, &&arm_data_processing_0_0_D_4, &&arm_data_processing_0_0_D_5, &&arm_data_processing_0_0_D_6, &&arm_data_processing_0_0_D_7, &&arm_data_processing_0_0_D_0, &&arm_halfword_data_transfer_0_1_1_1_0_0, &&arm_data_processing_0_0_D_2, &&arm_halfword_data_transfer_0_1_1_1_1_0, &&arm_data_processing_0_0_D_4, &&arm_halfword_data_transfer_0_1_1_1_2_0, &&arm_data_processing_0_0_D_6, &&arm_halfword_data_transfer_0_1_1_1_3_0, &&arm_data_processing_1_0_D_0, &&arm_data_processing_1_0_D_1, &&arm_data_processing_1_0_D_2, &&arm_data_processing_1_0_D_3, &&arm_data_processing_1_0_D_4, &&arm_data_processing_1_0_D_5, &&arm_data_processing_1_0_D_6, &&arm_data_processing_1_0_D_7, &&arm_data_processing_1_0_D_0, &&arm_halfword_data_transfer_1_1_1_1_0_0, &&arm_data_processing_1_0_D_2, &&arm_halfword_data_transfer_1_1_1_1_1_0, &&arm_data_processing_1_0_D_4, &&arm_halfword_data_transfer_1_1_1_1_2_0, &&arm_data_processing_1_0_D_6, &&arm_halfword_data_transfer_1_1_1_1_3_0, &&arm_data_processing_0_0_E_0, &&arm_data_processing_0_0_E_1, &&arm_data_processing_0_0_E_2, &&arm_data_processing_0_0_E_3, &&arm_data_processing_0_0_E_4, &&arm_data_processing_0_0_E_5, &&arm_data_processing_0_0_E_6, &&arm_data_processing_0_0_E_7, &&arm_data_processing_0_0_E_0, &&arm_halfword_data_transfer_0_1_1_0_0_1, &&arm_data_processing_0_0_E_2, &&arm_halfword_data_transfer_0_1_1_0_1_1, &&arm_data_processing_0_0_E_4, &&arm_halfword_data_transfer_0_1_1_0_2_1, &&arm_data_processing_0_0_E_6, &&arm_halfword_data_transfer_0_1_1_0_3_1, &&arm_data_processing_1_0_E_0, &&arm_data_processing_1_0_E_1, &&arm_data_processing_1_0_E_2, &&arm_data_processing_1_0_E_3, &&arm_data_processing_1_0_E_4, &&arm_data_processing_1_0_E_5, &&arm_data_processing_1_0_E_6, &&arm_data_processing_1_0_E_7, &&arm_data_processing_1_0_E_0, &&arm_halfword_data_transfer_1_1_1_0_0_1, &&arm_data_processing_1_0_E_2, &&arm_halfword_data_transfer_1_1_1_0_1_1, &&arm_data_processing_1_0_E_4, &&arm_halfword_data_transfer_1_1_1_0_2_1, &&arm_data_processing_1_0_E_6, &&arm_halfword_data_transfer_1_1_1_0_3_1, &&arm_data_processing_0_0_F_0, &&arm_data_processing_0_0_F_1, &&arm_data_processing_0_0_F_2, &&arm_data_processing_0_0_F_3, &&arm_data_processing_0_0_F_4, &&arm_data_processing_0_0_F_5, &&arm_data_processing_0_0_F_6, &&arm_data_processing_0_0_F_7, &&arm_data_processing_0_0_F_0, &&arm_halfword_data_transfer_0_1_1_1_0_1, &&arm_data_processing_0_0_F_2, &&arm_halfword_data_transfer_0_1_1_1_1_1, &&arm_data_processing_0_0_F_4, &&arm_halfword_data_transfer_0_1_1_1_2_1, &&arm_data_processing_0_0_F_6, &&arm_halfword_data_transfer_0_1_1_1_3_1, &&arm_data_processing_1_0_F_0, &&arm_data_processing_1_0_F_1, &&arm_data_processing_1_0_F_2, &&arm_data_processing_1_0_F_3, &&arm_data_processing_1_0_F_4, &&arm_data_processing_1_0_F_5, &&arm_data_processing_1_0_F_6, &&arm_data_processing_1_0_F_7, &&arm_data_processing_1_0_F_0, &&arm_halfword_data_transfer_1_1_1_1_0_1, &&arm_data_processing_1_0_F_2, &&arm_halfword_data_transfer_1_1_1_1_1_1, &&arm_data_processing_1_0_F_4, &&arm_halfword_data_transfer_1_1_1_1_2_1, &&arm_data_processing_1_0_F_6, &&arm_halfword_data_transfer_1_1_1_1_3_1, &&arm_data_processing_0_1_0_0, &&arm_data_processing_0_1_0_1, &&arm_data_processing_0_1_0_2, &&arm_data_processing_0_1_0_3, &&arm_data_processing_0_1_0_4, &&arm_data_processing_0_1_0_5, &&arm_data_processing_0_1_0_6, &&arm_data_processing_0_1_0_7, &&arm_data_processing_0_1_0_0, &&arm_data_processing_0_1_0_1, &&arm_data_processing_0_1_0_2, &&arm_data_processing_0_1_0_3, &&arm_data_processing_0_1_0_4, &&arm_data_processing_0_1_0_5, &&arm_data_processing_0_1_0_6, &&arm_data_processing_0_1_0_7, &&arm_data_processing_1_1_0_0, &&arm_data_processing_1_1_0_1, &&arm_data_processing_1_1_0_2, &&arm_data_processing_1_1_0_3, &&arm_data_processing_1_1_0_4, &&arm_data_processing_1_1_0_5, &&arm_data_processing_1_1_0_6, &&arm_data_processing_1_1_0_7, &&arm_data_processing_1_1_0_0, &&arm_data_processing_1_1_0_1, &&arm_data_processing_1_1_0_2, &&arm_data_processing_1_1_0_3, &&arm_data_processing_1_1_0_4, &&arm_data_processing_1_1_0_5, &&arm_data_processing_1_1_0_6, &&arm_data_processing_1_1_0_7, &&arm_data_processing_0_1_1_0, &&arm_data_processing_0_1_1_1, &&arm_data_processing_0_1_1_2, &&arm_data_processing_0_1_1_3, &&arm_data_processing_0_1_1_4, &&arm_data_processing_0_1_1_5, &&arm_data_processing_0_1_1_6, &&arm_data_processing_0_1_1_7, &&arm_data_processing_0_1_1_0, &&arm_data_processing_0_1_1_1, &&arm_data_processing_0_1_1_2, &&arm_data_processing_0_1_1_3, &&arm_data_processing_0_1_1_4, &&arm_data_processing_0_1_1_5, &&arm_data_processing_0_1_1_6, &&arm_data_processing_0_1_1_7, &&arm_data_processing_1_1_1_0, &&arm_data_processing_1_1_1_1, &&arm_data_processing_1_1_1_2, &&arm_data_processing_1_1_1_3, &&arm_data_processing_1_1_1_4, &&arm_data_processing_1_1_1_5, &&arm_data_processing_1_1_1_6, &&arm_data_processing_1_1_1_7, &&arm_data_processing_1_1_1_0, &&arm_data_processing_1_1_1_1, &&arm_data_processing_1_1_1_2, &&arm_data_processing_1_1_1_3, &&arm_data_processing_1_1_1_4, &&arm_data_processing_1_1_1_5, &&arm_data_processing_1_1_1_6, &&arm_data_processing_1_1_1_7, &&arm_data_processing_0_1_2_0, &&arm_data_processing_0_1_2_1, &&arm_data_processing_0_1_2_2, &&arm_data_processing_0_1_2_3, &&arm_data_processing_0_1_2_4, &&arm_data_processing_0_1_2_5, &&arm_data_processing_0_1_2_6, &&arm_data_processing_0_1_2_7, &&arm_data_processing_0_1_2_0, &&arm_data_processing_0_1_2_1, &&arm_data_processing_0_1_2_2, &&arm_data_processing_0_1_2_3, &&arm_data_processing_0_1_2_4, &&arm_data_processing_0_1_2_5, &&arm_data_processing_0_1_2_6, &&arm_data_processing_0_1_2_7, &&arm_data_processing_1_1_2_0, &&arm_data_processing_1_1_2_1, &&arm_data_processing_1_1_2_2, &&arm_data_processing_1_1_2_3, &&arm_data_processing_1_1_2_4, &&arm_data_processing_1_1_2_5, &&arm_data_processing_1_1_2_6, &&arm_data_processing_1_1_2_7, &&arm_data_processing_1_1_2_0, &&arm_data_processing_1_1_2_1, &&arm_data_processing_1_1_2_2, &&arm_data_processing_1_1_2_3, &&arm_data_processing_1_1_2_4, &&arm_data_processing_1_1_2_5, &&arm_data_processing_1_1_2_6, &&arm_data_processing_1_1_2_7, &&arm_data_processing_0_1_3_0, &&arm_data_processing_0_1_3_1, &&arm_data_processing_0_1_3_2, &&arm_data_processing_0_1_3_3, &&arm_data_processing_0_1_3_4, &&arm_data_processing_0_1_3_5, &&arm_data_processing_0_1_3_6, &&arm_data_processing_0_1_3_7, &&arm_data_processing_0_1_3_0, &&arm_data_processing_0_1_3_1, &&arm_data_processing_0_1_3_2, &&arm_data_processing_0_1_3_3, &&arm_data_processing_0_1_3_4, &&arm_data_processing_0_1_3_5, &&arm_data_processing_0_1_3_6, &&arm_data_processing_0_1_3_7, &&arm_data_processing_1_1_3_0, &&arm_data_processing_1_1_3_1, &&arm_data_processing_1_1_3_2, &&arm_data_processing_1_1_3_3, &&arm_data_processing_1_1_3_4, &&arm_data_processing_1_1_3_5, &&arm_data_processing_1_1_3_6, &&arm_data_processing_1_1_3_7, &&arm_data_processing_1_1_3_0, &&arm_data_processing_1_1_3_1, &&arm_data_processing_1_1_3_2, &&arm_data_processing_1_1_3_3, &&arm_data_processing_1_1_3_4, &&arm_data_processing_1_1_3_5, &&arm_data_processing_1_1_3_6, &&arm_data_processing_1_1_3_7, &&arm_data_processing_0_1_4_0, &&arm_data_processing_0_1_4_1, &&arm_data_processing_0_1_4_2, &&arm_data_processing_0_1_4_3, &&arm_data_processing_0_1_4_4, &&arm_data_processing_0_1_4_5, &&arm_data_processing_0_1_4_6, &&arm_data_processing_0_1_4_7, &&arm_data_processing_0_1_4_0, &&arm_data_processing_0_1_4_1, &&arm_data_processing_0_1_4_2, &&arm_data_processing_0_1_4_3, &&arm_data_processing_0_1_4_4, &&arm_data_processing_0_1_4_5, &&arm_data_processing_0_1_4_6, &&arm_data_processing_0_1_4_7, &&arm_data_processing_1_1_4_0, &&arm_data_processing_1_1_4_1, &&arm_data_processing_1_1_4_2, &&arm_data_processing_1_1_4_3, &&arm_data_processing_1_1_4_4, &&arm_data_processing_1_1_4_5, &&arm_data_processing_1_1_4_6, &&arm_data_processing_1_1_4_7, &&arm_data_processing_1_1_4_0, &&arm_data_processing_1_1_4_1, &&arm_data_processing_1_1_4_2, &&arm_data_processing_1_1_4_3, &&arm_data_processing_1_1_4_4, &&arm_data_processing_1_1_4_5, &&arm_data_processing_1_1_4_6, &&arm_data_processing_1_1_4_7, &&arm_data_processing_0_1_5_0, &&arm_data_processing_0_1_5_1, &&arm_data_processing_0_1_5_2, &&arm_data_processing_0_1_5_3, &&arm_data_processing_0_1_5_4, &&arm_data_processing_0_1_5_5, &&arm_data_processing_0_1_5_6, &&arm_data_processing_0_1_5_7, &&arm_data_processing_0_1_5_0, &&arm_data_processing_0_1_5_1, &&arm_data_processing_0_1_5_2, &&arm_data_processing_0_1_5_3, &&arm_data_processing_0_1_5_4, &&arm_data_processing_0_1_5_5, &&arm_data_processing_0_1_5_6, &&arm_data_processing_0_1_5_7, &&arm_data_processing_1_1_5_0, &&arm_data_processing_1_1_5_1, &&arm_data_processing_1_1_5_2, &&arm_data_processing_1_1_5_3, &&arm_data_processing_1_1_5_4, &&arm_data_processing_1_1_5_5, &&arm_data_processing_1_1_5_6, &&arm_data_processing_1_1_5_7, &&arm_data_processing_1_1_5_0, &&arm_data_processing_1_1_5_1, &&arm_data_processing_1_1_5_2, &&arm_data_processing_1_1_5_3, &&arm_data_processing_1_1_5_4, &&arm_data_processing_1_1_5_5, &&arm_data_processing_1_1_5_6, &&arm_data_processing_1_1_5_7, &&arm_data_processing_0_1_6_0, &&arm_data_processing_0_1_6_1, &&arm_data_processing_0_1_6_2, &&arm_data_processing_0_1_6_3, &&arm_data_processing_0_1_6_4, &&arm_data_processing_0_1_6_5, &&arm_data_processing_0_1_6_6, &&arm_data_processing_0_1_6_7, &&arm_data_processing_0_1_6_0, &&arm_data_processing_0_1_6_1, &&arm_data_processing_0_1_6_2, &&arm_data_processing_0_1_6_3, &&arm_data_processing_0_1_6_4, &&arm_data_processing_0_1_6_5, &&arm_data_processing_0_1_6_6, &&arm_data_processing_0_1_6_7, &&arm_data_processing_1_1_6_0, &&arm_data_processing_1_1_6_1, &&arm_data_processing_1_1_6_2, &&arm_data_processing_1_1_6_3, &&arm_data_processing_1_1_6_4, &&arm_data_processing_1_1_6_5, &&arm_data_processing_1_1_6_6, &&arm_data_processing_1_1_6_7, &&arm_data_processing_1_1_6_0, &&arm_data_processing_1_1_6_1, &&arm_data_processing_1_1_6_2, &&arm_data_processing_1_1_6_3, &&arm_data_processing_1_1_6_4, &&arm_data_processing_1_1_6_5, &&arm_data_processing_1_1_6_6, &&arm_data_processing_1_1_6_7, &&arm_data_processing_0_1_7_0, &&arm_data_processing_0_1_7_1, &&arm_data_processing_0_1_7_2, &&arm_data_processing_0_1_7_3, &&arm_data_processing_0_1_7_4, &&arm_data_processing_0_1_7_5, &&arm_data_processing_0_1_7_6, &&arm_data_processing_0_1_7_7, &&arm_data_processing_0_1_7_0, &&arm_data_processing_0_1_7_1, &&arm_data_processing_0_1_7_2, &&arm_data_processing_0_1_7_3, &&arm_data_processing_0_1_7_4, &&arm_data_processing_0_1_7_5, &&arm_data_processing_0_1_7_6, &&arm_data_processing_0_1_7_7, &&arm_data_processing_1_1_7_0, &&arm_data_processing_1_1_7_1, &&arm_data_processing_1_1_7_2, &&arm_data_processing_1_1_7_3, &&arm_data_processing_1_1_7_4, &&arm_data_processing_1_1_7_5, &&arm_data_processing_1_1_7_6, &&arm_data_processing_1_1_7_7, &&arm_data_processing_1_1_7_0, &&arm_data_processing_1_1_7_1, &&arm_data_processing_1_1_7_2, &&arm_data_processing_1_1_7_3, &&arm_data_processing_1_1_7_4, &&arm_data_processing_1_1_7_5, &&arm_data_processing_1_1_7_6, &&arm_data_processing_1_1_7_7, &&arm_data_processing_0_1_8_0, &&arm_data_processing_0_1_8_1, &&arm_data_processing_0_1_8_2, &&arm_data_processing_0_1_8_3, &&arm_data_processing_0_1_8_4, &&arm_data_processing_0_1_8_5, &&arm_data_processing_0_1_8_6, &&arm_data_processing_0_1_8_7, &&arm_data_processing_0_1_8_0, &&arm_data_processing_0_1_8_1, &&arm_data_processing_0_1_8_2, &&arm_data_processing_0_1_8_3, &&arm_data_processing_0_1_8_4, &&arm_data_processing_0_1_8_5, &&arm_data_processing_0_1_8_6, &&arm_data_processing_0_1_8_7, &&arm_data_processing_1_1_8_0, &&arm_data_processing_1_1_8_1, &&arm_data_processing_1_1_8_2, &&arm_data_processing_1_1_8_3, &&arm_data_processing_1_1_8_4, &&arm_data_processing_1_1_8_5, &&arm_data_processing_1_1_8_6, &&arm_data_processing_1_1_8_7, &&arm_data_processing_1_1_8_0, &&arm_data_processing_1_1_8_1, &&arm_data_processing_1_1_8_2, &&arm_data_processing_1_1_8_3, &&arm_data_processing_1_1_8_4, &&arm_data_processing_1_1_8_5, &&arm_data_processing_1_1_8_6, &&arm_data_processing_1_1_8_7, &&arm_msr_0_1, &&arm_msr_0_1, &&arm_msr_0_1, &&arm_msr_0_1, &&arm_msr_0_1, &&arm_msr_0_1, &&arm_msr_0_1, &&arm_msr_0_1, &&arm_msr_0_1, &&arm_msr_0_1, &&arm_msr_0_1, &&arm_msr_0_1, &&arm_msr_0_1, &&arm_msr_0_1, &&arm_msr_0_1, &&arm_msr_0_1, &&arm_data_processing_1_1_9_0, &&arm_data_processing_1_1_9_1, &&arm_data_processing_1_1_9_2, &&arm_data_processing_1_1_9_3, &&arm_data_processing_1_1_9_4, &&arm_data_processing_1_1_9_5, &&arm_data_processing_1_1_9_6, &&arm_data_processing_1_1_9_7, &&arm_data_processing_1_1_9_0, &&arm_data_processing_1_1_9_1, &&arm_data_processing_1_1_9_2, &&arm_data_processing_1_1_9_3, &&arm_data_processing_1_1_9_4, &&arm_data_processing_1_1_9_5, &&arm_data_processing_1_1_9_6, &&arm_data_processing_1_1_9_7, &&arm_data_processing_0_1_A_0, &&arm_data_processing_0_1_A_1, &&arm_data_processing_0_1_A_2, &&arm_data_processing_0_1_A_3, &&arm_data_processing_0_1_A_4, &&arm_data_processing_0_1_A_5, &&arm_data_processing_0_1_A_6, &&arm_data_processing_0_1_A_7, &&arm_data_processing_0_1_A_0, &&arm_data_processing_0_1_A_1, &&arm_data_processing_0_1_A_2, &&arm_data_processing_0_1_A_3, &&arm_data_processing_0_1_A_4, &&arm_data_processing_0_1_A_5, &&arm_data_processing_0_1_A_6, &&arm_data_processing_0_1_A_7, &&arm_data_processing_1_1_A_0, &&arm_data_processing_1_1_A_1, &&arm_data_processing_1_1_A_2, &&arm_data_processing_1_1_A_3, &&arm_data_processing_1_1_A_4, &&arm_data_processing_1_1_A_5, &&arm_data_processing_1_1_A_6, &&arm_data_processing_1_1_A_7, &&arm_data_processing_1_1_A_0, &&arm_data_processing_1_1_A_1, &&arm_data_processing_1_1_A_2, &&arm_data_processing_1_1_A_3, &&arm_data_processing_1_1_A_4, &&arm_data_processing_1_1_A_5, &&arm_data_processing_1_1_A_6, &&arm_data_processing_1_1_A_7, &&arm_msr_1_1, &&arm_msr_1_1, &&arm_msr_1_1, &&arm_msr_1_1, &&arm_msr_1_1, &&arm_msr_1_1, &&arm_msr_1_1, &&arm_msr_1_1, &&arm_msr_1_1, &&arm_msr_1_1, &&arm_msr_1_1, &&arm_msr_1_1, &&arm_msr_1_1, &&arm_msr_1_1, &&arm_msr_1_1, &&arm_msr_1_1, &&arm_data_processing_1_1_B_0, &&arm_data_processing_1_1_B_1, &&arm_data_processing_1_1_B_2, &&arm_data_processing_1_1_B_3, &&arm_data_processing_1_1_B_4, &&arm_data_processing_1_1_B_5, &&arm_data_processing_1_1_B_6, &&arm_data_processing_1_1_B_7, &&arm_data_processing_1_1_B_0, &&arm_data_processing_1_1_B_1, &&arm_data_processing_1_1_B_2, &&arm_data_processing_1_1_B_3, &&arm_data_processing_1_1_B_4, &&arm_data_processing_1_1_B_5, &&arm_data_processing_1_1_B_6, &&arm_data_processing_1_1_B_7, &&arm_data_processing_0_1_C_0, &&arm_data_processing_0_1_C_1, &&arm_data_processing_0_1_C_2, &&arm_data_processing_0_1_C_3, &&arm_data_processing_0_1_C_4, &&arm_data_processing_0_1_C_5, &&arm_data_processing_0_1_C_6, &&arm_data_processing_0_1_C_7, &&arm_data_processing_0_1_C_0, &&arm_data_processing_0_1_C_1, &&arm_data_processing_0_1_C_2, &&arm_data_processing_0_1_C_3, &&arm_data_processing_0_1_C_4, &&arm_data_processing_0_1_C_5, &&arm_data_processing_0_1_C_6, &&arm_data_processing_0_1_C_7, &&arm_data_processing_1_1_C_0, &&arm_data_processing_1_1_C_1, &&arm_data_processing_1_1_C_2, &&arm_data_processing_1_1_C_3, &&arm_data_processing_1_1_C_4, &&arm_data_processing_1_1_C_5, &&arm_data_processing_1_1_C_6, &&arm_data_processing_1_1_C_7, &&arm_data_processing_1_1_C_0, &&arm_data_processing_1_1_C_1, &&arm_data_processing_1_1_C_2, &&arm_data_processing_1_1_C_3, &&arm_data_processing_1_1_C_4, &&arm_data_processing_1_1_C_5, &&arm_data_processing_1_1_C_6, &&arm_data_processing_1_1_C_7, &&arm_data_processing_0_1_D_0, &&arm_data_processing_0_1_D_1, &&arm_data_processing_0_1_D_2, &&arm_data_processing_0_1_D_3, &&arm_data_processing_0_1_D_4, &&arm_data_processing_0_1_D_5, &&arm_data_processing_0_1_D_6, &&arm_data_processing_0_1_D_7, &&arm_data_processing_0_1_D_0, &&arm_data_processing_0_1_D_1, &&arm_data_processing_0_1_D_2, &&arm_data_processing_0_1_D_3, &&arm_data_processing_0_1_D_4, &&arm_data_processing_0_1_D_5, &&arm_data_processing_0_1_D_6, &&arm_data_processing_0_1_D_7, &&arm_data_processing_1_1_D_0, &&arm_data_processing_1_1_D_1, &&arm_data_processing_1_1_D_2, &&arm_data_processing_1_1_D_3, &&arm_data_processing_1_1_D_4, &&arm_data_processing_1_1_D_5, &&arm_data_processing_1_1_D_6, &&arm_data_processing_1_1_D_7, &&arm_data_processing_1_1_D_0, &&arm_data_processing_1_1_D_1, &&arm_data_processing_1_1_D_2, &&arm_data_processing_1_1_D_3, &&arm_data_processing_1_1_D_4, &&arm_data_processing_1_1_D_5, &&arm_data_processing_1_1_D_6, &&arm_data_processing_1_1_D_7, &&arm_data_processing_0_1_E_0, &&arm_data_processing_0_1_E_1, &&arm_data_processing_0_1_E_2, &&arm_data_processing_0_1_E_3, &&arm_data_processing_0_1_E_4, &&arm_data_processing_0_1_E_5, &&arm_data_processing_0_1_E_6, &&arm_data_processing_0_1_E_7, &&arm_data_processing_0_1_E_0, &&arm_data_processing_0_1_E_1, &&arm_data_processing_0_1_E_2, &&arm_data_processing_0_1_E_3, &&arm_data_processing_0_1_E_4, &&arm_data_processing_0_1_E_5, &&arm_data_processing_0_1_E_6, &&arm_data_processing_0_1_E_7, &&arm_data_processing_1_1_E_0, &&arm_data_processing_1_1_E_1, &&arm_data_processing_1_1_E_2, &&arm_data_processing_1_1_E_3, &&arm_data_processing_1_1_E_4, &&arm_data_processing_1_1_E_5, &&arm_data_processing_1_1_E_6, &&arm_data_processing_1_1_E_7, &&arm_data_processing_1_1_E_0, &&arm_data_processing_1_1_E_1, &&arm_data_processing_1_1_E_2, &&arm_data_processing_1_1_E_3, &&arm_data_processing_1_1_E_4, &&arm_data_processing_1_1_E_5, &&arm_data_processing_1_1_E_6, &&arm_data_processing_1_1_E_7, &&arm_data_processing_0_1_F_0, &&arm_data_processing_0_1_F_1, &&arm_data_processing_0_1_F_2, &&arm_data_processing_0_1_F_3, &&arm_data_processing_0_1_F_4, &&arm_data_processing_0_1_F_5, &&arm_data_processing_0_1_F_6, &&arm_data_processing_0_1_F_7, &&arm_data_processing_0_1_F_0, &&arm_data_processing_0_1_F_1, &&arm_data_processing_0_1_F_2, &&arm_data_processing_0_1_F_3, &&arm_data_processing_0_1_F_4, &&arm_data_processing_0_1_F_5, &&arm_data_processing_0_1_F_6, &&arm_data_processing_0_1_F_7, &&arm_data_processing_1_1_F_0, &&arm_data_processing_1_1_F_1, &&arm_data_processing_1_1_F_2, &&arm_data_processing_1_1_F_3, &&arm_data_processing_1_1_F_4, &&arm_data_processing_1_1_F_5, &&arm_data_processing_1_1_F_6, &&arm_data_processing_1_1_F_7, &&arm_data_processing_1_1_F_0, &&arm_data_processing_1_1_F_1, &&arm_data_processing_1_1_F_2, &&arm_data_processing_1_1_F_3, &&arm_data_processing_1_1_F_4, &&arm_data_processing_1_1_F_5, &&arm_data_processing_1_1_F_6, &&arm_data_processing_1_1_F_7, &&arm_single_data_transfer_0_0_0_0_0_0_0, &&arm_single_data_transfer_0_0_0_0_0_0_1, &&arm_single_data_transfer_0_0_0_0_0_0_2, &&arm_single_data_transfer_0_0_0_0_0_0_3, &&arm_single_data_transfer_0_0_0_0_0_0_4, &&arm_single_data_transfer_0_0_0_0_0_0_5, &&arm_single_data_transfer_0_0_0_0_0_0_6, &&arm_single_data_transfer_0_0_0_0_0_0_7, &&arm_single_data_transfer_0_0_0_0_0_0_0, &&arm_single_data_transfer_0_0_0_0_0_0_1, &&arm_single_data_transfer_0_0_0_0_0_0_2, &&arm_single_data_transfer_0_0_0_0_0_0_3, &&arm_single_data_transfer_0_0_0_0_0_0_4, &&arm_single_data_transfer_0_0_0_0_0_0_5, &&arm_single_data_transfer_0_0_0_0_0_0_6, &&arm_single_data_transfer_0_0_0_0_0_0_7, &&arm_single_data_transfer_0_0_0_0_0_1_0, &&arm_single_data_transfer_0_0_0_0_0_1_1, &&arm_single_data_transfer_0_0_0_0_0_1_2, &&arm_single_data_transfer_0_0_0_0_0_1_3, &&arm_single_data_transfer_0_0_0_0_0_1_4, &&arm_single_data_transfer_0_0_0_0_0_1_5, &&arm_single_data_transfer_0_0_0_0_0_1_6, &&arm_single_data_transfer_0_0_0_0_0_1_7, &&arm_single_data_transfer_0_0_0_0_0_1_0, &&arm_single_data_transfer_0_0_0_0_0_1_1, &&arm_single_data_transfer_0_0_0_0_0_1_2, &&arm_single_data_transfer_0_0_0_0_0_1_3, &&arm_single_data_transfer_0_0_0_0_0_1_4, &&arm_single_data_transfer_0_0_0_0_0_1_5, &&arm_single_data_transfer_0_0_0_0_0_1_6, &&arm_single_data_transfer_0_0_0_0_0_1_7, &&arm_single_data_transfer_0_0_0_0_1_0_0, &&arm_single_data_transfer_0_0_0_0_1_0_1, &&arm_single_data_transfer_0_0_0_0_1_0_2, &&arm_single_data_transfer_0_0_0_0_1_0_3, &&arm_single_data_transfer_0_0_0_0_1_0_4, &&arm_single_data_transfer_0_0_0_0_1_0_5, &&arm_single_data_transfer_0_0_0_0_1_0_6, &&arm_single_data_transfer_0_0_0_0_1_0_7, &&arm_single_data_transfer_0_0_0_0_1_0_0, &&arm_single_data_transfer_0_0_0_0_1_0_1, &&arm_single_data_transfer_0_0_0_0_1_0_2, &&arm_single_data_transfer_0_0_0_0_1_0_3, &&arm_single_data_transfer_0_0_0_0_1_0_4, &&arm_single_data_transfer_0_0_0_0_1_0_5, &&arm_single_data_transfer_0_0_0_0_1_0_6, &&arm_single_data_transfer_0_0_0_0_1_0_7, &&arm_single_data_transfer_0_0_0_0_1_1_0, &&arm_single_data_transfer_0_0_0_0_1_1_1, &&arm_single_data_transfer_0_0_0_0_1_1_2, &&arm_single_data_transfer_0_0_0_0_1_1_3, &&arm_single_data_transfer_0_0_0_0_1_1_4, &&arm_single_data_transfer_0_0_0_0_1_1_5, &&arm_single_data_transfer_0_0_0_0_1_1_6, &&arm_single_data_transfer_0_0_0_0_1_1_7, &&arm_single_data_transfer_0_0_0_0_1_1_0, &&arm_single_data_transfer_0_0_0_0_1_1_1, &&arm_single_data_transfer_0_0_0_0_1_1_2, &&arm_single_data_transfer_0_0_0_0_1_1_3, &&arm_single_data_transfer_0_0_0_0_1_1_4, &&arm_single_data_transfer_0_0_0_0_1_1_5, &&arm_single_data_transfer_0_0_0_0_1_1_6, &&arm_single_data_transfer_0_0_0_0_1_1_7, &&arm_single_data_transfer_0_0_0_1_0_0_0, &&arm_single_data_transfer_0_0_0_1_0_0_1, &&arm_single_data_transfer_0_0_0_1_0_0_2, &&arm_single_data_transfer_0_0_0_1_0_0_3, &&arm_single_data_transfer_0_0_0_1_0_0_4, &&arm_single_data_transfer_0_0_0_1_0_0_5, &&arm_single_data_transfer_0_0_0_1_0_0_6, &&arm_single_data_transfer_0_0_0_1_0_0_7, &&arm_single_data_transfer_0_0_0_1_0_0_0, &&arm_single_data_transfer_0_0_0_1_0_0_1, &&arm_single_data_transfer_0_0_0_1_0_0_2, &&arm_single_data_transfer_0_0_0_1_0_0_3, &&arm_single_data_transfer_0_0_0_1_0_0_4, &&arm_single_data_transfer_0_0_0_1_0_0_5, &&arm_single_data_transfer_0_0_0_1_0_0_6, &&arm_single_data_transfer_0_0_0_1_0_0_7, &&arm_single_data_transfer_0_0_0_1_0_1_0, &&arm_single_data_transfer_0_0_0_1_0_1_1, &&arm_single_data_transfer_0_0_0_1_0_1_2, &&arm_single_data_transfer_0_0_0_1_0_1_3, &&arm_single_data_transfer_0_0_0_1_0_1_4, &&arm_single_data_transfer_0_0_0_1_0_1_5, &&arm_single_data_transfer_0_0_0_1_0_1_6, &&arm_single_data_transfer_0_0_0_1_0_1_7, &&arm_single_data_transfer_0_0_0_1_0_1_0, &&arm_single_data_transfer_0_0_0_1_0_1_1, &&arm_single_data_transfer_0_0_0_1_0_1_2, &&arm_single_data_transfer_0_0_0_1_0_1_3, &&arm_single_data_transfer_0_0_0_1_0_1_4, &&arm_single_data_transfer_0_0_0_1_0_1_5, &&arm_single_data_transfer_0_0_0_1_0_1_6, &&arm_single_data_transfer_0_0_0_1_0_1_7, &&arm_single_data_transfer_0_0_0_1_1_0_0, &&arm_single_data_transfer_0_0_0_1_1_0_1, &&arm_single_data_transfer_0_0_0_1_1_0_2, &&arm_single_data_transfer_0_0_0_1_1_0_3, &&arm_single_data_transfer_0_0_0_1_1_0_4, &&arm_single_data_transfer_0_0_0_1_1_0_5, &&arm_single_data_transfer_0_0_0_1_1_0_6, &&arm_single_data_transfer_0_0_0_1_1_0_7, &&arm_single_data_transfer_0_0_0_1_1_0_0, &&arm_single_data_transfer_0_0_0_1_1_0_1, &&arm_single_data_transfer_0_0_0_1_1_0_2, &&arm_single_data_transfer_0_0_0_1_1_0_3, &&arm_single_data_transfer_0_0_0_1_1_0_4, &&arm_single_data_transfer_0_0_0_1_1_0_5, &&arm_single_data_transfer_0_0_0_1_1_0_6, &&arm_single_data_transfer_0_0_0_1_1_0_7, &&arm_single_data_transfer_0_0_0_1_1_1_0, &&arm_single_data_transfer_0_0_0_1_1_1_1, &&arm_single_data_transfer_0_0_0_1_1_1_2, &&arm_single_data_transfer_0_0_0_1_1_1_3, &&arm_single_data_transfer_0_0_0_1_1_1_4, &&arm_single_data_transfer_0_0_0_1_1_1_5, &&arm_single_data_transfer_0_0_0_1_1_1_6, &&arm_single_data_transfer_0_0_0_1_1_1_7, &&arm_single_data_transfer_0_0_0_1_1_1_0, &&arm_single_data_transfer_0_0_0_1_1_1_1, &&arm_single_data_transfer_0_0_0_1_1_1_2, &&arm_single_data_transfer_0_0_0_1_1_1_3, &&arm_single_data_transfer_0_0_0_1_1_1_4, &&arm_single_data_transfer_0_0_0_1_1_1_5, &&arm_single_data_transfer_0_0_0_1_1_1_6, &&arm_single_data_transfer_0_0_0_1_1_1_7, &&arm_single_data_transfer_0_0_1_0_0_0_0, &&arm_single_data_transfer_0_0_1_0_0_0_1, &&arm_single_data_transfer_0_0_1_0_0_0_2, &&arm_single_data_transfer_0_0_1_0_0_0_3, &&arm_single_data_transfer_0_0_1_0_0_0_4, &&arm_single_data_transfer_0_0_1_0_0_0_5, &&arm_single_data_transfer_0_0_1_0_0_0_6, &&arm_single_data_transfer_0_0_1_0_0_0_7, &&arm_single_data_transfer_0_0_1_0_0_0_0, &&arm_single_data_transfer_0_0_1_0_0_0_1, &&arm_single_data_transfer_0_0_1_0_0_0_2, &&arm_single_data_transfer_0_0_1_0_0_0_3, &&arm_single_data_transfer_0_0_1_0_0_0_4, &&arm_single_data_transfer_0_0_1_0_0_0_5, &&arm_single_data_transfer_0_0_1_0_0_0_6, &&arm_single_data_transfer_0_0_1_0_0_0_7, &&arm_single_data_transfer_0_0_1_0_0_1_0, &&arm_single_data_transfer_0_0_1_0_0_1_1, &&arm_single_data_transfer_0_0_1_0_0_1_2, &&arm_single_data_transfer_0_0_1_0_0_1_3, &&arm_single_data_transfer_0_0_1_0_0_1_4, &&arm_single_data_transfer_0_0_1_0_0_1_5, &&arm_single_data_transfer_0_0_1_0_0_1_6, &&arm_single_data_transfer_0_0_1_0_0_1_7, &&arm_single_data_transfer_0_0_1_0_0_1_0, &&arm_single_data_transfer_0_0_1_0_0_1_1, &&arm_single_data_transfer_0_0_1_0_0_1_2, &&arm_single_data_transfer_0_0_1_0_0_1_3, &&arm_single_data_transfer_0_0_1_0_0_1_4, &&arm_single_data_transfer_0_0_1_0_0_1_5, &&arm_single_data_transfer_0_0_1_0_0_1_6, &&arm_single_data_transfer_0_0_1_0_0_1_7, &&arm_single_data_transfer_0_0_1_0_1_0_0, &&arm_single_data_transfer_0_0_1_0_1_0_1, &&arm_single_data_transfer_0_0_1_0_1_0_2, &&arm_single_data_transfer_0_0_1_0_1_0_3, &&arm_single_data_transfer_0_0_1_0_1_0_4, &&arm_single_data_transfer_0_0_1_0_1_0_5, &&arm_single_data_transfer_0_0_1_0_1_0_6, &&arm_single_data_transfer_0_0_1_0_1_0_7, &&arm_single_data_transfer_0_0_1_0_1_0_0, &&arm_single_data_transfer_0_0_1_0_1_0_1, &&arm_single_data_transfer_0_0_1_0_1_0_2, &&arm_single_data_transfer_0_0_1_0_1_0_3, &&arm_single_data_transfer_0_0_1_0_1_0_4, &&arm_single_data_transfer_0_0_1_0_1_0_5, &&arm_single_data_transfer_0_0_1_0_1_0_6, &&arm_single_data_transfer_0_0_1_0_1_0_7, &&arm_single_data_transfer_0_0_1_0_1_1_0, &&arm_single_data_transfer_0_0_1_0_1_1_1, &&arm_single_data_transfer_0_0_1_0_1_1_2, &&arm_single_data_transfer_0_0_1_0_1_1_3, &&arm_single_data_transfer_0_0_1_0_1_1_4, &&arm_single_data_transfer_0_0_1_0_1_1_5, &&arm_single_data_transfer_0_0_1_0_1_1_6, &&arm_single_data_transfer_0_0_1_0_1_1_7, &&arm_single_data_transfer_0_0_1_0_1_1_0, &&arm_single_data_transfer_0_0_1_0_1_1_1, &&arm_single_data_transfer_0_0_1_0_1_1_2, &&arm_single_data_transfer_0_0_1_0_1_1_3, &&arm_single_data_transfer_0_0_1_0_1_1_4, &&arm_single_data_transfer_0_0_1_0_1_1_5, &&arm_single_data_transfer_0_0_1_0_1_1_6, &&arm_single_data_transfer_0_0_1_0_1_1_7, &&arm_single_data_transfer_0_0_1_1_0_0_0, &&arm_single_data_transfer_0_0_1_1_0_0_1, &&arm_single_data_transfer_0_0_1_1_0_0_2, &&arm_single_data_transfer_0_0_1_1_0_0_3, &&arm_single_data_transfer_0_0_1_1_0_0_4, &&arm_single_data_transfer_0_0_1_1_0_0_5, &&arm_single_data_transfer_0_0_1_1_0_0_6, &&arm_single_data_transfer_0_0_1_1_0_0_7, &&arm_single_data_transfer_0_0_1_1_0_0_0, &&arm_single_data_transfer_0_0_1_1_0_0_1, &&arm_single_data_transfer_0_0_1_1_0_0_2, &&arm_single_data_transfer_0_0_1_1_0_0_3, &&arm_single_data_transfer_0_0_1_1_0_0_4, &&arm_single_data_transfer_0_0_1_1_0_0_5, &&arm_single_data_transfer_0_0_1_1_0_0_6, &&arm_single_data_transfer_0_0_1_1_0_0_7, &&arm_single_data_transfer_0_0_1_1_0_1_0, &&arm_single_data_transfer_0_0_1_1_0_1_1, &&arm_single_data_transfer_0_0_1_1_0_1_2, &&arm_single_data_transfer_0_0_1_1_0_1_3, &&arm_single_data_transfer_0_0_1_1_0_1_4, &&arm_single_data_transfer_0_0_1_1_0_1_5, &&arm_single_data_transfer_0_0_1_1_0_1_6, &&arm_single_data_transfer_0_0_1_1_0_1_7, &&arm_single_data_transfer_0_0_1_1_0_1_0, &&arm_single_data_transfer_0_0_1_1_0_1_1, &&arm_single_data_transfer_0_0_1_1_0_1_2, &&arm_single_data_transfer_0_0_1_1_0_1_3, &&arm_single_data_transfer_0_0_1_1_0_1_4, &&arm_single_data_transfer_0_0_1_1_0_1_5, &&arm_single_data_transfer_0_0_1_1_0_1_6, &&arm_single_data_transfer_0_0_1_1_0_1_7, &&arm_single_data_transfer_0_0_1_1_1_0_0, &&arm_single_data_transfer_0_0_1_1_1_0_1, &&arm_single_data_transfer_0_0_1_1_1_0_2, &&arm_single_data_transfer_0_0_1_1_1_0_3, &&arm_single_data_transfer_0_0_1_1_1_0_4, &&arm_single_data_transfer_0_0_1_1_1_0_5, &&arm_single_data_transfer_0_0_1_1_1_0_6, &&arm_single_data_transfer_0_0_1_1_1_0_7, &&arm_single_data_transfer_0_0_1_1_1_0_0, &&arm_single_data_transfer_0_0_1_1_1_0_1, &&arm_single_data_transfer_0_0_1_1_1_0_2, &&arm_single_data_transfer_0_0_1_1_1_0_3, &&arm_single_data_transfer_0_0_1_1_1_0_4, &&arm_single_data_transfer_0_0_1_1_1_0_5, &&arm_single_data_transfer_0_0_1_1_1_0_6, &&arm_single_data_transfer_0_0_1_1_1_0_7, &&arm_single_data_transfer_0_0_1_1_1_1_0, &&arm_single_data_transfer_0_0_1_1_1_1_1, &&arm_single_data_transfer_0_0_1_1_1_1_2, &&arm_single_data_transfer_0_0_1_1_1_1_3, &&arm_single_data_transfer_0_0_1_1_1_1_4, &&arm_single_data_transfer_0_0_1_1_1_1_5, &&arm_single_data_transfer_0_0_1_1_1_1_6, &&arm_single_data_transfer_0_0_1_1_1_1_7, &&arm_single_data_transfer_0_0_1_1_1_1_0, &&arm_single_data_transfer_0_0_1_1_1_1_1, &&arm_single_data_transfer_0_0_1_1_1_1_2, &&arm_single_data_transfer_0_0_1_1_1_1_3, &&arm_single_data_transfer_0_0_1_1_1_1_4, &&arm_single_data_transfer_0_0_1_1_1_1_5, &&arm_single_data_transfer_0_0_1_1_1_1_6, &&arm_single_data_transfer_0_0_1_1_1_1_7, &&arm_single_data_transfer_0_1_0_0_0_0_0, &&arm_single_data_transfer_0_1_0_0_0_0_1, &&arm_single_data_transfer_0_1_0_0_0_0_2, &&arm_single_data_transfer_0_1_0_0_0_0_3, &&arm_single_data_transfer_0_1_0_0_0_0_4, &&arm_single_data_transfer_0_1_0_0_0_0_5, &&arm_single_data_transfer_0_1_0_0_0_0_6, &&arm_single_data_transfer_0_1_0_0_0_0_7, &&arm_single_data_transfer_0_1_0_0_0_0_0, &&arm_single_data_transfer_0_1_0_0_0_0_1, &&arm_single_data_transfer_0_1_0_0_0_0_2, &&arm_single_data_transfer_0_1_0_0_0_0_3, &&arm_single_data_transfer_0_1_0_0_0_0_4, &&arm_single_data_transfer_0_1_0_0_0_0_5, &&arm_single_data_transfer_0_1_0_0_0_0_6, &&arm_single_data_transfer_0_1_0_0_0_0_7, &&arm_single_data_transfer_0_1_0_0_0_1_0, &&arm_single_data_transfer_0_1_0_0_0_1_1, &&arm_single_data_transfer_0_1_0_0_0_1_2, &&arm_single_data_transfer_0_1_0_0_0_1_3, &&arm_single_data_transfer_0_1_0_0_0_1_4, &&arm_single_data_transfer_0_1_0_0_0_1_5, &&arm_single_data_transfer_0_1_0_0_0_1_6, &&arm_single_data_transfer_0_1_0_0_0_1_7, &&arm_single_data_transfer_0_1_0_0_0_1_0, &&arm_single_data_transfer_0_1_0_0_0_1_1, &&arm_single_data_transfer_0_1_0_0_0_1_2, &&arm_single_data_transfer_0_1_0_0_0_1_3, &&arm_single_data_transfer_0_1_0_0_0_1_4, &&arm_single_data_transfer_0_1_0_0_0_1_5, &&arm_single_data_transfer_0_1_0_0_0_1_6, &&arm_single_data_transfer_0_1_0_0_0_1_7, &&arm_single_data_transfer_0_1_0_0_1_0_0, &&arm_single_data_transfer_0_1_0_0_1_0_1, &&arm_single_data_transfer_0_1_0_0_1_0_2, &&arm_single_data_transfer_0_1_0_0_1_0_3, &&arm_single_data_transfer_0_1_0_0_1_0_4, &&arm_single_data_transfer_0_1_0_0_1_0_5, &&arm_single_data_transfer_0_1_0_0_1_0_6, &&arm_single_data_transfer_0_1_0_0_1_0_7, &&arm_single_data_transfer_0_1_0_0_1_0_0, &&arm_single_data_transfer_0_1_0_0_1_0_1, &&arm_single_data_transfer_0_1_0_0_1_0_2, &&arm_single_data_transfer_0_1_0_0_1_0_3, &&arm_single_data_transfer_0_1_0_0_1_0_4, &&arm_single_data_transfer_0_1_0_0_1_0_5, &&arm_single_data_transfer_0_1_0_0_1_0_6, &&arm_single_data_transfer_0_1_0_0_1_0_7, &&arm_single_data_transfer_0_1_0_0_1_1_0, &&arm_single_data_transfer_0_1_0_0_1_1_1, &&arm_single_data_transfer_0_1_0_0_1_1_2, &&arm_single_data_transfer_0_1_0_0_1_1_3, &&arm_single_data_transfer_0_1_0_0_1_1_4, &&arm_single_data_transfer_0_1_0_0_1_1_5, &&arm_single_data_transfer_0_1_0_0_1_1_6, &&arm_single_data_transfer_0_1_0_0_1_1_7, &&arm_single_data_transfer_0_1_0_0_1_1_0, &&arm_single_data_transfer_0_1_0_0_1_1_1, &&arm_single_data_transfer_0_1_0_0_1_1_2, &&arm_single_data_transfer_0_1_0_0_1_1_3, &&arm_single_data_transfer_0_1_0_0_1_1_4, &&arm_single_data_transfer_0_1_0_0_1_1_5, &&arm_single_data_transfer_0_1_0_0_1_1_6, &&arm_single_data_transfer_0_1_0_0_1_1_7, &&arm_single_data_transfer_0_1_0_1_0_0_0, &&arm_single_data_transfer_0_1_0_1_0_0_1, &&arm_single_data_transfer_0_1_0_1_0_0_2, &&arm_single_data_transfer_0_1_0_1_0_0_3, &&arm_single_data_transfer_0_1_0_1_0_0_4, &&arm_single_data_transfer_0_1_0_1_0_0_5, &&arm_single_data_transfer_0_1_0_1_0_0_6, &&arm_single_data_transfer_0_1_0_1_0_0_7, &&arm_single_data_transfer_0_1_0_1_0_0_0, &&arm_single_data_transfer_0_1_0_1_0_0_1, &&arm_single_data_transfer_0_1_0_1_0_0_2, &&arm_single_data_transfer_0_1_0_1_0_0_3, &&arm_single_data_transfer_0_1_0_1_0_0_4, &&arm_single_data_transfer_0_1_0_1_0_0_5, &&arm_single_data_transfer_0_1_0_1_0_0_6, &&arm_single_data_transfer_0_1_0_1_0_0_7, &&arm_single_data_transfer_0_1_0_1_0_1_0, &&arm_single_data_transfer_0_1_0_1_0_1_1, &&arm_single_data_transfer_0_1_0_1_0_1_2, &&arm_single_data_transfer_0_1_0_1_0_1_3, &&arm_single_data_transfer_0_1_0_1_0_1_4, &&arm_single_data_transfer_0_1_0_1_0_1_5, &&arm_single_data_transfer_0_1_0_1_0_1_6, &&arm_single_data_transfer_0_1_0_1_0_1_7, &&arm_single_data_transfer_0_1_0_1_0_1_0, &&arm_single_data_transfer_0_1_0_1_0_1_1, &&arm_single_data_transfer_0_1_0_1_0_1_2, &&arm_single_data_transfer_0_1_0_1_0_1_3, &&arm_single_data_transfer_0_1_0_1_0_1_4, &&arm_single_data_transfer_0_1_0_1_0_1_5, &&arm_single_data_transfer_0_1_0_1_0_1_6, &&arm_single_data_transfer_0_1_0_1_0_1_7, &&arm_single_data_transfer_0_1_0_1_1_0_0, &&arm_single_data_transfer_0_1_0_1_1_0_1, &&arm_single_data_transfer_0_1_0_1_1_0_2, &&arm_single_data_transfer_0_1_0_1_1_0_3, &&arm_single_data_transfer_0_1_0_1_1_0_4, &&arm_single_data_transfer_0_1_0_1_1_0_5, &&arm_single_data_transfer_0_1_0_1_1_0_6, &&arm_single_data_transfer_0_1_0_1_1_0_7, &&arm_single_data_transfer_0_1_0_1_1_0_0, &&arm_single_data_transfer_0_1_0_1_1_0_1, &&arm_single_data_transfer_0_1_0_1_1_0_2, &&arm_single_data_transfer_0_1_0_1_1_0_3, &&arm_single_data_transfer_0_1_0_1_1_0_4, &&arm_single_data_transfer_0_1_0_1_1_0_5, &&arm_single_data_transfer_0_1_0_1_1_0_6, &&arm_single_data_transfer_0_1_0_1_1_0_7, &&arm_single_data_transfer_0_1_0_1_1_1_0, &&arm_single_data_transfer_0_1_0_1_1_1_1, &&arm_single_data_transfer_0_1_0_1_1_1_2, &&arm_single_data_transfer_0_1_0_1_1_1_3, &&arm_single_data_transfer_0_1_0_1_1_1_4, &&arm_single_data_transfer_0_1_0_1_1_1_5, &&arm_single_data_transfer_0_1_0_1_1_1_6, &&arm_single_data_transfer_0_1_0_1_1_1_7, &&arm_single_data_transfer_0_1_0_1_1_1_0, &&arm_single_data_transfer_0_1_0_1_1_1_1, &&arm_single_data_transfer_0_1_0_1_1_1_2, &&arm_single_data_transfer_0_1_0_1_1_1_3, &&arm_single_data_transfer_0_1_0_1_1_1_4, &&arm_single_data_transfer_0_1_0_1_1_1_5, &&arm_single_data_transfer_0_1_0_1_1_1_6, &&arm_single_data_transfer_0_1_0_1_1_1_7, &&arm_single_data_transfer_0_1_1_0_0_0_0, &&arm_single_data_transfer_0_1_1_0_0_0_1, &&arm_single_data_transfer_0_1_1_0_0_0_2, &&arm_single_data_transfer_0_1_1_0_0_0_3, &&arm_single_data_transfer_0_1_1_0_0_0_4, &&arm_single_data_transfer_0_1_1_0_0_0_5, &&arm_single_data_transfer_0_1_1_0_0_0_6, &&arm_single_data_transfer_0_1_1_0_0_0_7, &&arm_single_data_transfer_0_1_1_0_0_0_0, &&arm_single_data_transfer_0_1_1_0_0_0_1, &&arm_single_data_transfer_0_1_1_0_0_0_2, &&arm_single_data_transfer_0_1_1_0_0_0_3, &&arm_single_data_transfer_0_1_1_0_0_0_4, &&arm_single_data_transfer_0_1_1_0_0_0_5, &&arm_single_data_transfer_0_1_1_0_0_0_6, &&arm_single_data_transfer_0_1_1_0_0_0_7, &&arm_single_data_transfer_0_1_1_0_0_1_0, &&arm_single_data_transfer_0_1_1_0_0_1_1, &&arm_single_data_transfer_0_1_1_0_0_1_2, &&arm_single_data_transfer_0_1_1_0_0_1_3, &&arm_single_data_transfer_0_1_1_0_0_1_4, &&arm_single_data_transfer_0_1_1_0_0_1_5, &&arm_single_data_transfer_0_1_1_0_0_1_6, &&arm_single_data_transfer_0_1_1_0_0_1_7, &&arm_single_data_transfer_0_1_1_0_0_1_0, &&arm_single_data_transfer_0_1_1_0_0_1_1, &&arm_single_data_transfer_0_1_1_0_0_1_2, &&arm_single_data_transfer_0_1_1_0_0_1_3, &&arm_single_data_transfer_0_1_1_0_0_1_4, &&arm_single_data_transfer_0_1_1_0_0_1_5, &&arm_single_data_transfer_0_1_1_0_0_1_6, &&arm_single_data_transfer_0_1_1_0_0_1_7, &&arm_single_data_transfer_0_1_1_0_1_0_0, &&arm_single_data_transfer_0_1_1_0_1_0_1, &&arm_single_data_transfer_0_1_1_0_1_0_2, &&arm_single_data_transfer_0_1_1_0_1_0_3, &&arm_single_data_transfer_0_1_1_0_1_0_4, &&arm_single_data_transfer_0_1_1_0_1_0_5, &&arm_single_data_transfer_0_1_1_0_1_0_6, &&arm_single_data_transfer_0_1_1_0_1_0_7, &&arm_single_data_transfer_0_1_1_0_1_0_0, &&arm_single_data_transfer_0_1_1_0_1_0_1, &&arm_single_data_transfer_0_1_1_0_1_0_2, &&arm_single_data_transfer_0_1_1_0_1_0_3, &&arm_single_data_transfer_0_1_1_0_1_0_4, &&arm_single_data_transfer_0_1_1_0_1_0_5, &&arm_single_data_transfer_0_1_1_0_1_0_6, &&arm_single_data_transfer_0_1_1_0_1_0_7, &&arm_single_data_transfer_0_1_1_0_1_1_0, &&arm_single_data_transfer_0_1_1_0_1_1_1, &&arm_single_data_transfer_0_1_1_0_1_1_2, &&arm_single_data_transfer_0_1_1_0_1_1_3, &&arm_single_data_transfer_0_1_1_0_1_1_4, &&arm_single_data_transfer_0_1_1_0_1_1_5, &&arm_single_data_transfer_0_1_1_0_1_1_6, &&arm_single_data_transfer_0_1_1_0_1_1_7, &&arm_single_data_transfer_0_1_1_0_1_1_0, &&arm_single_data_transfer_0_1_1_0_1_1_1, &&arm_single_data_transfer_0_1_1_0_1_1_2, &&arm_single_data_transfer_0_1_1_0_1_1_3, &&arm_single_data_transfer_0_1_1_0_1_1_4, &&arm_single_data_transfer_0_1_1_0_1_1_5, &&arm_single_data_transfer_0_1_1_0_1_1_6, &&arm_single_data_transfer_0_1_1_0_1_1_7, &&arm_single_data_transfer_0_1_1_1_0_0_0, &&arm_single_data_transfer_0_1_1_1_0_0_1, &&arm_single_data_transfer_0_1_1_1_0_0_2, &&arm_single_data_transfer_0_1_1_1_0_0_3, &&arm_single_data_transfer_0_1_1_1_0_0_4, &&arm_single_data_transfer_0_1_1_1_0_0_5, &&arm_single_data_transfer_0_1_1_1_0_0_6, &&arm_single_data_transfer_0_1_1_1_0_0_7, &&arm_single_data_transfer_0_1_1_1_0_0_0, &&arm_single_data_transfer_0_1_1_1_0_0_1, &&arm_single_data_transfer_0_1_1_1_0_0_2, &&arm_single_data_transfer_0_1_1_1_0_0_3, &&arm_single_data_transfer_0_1_1_1_0_0_4, &&arm_single_data_transfer_0_1_1_1_0_0_5, &&arm_single_data_transfer_0_1_1_1_0_0_6, &&arm_single_data_transfer_0_1_1_1_0_0_7, &&arm_single_data_transfer_0_1_1_1_0_1_0, &&arm_single_data_transfer_0_1_1_1_0_1_1, &&arm_single_data_transfer_0_1_1_1_0_1_2, &&arm_single_data_transfer_0_1_1_1_0_1_3, &&arm_single_data_transfer_0_1_1_1_0_1_4, &&arm_single_data_transfer_0_1_1_1_0_1_5, &&arm_single_data_transfer_0_1_1_1_0_1_6, &&arm_single_data_transfer_0_1_1_1_0_1_7, &&arm_single_data_transfer_0_1_1_1_0_1_0, &&arm_single_data_transfer_0_1_1_1_0_1_1, &&arm_single_data_transfer_0_1_1_1_0_1_2, &&arm_single_data_transfer_0_1_1_1_0_1_3, &&arm_single_data_transfer_0_1_1_1_0_1_4, &&arm_single_data_transfer_0_1_1_1_0_1_5, &&arm_single_data_transfer_0_1_1_1_0_1_6, &&arm_single_data_transfer_0_1_1_1_0_1_7, &&arm_single_data_transfer_0_1_1_1_1_0_0, &&arm_single_data_transfer_0_1_1_1_1_0_1, &&arm_single_data_transfer_0_1_1_1_1_0_2, &&arm_single_data_transfer_0_1_1_1_1_0_3, &&arm_single_data_transfer_0_1_1_1_1_0_4, &&arm_single_data_transfer_0_1_1_1_1_0_5, &&arm_single_data_transfer_0_1_1_1_1_0_6, &&arm_single_data_transfer_0_1_1_1_1_0_7, &&arm_single_data_transfer_0_1_1_1_1_0_0, &&arm_single_data_transfer_0_1_1_1_1_0_1, &&arm_single_data_transfer_0_1_1_1_1_0_2, &&arm_single_data_transfer_0_1_1_1_1_0_3, &&arm_single_data_transfer_0_1_1_1_1_0_4, &&arm_single_data_transfer_0_1_1_1_1_0_5, &&arm_single_data_transfer_0_1_1_1_1_0_6, &&arm_single_data_transfer_0_1_1_1_1_0_7, &&arm_single_data_transfer_0_1_1_1_1_1_0, &&arm_single_data_transfer_0_1_1_1_1_1_1, &&arm_single_data_transfer_0_1_1_1_1_1_2, &&arm_single_data_transfer_0_1_1_1_1_1_3, &&arm_single_data_transfer_0_1_1_1_1_1_4, &&arm_single_data_transfer_0_1_1_1_1_1_5, &&arm_single_data_transfer_0_1_1_1_1_1_6, &&arm_single_data_transfer_0_1_1_1_1_1_7, &&arm_single_data_transfer_0_1_1_1_1_1_0, &&arm_single_data_transfer_0_1_1_1_1_1_1, &&arm_single_data_transfer_0_1_1_1_1_1_2, &&arm_single_data_transfer_0_1_1_1_1_1_3, &&arm_single_data_transfer_0_1_1_1_1_1_4, &&arm_single_data_transfer_0_1_1_1_1_1_5, &&arm_single_data_transfer_0_1_1_1_1_1_6, &&arm_single_data_transfer_0_1_1_1_1_1_7, &&arm_single_data_transfer_1_0_0_0_0_0_0, &&arm_single_data_transfer_1_0_0_0_0_0_1, &&arm_single_data_transfer_1_0_0_0_0_0_2, &&arm_single_data_transfer_1_0_0_0_0_0_3, &&arm_single_data_transfer_1_0_0_0_0_0_4, &&arm_single_data_transfer_1_0_0_0_0_0_5, &&arm_single_data_transfer_1_0_0_0_0_0_6, &&arm_single_data_transfer_1_0_0_0_0_0_7, &&arm_single_data_transfer_1_0_0_0_0_0_0, &&arm_single_data_transfer_1_0_0_0_0_0_1, &&arm_single_data_transfer_1_0_0_0_0_0_2, &&arm_single_data_transfer_1_0_0_0_0_0_3, &&arm_single_data_transfer_1_0_0_0_0_0_4, &&arm_single_data_transfer_1_0_0_0_0_0_5, &&arm_single_data_transfer_1_0_0_0_0_0_6, &&arm_single_data_transfer_1_0_0_0_0_0_7, &&arm_single_data_transfer_1_0_0_0_0_1_0, &&arm_single_data_transfer_1_0_0_0_0_1_1, &&arm_single_data_transfer_1_0_0_0_0_1_2, &&arm_single_data_transfer_1_0_0_0_0_1_3, &&arm_single_data_transfer_1_0_0_0_0_1_4, &&arm_single_data_transfer_1_0_0_0_0_1_5, &&arm_single_data_transfer_1_0_0_0_0_1_6, &&arm_single_data_transfer_1_0_0_0_0_1_7, &&arm_single_data_transfer_1_0_0_0_0_1_0, &&arm_single_data_transfer_1_0_0_0_0_1_1, &&arm_single_data_transfer_1_0_0_0_0_1_2, &&arm_single_data_transfer_1_0_0_0_0_1_3, &&arm_single_data_transfer_1_0_0_0_0_1_4, &&arm_single_data_transfer_1_0_0_0_0_1_5, &&arm_single_data_transfer_1_0_0_0_0_1_6, &&arm_single_data_transfer_1_0_0_0_0_1_7, &&arm_single_data_transfer_1_0_0_0_1_0_0, &&arm_single_data_transfer_1_0_0_0_1_0_1, &&arm_single_data_transfer_1_0_0_0_1_0_2, &&arm_single_data_transfer_1_0_0_0_1_0_3, &&arm_single_data_transfer_1_0_0_0_1_0_4, &&arm_single_data_transfer_1_0_0_0_1_0_5, &&arm_single_data_transfer_1_0_0_0_1_0_6, &&arm_single_data_transfer_1_0_0_0_1_0_7, &&arm_single_data_transfer_1_0_0_0_1_0_0, &&arm_single_data_transfer_1_0_0_0_1_0_1, &&arm_single_data_transfer_1_0_0_0_1_0_2, &&arm_single_data_transfer_1_0_0_0_1_0_3, &&arm_single_data_transfer_1_0_0_0_1_0_4, &&arm_single_data_transfer_1_0_0_0_1_0_5, &&arm_single_data_transfer_1_0_0_0_1_0_6, &&arm_single_data_transfer_1_0_0_0_1_0_7, &&arm_single_data_transfer_1_0_0_0_1_1_0, &&arm_single_data_transfer_1_0_0_0_1_1_1, &&arm_single_data_transfer_1_0_0_0_1_1_2, &&arm_single_data_transfer_1_0_0_0_1_1_3, &&arm_single_data_transfer_1_0_0_0_1_1_4, &&arm_single_data_transfer_1_0_0_0_1_1_5, &&arm_single_data_transfer_1_0_0_0_1_1_6, &&arm_single_data_transfer_1_0_0_0_1_1_7, &&arm_single_data_transfer_1_0_0_0_1_1_0, &&arm_single_data_transfer_1_0_0_0_1_1_1, &&arm_single_data_transfer_1_0_0_0_1_1_2, &&arm_single_data_transfer_1_0_0_0_1_1_3, &&arm_single_data_transfer_1_0_0_0_1_1_4, &&arm_single_data_transfer_1_0_0_0_1_1_5, &&arm_single_data_transfer_1_0_0_0_1_1_6, &&arm_single_data_transfer_1_0_0_0_1_1_7, &&arm_single_data_transfer_1_0_0_1_0_0_0, &&arm_single_data_transfer_1_0_0_1_0_0_1, &&arm_single_data_transfer_1_0_0_1_0_0_2, &&arm_single_data_transfer_1_0_0_1_0_0_3, &&arm_single_data_transfer_1_0_0_1_0_0_4, &&arm_single_data_transfer_1_0_0_1_0_0_5, &&arm_single_data_transfer_1_0_0_1_0_0_6, &&arm_single_data_transfer_1_0_0_1_0_0_7, &&arm_single_data_transfer_1_0_0_1_0_0_0, &&arm_single_data_transfer_1_0_0_1_0_0_1, &&arm_single_data_transfer_1_0_0_1_0_0_2, &&arm_single_data_transfer_1_0_0_1_0_0_3, &&arm_single_data_transfer_1_0_0_1_0_0_4, &&arm_single_data_transfer_1_0_0_1_0_0_5, &&arm_single_data_transfer_1_0_0_1_0_0_6, &&arm_single_data_transfer_1_0_0_1_0_0_7, &&arm_single_data_transfer_1_0_0_1_0_1_0, &&arm_single_data_transfer_1_0_0_1_0_1_1, &&arm_single_data_transfer_1_0_0_1_0_1_2, &&arm_single_data_transfer_1_0_0_1_0_1_3, &&arm_single_data_transfer_1_0_0_1_0_1_4, &&arm_single_data_transfer_1_0_0_1_0_1_5, &&arm_single_data_transfer_1_0_0_1_0_1_6, &&arm_single_data_transfer_1_0_0_1_0_1_7, &&arm_single_data_transfer_1_0_0_1_0_1_0, &&arm_single_data_transfer_1_0_0_1_0_1_1, &&arm_single_data_transfer_1_0_0_1_0_1_2, &&arm_single_data_transfer_1_0_0_1_0_1_3, &&arm_single_data_transfer_1_0_0_1_0_1_4, &&arm_single_data_transfer_1_0_0_1_0_1_5, &&arm_single_data_transfer_1_0_0_1_0_1_6, &&arm_single_data_transfer_1_0_0_1_0_1_7, &&arm_single_data_transfer_1_0_0_1_1_0_0, &&arm_single_data_transfer_1_0_0_1_1_0_1, &&arm_single_data_transfer_1_0_0_1_1_0_2, &&arm_single_data_transfer_1_0_0_1_1_0_3, &&arm_single_data_transfer_1_0_0_1_1_0_4, &&arm_single_data_transfer_1_0_0_1_1_0_5, &&arm_single_data_transfer_1_0_0_1_1_0_6, &&arm_single_data_transfer_1_0_0_1_1_0_7, &&arm_single_data_transfer_1_0_0_1_1_0_0, &&arm_single_data_transfer_1_0_0_1_1_0_1, &&arm_single_data_transfer_1_0_0_1_1_0_2, &&arm_single_data_transfer_1_0_0_1_1_0_3, &&arm_single_data_transfer_1_0_0_1_1_0_4, &&arm_single_data_transfer_1_0_0_1_1_0_5, &&arm_single_data_transfer_1_0_0_1_1_0_6, &&arm_single_data_transfer_1_0_0_1_1_0_7, &&arm_single_data_transfer_1_0_0_1_1_1_0, &&arm_single_data_transfer_1_0_0_1_1_1_1, &&arm_single_data_transfer_1_0_0_1_1_1_2, &&arm_single_data_transfer_1_0_0_1_1_1_3, &&arm_single_data_transfer_1_0_0_1_1_1_4, &&arm_single_data_transfer_1_0_0_1_1_1_5, &&arm_single_data_transfer_1_0_0_1_1_1_6, &&arm_single_data_transfer_1_0_0_1_1_1_7, &&arm_single_data_transfer_1_0_0_1_1_1_0, &&arm_single_data_transfer_1_0_0_1_1_1_1, &&arm_single_data_transfer_1_0_0_1_1_1_2, &&arm_single_data_transfer_1_0_0_1_1_1_3, &&arm_single_data_transfer_1_0_0_1_1_1_4, &&arm_single_data_transfer_1_0_0_1_1_1_5, &&arm_single_data_transfer_1_0_0_1_1_1_6, &&arm_single_data_transfer_1_0_0_1_1_1_7, &&arm_single_data_transfer_1_0_1_0_0_0_0, &&arm_single_data_transfer_1_0_1_0_0_0_1, &&arm_single_data_transfer_1_0_1_0_0_0_2, &&arm_single_data_transfer_1_0_1_0_0_0_3, &&arm_single_data_transfer_1_0_1_0_0_0_4, &&arm_single_data_transfer_1_0_1_0_0_0_5, &&arm_single_data_transfer_1_0_1_0_0_0_6, &&arm_single_data_transfer_1_0_1_0_0_0_7, &&arm_single_data_transfer_1_0_1_0_0_0_0, &&arm_single_data_transfer_1_0_1_0_0_0_1, &&arm_single_data_transfer_1_0_1_0_0_0_2, &&arm_single_data_transfer_1_0_1_0_0_0_3, &&arm_single_data_transfer_1_0_1_0_0_0_4, &&arm_single_data_transfer_1_0_1_0_0_0_5, &&arm_single_data_transfer_1_0_1_0_0_0_6, &&arm_single_data_transfer_1_0_1_0_0_0_7, &&arm_single_data_transfer_1_0_1_0_0_1_0, &&arm_single_data_transfer_1_0_1_0_0_1_1, &&arm_single_data_transfer_1_0_1_0_0_1_2, &&arm_single_data_transfer_1_0_1_0_0_1_3, &&arm_single_data_transfer_1_0_1_0_0_1_4, &&arm_single_data_transfer_1_0_1_0_0_1_5, &&arm_single_data_transfer_1_0_1_0_0_1_6, &&arm_single_data_transfer_1_0_1_0_0_1_7, &&arm_single_data_transfer_1_0_1_0_0_1_0, &&arm_single_data_transfer_1_0_1_0_0_1_1, &&arm_single_data_transfer_1_0_1_0_0_1_2, &&arm_single_data_transfer_1_0_1_0_0_1_3, &&arm_single_data_transfer_1_0_1_0_0_1_4, &&arm_single_data_transfer_1_0_1_0_0_1_5, &&arm_single_data_transfer_1_0_1_0_0_1_6, &&arm_single_data_transfer_1_0_1_0_0_1_7, &&arm_single_data_transfer_1_0_1_0_1_0_0, &&arm_single_data_transfer_1_0_1_0_1_0_1, &&arm_single_data_transfer_1_0_1_0_1_0_2, &&arm_single_data_transfer_1_0_1_0_1_0_3, &&arm_single_data_transfer_1_0_1_0_1_0_4, &&arm_single_data_transfer_1_0_1_0_1_0_5, &&arm_single_data_transfer_1_0_1_0_1_0_6, &&arm_single_data_transfer_1_0_1_0_1_0_7, &&arm_single_data_transfer_1_0_1_0_1_0_0, &&arm_single_data_transfer_1_0_1_0_1_0_1, &&arm_single_data_transfer_1_0_1_0_1_0_2, &&arm_single_data_transfer_1_0_1_0_1_0_3, &&arm_single_data_transfer_1_0_1_0_1_0_4, &&arm_single_data_transfer_1_0_1_0_1_0_5, &&arm_single_data_transfer_1_0_1_0_1_0_6, &&arm_single_data_transfer_1_0_1_0_1_0_7, &&arm_single_data_transfer_1_0_1_0_1_1_0, &&arm_single_data_transfer_1_0_1_0_1_1_1, &&arm_single_data_transfer_1_0_1_0_1_1_2, &&arm_single_data_transfer_1_0_1_0_1_1_3, &&arm_single_data_transfer_1_0_1_0_1_1_4, &&arm_single_data_transfer_1_0_1_0_1_1_5, &&arm_single_data_transfer_1_0_1_0_1_1_6, &&arm_single_data_transfer_1_0_1_0_1_1_7, &&arm_single_data_transfer_1_0_1_0_1_1_0, &&arm_single_data_transfer_1_0_1_0_1_1_1, &&arm_single_data_transfer_1_0_1_0_1_1_2, &&arm_single_data_transfer_1_0_1_0_1_1_3, &&arm_single_data_transfer_1_0_1_0_1_1_4, &&arm_single_data_transfer_1_0_1_0_1_1_5, &&arm_single_data_transfer_1_0_1_0_1_1_6, &&arm_single_data_transfer_1_0_1_0_1_1_7, &&arm_single_data_transfer_1_0_1_1_0_0_0, &&arm_single_data_transfer_1_0_1_1_0_0_1, &&arm_single_data_transfer_1_0_1_1_0_0_2, &&arm_single_data_transfer_1_0_1_1_0_0_3, &&arm_single_data_transfer_1_0_1_1_0_0_4, &&arm_single_data_transfer_1_0_1_1_0_0_5, &&arm_single_data_transfer_1_0_1_1_0_0_6, &&arm_single_data_transfer_1_0_1_1_0_0_7, &&arm_single_data_transfer_1_0_1_1_0_0_0, &&arm_single_data_transfer_1_0_1_1_0_0_1, &&arm_single_data_transfer_1_0_1_1_0_0_2, &&arm_single_data_transfer_1_0_1_1_0_0_3, &&arm_single_data_transfer_1_0_1_1_0_0_4, &&arm_single_data_transfer_1_0_1_1_0_0_5, &&arm_single_data_transfer_1_0_1_1_0_0_6, &&arm_single_data_transfer_1_0_1_1_0_0_7, &&arm_single_data_transfer_1_0_1_1_0_1_0, &&arm_single_data_transfer_1_0_1_1_0_1_1, &&arm_single_data_transfer_1_0_1_1_0_1_2, &&arm_single_data_transfer_1_0_1_1_0_1_3, &&arm_single_data_transfer_1_0_1_1_0_1_4, &&arm_single_data_transfer_1_0_1_1_0_1_5, &&arm_single_data_transfer_1_0_1_1_0_1_6, &&arm_single_data_transfer_1_0_1_1_0_1_7, &&arm_single_data_transfer_1_0_1_1_0_1_0, &&arm_single_data_transfer_1_0_1_1_0_1_1, &&arm_single_data_transfer_1_0_1_1_0_1_2, &&arm_single_data_transfer_1_0_1_1_0_1_3, &&arm_single_data_transfer_1_0_1_1_0_1_4, &&arm_single_data_transfer_1_0_1_1_0_1_5, &&arm_single_data_transfer_1_0_1_1_0_1_6, &&arm_single_data_transfer_1_0_1_1_0_1_7, &&arm_single_data_transfer_1_0_1_1_1_0_0, &&arm_single_data_transfer_1_0_1_1_1_0_1, &&arm_single_data_transfer_1_0_1_1_1_0_2, &&arm_single_data_transfer_1_0_1_1_1_0_3, &&arm_single_data_transfer_1_0_1_1_1_0_4, &&arm_single_data_transfer_1_0_1_1_1_0_5, &&arm_single_data_transfer_1_0_1_1_1_0_6, &&arm_single_data_transfer_1_0_1_1_1_0_7, &&arm_single_data_transfer_1_0_1_1_1_0_0, &&arm_single_data_transfer_1_0_1_1_1_0_1, &&arm_single_data_transfer_1_0_1_1_1_0_2, &&arm_single_data_transfer_1_0_1_1_1_0_3, &&arm_single_data_transfer_1_0_1_1_1_0_4, &&arm_single_data_transfer_1_0_1_1_1_0_5, &&arm_single_data_transfer_1_0_1_1_1_0_6, &&arm_single_data_transfer_1_0_1_1_1_0_7, &&arm_single_data_transfer_1_0_1_1_1_1_0, &&arm_single_data_transfer_1_0_1_1_1_1_1, &&arm_single_data_transfer_1_0_1_1_1_1_2, &&arm_single_data_transfer_1_0_1_1_1_1_3, &&arm_single_data_transfer_1_0_1_1_1_1_4, &&arm_single_data_transfer_1_0_1_1_1_1_5, &&arm_single_data_transfer_1_0_1_1_1_1_6, &&arm_single_data_transfer_1_0_1_1_1_1_7, &&arm_single_data_transfer_1_0_1_1_1_1_0, &&arm_single_data_transfer_1_0_1_1_1_1_1, &&arm_single_data_transfer_1_0_1_1_1_1_2, &&arm_single_data_transfer_1_0_1_1_1_1_3, &&arm_single_data_transfer_1_0_1_1_1_1_4, &&arm_single_data_transfer_1_0_1_1_1_1_5, &&arm_single_data_transfer_1_0_1_1_1_1_6, &&arm_single_data_transfer_1_0_1_1_1_1_7, &&arm_single_data_transfer_1_1_0_0_0_0_0, &&arm_single_data_transfer_1_1_0_0_0_0_1, &&arm_single_data_transfer_1_1_0_0_0_0_2, &&arm_single_data_transfer_1_1_0_0_0_0_3, &&arm_single_data_transfer_1_1_0_0_0_0_4, &&arm_single_data_transfer_1_1_0_0_0_0_5, &&arm_single_data_transfer_1_1_0_0_0_0_6, &&arm_single_data_transfer_1_1_0_0_0_0_7, &&arm_single_data_transfer_1_1_0_0_0_0_0, &&arm_single_data_transfer_1_1_0_0_0_0_1, &&arm_single_data_transfer_1_1_0_0_0_0_2, &&arm_single_data_transfer_1_1_0_0_0_0_3, &&arm_single_data_transfer_1_1_0_0_0_0_4, &&arm_single_data_transfer_1_1_0_0_0_0_5, &&arm_single_data_transfer_1_1_0_0_0_0_6, &&arm_single_data_transfer_1_1_0_0_0_0_7, &&arm_single_data_transfer_1_1_0_0_0_1_0, &&arm_single_data_transfer_1_1_0_0_0_1_1, &&arm_single_data_transfer_1_1_0_0_0_1_2, &&arm_single_data_transfer_1_1_0_0_0_1_3, &&arm_single_data_transfer_1_1_0_0_0_1_4, &&arm_single_data_transfer_1_1_0_0_0_1_5, &&arm_single_data_transfer_1_1_0_0_0_1_6, &&arm_single_data_transfer_1_1_0_0_0_1_7, &&arm_single_data_transfer_1_1_0_0_0_1_0, &&arm_single_data_transfer_1_1_0_0_0_1_1, &&arm_single_data_transfer_1_1_0_0_0_1_2, &&arm_single_data_transfer_1_1_0_0_0_1_3, &&arm_single_data_transfer_1_1_0_0_0_1_4, &&arm_single_data_transfer_1_1_0_0_0_1_5, &&arm_single_data_transfer_1_1_0_0_0_1_6, &&arm_single_data_transfer_1_1_0_0_0_1_7, &&arm_single_data_transfer_1_1_0_0_1_0_0, &&arm_single_data_transfer_1_1_0_0_1_0_1, &&arm_single_data_transfer_1_1_0_0_1_0_2, &&arm_single_data_transfer_1_1_0_0_1_0_3, &&arm_single_data_transfer_1_1_0_0_1_0_4, &&arm_single_data_transfer_1_1_0_0_1_0_5, &&arm_single_data_transfer_1_1_0_0_1_0_6, &&arm_single_data_transfer_1_1_0_0_1_0_7, &&arm_single_data_transfer_1_1_0_0_1_0_0, &&arm_single_data_transfer_1_1_0_0_1_0_1, &&arm_single_data_transfer_1_1_0_0_1_0_2, &&arm_single_data_transfer_1_1_0_0_1_0_3, &&arm_single_data_transfer_1_1_0_0_1_0_4, &&arm_single_data_transfer_1_1_0_0_1_0_5, &&arm_single_data_transfer_1_1_0_0_1_0_6, &&arm_single_data_transfer_1_1_0_0_1_0_7, &&arm_single_data_transfer_1_1_0_0_1_1_0, &&arm_single_data_transfer_1_1_0_0_1_1_1, &&arm_single_data_transfer_1_1_0_0_1_1_2, &&arm_single_data_transfer_1_1_0_0_1_1_3, &&arm_single_data_transfer_1_1_0_0_1_1_4, &&arm_single_data_transfer_1_1_0_0_1_1_5, &&arm_single_data_transfer_1_1_0_0_1_1_6, &&arm_single_data_transfer_1_1_0_0_1_1_7, &&arm_single_data_transfer_1_1_0_0_1_1_0, &&arm_single_data_transfer_1_1_0_0_1_1_1, &&arm_single_data_transfer_1_1_0_0_1_1_2, &&arm_single_data_transfer_1_1_0_0_1_1_3, &&arm_single_data_transfer_1_1_0_0_1_1_4, &&arm_single_data_transfer_1_1_0_0_1_1_5, &&arm_single_data_transfer_1_1_0_0_1_1_6, &&arm_single_data_transfer_1_1_0_0_1_1_7, &&arm_single_data_transfer_1_1_0_1_0_0_0, &&arm_single_data_transfer_1_1_0_1_0_0_1, &&arm_single_data_transfer_1_1_0_1_0_0_2, &&arm_single_data_transfer_1_1_0_1_0_0_3, &&arm_single_data_transfer_1_1_0_1_0_0_4, &&arm_single_data_transfer_1_1_0_1_0_0_5, &&arm_single_data_transfer_1_1_0_1_0_0_6, &&arm_single_data_transfer_1_1_0_1_0_0_7, &&arm_single_data_transfer_1_1_0_1_0_0_0, &&arm_single_data_transfer_1_1_0_1_0_0_1, &&arm_single_data_transfer_1_1_0_1_0_0_2, &&arm_single_data_transfer_1_1_0_1_0_0_3, &&arm_single_data_transfer_1_1_0_1_0_0_4, &&arm_single_data_transfer_1_1_0_1_0_0_5, &&arm_single_data_transfer_1_1_0_1_0_0_6, &&arm_single_data_transfer_1_1_0_1_0_0_7, &&arm_single_data_transfer_1_1_0_1_0_1_0, &&arm_single_data_transfer_1_1_0_1_0_1_1, &&arm_single_data_transfer_1_1_0_1_0_1_2, &&arm_single_data_transfer_1_1_0_1_0_1_3, &&arm_single_data_transfer_1_1_0_1_0_1_4, &&arm_single_data_transfer_1_1_0_1_0_1_5, &&arm_single_data_transfer_1_1_0_1_0_1_6, &&arm_single_data_transfer_1_1_0_1_0_1_7, &&arm_single_data_transfer_1_1_0_1_0_1_0, &&arm_single_data_transfer_1_1_0_1_0_1_1, &&arm_single_data_transfer_1_1_0_1_0_1_2, &&arm_single_data_transfer_1_1_0_1_0_1_3, &&arm_single_data_transfer_1_1_0_1_0_1_4, &&arm_single_data_transfer_1_1_0_1_0_1_5, &&arm_single_data_transfer_1_1_0_1_0_1_6, &&arm_single_data_transfer_1_1_0_1_0_1_7, &&arm_single_data_transfer_1_1_0_1_1_0_0, &&arm_single_data_transfer_1_1_0_1_1_0_1, &&arm_single_data_transfer_1_1_0_1_1_0_2, &&arm_single_data_transfer_1_1_0_1_1_0_3, &&arm_single_data_transfer_1_1_0_1_1_0_4, &&arm_single_data_transfer_1_1_0_1_1_0_5, &&arm_single_data_transfer_1_1_0_1_1_0_6, &&arm_single_data_transfer_1_1_0_1_1_0_7, &&arm_single_data_transfer_1_1_0_1_1_0_0, &&arm_single_data_transfer_1_1_0_1_1_0_1, &&arm_single_data_transfer_1_1_0_1_1_0_2, &&arm_single_data_transfer_1_1_0_1_1_0_3, &&arm_single_data_transfer_1_1_0_1_1_0_4, &&arm_single_data_transfer_1_1_0_1_1_0_5, &&arm_single_data_transfer_1_1_0_1_1_0_6, &&arm_single_data_transfer_1_1_0_1_1_0_7, &&arm_single_data_transfer_1_1_0_1_1_1_0, &&arm_single_data_transfer_1_1_0_1_1_1_1, &&arm_single_data_transfer_1_1_0_1_1_1_2, &&arm_single_data_transfer_1_1_0_1_1_1_3, &&arm_single_data_transfer_1_1_0_1_1_1_4, &&arm_single_data_transfer_1_1_0_1_1_1_5, &&arm_single_data_transfer_1_1_0_1_1_1_6, &&arm_single_data_transfer_1_1_0_1_1_1_7, &&arm_single_data_transfer_1_1_0_1_1_1_0, &&arm_single_data_transfer_1_1_0_1_1_1_1, &&arm_single_data_transfer_1_1_0_1_1_1_2, &&arm_single_data_transfer_1_1_0_1_1_1_3, &&arm_single_data_transfer_1_1_0_1_1_1_4, &&arm_single_data_transfer_1_1_0_1_1_1_5, &&arm_single_data_transfer_1_1_0_1_1_1_6, &&arm_single_data_transfer_1_1_0_1_1_1_7, &&arm_single_data_transfer_1_1_1_0_0_0_0, &&arm_single_data_transfer_1_1_1_0_0_0_1, &&arm_single_data_transfer_1_1_1_0_0_0_2, &&arm_single_data_transfer_1_1_1_0_0_0_3, &&arm_single_data_transfer_1_1_1_0_0_0_4, &&arm_single_data_transfer_1_1_1_0_0_0_5, &&arm_single_data_transfer_1_1_1_0_0_0_6, &&arm_single_data_transfer_1_1_1_0_0_0_7, &&arm_single_data_transfer_1_1_1_0_0_0_0, &&arm_single_data_transfer_1_1_1_0_0_0_1, &&arm_single_data_transfer_1_1_1_0_0_0_2, &&arm_single_data_transfer_1_1_1_0_0_0_3, &&arm_single_data_transfer_1_1_1_0_0_0_4, &&arm_single_data_transfer_1_1_1_0_0_0_5, &&arm_single_data_transfer_1_1_1_0_0_0_6, &&arm_single_data_transfer_1_1_1_0_0_0_7, &&arm_single_data_transfer_1_1_1_0_0_1_0, &&arm_single_data_transfer_1_1_1_0_0_1_1, &&arm_single_data_transfer_1_1_1_0_0_1_2, &&arm_single_data_transfer_1_1_1_0_0_1_3, &&arm_single_data_transfer_1_1_1_0_0_1_4, &&arm_single_data_transfer_1_1_1_0_0_1_5, &&arm_single_data_transfer_1_1_1_0_0_1_6, &&arm_single_data_transfer_1_1_1_0_0_1_7, &&arm_single_data_transfer_1_1_1_0_0_1_0, &&arm_single_data_transfer_1_1_1_0_0_1_1, &&arm_single_data_transfer_1_1_1_0_0_1_2, &&arm_single_data_transfer_1_1_1_0_0_1_3, &&arm_single_data_transfer_1_1_1_0_0_1_4, &&arm_single_data_transfer_1_1_1_0_0_1_5, &&arm_single_data_transfer_1_1_1_0_0_1_6, &&arm_single_data_transfer_1_1_1_0_0_1_7, &&arm_single_data_transfer_1_1_1_0_1_0_0, &&arm_single_data_transfer_1_1_1_0_1_0_1, &&arm_single_data_transfer_1_1_1_0_1_0_2, &&arm_single_data_transfer_1_1_1_0_1_0_3, &&arm_single_data_transfer_1_1_1_0_1_0_4, &&arm_single_data_transfer_1_1_1_0_1_0_5, &&arm_single_data_transfer_1_1_1_0_1_0_6, &&arm_single_data_transfer_1_1_1_0_1_0_7, &&arm_single_data_transfer_1_1_1_0_1_0_0, &&arm_single_data_transfer_1_1_1_0_1_0_1, &&arm_single_data_transfer_1_1_1_0_1_0_2, &&arm_single_data_transfer_1_1_1_0_1_0_3, &&arm_single_data_transfer_1_1_1_0_1_0_4, &&arm_single_data_transfer_1_1_1_0_1_0_5, &&arm_single_data_transfer_1_1_1_0_1_0_6, &&arm_single_data_transfer_1_1_1_0_1_0_7, &&arm_single_data_transfer_1_1_1_0_1_1_0, &&arm_single_data_transfer_1_1_1_0_1_1_1, &&arm_single_data_transfer_1_1_1_0_1_1_2, &&arm_single_data_transfer_1_1_1_0_1_1_3, &&arm_single_data_transfer_1_1_1_0_1_1_4, &&arm_single_data_transfer_1_1_1_0_1_1_5, &&arm_single_data_transfer_1_1_1_0_1_1_6, &&arm_single_data_transfer_1_1_1_0_1_1_7, &&arm_single_data_transfer_1_1_1_0_1_1_0, &&arm_single_data_transfer_1_1_1_0_1_1_1, &&arm_single_data_transfer_1_1_1_0_1_1_2, &&arm_single_data_transfer_1_1_1_0_1_1_3, &&arm_single_data_transfer_1_1_1_0_1_1_4, &&arm_single_data_transfer_1_1_1_0_1_1_5, &&arm_single_data_transfer_1_1_1_0_1_1_6, &&arm_single_data_transfer_1_1_1_0_1_1_7, &&arm_single_data_transfer_1_1_1_1_0_0_0, &&arm_single_data_transfer_1_1_1_1_0_0_1, &&arm_single_data_transfer_1_1_1_1_0_0_2, &&arm_single_data_transfer_1_1_1_1_0_0_3, &&arm_single_data_transfer_1_1_1_1_0_0_4, &&arm_single_data_transfer_1_1_1_1_0_0_5, &&arm_single_data_transfer_1_1_1_1_0_0_6, &&arm_single_data_transfer_1_1_1_1_0_0_7, &&arm_single_data_transfer_1_1_1_1_0_0_0, &&arm_single_data_transfer_1_1_1_1_0_0_1, &&arm_single_data_transfer_1_1_1_1_0_0_2, &&arm_single_data_transfer_1_1_1_1_0_0_3, &&arm_single_data_transfer_1_1_1_1_0_0_4, &&arm_single_data_transfer_1_1_1_1_0_0_5, &&arm_single_data_transfer_1_1_1_1_0_0_6, &&arm_single_data_transfer_1_1_1_1_0_0_7, &&arm_single_data_transfer_1_1_1_1_0_1_0, &&arm_single_data_transfer_1_1_1_1_0_1_1, &&arm_single_data_transfer_1_1_1_1_0_1_2, &&arm_single_data_transfer_1_1_1_1_0_1_3, &&arm_single_data_transfer_1_1_1_1_0_1_4, &&arm_single_data_transfer_1_1_1_1_0_1_5, &&arm_single_data_transfer_1_1_1_1_0_1_6, &&arm_single_data_transfer_1_1_1_1_0_1_7, &&arm_single_data_transfer_1_1_1_1_0_1_0, &&arm_single_data_transfer_1_1_1_1_0_1_1, &&arm_single_data_transfer_1_1_1_1_0_1_2, &&arm_single_data_transfer_1_1_1_1_0_1_3, &&arm_single_data_transfer_1_1_1_1_0_1_4, &&arm_single_data_transfer_1_1_1_1_0_1_5, &&arm_single_data_transfer_1_1_1_1_0_1_6, &&arm_single_data_transfer_1_1_1_1_0_1_7, &&arm_single_data_transfer_1_1_1_1_1_0_0, &&arm_single_data_transfer_1_1_1_1_1_0_1, &&arm_single_data_transfer_1_1_1_1_1_0_2, &&arm_single_data_transfer_1_1_1_1_1_0_3, &&arm_single_data_transfer_1_1_1_1_1_0_4, &&arm_single_data_transfer_1_1_1_1_1_0_5, &&arm_single_data_transfer_1_1_1_1_1_0_6, &&arm_single_data_transfer_1_1_1_1_1_0_7, &&arm_single_data_transfer_1_1_1_1_1_0_0, &&arm_single_data_transfer_1_1_1_1_1_0_1, &&arm_single_data_transfer_1_1_1_1_1_0_2, &&arm_single_data_transfer_1_1_1_1_1_0_3, &&arm_single_data_transfer_1_1_1_1_1_0_4, &&arm_single_data_transfer_1_1_1_1_1_0_5, &&arm_single_data_transfer_1_1_1_1_1_0_6, &&arm_single_data_transfer_1_1_1_1_1_0_7, &&arm_single_data_transfer_1_1_1_1_1_1_0, &&arm_single_data_transfer_1_1_1_1_1_1_1, &&arm_single_data_transfer_1_1_1_1_1_1_2, &&arm_single_data_transfer_1_1_1_1_1_1_3, &&arm_single_data_transfer_1_1_1_1_1_1_4, &&arm_single_data_transfer_1_1_1_1_1_1_5, &&arm_single_data_transfer_1_1_1_1_1_1_6, &&arm_single_data_transfer_1_1_1_1_1_1_7, &&arm_single_data_transfer_1_1_1_1_1_1_0, &&arm_single_data_transfer_1_1_1_1_1_1_1, &&arm_single_data_transfer_1_1_1_1_1_1_2, &&arm_single_data_transfer_1_1_1_1_1_1_3, &&arm_single_data_transfer_1_1_1_1_1_1_4, &&arm_single_data_transfer_1_1_1_1_1_1_5, &&arm_single_data_transfer_1_1_1_1_1_1_6, &&arm_single_data_transfer_1_1_1_1_1_1_7, &&arm_block_data_transfer_0_0_0_0_0_0, &&arm_block_data_transfer_0_0_0_0_0_0, &&arm_block_data_transfer_0_0_0_0_0_0, &&arm_block_data_transfer_0_0_0_0_0_0, &&arm_block_data_transfer_0_0_0_0_0_0, &&arm_block_data_transfer_0_0_0_0_0_0, &&arm_block_data_transfer_0_0_0_0_0_0, &&arm_block_data_transfer_0_0_0_0_0_0, &&arm_block_data_transfer_0_0_0_0_0_0, &&arm_block_data_transfer_0_0_0_0_0_0, &&arm_block_data_transfer_0_0_0_0_0_0, &&arm_block_data_transfer_0_0_0_0_0_0, &&arm_block_data_transfer_0_0_0_0_0_0, &&arm_block_data_transfer_0_0_0_0_0_0, &&arm_block_data_transfer_0_0_0_0_0_0, &&arm_block_data_transfer_0_0_0_0_0_0, &&arm_block_data_transfer_0_0_0_0_1_0, &&arm_block_data_transfer_0_0_0_0_1_0, &&arm_block_data_transfer_0_0_0_0_1_0, &&arm_block_data_transfer_0_0_0_0_1_0, &&arm_block_data_transfer_0_0_0_0_1_0, &&arm_block_data_transfer_0_0_0_0_1_0, &&arm_block_data_transfer_0_0_0_0_1_0, &&arm_block_data_transfer_0_0_0_0_1_0, &&arm_block_data_transfer_0_0_0_0_1_0, &&arm_block_data_transfer_0_0_0_0_1_0, &&arm_block_data_transfer_0_0_0_0_1_0, &&arm_block_data_transfer_0_0_0_0_1_0, &&arm_block_data_transfer_0_0_0_0_1_0, &&arm_block_data_transfer_0_0_0_0_1_0, &&arm_block_data_transfer_0_0_0_0_1_0, &&arm_block_data_transfer_0_0_0_0_1_0, &&arm_block_data_transfer_0_0_0_1_0_0, &&arm_block_data_transfer_0_0_0_1_0_0, &&arm_block_data_transfer_0_0_0_1_0_0, &&arm_block_data_transfer_0_0_0_1_0_0, &&arm_block_data_transfer_0_0_0_1_0_0, &&arm_block_data_transfer_0_0_0_1_0_0, &&arm_block_data_transfer_0_0_0_1_0_0, &&arm_block_data_transfer_0_0_0_1_0_0, &&arm_block_data_transfer_0_0_0_1_0_0, &&arm_block_data_transfer_0_0_0_1_0_0, &&arm_block_data_transfer_0_0_0_1_0_0, &&arm_block_data_transfer_0_0_0_1_0_0, &&arm_block_data_transfer_0_0_0_1_0_0, &&arm_block_data_transfer_0_0_0_1_0_0, &&arm_block_data_transfer_0_0_0_1_0_0, &&arm_block_data_transfer_0_0_0_1_0_0, &&arm_block_data_transfer_0_0_0_1_1_0, &&arm_block_data_transfer_0_0_0_1_1_0, &&arm_block_data_transfer_0_0_0_1_1_0, &&arm_block_data_transfer_0_0_0_1_1_0, &&arm_block_data_transfer_0_0_0_1_1_0, &&arm_block_data_transfer_0_0_0_1_1_0, &&arm_block_data_transfer_0_0_0_1_1_0, &&arm_block_data_transfer_0_0_0_1_1_0, &&arm_block_data_transfer_0_0_0_1_1_0, &&arm_block_data_transfer_0_0_0_1_1_0, &&arm_block_data_transfer_0_0_0_1_1_0, &&arm_block_data_transfer_0_0_0_1_1_0, &&arm_block_data_transfer_0_0_0_1_1_0, &&arm_block_data_transfer_0_0_0_1_1_0, &&arm_block_data_transfer_0_0_0_1_1_0, &&arm_block_data_transfer_0_0_0_1_1_0, &&arm_block_data_transfer_0_0_1_0_0_0, &&arm_block_data_transfer_0_0_1_0_0_0, &&arm_block_data_transfer_0_0_1_0_0_0, &&arm_block_data_transfer_0_0_1_0_0_0, &&arm_block_data_transfer_0_0_1_0_0_0, &&arm_block_data_transfer_0_0_1_0_0_0, &&arm_block_data_transfer_0_0_1_0_0_0, &&arm_block_data_transfer_0_0_1_0_0_0, &&arm_block_data_transfer_0_0_1_0_0_0, &&arm_block_data_transfer_0_0_1_0_0_0, &&arm_block_data_transfer_0_0_1_0_0_0, &&arm_block_data_transfer_0_0_1_0_0_0, &&arm_block_data_transfer_0_0_1_0_0_0, &&arm_block_data_transfer_0_0_1_0_0_0, &&arm_block_data_transfer_0_0_1_0_0_0, &&arm_block_data_transfer_0_0_1_0_0_0, &&arm_block_data_transfer_0_0_1_0_1_0, &&arm_block_data_transfer_0_0_1_0_1_0, &&arm_block_data_transfer_0_0_1_0_1_0, &&arm_block_data_transfer_0_0_1_0_1_0, &&arm_block_data_transfer_0_0_1_0_1_0, &&arm_block_data_transfer_0_0_1_0_1_0, &&arm_block_data_transfer_0_0_1_0_1_0, &&arm_block_data_transfer_0_0_1_0_1_0, &&arm_block_data_transfer_0_0_1_0_1_0, &&arm_block_data_transfer_0_0_1_0_1_0, &&arm_block_data_transfer_0_0_1_0_1_0, &&arm_block_data_transfer_0_0_1_0_1_0, &&arm_block_data_transfer_0_0_1_0_1_0, &&arm_block_data_transfer_0_0_1_0_1_0, &&arm_block_data_transfer_0_0_1_0_1_0, &&arm_block_data_transfer_0_0_1_0_1_0, &&arm_block_data_transfer_0_0_1_1_0_0, &&arm_block_data_transfer_0_0_1_1_0_0, &&arm_block_data_transfer_0_0_1_1_0_0, &&arm_block_data_transfer_0_0_1_1_0_0, &&arm_block_data_transfer_0_0_1_1_0_0, &&arm_block_data_transfer_0_0_1_1_0_0, &&arm_block_data_transfer_0_0_1_1_0_0, &&arm_block_data_transfer_0_0_1_1_0_0, &&arm_block_data_transfer_0_0_1_1_0_0, &&arm_block_data_transfer_0_0_1_1_0_0, &&arm_block_data_transfer_0_0_1_1_0_0, &&arm_block_data_transfer_0_0_1_1_0_0, &&arm_block_data_transfer_0_0_1_1_0_0, &&arm_block_data_transfer_0_0_1_1_0_0, &&arm_block_data_transfer_0_0_1_1_0_0, &&arm_block_data_transfer_0_0_1_1_0_0, &&arm_block_data_transfer_0_0_1_1_1_0, &&arm_block_data_transfer_0_0_1_1_1_0, &&arm_block_data_transfer_0_0_1_1_1_0, &&arm_block_data_transfer_0_0_1_1_1_0, &&arm_block_data_transfer_0_0_1_1_1_0, &&arm_block_data_transfer_0_0_1_1_1_0, &&arm_block_data_transfer_0_0_1_1_1_0, &&arm_block_data_transfer_0_0_1_1_1_0, &&arm_block_data_transfer_0_0_1_1_1_0, &&arm_block_data_transfer_0_0_1_1_1_0, &&arm_block_data_transfer_0_0_1_1_1_0, &&arm_block_data_transfer_0_0_1_1_1_0, &&arm_block_data_transfer_0_0_1_1_1_0, &&arm_block_data_transfer_0_0_1_1_1_0, &&arm_block_data_transfer_0_0_1_1_1_0, &&arm_block_data_transfer_0_0_1_1_1_0, &&arm_block_data_transfer_0_1_0_0_0_0, &&arm_block_data_transfer_0_1_0_0_0_0, &&arm_block_data_transfer_0_1_0_0_0_0, &&arm_block_data_transfer_0_1_0_0_0_0, &&arm_block_data_transfer_0_1_0_0_0_0, &&arm_block_data_transfer_0_1_0_0_0_0, &&arm_block_data_transfer_0_1_0_0_0_0, &&arm_block_data_transfer_0_1_0_0_0_0, &&arm_block_data_transfer_0_1_0_0_0_0, &&arm_block_data_transfer_0_1_0_0_0_0, &&arm_block_data_transfer_0_1_0_0_0_0, &&arm_block_data_transfer_0_1_0_0_0_0, &&arm_block_data_transfer_0_1_0_0_0_0, &&arm_block_data_transfer_0_1_0_0_0_0, &&arm_block_data_transfer_0_1_0_0_0_0, &&arm_block_data_transfer_0_1_0_0_0_0, &&arm_block_data_transfer_0_1_0_0_1_0, &&arm_block_data_transfer_0_1_0_0_1_0, &&arm_block_data_transfer_0_1_0_0_1_0, &&arm_block_data_transfer_0_1_0_0_1_0, &&arm_block_data_transfer_0_1_0_0_1_0, &&arm_block_data_transfer_0_1_0_0_1_0, &&arm_block_data_transfer_0_1_0_0_1_0, &&arm_block_data_transfer_0_1_0_0_1_0, &&arm_block_data_transfer_0_1_0_0_1_0, &&arm_block_data_transfer_0_1_0_0_1_0, &&arm_block_data_transfer_0_1_0_0_1_0, &&arm_block_data_transfer_0_1_0_0_1_0, &&arm_block_data_transfer_0_1_0_0_1_0, &&arm_block_data_transfer_0_1_0_0_1_0, &&arm_block_data_transfer_0_1_0_0_1_0, &&arm_block_data_transfer_0_1_0_0_1_0, &&arm_block_data_transfer_0_1_0_1_0_0, &&arm_block_data_transfer_0_1_0_1_0_0, &&arm_block_data_transfer_0_1_0_1_0_0, &&arm_block_data_transfer_0_1_0_1_0_0, &&arm_block_data_transfer_0_1_0_1_0_0, &&arm_block_data_transfer_0_1_0_1_0_0, &&arm_block_data_transfer_0_1_0_1_0_0, &&arm_block_data_transfer_0_1_0_1_0_0, &&arm_block_data_transfer_0_1_0_1_0_0, &&arm_block_data_transfer_0_1_0_1_0_0, &&arm_block_data_transfer_0_1_0_1_0_0, &&arm_block_data_transfer_0_1_0_1_0_0, &&arm_block_data_transfer_0_1_0_1_0_0, &&arm_block_data_transfer_0_1_0_1_0_0, &&arm_block_data_transfer_0_1_0_1_0_0, &&arm_block_data_transfer_0_1_0_1_0_0, &&arm_block_data_transfer_0_1_0_1_1_0, &&arm_block_data_transfer_0_1_0_1_1_0, &&arm_block_data_transfer_0_1_0_1_1_0, &&arm_block_data_transfer_0_1_0_1_1_0, &&arm_block_data_transfer_0_1_0_1_1_0, &&arm_block_data_transfer_0_1_0_1_1_0, &&arm_block_data_transfer_0_1_0_1_1_0, &&arm_block_data_transfer_0_1_0_1_1_0, &&arm_block_data_transfer_0_1_0_1_1_0, &&arm_block_data_transfer_0_1_0_1_1_0, &&arm_block_data_transfer_0_1_0_1_1_0, &&arm_block_data_transfer_0_1_0_1_1_0, &&arm_block_data_transfer_0_1_0_1_1_0, &&arm_block_data_transfer_0_1_0_1_1_0, &&arm_block_data_transfer_0_1_0_1_1_0, &&arm_block_data_transfer_0_1_0_1_1_0, &&arm_block_data_transfer_0_1_1_0_0_0, &&arm_block_data_transfer_0_1_1_0_0_0, &&arm_block_data_transfer_0_1_1_0_0_0, &&arm_block_data_transfer_0_1_1_0_0_0, &&arm_block_data_transfer_0_1_1_0_0_0, &&arm_block_data_transfer_0_1_1_0_0_0, &&arm_block_data_transfer_0_1_1_0_0_0, &&arm_block_data_transfer_0_1_1_0_0_0, &&arm_block_data_transfer_0_1_1_0_0_0, &&arm_block_data_transfer_0_1_1_0_0_0, &&arm_block_data_transfer_0_1_1_0_0_0, &&arm_block_data_transfer_0_1_1_0_0_0, &&arm_block_data_transfer_0_1_1_0_0_0, &&arm_block_data_transfer_0_1_1_0_0_0, &&arm_block_data_transfer_0_1_1_0_0_0, &&arm_block_data_transfer_0_1_1_0_0_0, &&arm_block_data_transfer_0_1_1_0_1_0, &&arm_block_data_transfer_0_1_1_0_1_0, &&arm_block_data_transfer_0_1_1_0_1_0, &&arm_block_data_transfer_0_1_1_0_1_0, &&arm_block_data_transfer_0_1_1_0_1_0, &&arm_block_data_transfer_0_1_1_0_1_0, &&arm_block_data_transfer_0_1_1_0_1_0, &&arm_block_data_transfer_0_1_1_0_1_0, &&arm_block_data_transfer_0_1_1_0_1_0, &&arm_block_data_transfer_0_1_1_0_1_0, &&arm_block_data_transfer_0_1_1_0_1_0, &&arm_block_data_transfer_0_1_1_0_1_0, &&arm_block_data_transfer_0_1_1_0_1_0, &&arm_block_data_transfer_0_1_1_0_1_0, &&arm_block_data_transfer_0_1_1_0_1_0, &&arm_block_data_transfer_0_1_1_0_1_0, &&arm_block_data_transfer_0_1_1_1_0_0, &&arm_block_data_transfer_0_1_1_1_0_0, &&arm_block_data_transfer_0_1_1_1_0_0, &&arm_block_data_transfer_0_1_1_1_0_0, &&arm_block_data_transfer_0_1_1_1_0_0, &&arm_block_data_transfer_0_1_1_1_0_0, &&arm_block_data_transfer_0_1_1_1_0_0, &&arm_block_data_transfer_0_1_1_1_0_0, &&arm_block_data_transfer_0_1_1_1_0_0, &&arm_block_data_transfer_0_1_1_1_0_0, &&arm_block_data_transfer_0_1_1_1_0_0, &&arm_block_data_transfer_0_1_1_1_0_0, &&arm_block_data_transfer_0_1_1_1_0_0, &&arm_block_data_transfer_0_1_1_1_0_0, &&arm_block_data_transfer_0_1_1_1_0_0, &&arm_block_data_transfer_0_1_1_1_0_0, &&arm_block_data_transfer_0_1_1_1_1_0, &&arm_block_data_transfer_0_1_1_1_1_0, &&arm_block_data_transfer_0_1_1_1_1_0, &&arm_block_data_transfer_0_1_1_1_1_0, &&arm_block_data_transfer_0_1_1_1_1_0, &&arm_block_data_transfer_0_1_1_1_1_0, &&arm_block_data_transfer_0_1_1_1_1_0, &&arm_block_data_transfer_0_1_1_1_1_0, &&arm_block_data_transfer_0_1_1_1_1_0, &&arm_block_data_transfer_0_1_1_1_1_0, &&arm_block_data_transfer_0_1_1_1_1_0, &&arm_block_data_transfer_0_1_1_1_1_0, &&arm_block_data_transfer_0_1_1_1_1_0, &&arm_block_data_transfer_0_1_1_1_1_0, &&arm_block_data_transfer_0_1_1_1_1_0, &&arm_block_data_transfer_0_1_1_1_1_0, &&arm_block_data_transfer_1_0_0_0_0_0, &&arm_block_data_transfer_1_0_0_0_0_0, &&arm_block_data_transfer_1_0_0_0_0_0, &&arm_block_data_transfer_1_0_0_0_0_0, &&arm_block_data_transfer_1_0_0_0_0_0, &&arm_block_data_transfer_1_0_0_0_0_0, &&arm_block_data_transfer_1_0_0_0_0_0, &&arm_block_data_transfer_1_0_0_0_0_0, &&arm_block_data_transfer_1_0_0_0_0_0, &&arm_block_data_transfer_1_0_0_0_0_0, &&arm_block_data_transfer_1_0_0_0_0_0, &&arm_block_data_transfer_1_0_0_0_0_0, &&arm_block_data_transfer_1_0_0_0_0_0, &&arm_block_data_transfer_1_0_0_0_0_0, &&arm_block_data_transfer_1_0_0_0_0_0, &&arm_block_data_transfer_1_0_0_0_0_0, &&arm_block_data_transfer_1_0_0_0_1_0, &&arm_block_data_transfer_1_0_0_0_1_0, &&arm_block_data_transfer_1_0_0_0_1_0, &&arm_block_data_transfer_1_0_0_0_1_0, &&arm_block_data_transfer_1_0_0_0_1_0, &&arm_block_data_transfer_1_0_0_0_1_0, &&arm_block_data_transfer_1_0_0_0_1_0, &&arm_block_data_transfer_1_0_0_0_1_0, &&arm_block_data_transfer_1_0_0_0_1_0, &&arm_block_data_transfer_1_0_0_0_1_0, &&arm_block_data_transfer_1_0_0_0_1_0, &&arm_block_data_transfer_1_0_0_0_1_0, &&arm_block_data_transfer_1_0_0_0_1_0, &&arm_block_data_transfer_1_0_0_0_1_0, &&arm_block_data_transfer_1_0_0_0_1_0, &&arm_block_data_transfer_1_0_0_0_1_0, &&arm_block_data_transfer_1_0_0_1_0_0, &&arm_block_data_transfer_1_0_0_1_0_0, &&arm_block_data_transfer_1_0_0_1_0_0, &&arm_block_data_transfer_1_0_0_1_0_0, &&arm_block_data_transfer_1_0_0_1_0_0, &&arm_block_data_transfer_1_0_0_1_0_0, &&arm_block_data_transfer_1_0_0_1_0_0, &&arm_block_data_transfer_1_0_0_1_0_0, &&arm_block_data_transfer_1_0_0_1_0_0, &&arm_block_data_transfer_1_0_0_1_0_0, &&arm_block_data_transfer_1_0_0_1_0_0, &&arm_block_data_transfer_1_0_0_1_0_0, &&arm_block_data_transfer_1_0_0_1_0_0, &&arm_block_data_transfer_1_0_0_1_0_0, &&arm_block_data_transfer_1_0_0_1_0_0, &&arm_block_data_transfer_1_0_0_1_0_0, &&arm_block_data_transfer_1_0_0_1_1_0, &&arm_block_data_transfer_1_0_0_1_1_0, &&arm_block_data_transfer_1_0_0_1_1_0, &&arm_block_data_transfer_1_0_0_1_1_0, &&arm_block_data_transfer_1_0_0_1_1_0, &&arm_block_data_transfer_1_0_0_1_1_0, &&arm_block_data_transfer_1_0_0_1_1_0, &&arm_block_data_transfer_1_0_0_1_1_0, &&arm_block_data_transfer_1_0_0_1_1_0, &&arm_block_data_transfer_1_0_0_1_1_0, &&arm_block_data_transfer_1_0_0_1_1_0, &&arm_block_data_transfer_1_0_0_1_1_0, &&arm_block_data_transfer_1_0_0_1_1_0, &&arm_block_data_transfer_1_0_0_1_1_0, &&arm_block_data_transfer_1_0_0_1_1_0, &&arm_block_data_transfer_1_0_0_1_1_0, &&arm_block_data_transfer_1_0_1_0_0_0, &&arm_block_data_transfer_1_0_1_0_0_0, &&arm_block_data_transfer_1_0_1_0_0_0, &&arm_block_data_transfer_1_0_1_0_0_0, &&arm_block_data_transfer_1_0_1_0_0_0, &&arm_block_data_transfer_1_0_1_0_0_0, &&arm_block_data_transfer_1_0_1_0_0_0, &&arm_block_data_transfer_1_0_1_0_0_0, &&arm_block_data_transfer_1_0_1_0_0_0, &&arm_block_data_transfer_1_0_1_0_0_0, &&arm_block_data_transfer_1_0_1_0_0_0, &&arm_block_data_transfer_1_0_1_0_0_0, &&arm_block_data_transfer_1_0_1_0_0_0, &&arm_block_data_transfer_1_0_1_0_0_0, &&arm_block_data_transfer_1_0_1_0_0_0, &&arm_block_data_transfer_1_0_1_0_0_0, &&arm_block_data_transfer_1_0_1_0_1_0, &&arm_block_data_transfer_1_0_1_0_1_0, &&arm_block_data_transfer_1_0_1_0_1_0, &&arm_block_data_transfer_1_0_1_0_1_0, &&arm_block_data_transfer_1_0_1_0_1_0, &&arm_block_data_transfer_1_0_1_0_1_0, &&arm_block_data_transfer_1_0_1_0_1_0, &&arm_block_data_transfer_1_0_1_0_1_0, &&arm_block_data_transfer_1_0_1_0_1_0, &&arm_block_data_transfer_1_0_1_0_1_0, &&arm_block_data_transfer_1_0_1_0_1_0, &&arm_block_data_transfer_1_0_1_0_1_0, &&arm_block_data_transfer_1_0_1_0_1_0, &&arm_block_data_transfer_1_0_1_0_1_0, &&arm_block_data_transfer_1_0_1_0_1_0, &&arm_block_data_transfer_1_0_1_0_1_0, &&arm_block_data_transfer_1_0_1_1_0_0, &&arm_block_data_transfer_1_0_1_1_0_0, &&arm_block_data_transfer_1_0_1_1_0_0, &&arm_block_data_transfer_1_0_1_1_0_0, &&arm_block_data_transfer_1_0_1_1_0_0, &&arm_block_data_transfer_1_0_1_1_0_0, &&arm_block_data_transfer_1_0_1_1_0_0, &&arm_block_data_transfer_1_0_1_1_0_0, &&arm_block_data_transfer_1_0_1_1_0_0, &&arm_block_data_transfer_1_0_1_1_0_0, &&arm_block_data_transfer_1_0_1_1_0_0, &&arm_block_data_transfer_1_0_1_1_0_0, &&arm_block_data_transfer_1_0_1_1_0_0, &&arm_block_data_transfer_1_0_1_1_0_0, &&arm_block_data_transfer_1_0_1_1_0_0, &&arm_block_data_transfer_1_0_1_1_0_0, &&arm_block_data_transfer_1_0_1_1_1_0, &&arm_block_data_transfer_1_0_1_1_1_0, &&arm_block_data_transfer_1_0_1_1_1_0, &&arm_block_data_transfer_1_0_1_1_1_0, &&arm_block_data_transfer_1_0_1_1_1_0, &&arm_block_data_transfer_1_0_1_1_1_0, &&arm_block_data_transfer_1_0_1_1_1_0, &&arm_block_data_transfer_1_0_1_1_1_0, &&arm_block_data_transfer_1_0_1_1_1_0, &&arm_block_data_transfer_1_0_1_1_1_0, &&arm_block_data_transfer_1_0_1_1_1_0, &&arm_block_data_transfer_1_0_1_1_1_0, &&arm_block_data_transfer_1_0_1_1_1_0, &&arm_block_data_transfer_1_0_1_1_1_0, &&arm_block_data_transfer_1_0_1_1_1_0, &&arm_block_data_transfer_1_0_1_1_1_0, &&arm_block_data_transfer_1_1_0_0_0_0, &&arm_block_data_transfer_1_1_0_0_0_0, &&arm_block_data_transfer_1_1_0_0_0_0, &&arm_block_data_transfer_1_1_0_0_0_0, &&arm_block_data_transfer_1_1_0_0_0_0, &&arm_block_data_transfer_1_1_0_0_0_0, &&arm_block_data_transfer_1_1_0_0_0_0, &&arm_block_data_transfer_1_1_0_0_0_0, &&arm_block_data_transfer_1_1_0_0_0_0, &&arm_block_data_transfer_1_1_0_0_0_0, &&arm_block_data_transfer_1_1_0_0_0_0, &&arm_block_data_transfer_1_1_0_0_0_0, &&arm_block_data_transfer_1_1_0_0_0_0, &&arm_block_data_transfer_1_1_0_0_0_0, &&arm_block_data_transfer_1_1_0_0_0_0, &&arm_block_data_transfer_1_1_0_0_0_0, &&arm_block_data_transfer_1_1_0_0_1_0, &&arm_block_data_transfer_1_1_0_0_1_0, &&arm_block_data_transfer_1_1_0_0_1_0, &&arm_block_data_transfer_1_1_0_0_1_0, &&arm_block_data_transfer_1_1_0_0_1_0, &&arm_block_data_transfer_1_1_0_0_1_0, &&arm_block_data_transfer_1_1_0_0_1_0, &&arm_block_data_transfer_1_1_0_0_1_0, &&arm_block_data_transfer_1_1_0_0_1_0, &&arm_block_data_transfer_1_1_0_0_1_0, &&arm_block_data_transfer_1_1_0_0_1_0, &&arm_block_data_transfer_1_1_0_0_1_0, &&arm_block_data_transfer_1_1_0_0_1_0, &&arm_block_data_transfer_1_1_0_0_1_0, &&arm_block_data_transfer_1_1_0_0_1_0, &&arm_block_data_transfer_1_1_0_0_1_0, &&arm_block_data_transfer_1_1_0_1_0_0, &&arm_block_data_transfer_1_1_0_1_0_0, &&arm_block_data_transfer_1_1_0_1_0_0, &&arm_block_data_transfer_1_1_0_1_0_0, &&arm_block_data_transfer_1_1_0_1_0_0, &&arm_block_data_transfer_1_1_0_1_0_0, &&arm_block_data_transfer_1_1_0_1_0_0, &&arm_block_data_transfer_1_1_0_1_0_0, &&arm_block_data_transfer_1_1_0_1_0_0, &&arm_block_data_transfer_1_1_0_1_0_0, &&arm_block_data_transfer_1_1_0_1_0_0, &&arm_block_data_transfer_1_1_0_1_0_0, &&arm_block_data_transfer_1_1_0_1_0_0, &&arm_block_data_transfer_1_1_0_1_0_0, &&arm_block_data_transfer_1_1_0_1_0_0, &&arm_block_data_transfer_1_1_0_1_0_0, &&arm_block_data_transfer_1_1_0_1_1_0, &&arm_block_data_transfer_1_1_0_1_1_0, &&arm_block_data_transfer_1_1_0_1_1_0, &&arm_block_data_transfer_1_1_0_1_1_0, &&arm_block_data_transfer_1_1_0_1_1_0, &&arm_block_data_transfer_1_1_0_1_1_0, &&arm_block_data_transfer_1_1_0_1_1_0, &&arm_block_data_transfer_1_1_0_1_1_0, &&arm_block_data_transfer_1_1_0_1_1_0, &&arm_block_data_transfer_1_1_0_1_1_0, &&arm_block_data_transfer_1_1_0_1_1_0, &&arm_block_data_transfer_1_1_0_1_1_0, &&arm_block_data_transfer_1_1_0_1_1_0, &&arm_block_data_transfer_1_1_0_1_1_0, &&arm_block_data_transfer_1_1_0_1_1_0, &&arm_block_data_transfer_1_1_0_1_1_0, &&arm_block_data_transfer_1_1_1_0_0_0, &&arm_block_data_transfer_1_1_1_0_0_0, &&arm_block_data_transfer_1_1_1_0_0_0, &&arm_block_data_transfer_1_1_1_0_0_0, &&arm_block_data_transfer_1_1_1_0_0_0, &&arm_block_data_transfer_1_1_1_0_0_0, &&arm_block_data_transfer_1_1_1_0_0_0, &&arm_block_data_transfer_1_1_1_0_0_0, &&arm_block_data_transfer_1_1_1_0_0_0, &&arm_block_data_transfer_1_1_1_0_0_0, &&arm_block_data_transfer_1_1_1_0_0_0, &&arm_block_data_transfer_1_1_1_0_0_0, &&arm_block_data_transfer_1_1_1_0_0_0, &&arm_block_data_transfer_1_1_1_0_0_0, &&arm_block_data_transfer_1_1_1_0_0_0, &&arm_block_data_transfer_1_1_1_0_0_0, &&arm_block_data_transfer_1_1_1_0_1_0, &&arm_block_data_transfer_1_1_1_0_1_0, &&arm_block_data_transfer_1_1_1_0_1_0, &&arm_block_data_transfer_1_1_1_0_1_0, &&arm_block_data_transfer_1_1_1_0_1_0, &&arm_block_data_transfer_1_1_1_0_1_0, &&arm_block_data_transfer_1_1_1_0_1_0, &&arm_block_data_transfer_1_1_1_0_1_0, &&arm_block_data_transfer_1_1_1_0_1_0, &&arm_block_data_transfer_1_1_1_0_1_0, &&arm_block_data_transfer_1_1_1_0_1_0, &&arm_block_data_transfer_1_1_1_0_1_0, &&arm_block_data_transfer_1_1_1_0_1_0, &&arm_block_data_transfer_1_1_1_0_1_0, &&arm_block_data_transfer_1_1_1_0_1_0, &&arm_block_data_transfer_1_1_1_0_1_0, &&arm_block_data_transfer_1_1_1_1_0_0, &&arm_block_data_transfer_1_1_1_1_0_0, &&arm_block_data_transfer_1_1_1_1_0_0, &&arm_block_data_transfer_1_1_1_1_0_0, &&arm_block_data_transfer_1_1_1_1_0_0, &&arm_block_data_transfer_1_1_1_1_0_0, &&arm_block_data_transfer_1_1_1_1_0_0, &&arm_block_data_transfer_1_1_1_1_0_0, &&arm_block_data_transfer_1_1_1_1_0_0, &&arm_block_data_transfer_1_1_1_1_0_0, &&arm_block_data_transfer_1_1_1_1_0_0, &&arm_block_data_transfer_1_1_1_1_0_0, &&arm_block_data_transfer_1_1_1_1_0_0, &&arm_block_data_transfer_1_1_1_1_0_0, &&arm_block_data_transfer_1_1_1_1_0_0, &&arm_block_data_transfer_1_1_1_1_0_0, &&arm_block_data_transfer_1_1_1_1_1_0, &&arm_block_data_transfer_1_1_1_1_1_0, &&arm_block_data_transfer_1_1_1_1_1_0, &&arm_block_data_transfer_1_1_1_1_1_0, &&arm_block_data_transfer_1_1_1_1_1_0, &&arm_block_data_transfer_1_1_1_1_1_0, &&arm_block_data_transfer_1_1_1_1_1_0, &&arm_block_data_transfer_1_1_1_1_1_0, &&arm_block_data_transfer_1_1_1_1_1_0, &&arm_block_data_transfer_1_1_1_1_1_0, &&arm_block_data_transfer_1_1_1_1_1_0, &&arm_block_data_transfer_1_1_1_1_1_0, &&arm_block_data_transfer_1_1_1_1_1_0, &&arm_block_data_transfer_1_1_1_1_1_0, &&arm_block_data_transfer_1_1_1_1_1_0, &&arm_block_data_transfer_1_1_1_1_1_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_0, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_0_1, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_0, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_b_bl_1_1, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&arm_not_decoded, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, &&swi, };

goto *arm_table[(((opcode >> 20) & 0xFF) << 4) | ((opcode >> 4) & 0xF)];

swi:{
arm7tdmi_trigger_exception(cpu, 0x8, 0x13);
return; }
arm_mrs_0:{
cpu->r[(opcode >> 12) & 0xF] = cpu->CPSR;
return; }
arm_mrs_1:{
cpu->r[(opcode >> 12) & 0xF] = *getSPSR(cpu);
return; }
arm_msr_0_0:{
u32 operand;
u8 field_mask = (opcode >> 16) & 0xF;
u32 mask = 0;
if(field_mask & 0b1000)
mask |= 0xFF000000;
if(field_mask & 0b1)
mask |= 0xFF;
operand = cpu->r[opcode & 0xF];
saveBankedReg(cpu);
cpu->CPSR = (cpu->CPSR & ~mask) | (operand & mask);
loadBankedReg(cpu);
return; }
arm_msr_0_1:{
u32 operand;
u8 field_mask = (opcode >> 16) & 0xF;
u32 mask = 0;
if(field_mask & 0b1000)
mask |= 0xFF000000;
if(field_mask & 0b1)
mask |= 0xFF;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
operand = alu_ROR(cpu, val, rot_amnt, 0);
}
saveBankedReg(cpu);
cpu->CPSR = (cpu->CPSR & ~mask) | (operand & mask);
loadBankedReg(cpu);
return; }
arm_msr_1_0:{
u32 operand;
u8 field_mask = (opcode >> 16) & 0xF;
u32 mask = 0;
if(field_mask & 0b1000)
mask |= 0xFF000000;
if(field_mask & 0b1)
mask |= 0xFF;
operand = cpu->r[opcode & 0xF];
u32* spsr = getSPSR(cpu);
*spsr = (*spsr & ~mask) | (operand & mask);
return; }
arm_msr_1_1:{
u32 operand;
u8 field_mask = (opcode >> 16) & 0xF;
u32 mask = 0;
if(field_mask & 0b1000)
mask |= 0xFF000000;
if(field_mask & 0b1)
mask |= 0xFF;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
operand = alu_ROR(cpu, val, rot_amnt, 0);
}
u32* spsr = getSPSR(cpu);
*spsr = (*spsr & ~mask) | (operand & mask);
return; }
arm_bx:{
cpu->r[15] = cpu->r[opcode & 0xF];
cpu->thumb_mode = (cpu->r[15] & 0b1);
cpu->r[15] &= 0xFFFFFFFE;
arm7tdmi_pipeline_refill(cpu);
return; }
arm_b_bl_0_0:{
u32 offset = opcode & 0xFFFFFF;
offset <<= 2;
cpu->r[15] += offset;
arm7tdmi_pipeline_refill(cpu);
return; }
arm_b_bl_0_1:{
u32 offset = opcode & 0xFFFFFF;
offset |= 0xFF000000;
offset <<= 2;
cpu->r[15] += offset;
arm7tdmi_pipeline_refill(cpu);
return; }
arm_b_bl_1_0:{
cpu->r[14] = cpu->r[15] - 4;
u32 offset = opcode & 0xFFFFFF;
offset <<= 2;
cpu->r[15] += offset;
arm7tdmi_pipeline_refill(cpu);
return; }
arm_b_bl_1_1:{
cpu->r[14] = cpu->r[15] - 4;
u32 offset = opcode & 0xFFFFFF;
offset |= 0xFF000000;
offset <<= 2;
cpu->r[15] += offset;
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_0_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
alu_AND(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_0_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_AND(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_0_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
alu_AND(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_0_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_AND(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_0_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
alu_AND(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_0_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_AND(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_0_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
alu_AND(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_0_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_AND(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_1_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
alu_EOR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_1_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_EOR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_1_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
alu_EOR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_1_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_EOR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_1_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
alu_EOR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_1_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_EOR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_1_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
alu_EOR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_1_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_EOR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_2_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
alu_SUB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_2_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_SUB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_2_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
alu_SUB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_2_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_SUB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_2_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
alu_SUB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_2_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_SUB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_2_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
alu_SUB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_2_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_SUB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_3_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_3_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_3_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_3_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_3_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_3_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_3_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_3_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_4_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_4_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_4_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_4_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_4_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_4_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_4_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_4_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_5_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_5_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_5_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_5_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_5_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_5_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_5_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_5_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_6_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_6_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_6_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_6_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_6_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_6_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_6_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_6_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_7_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_7_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_7_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_7_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_7_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_7_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_7_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_7_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_8_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
alu_TST(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_8_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_TST(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_8_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
alu_TST(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_8_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_TST(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_8_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
alu_TST(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_8_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_TST(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_8_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
alu_TST(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_8_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_TST(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_9_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
alu_TEQ(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_9_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_TEQ(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_9_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
alu_TEQ(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_9_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_TEQ(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_9_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
alu_TEQ(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_9_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_TEQ(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_9_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
alu_TEQ(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_9_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_TEQ(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_A_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
alu_CMP(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_A_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_CMP(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_A_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
alu_CMP(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_A_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_CMP(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_A_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
alu_CMP(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_A_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_CMP(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_A_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
alu_CMP(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_A_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_CMP(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_B_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
alu_CMN(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_B_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_CMN(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_B_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
alu_CMN(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_B_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_CMN(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_B_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
alu_CMN(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_B_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_CMN(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_B_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
alu_CMN(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_B_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_CMN(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_0_C_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
alu_ORR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_C_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_ORR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_C_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
alu_ORR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_C_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_ORR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_C_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
alu_ORR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_C_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_ORR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_C_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
alu_ORR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_C_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_ORR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_D_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
alu_MOV(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_D_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_MOV(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_D_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
alu_MOV(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_D_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_MOV(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_D_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
alu_MOV(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_D_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_MOV(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_D_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
alu_MOV(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_D_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_MOV(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_E_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
alu_BIC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_E_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_BIC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_E_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
alu_BIC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_E_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_BIC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_E_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
alu_BIC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_E_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_BIC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_E_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
alu_BIC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_E_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_BIC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_F_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
alu_MVN(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_F_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_MVN(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_F_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
alu_MVN(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_F_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_MVN(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_F_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
alu_MVN(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_F_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_MVN(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_F_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
alu_MVN(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_0_F_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 0);
}
if(rn_idx == 15)
rn += 4;
alu_MVN(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_0_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_AND(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_0_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_AND(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_0_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_AND(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_0_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_AND(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_0_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_AND(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_0_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_AND(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_0_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_AND(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_0_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_AND(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_1_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_EOR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_1_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_EOR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_1_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_EOR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_1_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_EOR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_1_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_EOR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_1_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_EOR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_1_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_EOR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_1_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_EOR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_2_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_SUB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_2_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_SUB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_2_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_SUB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_2_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_SUB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_2_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_SUB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_2_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_SUB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_2_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_SUB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_2_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_SUB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_3_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_3_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_3_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_3_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_3_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_3_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_3_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_3_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_4_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_4_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_4_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_4_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_4_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_4_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_4_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_4_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_5_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_5_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_5_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_5_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_5_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_5_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_5_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_5_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_6_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_6_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_6_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_6_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_6_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_6_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_6_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_6_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_7_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_7_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_7_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_7_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_7_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_7_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_7_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_7_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_8_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_TST(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_8_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_TST(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_8_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_TST(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_8_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_TST(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_8_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_TST(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_8_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_TST(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_8_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_TST(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_8_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_TST(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_9_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_TEQ(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_9_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_TEQ(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_9_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_TEQ(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_9_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_TEQ(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_9_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_TEQ(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_9_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_TEQ(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_9_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_TEQ(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_9_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_TEQ(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_A_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_CMP(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_A_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_CMP(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_A_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_CMP(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_A_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_CMP(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_A_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_CMP(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_A_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_CMP(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_A_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_CMP(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_A_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_CMP(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_B_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_CMN(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_B_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_CMN(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_B_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_CMN(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_B_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_CMN(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_B_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_CMN(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_B_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_CMN(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_B_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_CMN(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_B_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_CMN(cpu, rd, rn, op2, 0);
return; }
arm_data_processing_0_1_C_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_ORR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_C_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_ORR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_C_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_ORR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_C_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_ORR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_C_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_ORR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_C_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_ORR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_C_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_ORR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_C_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_ORR(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_D_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_MOV(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_D_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_MOV(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_D_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_MOV(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_D_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_MOV(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_D_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_MOV(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_D_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_MOV(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_D_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_MOV(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_D_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_MOV(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_E_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_BIC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_E_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_BIC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_E_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_BIC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_E_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_BIC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_E_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_BIC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_E_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_BIC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_E_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_BIC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_E_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_BIC(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_F_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_MVN(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_F_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_MVN(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_F_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_MVN(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_F_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_MVN(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_F_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_MVN(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_F_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_MVN(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_F_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_MVN(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_0_1_F_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 0);
}
alu_MVN(cpu, rd, rn, op2, 0);
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_0_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
alu_AND(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_0_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_AND(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_0_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
alu_AND(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_0_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_AND(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_0_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
alu_AND(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_0_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_AND(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_0_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 1) : alu_ROR(cpu, val, shift_amnt, 1);
}
alu_AND(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_0_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_AND(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_1_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
alu_EOR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_1_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_EOR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_1_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
alu_EOR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_1_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_EOR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_1_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
alu_EOR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_1_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_EOR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_1_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 1) : alu_ROR(cpu, val, shift_amnt, 1);
}
alu_EOR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_1_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_EOR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_2_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
alu_SUB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_2_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_SUB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_2_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
alu_SUB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_2_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_SUB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_2_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
alu_SUB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_2_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_SUB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_2_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 1) : alu_ROR(cpu, val, shift_amnt, 1);
}
alu_SUB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_2_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_SUB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_3_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_3_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_3_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_3_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_3_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_3_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_3_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 1) : alu_ROR(cpu, val, shift_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_3_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_4_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_4_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_4_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_4_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_4_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_4_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_4_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 1) : alu_ROR(cpu, val, shift_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_4_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_5_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_5_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_5_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_5_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_5_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_5_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_5_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 1) : alu_ROR(cpu, val, shift_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_5_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_6_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_6_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_6_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_6_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_6_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_6_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_6_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 1) : alu_ROR(cpu, val, shift_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_6_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_7_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_7_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_7_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_7_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_7_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_7_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_7_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 1) : alu_ROR(cpu, val, shift_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_7_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_8_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
alu_TST(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_8_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_TST(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_8_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
alu_TST(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_8_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_TST(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_8_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
alu_TST(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_8_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_TST(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_8_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 1) : alu_ROR(cpu, val, shift_amnt, 1);
}
alu_TST(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_8_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_TST(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_9_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
alu_TEQ(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_9_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_TEQ(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_9_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
alu_TEQ(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_9_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_TEQ(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_9_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
alu_TEQ(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_9_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_TEQ(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_9_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 1) : alu_ROR(cpu, val, shift_amnt, 1);
}
alu_TEQ(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_9_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_TEQ(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_A_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
alu_CMP(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_A_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_CMP(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_A_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
alu_CMP(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_A_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_CMP(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_A_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
alu_CMP(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_A_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_CMP(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_A_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 1) : alu_ROR(cpu, val, shift_amnt, 1);
}
alu_CMP(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_A_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_CMP(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_B_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
alu_CMN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_B_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_CMN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_B_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
alu_CMN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_B_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_CMN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_B_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
alu_CMN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_B_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_CMN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_B_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 1) : alu_ROR(cpu, val, shift_amnt, 1);
}
alu_CMN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_B_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_CMN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_0_C_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
alu_ORR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_C_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_ORR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_C_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
alu_ORR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_C_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_ORR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_C_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
alu_ORR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_C_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_ORR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_C_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 1) : alu_ROR(cpu, val, shift_amnt, 1);
}
alu_ORR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_C_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_ORR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_D_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
alu_MOV(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_D_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_MOV(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_D_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
alu_MOV(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_D_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_MOV(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_D_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
alu_MOV(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_D_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_MOV(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_D_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 1) : alu_ROR(cpu, val, shift_amnt, 1);
}
alu_MOV(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_D_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_MOV(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_E_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
alu_BIC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_E_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_BIC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_E_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
alu_BIC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_E_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_BIC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_E_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
alu_BIC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_E_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_BIC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_E_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 1) : alu_ROR(cpu, val, shift_amnt, 1);
}
alu_BIC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_E_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_BIC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_F_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
alu_MVN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_F_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSL(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_MVN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_F_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
alu_MVN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_F_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_LSR(cpu, val ,shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_MVN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_F_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
alu_MVN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_F_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ASR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_MVN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_F_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
op2 = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 1) : alu_ROR(cpu, val, shift_amnt, 1);
}
alu_MVN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_0_F_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
op2 = alu_ROR(cpu, val, shift_amnt, 1);
}
if(rn_idx == 15)
rn += 4;
alu_MVN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_0_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_AND(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_0_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_AND(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_0_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_AND(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_0_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_AND(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_0_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_AND(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_0_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_AND(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_0_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_AND(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_0_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_AND(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_1_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_EOR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_1_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_EOR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_1_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_EOR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_1_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_EOR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_1_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_EOR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_1_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_EOR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_1_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_EOR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_1_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_EOR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_2_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_SUB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_2_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_SUB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_2_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_SUB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_2_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_SUB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_2_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_SUB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_2_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_SUB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_2_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_SUB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_2_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_SUB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_3_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_3_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_3_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_3_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_3_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_3_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_3_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_3_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_RSB(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_4_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_4_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_4_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_4_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_4_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_4_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_4_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_4_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_ADD(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_5_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_5_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_5_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_5_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_5_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_5_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_5_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_5_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_ADC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_6_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_6_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_6_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_6_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_6_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_6_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_6_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_6_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_SBC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_7_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_7_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_7_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_7_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_7_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_7_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_7_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_7_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
bool old_carry = cpu->C_FLAG;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
cpu->C_FLAG = old_carry;
alu_RSC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_8_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_TST(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_8_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_TST(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_8_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_TST(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_8_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_TST(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_8_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_TST(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_8_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_TST(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_8_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_TST(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_8_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_TST(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_9_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_TEQ(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_9_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_TEQ(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_9_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_TEQ(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_9_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_TEQ(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_9_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_TEQ(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_9_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_TEQ(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_9_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_TEQ(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_9_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_TEQ(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_A_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_CMP(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_A_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_CMP(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_A_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_CMP(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_A_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_CMP(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_A_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_CMP(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_A_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_CMP(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_A_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_CMP(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_A_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_CMP(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_B_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_CMN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_B_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_CMN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_B_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_CMN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_B_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_CMN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_B_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_CMN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_B_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_CMN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_B_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_CMN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_B_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_CMN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
return; }
arm_data_processing_1_1_C_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_ORR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_C_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_ORR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_C_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_ORR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_C_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_ORR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_C_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_ORR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_C_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_ORR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_C_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_ORR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_C_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_ORR(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_D_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_MOV(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_D_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_MOV(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_D_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_MOV(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_D_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_MOV(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_D_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_MOV(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_D_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_MOV(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_D_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_MOV(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_D_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_MOV(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_E_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_BIC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_E_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_BIC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_E_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_BIC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_E_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_BIC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_E_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_BIC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_E_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_BIC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_E_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_BIC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_E_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_BIC(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_F_0:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_MVN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_F_1:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_MVN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_F_2:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_MVN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_F_3:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_MVN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_F_4:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_MVN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_F_5:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_MVN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_F_6:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_MVN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_data_processing_1_1_F_7:{
u8 rd_idx = (opcode >> 12) & 0xF;
u8 rn_idx = (opcode >> 16) & 0xF;
u32 rn = cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 op2;
{
u32 val = opcode & 0xFF;
u8 rot_amnt = (opcode >> 8) & 0xF;
rot_amnt <<= 1;
op2 = alu_ROR(cpu, val, rot_amnt, 1);
}
alu_MVN(cpu, rd, rn, op2, 1);
if(rd_idx == 15){
saveBankedReg(cpu);
cpu->CPSR = *getSPSR(cpu);
loadBankedReg(cpu);
}
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_halfword_data_transfer_0_0_0_0_0_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_0_0_0_0_0_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_0_0_0_0_1_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
addr += -offset;
*rn = addr;
return; }
arm_halfword_data_transfer_0_0_0_0_1_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
addr += -offset;
*rn = addr;
return; }
arm_halfword_data_transfer_0_0_0_0_2_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
cpu->fetch_seq = false;
writeByteAndTick(cpu, addr, *rd, false);
addr += -offset;
*rn = addr;
return; }
arm_halfword_data_transfer_0_0_0_0_2_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
cpu->fetch_seq = false;
writeByteAndTick(cpu, addr, *rd, false);
addr += -offset;
*rn = addr;
return; }
arm_halfword_data_transfer_0_0_0_0_3_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
addr += -offset;
*rn = addr;
return; }
arm_halfword_data_transfer_0_0_0_0_3_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
addr += -offset;
*rn = addr;
return; }
arm_halfword_data_transfer_0_0_0_1_0_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_0_0_0_1_0_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_0_0_0_1_1_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
addr += -offset;
*rn = addr;
return; }
arm_halfword_data_transfer_0_0_0_1_1_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
addr += -offset;
*rn = addr;
return; }
arm_halfword_data_transfer_0_0_0_1_2_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
cpu->fetch_seq = false;
writeByteAndTick(cpu, addr, *rd, false);
addr += -offset;
*rn = addr;
return; }
arm_halfword_data_transfer_0_0_0_1_2_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
cpu->fetch_seq = false;
writeByteAndTick(cpu, addr, *rd, false);
addr += -offset;
*rn = addr;
return; }
arm_halfword_data_transfer_0_0_0_1_3_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
addr += -offset;
*rn = addr;
return; }
arm_halfword_data_transfer_0_0_0_1_3_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
addr += -offset;
*rn = addr;
return; }
arm_halfword_data_transfer_0_0_1_0_0_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += -offset;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_0_0_1_0_0_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += -offset;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_0_0_1_0_1_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += -offset;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
return; }
arm_halfword_data_transfer_0_0_1_0_1_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += -offset;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
return; }
arm_halfword_data_transfer_0_0_1_0_2_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += -offset;
cpu->fetch_seq = false;
writeByteAndTick(cpu, addr, *rd, false);
return; }
arm_halfword_data_transfer_0_0_1_0_2_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += -offset;
cpu->fetch_seq = false;
writeByteAndTick(cpu, addr, *rd, false);
return; }
arm_halfword_data_transfer_0_0_1_0_3_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += -offset;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
return; }
arm_halfword_data_transfer_0_0_1_0_3_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += -offset;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
return; }
arm_halfword_data_transfer_0_0_1_1_0_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += -offset;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_0_0_1_1_0_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += -offset;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_0_0_1_1_1_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += -offset;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
*rn = addr;
return; }
arm_halfword_data_transfer_0_0_1_1_1_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += -offset;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
*rn = addr;
return; }
arm_halfword_data_transfer_0_0_1_1_2_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += -offset;
cpu->fetch_seq = false;
writeByteAndTick(cpu, addr, *rd, false);
*rn = addr;
return; }
arm_halfword_data_transfer_0_0_1_1_2_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += -offset;
cpu->fetch_seq = false;
writeByteAndTick(cpu, addr, *rd, false);
*rn = addr;
return; }
arm_halfword_data_transfer_0_0_1_1_3_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += -offset;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
*rn = addr;
return; }
arm_halfword_data_transfer_0_0_1_1_3_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += -offset;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
*rn = addr;
return; }
arm_halfword_data_transfer_0_1_0_0_0_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_0_1_0_0_0_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_0_1_0_0_1_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
addr += offset;
*rn = addr;
return; }
arm_halfword_data_transfer_0_1_0_0_1_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
addr += offset;
*rn = addr;
return; }
arm_halfword_data_transfer_0_1_0_0_2_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
cpu->fetch_seq = false;
writeByteAndTick(cpu, addr, *rd, false);
addr += offset;
*rn = addr;
return; }
arm_halfword_data_transfer_0_1_0_0_2_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
cpu->fetch_seq = false;
writeByteAndTick(cpu, addr, *rd, false);
addr += offset;
*rn = addr;
return; }
arm_halfword_data_transfer_0_1_0_0_3_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
addr += offset;
*rn = addr;
return; }
arm_halfword_data_transfer_0_1_0_0_3_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
addr += offset;
*rn = addr;
return; }
arm_halfword_data_transfer_0_1_0_1_0_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_0_1_0_1_0_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_0_1_0_1_1_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
addr += offset;
*rn = addr;
return; }
arm_halfword_data_transfer_0_1_0_1_1_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
addr += offset;
*rn = addr;
return; }
arm_halfword_data_transfer_0_1_0_1_2_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
cpu->fetch_seq = false;
writeByteAndTick(cpu, addr, *rd, false);
addr += offset;
*rn = addr;
return; }
arm_halfword_data_transfer_0_1_0_1_2_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
cpu->fetch_seq = false;
writeByteAndTick(cpu, addr, *rd, false);
addr += offset;
*rn = addr;
return; }
arm_halfword_data_transfer_0_1_0_1_3_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
addr += offset;
*rn = addr;
return; }
arm_halfword_data_transfer_0_1_0_1_3_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
addr += offset;
*rn = addr;
return; }
arm_halfword_data_transfer_0_1_1_0_0_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += offset;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_0_1_1_0_0_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += offset;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_0_1_1_0_1_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += offset;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
return; }
arm_halfword_data_transfer_0_1_1_0_1_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += offset;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
return; }
arm_halfword_data_transfer_0_1_1_0_2_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += offset;
cpu->fetch_seq = false;
writeByteAndTick(cpu, addr, *rd, false);
return; }
arm_halfword_data_transfer_0_1_1_0_2_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += offset;
cpu->fetch_seq = false;
writeByteAndTick(cpu, addr, *rd, false);
return; }
arm_halfword_data_transfer_0_1_1_0_3_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += offset;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
return; }
arm_halfword_data_transfer_0_1_1_0_3_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += offset;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
return; }
arm_halfword_data_transfer_0_1_1_1_0_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += offset;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_0_1_1_1_0_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += offset;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_0_1_1_1_1_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += offset;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
*rn = addr;
return; }
arm_halfword_data_transfer_0_1_1_1_1_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += offset;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
*rn = addr;
return; }
arm_halfword_data_transfer_0_1_1_1_2_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += offset;
cpu->fetch_seq = false;
writeByteAndTick(cpu, addr, *rd, false);
*rn = addr;
return; }
arm_halfword_data_transfer_0_1_1_1_2_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += offset;
cpu->fetch_seq = false;
writeByteAndTick(cpu, addr, *rd, false);
*rn = addr;
return; }
arm_halfword_data_transfer_0_1_1_1_3_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += offset;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
*rn = addr;
return; }
arm_halfword_data_transfer_0_1_1_1_3_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += offset;
cpu->fetch_seq = false;
writeHalfWordAndTick(cpu, addr, *rd, false);
*rn = addr;
return; }
arm_halfword_data_transfer_1_0_0_0_0_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_1_0_0_0_0_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_1_0_0_0_1_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
*rd = readHalfWordAndTick(cpu, addr, false);
if(addr & 1)
*rd = (*rd >> 8) | (*rd << 24);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_0_0_0_1_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
*rd = readHalfWordAndTick(cpu, addr, false);
if(addr & 1)
*rd = (*rd >> 8) | (*rd << 24);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_0_0_0_2_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_0_0_0_2_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_0_0_0_3_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
*rd = readHalfWordAndTick(cpu, addr, false);
if(*rd & 0x8000)
*rd |= 0xFFFF0000;
if(addr & 1)
*rd = (*rd >> 8) | (*rd & 0x00800000 ? 0xFF000000 : 0);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_0_0_0_3_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
*rd = readHalfWordAndTick(cpu, addr, false);
if(*rd & 0x8000)
*rd |= 0xFFFF0000;
if(addr & 1)
*rd = (*rd >> 8) | (*rd & 0x00800000 ? 0xFF000000 : 0);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_0_0_1_0_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_1_0_0_1_0_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_1_0_0_1_1_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
*rd = readHalfWordAndTick(cpu, addr, false);
if(addr & 1)
*rd = (*rd >> 8) | (*rd << 24);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_0_0_1_1_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
*rd = readHalfWordAndTick(cpu, addr, false);
if(addr & 1)
*rd = (*rd >> 8) | (*rd << 24);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_0_0_1_2_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_0_0_1_2_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_0_0_1_3_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
*rd = readHalfWordAndTick(cpu, addr, false);
if(*rd & 0x8000)
*rd |= 0xFFFF0000;
if(addr & 1)
*rd = (*rd >> 8) | (*rd & 0x00800000 ? 0xFF000000 : 0);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_0_0_1_3_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
*rd = readHalfWordAndTick(cpu, addr, false);
if(*rd & 0x8000)
*rd |= 0xFFFF0000;
if(addr & 1)
*rd = (*rd >> 8) | (*rd & 0x00800000 ? 0xFF000000 : 0);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_0_1_0_0_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += -offset;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_1_0_1_0_0_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += -offset;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_1_0_1_0_1_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += -offset;
*rd = readHalfWordAndTick(cpu, addr, false);
if(addr & 1)
*rd = (*rd >> 8) | (*rd << 24);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_halfword_data_transfer_1_0_1_0_1_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += -offset;
*rd = readHalfWordAndTick(cpu, addr, false);
if(addr & 1)
*rd = (*rd >> 8) | (*rd << 24);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_halfword_data_transfer_1_0_1_0_2_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
return; }
arm_halfword_data_transfer_1_0_1_0_2_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
return; }
arm_halfword_data_transfer_1_0_1_0_3_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += -offset;
*rd = readHalfWordAndTick(cpu, addr, false);
if(*rd & 0x8000)
*rd |= 0xFFFF0000;
if(addr & 1)
*rd = (*rd >> 8) | (*rd & 0x00800000 ? 0xFF000000 : 0);
return; }
arm_halfword_data_transfer_1_0_1_0_3_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += -offset;
*rd = readHalfWordAndTick(cpu, addr, false);
if(*rd & 0x8000)
*rd |= 0xFFFF0000;
if(addr & 1)
*rd = (*rd >> 8) | (*rd & 0x00800000 ? 0xFF000000 : 0);
return; }
arm_halfword_data_transfer_1_0_1_1_0_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += -offset;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_1_0_1_1_0_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += -offset;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_1_0_1_1_1_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += -offset;
*rd = readHalfWordAndTick(cpu, addr, false);
if(addr & 1)
*rd = (*rd >> 8) | (*rd << 24);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_0_1_1_1_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += -offset;
*rd = readHalfWordAndTick(cpu, addr, false);
if(addr & 1)
*rd = (*rd >> 8) | (*rd << 24);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_0_1_1_2_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_0_1_1_2_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_0_1_1_3_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += -offset;
*rd = readHalfWordAndTick(cpu, addr, false);
if(*rd & 0x8000)
*rd |= 0xFFFF0000;
if(addr & 1)
*rd = (*rd >> 8) | (*rd & 0x00800000 ? 0xFF000000 : 0);
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_0_1_1_3_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += -offset;
*rd = readHalfWordAndTick(cpu, addr, false);
if(*rd & 0x8000)
*rd |= 0xFFFF0000;
if(addr & 1)
*rd = (*rd >> 8) | (*rd & 0x00800000 ? 0xFF000000 : 0);
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_1_0_0_0_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_1_1_0_0_0_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_1_1_0_0_1_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
*rd = readHalfWordAndTick(cpu, addr, false);
if(addr & 1)
*rd = (*rd >> 8) | (*rd << 24);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_1_0_0_1_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
*rd = readHalfWordAndTick(cpu, addr, false);
if(addr & 1)
*rd = (*rd >> 8) | (*rd << 24);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_1_0_0_2_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_1_0_0_2_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_1_0_0_3_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
*rd = readHalfWordAndTick(cpu, addr, false);
if(*rd & 0x8000)
*rd |= 0xFFFF0000;
if(addr & 1)
*rd = (*rd >> 8) | (*rd & 0x00800000 ? 0xFF000000 : 0);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_1_0_0_3_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
*rd = readHalfWordAndTick(cpu, addr, false);
if(*rd & 0x8000)
*rd |= 0xFFFF0000;
if(addr & 1)
*rd = (*rd >> 8) | (*rd & 0x00800000 ? 0xFF000000 : 0);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_1_0_1_0_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_1_1_0_1_0_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_1_1_0_1_1_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
*rd = readHalfWordAndTick(cpu, addr, false);
if(addr & 1)
*rd = (*rd >> 8) | (*rd << 24);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_1_0_1_1_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
*rd = readHalfWordAndTick(cpu, addr, false);
if(addr & 1)
*rd = (*rd >> 8) | (*rd << 24);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_1_0_1_2_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_1_0_1_2_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_1_0_1_3_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
*rd = readHalfWordAndTick(cpu, addr, false);
if(*rd & 0x8000)
*rd |= 0xFFFF0000;
if(addr & 1)
*rd = (*rd >> 8) | (*rd & 0x00800000 ? 0xFF000000 : 0);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_1_0_1_3_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
*rd = readHalfWordAndTick(cpu, addr, false);
if(*rd & 0x8000)
*rd |= 0xFFFF0000;
if(addr & 1)
*rd = (*rd >> 8) | (*rd & 0x00800000 ? 0xFF000000 : 0);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_1_1_0_0_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += offset;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_1_1_1_0_0_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += offset;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_1_1_1_0_1_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += offset;
*rd = readHalfWordAndTick(cpu, addr, false);
if(addr & 1)
*rd = (*rd >> 8) | (*rd << 24);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_halfword_data_transfer_1_1_1_0_1_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += offset;
*rd = readHalfWordAndTick(cpu, addr, false);
if(addr & 1)
*rd = (*rd >> 8) | (*rd << 24);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_halfword_data_transfer_1_1_1_0_2_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
return; }
arm_halfword_data_transfer_1_1_1_0_2_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
return; }
arm_halfword_data_transfer_1_1_1_0_3_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += offset;
*rd = readHalfWordAndTick(cpu, addr, false);
if(*rd & 0x8000)
*rd |= 0xFFFF0000;
if(addr & 1)
*rd = (*rd >> 8) | (*rd & 0x00800000 ? 0xFF000000 : 0);
return; }
arm_halfword_data_transfer_1_1_1_0_3_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += offset;
*rd = readHalfWordAndTick(cpu, addr, false);
if(*rd & 0x8000)
*rd |= 0xFFFF0000;
if(addr & 1)
*rd = (*rd >> 8) | (*rd & 0x00800000 ? 0xFF000000 : 0);
return; }
arm_halfword_data_transfer_1_1_1_1_0_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += offset;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_1_1_1_1_0_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += offset;
alu_SWP(cpu, opcode);
return; }
arm_halfword_data_transfer_1_1_1_1_1_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += offset;
*rd = readHalfWordAndTick(cpu, addr, false);
if(addr & 1)
*rd = (*rd >> 8) | (*rd << 24);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_1_1_1_1_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += offset;
*rd = readHalfWordAndTick(cpu, addr, false);
if(addr & 1)
*rd = (*rd >> 8) | (*rd << 24);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_1_1_1_2_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_1_1_1_2_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_1_1_1_3_0:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = cpu->r[opcode & 0xF];
u32 addr = *rn;
addr += offset;
*rd = readHalfWordAndTick(cpu, addr, false);
if(*rd & 0x8000)
*rd |= 0xFFFF0000;
if(addr & 1)
*rd = (*rd >> 8) | (*rd & 0x00800000 ? 0xFF000000 : 0);
if(rn != rd)
*rn = addr;
return; }
arm_halfword_data_transfer_1_1_1_1_3_1:{
u32 offset;
u32* rd = &cpu->r[(opcode >> 12) & 0xF];
u32* rn = &cpu->r[(opcode >> 16) & 0xF];
offset = (opcode & 0xF) | (((opcode >> 8) & 0xF) << 4);
u32 addr = *rn;
addr += offset;
*rd = readHalfWordAndTick(cpu, addr, false);
if(*rd & 0x8000)
*rd |= 0xFFFF0000;
if(addr & 1)
*rd = (*rd >> 8) | (*rd & 0x00800000 ? 0xFF000000 : 0);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_0_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_0_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_0_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_0_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_0_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_0_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_0_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_0_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_0_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_0_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_0_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_0_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_0_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_0_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_0_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_0_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_1_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_1_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_1_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_1_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_1_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_1_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_1_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_1_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_1_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_1_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_1_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_1_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_1_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_1_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_1_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_0_1_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_0_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_0_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_0_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_0_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_0_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_0_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_0_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_0_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_0_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_0_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_0_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_0_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_0_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_0_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_0_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_0_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_1_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_1_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_1_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_1_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_1_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_1_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_1_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_1_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_1_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_1_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_1_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_1_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_1_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_1_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_1_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_0_1_1_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_0_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_0_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_0_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_0_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_0_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_0_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_0_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_0_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_0_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_0_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_0_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_0_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_0_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_0_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_0_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_0_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_1_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_1_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_1_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_1_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_1_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_1_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_1_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_1_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_1_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_1_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_1_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_1_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_1_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_1_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_1_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_0_1_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_0_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_0_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_0_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_0_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_0_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_0_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_0_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_0_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_0_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_0_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_0_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_0_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_0_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_0_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_0_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_0_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_1_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_1_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_1_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_1_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_1_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_1_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_1_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_1_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_1_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_1_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_1_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_1_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_1_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_1_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_1_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_0_1_1_1_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_0_0_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_0_0_0_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_0_0_0_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_0_0_0_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_0_0_0_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_0_0_0_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_0_0_0_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_0_0_0_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_0_0_0_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_0_1_0_0_0_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_0_1_0_0_0_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_0_1_0_0_0_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_0_1_0_0_0_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_0_1_0_0_0_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_0_1_0_0_0_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_0_1_0_0_0_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_0_1_0_0_1_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_0_1_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_0_1_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_0_1_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_0_1_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_0_1_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_0_1_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_0_1_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_0_1_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_0_1_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_0_1_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_0_1_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_0_1_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_0_1_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_0_1_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_0_1_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_1_0_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_0_1_0_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_0_1_0_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_0_1_0_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_0_1_0_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_0_1_0_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_0_1_0_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_0_1_0_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_0_1_0_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_0_1_0_1_0_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_0_1_0_1_0_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_0_1_0_1_0_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_0_1_0_1_0_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_0_1_0_1_0_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_0_1_0_1_0_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_0_1_0_1_0_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_0_1_0_1_1_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_1_1_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_1_1_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_1_1_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_1_1_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_1_1_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_1_1_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_1_1_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_1_1_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_1_1_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_1_1_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_1_1_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_1_1_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_1_1_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_1_1_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_0_1_1_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_0_0_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_1_0_0_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_1_0_0_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_1_0_0_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_1_0_0_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_1_0_0_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_1_0_0_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_1_0_0_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_1_0_0_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_0_1_1_0_0_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_0_1_1_0_0_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_0_1_1_0_0_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_0_1_1_0_0_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_0_1_1_0_0_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_0_1_1_0_0_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_0_1_1_0_0_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_0_1_1_0_1_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_0_1_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_0_1_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_0_1_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_0_1_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_0_1_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_0_1_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_0_1_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_0_1_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_0_1_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_0_1_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_0_1_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_0_1_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_0_1_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_0_1_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_0_1_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_1_0_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_1_1_0_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_1_1_0_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_1_1_0_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_1_1_0_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_1_1_0_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_1_1_0_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_1_1_0_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_0_1_1_1_0_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_0_1_1_1_0_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_0_1_1_1_0_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_0_1_1_1_0_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_0_1_1_1_0_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_0_1_1_1_0_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_0_1_1_1_0_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_0_1_1_1_0_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_0_1_1_1_1_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_1_1_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_1_1_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_1_1_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_1_1_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_1_1_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_1_1_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_1_1_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_1_1_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_1_1_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_1_1_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_1_1_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_1_1_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_1_1_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_1_1_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_0_1_1_1_1_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
offset = opcode & 0xFFF;
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_0_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_0_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_0_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_0_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_0_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_0_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_0_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_0_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_0_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_0_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_0_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_0_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_0_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_0_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_0_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_0_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_1_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_1_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_1_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_1_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_1_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_1_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_1_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_1_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_1_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_1_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_1_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_1_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_1_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_1_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_1_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_0_1_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_0_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_0_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_0_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_0_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_0_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_0_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_0_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_0_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_0_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_0_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_0_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_0_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_0_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_0_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_0_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_0_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_1_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_1_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_1_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_1_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_1_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_1_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_1_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_1_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += -offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_1_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_1_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_1_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_1_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_1_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_1_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_1_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_0_1_1_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += -offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_0_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_0_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_0_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_0_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_0_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_0_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_0_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_0_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_0_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_0_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_0_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_0_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_0_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_0_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_0_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_0_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_1_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_1_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_1_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_1_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_1_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_1_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_1_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_1_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_1_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_1_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_1_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_1_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_1_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_1_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_1_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_0_1_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_0_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_0_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_0_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_0_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_0_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_0_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_0_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_0_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_0_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_0_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_0_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_0_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_0_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_0_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_0_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_0_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_1_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_1_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_1_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_1_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_1_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_1_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_1_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_1_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
addr += offset;
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_1_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_1_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_1_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_1_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_1_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_1_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_1_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_0_1_1_1_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
addr += offset;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_0_0_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_0_0_0_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_0_0_0_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_0_0_0_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_0_0_0_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_0_0_0_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_0_0_0_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_0_0_0_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_0_0_0_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_1_1_0_0_0_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_1_1_0_0_0_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_1_1_0_0_0_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_1_1_0_0_0_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_1_1_0_0_0_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_1_1_0_0_0_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_1_1_0_0_0_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_1_1_0_0_1_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_0_1_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_0_1_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_0_1_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_0_1_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_0_1_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_0_1_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_0_1_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_0_1_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_0_1_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_0_1_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_0_1_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_0_1_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_0_1_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_0_1_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_0_1_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
addr += -offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_1_0_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_0_1_0_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_0_1_0_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_0_1_0_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_0_1_0_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_0_1_0_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_0_1_0_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_0_1_0_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_0_1_0_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_1_1_0_1_0_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_1_1_0_1_0_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_1_1_0_1_0_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_1_1_0_1_0_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_1_1_0_1_0_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_1_1_0_1_0_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_1_1_0_1_0_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_1_1_0_1_1_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_1_1_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_1_1_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_1_1_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_1_1_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_1_1_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_1_1_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_1_1_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
addr += -offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_1_1_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_1_1_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_1_1_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_1_1_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_1_1_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_1_1_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_1_1_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_0_1_1_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
addr += -offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_0_0_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_1_0_0_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_1_0_0_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_1_0_0_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_1_0_0_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_1_0_0_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_1_0_0_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_1_0_0_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_1_0_0_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_1_1_1_0_0_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_1_1_1_0_0_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_1_1_1_0_0_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_1_1_1_0_0_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_1_1_1_0_0_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_1_1_1_0_0_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_1_1_1_0_0_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
return; }
arm_single_data_transfer_1_1_1_0_1_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_0_1_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_0_1_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_0_1_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_0_1_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_0_1_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_0_1_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_0_1_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeWordAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_0_1_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_0_1_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_0_1_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_0_1_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_0_1_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_0_1_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_0_1_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_0_1_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
addr += offset;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rd_idx == 15)
arm7tdmi_pipeline_refill(cpu);
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_1_0_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_1_1_0_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_1_1_0_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_1_1_0_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_1_1_0_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_1_1_0_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_1_1_0_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_1_1_0_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
return; }
arm_single_data_transfer_1_1_1_1_0_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_1_1_1_1_0_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_1_1_1_1_0_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_1_1_1_1_0_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_1_1_1_1_0_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_1_1_1_1_0_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_1_1_1_1_0_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_1_1_1_1_0_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
return; }
arm_single_data_transfer_1_1_1_1_1_0_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_1_1_0_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_1_1_0_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_1_1_0_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_1_1_0_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_1_1_0_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_1_1_0_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_1_1_0_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
addr += offset;
cpu->fetch_seq = false;
u32 val = *rd;
if(rd_idx == 15)
val += 4;
writeByteAndTick(cpu, addr, val, false);
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_1_1_1_0:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_1_1_1_1:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSL(cpu, val, shift_amnt, 0);
}
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_1_1_1_2:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_1_1_1_3:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_LSR(cpu, val ,shift_amnt, 0);
}
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_1_1_1_4:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
shift_amnt = !shift_amnt ? 32 : shift_amnt;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_1_1_1_5:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ASR(cpu, val, shift_amnt, 0);
}
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_1_1_1_6:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = (opcode >> 7) & 0x1F;
offset = !shift_amnt ? alu_RRX(cpu, val, shift_amnt, 0) : alu_ROR(cpu, val, shift_amnt, 0);
}
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_single_data_transfer_1_1_1_1_1_1_7:{
u32 rn_idx = (opcode >> 16) & 0xF;
u32 rd_idx = (opcode >> 12) & 0xF;
u32* rn = &cpu->r[rn_idx];
u32* rd = &cpu->r[rd_idx];
u32 addr = *rn;
u32 offset;
{
u8 shift_amnt;
u32 val = cpu->r[opcode & 0xF];
shift_amnt = cpu->r[(opcode >> 8) & 0xF] & 0xFF;
cpu->cycles += I_CYCLES;
if((opcode & 0xF) == 15)
val += 4;
offset = alu_ROR(cpu, val, shift_amnt, 0);
}
addr += offset;
*rd = readByteAndTick(cpu, addr, false);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(rn != rd)
*rn = addr;
return; }
arm_block_data_transfer_0_0_0_0_0_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn - 0x3C, cpu->r[15] + 4, false);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn - (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
}
return; }
arm_block_data_transfer_0_0_0_0_0_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn - 0x3C, cpu->r[15] + 4, false);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn - (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
}
return; }
arm_block_data_transfer_0_0_0_0_1_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
}
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_0_0_0_0_1_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
}
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_0_0_0_1_0_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn - 0x3C, cpu->r[15] + 4, false);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn - (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
*rn = addr;
}
return; }
arm_block_data_transfer_0_0_0_1_0_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn - 0x3C, cpu->r[15] + 4, false);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn - (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
*rn = addr;
}
return; }
arm_block_data_transfer_0_0_0_1_1_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
}
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
if(!(reg_list & (1 << base_idx)))
*rn = addr;
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_0_0_0_1_1_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
}
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
if(!(reg_list & (1 << base_idx)))
*rn = addr;
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_0_0_1_0_0_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
saveBankedReg(cpu);
regs = cpu->usr_r;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn - 0x3C, cpu->r[15] + 4, false);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn - (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
loadBankedReg(cpu);
}
return; }
arm_block_data_transfer_0_0_1_0_0_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn - 0x3C, cpu->r[15] + 4, false);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn - (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
}
return; }
arm_block_data_transfer_0_0_1_0_1_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
saveBankedReg(cpu);
regs = cpu->usr_r;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
printf("S BIT ON ARM PUSH/POP NOT IMPLEMENTED\n");
}
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
loadBankedReg(cpu);
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_0_0_1_0_1_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
printf("S BIT ON ARM PUSH/POP NOT IMPLEMENTED\n");
}
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_0_0_1_1_0_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
saveBankedReg(cpu);
regs = cpu->usr_r;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn - 0x3C, cpu->r[15] + 4, false);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn - (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
loadBankedReg(cpu);
*rn = addr;
}
return; }
arm_block_data_transfer_0_0_1_1_0_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn - 0x3C, cpu->r[15] + 4, false);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn - (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
*rn = addr;
}
return; }
arm_block_data_transfer_0_0_1_1_1_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
saveBankedReg(cpu);
regs = cpu->usr_r;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
printf("S BIT ON ARM PUSH/POP NOT IMPLEMENTED\n");
}
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
loadBankedReg(cpu);
if(!(reg_list & (1 << base_idx)))
*rn = addr;
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_0_0_1_1_1_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
printf("S BIT ON ARM PUSH/POP NOT IMPLEMENTED\n");
}
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
if(!(reg_list & (1 << base_idx)))
*rn = addr;
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_0_1_0_0_0_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn + 0x00, cpu->r[15] + 4, false);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn + (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
addr += 4;
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
}
return; }
arm_block_data_transfer_0_1_0_0_0_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn + 0x00, cpu->r[15] + 4, false);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn + (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
addr += 4;
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
}
return; }
arm_block_data_transfer_0_1_0_0_1_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
}
addr += 4;
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_0_1_0_0_1_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
}
addr += 4;
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_0_1_0_1_0_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn + 0x00, cpu->r[15] + 4, false);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn + (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
addr += 4;
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
*rn = addr;
}
return; }
arm_block_data_transfer_0_1_0_1_0_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn + 0x00, cpu->r[15] + 4, false);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn + (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
addr += 4;
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
*rn = addr;
}
return; }
arm_block_data_transfer_0_1_0_1_1_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
}
addr += 4;
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
if(!(reg_list & (1 << base_idx)))
*rn = addr;
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_0_1_0_1_1_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
}
addr += 4;
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
if(!(reg_list & (1 << base_idx)))
*rn = addr;
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_0_1_1_0_0_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
saveBankedReg(cpu);
regs = cpu->usr_r;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn + 0x00, cpu->r[15] + 4, false);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn + (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
addr += 4;
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
loadBankedReg(cpu);
}
return; }
arm_block_data_transfer_0_1_1_0_0_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn + 0x00, cpu->r[15] + 4, false);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn + (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
addr += 4;
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
}
return; }
arm_block_data_transfer_0_1_1_0_1_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
saveBankedReg(cpu);
regs = cpu->usr_r;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
printf("S BIT ON ARM PUSH/POP NOT IMPLEMENTED\n");
}
addr += 4;
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
loadBankedReg(cpu);
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_0_1_1_0_1_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
printf("S BIT ON ARM PUSH/POP NOT IMPLEMENTED\n");
}
addr += 4;
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_0_1_1_1_0_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
saveBankedReg(cpu);
regs = cpu->usr_r;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn + 0x00, cpu->r[15] + 4, false);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn + (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
addr += 4;
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
loadBankedReg(cpu);
*rn = addr;
}
return; }
arm_block_data_transfer_0_1_1_1_0_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn + 0x00, cpu->r[15] + 4, false);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn + (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
addr += 4;
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
*rn = addr;
}
return; }
arm_block_data_transfer_0_1_1_1_1_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
saveBankedReg(cpu);
regs = cpu->usr_r;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
printf("S BIT ON ARM PUSH/POP NOT IMPLEMENTED\n");
}
addr += 4;
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
loadBankedReg(cpu);
if(!(reg_list & (1 << base_idx)))
*rn = addr;
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_0_1_1_1_1_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
printf("S BIT ON ARM PUSH/POP NOT IMPLEMENTED\n");
}
addr += 4;
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
if(!(reg_list & (1 << base_idx)))
*rn = addr;
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_1_0_0_0_0_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn - 0x40, cpu->r[15] + 4, false);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn - (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
addr += 4;
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
}
return; }
arm_block_data_transfer_1_0_0_0_0_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn - 0x40, cpu->r[15] + 4, false);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn - (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
addr += 4;
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
}
return; }
arm_block_data_transfer_1_0_0_0_1_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
}
addr += 4;
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_1_0_0_0_1_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
}
addr += 4;
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_1_0_0_1_0_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn - 0x40, cpu->r[15] + 4, false);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn - (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
addr += 4;
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
*rn = addr;
}
return; }
arm_block_data_transfer_1_0_0_1_0_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn - 0x40, cpu->r[15] + 4, false);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn - (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
addr += 4;
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
*rn = addr;
}
return; }
arm_block_data_transfer_1_0_0_1_1_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
}
addr += 4;
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
if(!(reg_list & (1 << base_idx)))
*rn = addr;
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_1_0_0_1_1_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
}
addr += 4;
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
if(!(reg_list & (1 << base_idx)))
*rn = addr;
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_1_0_1_0_0_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
saveBankedReg(cpu);
regs = cpu->usr_r;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn - 0x40, cpu->r[15] + 4, false);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn - (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
addr += 4;
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
loadBankedReg(cpu);
}
return; }
arm_block_data_transfer_1_0_1_0_0_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn - 0x40, cpu->r[15] + 4, false);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn - (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
addr += 4;
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
}
return; }
arm_block_data_transfer_1_0_1_0_1_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
saveBankedReg(cpu);
regs = cpu->usr_r;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
printf("S BIT ON ARM PUSH/POP NOT IMPLEMENTED\n");
}
addr += 4;
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
loadBankedReg(cpu);
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_1_0_1_0_1_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
printf("S BIT ON ARM PUSH/POP NOT IMPLEMENTED\n");
}
addr += 4;
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_1_0_1_1_0_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
saveBankedReg(cpu);
regs = cpu->usr_r;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn - 0x40, cpu->r[15] + 4, false);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn - (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
addr += 4;
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
loadBankedReg(cpu);
*rn = addr;
}
return; }
arm_block_data_transfer_1_0_1_1_0_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn - 0x40, cpu->r[15] + 4, false);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn - (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
addr += 4;
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
*rn = addr;
}
return; }
arm_block_data_transfer_1_0_1_1_1_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
saveBankedReg(cpu);
regs = cpu->usr_r;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
printf("S BIT ON ARM PUSH/POP NOT IMPLEMENTED\n");
}
addr += 4;
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
loadBankedReg(cpu);
if(!(reg_list & (1 << base_idx)))
*rn = addr;
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_1_0_1_1_1_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
addr -= reg_count*4;
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] -= 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
printf("S BIT ON ARM PUSH/POP NOT IMPLEMENTED\n");
}
addr += 4;
first_transfer = false;
}
addr -= reg_count*4;
reg_list = opcode & 0xFFFF;
if(!(reg_list & (1 << base_idx)))
*rn = addr;
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_1_1_0_0_0_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn + 0x04, cpu->r[15] + 4, false);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn + (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
}
return; }
arm_block_data_transfer_1_1_0_0_0_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn + 0x04, cpu->r[15] + 4, false);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn + (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
}
return; }
arm_block_data_transfer_1_1_0_0_1_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
}
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_1_1_0_0_1_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
}
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_1_1_0_1_0_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn + 0x04, cpu->r[15] + 4, false);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn + (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
*rn = addr;
}
return; }
arm_block_data_transfer_1_1_0_1_0_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn + 0x04, cpu->r[15] + 4, false);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn + (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
*rn = addr;
}
return; }
arm_block_data_transfer_1_1_0_1_1_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
}
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
if(!(reg_list & (1 << base_idx)))
*rn = addr;
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_1_1_0_1_1_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
}
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
if(!(reg_list & (1 << base_idx)))
*rn = addr;
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_1_1_1_0_0_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
saveBankedReg(cpu);
regs = cpu->usr_r;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn + 0x04, cpu->r[15] + 4, false);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn + (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
loadBankedReg(cpu);
}
return; }
arm_block_data_transfer_1_1_1_0_0_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn + 0x04, cpu->r[15] + 4, false);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn + (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
}
return; }
arm_block_data_transfer_1_1_1_0_1_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
saveBankedReg(cpu);
regs = cpu->usr_r;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
printf("S BIT ON ARM PUSH/POP NOT IMPLEMENTED\n");
}
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
loadBankedReg(cpu);
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_1_1_1_0_1_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
printf("S BIT ON ARM PUSH/POP NOT IMPLEMENTED\n");
}
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_1_1_1_1_0_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
saveBankedReg(cpu);
regs = cpu->usr_r;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn + 0x04, cpu->r[15] + 4, false);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn + (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
loadBankedReg(cpu);
*rn = addr;
}
return; }
arm_block_data_transfer_1_1_1_1_0_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
writeWordAndTick(cpu, *rn + 0x04, cpu->r[15] + 4, false);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
if(i == base_idx && !first_transfer) {
writeWordAndTick(cpu, addr, *rn + (reg_count << 2), false);
} else
writeWordAndTick(cpu, addr, i == 15 ? regs[i] + 4 : regs[i], false);
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
*rn = addr;
}
return; }
arm_block_data_transfer_1_1_1_1_1_0:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
saveBankedReg(cpu);
regs = cpu->usr_r;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
printf("S BIT ON ARM PUSH/POP NOT IMPLEMENTED\n");
}
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
loadBankedReg(cpu);
if(!(reg_list & (1 << base_idx)))
*rn = addr;
}
cpu->cycles += I_CYCLES;
return; }
arm_block_data_transfer_1_1_1_1_1_1:{
u8 base_idx = (opcode >> 16) & 0xF;
u32* rn = &cpu->r[base_idx];
u16 reg_list = opcode & 0xFFFF;
u32* regs = cpu->r;
u32 addr = *rn;
u32 reg_count = __builtin_popcount(reg_list);
cpu->fetch_seq = false;
if(!reg_count){
cpu->r[15] = readWordAndTick(cpu, *rn, false);
arm7tdmi_pipeline_refill(cpu);
cpu->r[base_idx] += 0x40;
} else {
bool first_transfer = true;
for(int i = 0; i < 16 && reg_list; i++){
bool should_transfer = reg_list & 1;
reg_list >>= 1;
if(!should_transfer)
continue;
addr += 4;
regs[i] = readWordAndTick(cpu, addr, !first_transfer);
if(i == 15){
arm7tdmi_pipeline_refill(cpu);
printf("S BIT ON ARM PUSH/POP NOT IMPLEMENTED\n");
}
first_transfer = false;
}
reg_list = opcode & 0xFFFF;
if(!(reg_list & (1 << base_idx)))
*rn = addr;
}
cpu->cycles += I_CYCLES;
return; }
arm_multiply_0_0:{
u32 rm = cpu->r[opcode & 0xF];
u32 rs = cpu->r[(opcode >> 8) & 0xF];
u32 rn = cpu->r[(opcode >> 12) & 0xF];
u32* rd = &cpu->r[(opcode >> 16) & 0xF];
*rd = ((i32)rm) * ((i32)rs);
if(!(rs & 0xFFFFFF00) || !((~rs) & 0xFFFFFF00))
cpu->cycles += 1;
else if(!(rs & 0xFFFF0000) || !((~rs) & 0xFFFF0000))
cpu->cycles += 2;
else if(!(rs & 0xFF000000) || !((~rs) & 0xFF000000))
cpu->cycles += 3;
else
cpu->cycles += 4;
cpu->fetch_seq = false;
return; }
arm_multiply_0_1:{
u32 rm = cpu->r[opcode & 0xF];
u32 rs = cpu->r[(opcode >> 8) & 0xF];
u32 rn = cpu->r[(opcode >> 12) & 0xF];
u32* rd = &cpu->r[(opcode >> 16) & 0xF];
*rd = ((i32)rm) * ((i32)rs);
if(!(rs & 0xFFFFFF00) || !((~rs) & 0xFFFFFF00))
cpu->cycles += 1;
else if(!(rs & 0xFFFF0000) || !((~rs) & 0xFFFF0000))
cpu->cycles += 2;
else if(!(rs & 0xFF000000) || !((~rs) & 0xFF000000))
cpu->cycles += 3;
else
cpu->cycles += 4;
cpu->fetch_seq = false;
cpu->Z_FLAG = !(*rd);
cpu->N_FLAG = *rd >> 31;
return; }
arm_multiply_1_0:{
u32 rm = cpu->r[opcode & 0xF];
u32 rs = cpu->r[(opcode >> 8) & 0xF];
u32 rn = cpu->r[(opcode >> 12) & 0xF];
u32* rd = &cpu->r[(opcode >> 16) & 0xF];
*rd = ((i32)rm) * ((i32)rs);
*rd += rn;
if(!(rs & 0xFFFFFF00) || !((~rs) & 0xFFFFFF00))
cpu->cycles += 2;
else if(!(rs & 0xFFFF0000) || !((~rs) & 0xFFFF0000))
cpu->cycles += 3;
else if(!(rs & 0xFF000000) || !((~rs) & 0xFF000000))
cpu->cycles += 4;
else
cpu->cycles += 5;
cpu->fetch_seq = false;
return; }
arm_multiply_1_1:{
u32 rm = cpu->r[opcode & 0xF];
u32 rs = cpu->r[(opcode >> 8) & 0xF];
u32 rn = cpu->r[(opcode >> 12) & 0xF];
u32* rd = &cpu->r[(opcode >> 16) & 0xF];
*rd = ((i32)rm) * ((i32)rs);
*rd += rn;
if(!(rs & 0xFFFFFF00) || !((~rs) & 0xFFFFFF00))
cpu->cycles += 2;
else if(!(rs & 0xFFFF0000) || !((~rs) & 0xFFFF0000))
cpu->cycles += 3;
else if(!(rs & 0xFF000000) || !((~rs) & 0xFF000000))
cpu->cycles += 4;
else
cpu->cycles += 5;
cpu->fetch_seq = false;
cpu->Z_FLAG = !(*rd);
cpu->N_FLAG = *rd >> 31;
return; }
arm_multiply_long_0_0_0:{
u32 rm = cpu->r[opcode & 0xF];
u32 rs = cpu->r[(opcode >> 8) & 0xF];
u32* rd_lo = &cpu->r[(opcode >> 12) & 0xF];
u32* rd_hi = &cpu->r[(opcode >> 16) & 0xF];
u64 result;
cpu->fetch_seq = false;
result = ((u64)rm) * ((u64)rs);
*rd_hi = result >> 32;
*rd_lo = result;
if(!(rs & 0xFFFFFF00))
cpu->cycles += 2;
else if(!(rs & 0xFFFF0000))
cpu->cycles += 3;
else if(!(rs & 0xFF000000))
cpu->cycles += 4;
else
cpu->cycles += 5;
return; }
arm_multiply_long_0_0_1:{
u32 rm = cpu->r[opcode & 0xF];
u32 rs = cpu->r[(opcode >> 8) & 0xF];
u32* rd_lo = &cpu->r[(opcode >> 12) & 0xF];
u32* rd_hi = &cpu->r[(opcode >> 16) & 0xF];
u64 result;
cpu->fetch_seq = false;
result = ((u64)rm) * ((u64)rs);
*rd_hi = result >> 32;
*rd_lo = result;
cpu->Z_FLAG = !result;
cpu->N_FLAG = result >> 63;
if(!(rs & 0xFFFFFF00))
cpu->cycles += 2;
else if(!(rs & 0xFFFF0000))
cpu->cycles += 3;
else if(!(rs & 0xFF000000))
cpu->cycles += 4;
else
cpu->cycles += 5;
return; }
arm_multiply_long_0_1_0:{
u32 rm = cpu->r[opcode & 0xF];
u32 rs = cpu->r[(opcode >> 8) & 0xF];
u32* rd_lo = &cpu->r[(opcode >> 12) & 0xF];
u32* rd_hi = &cpu->r[(opcode >> 16) & 0xF];
u64 result;
cpu->fetch_seq = false;
result = ((u64)rm) * ((u64)rs);
result += (((u64)*rd_hi) << 32) | (u64)(*rd_lo);
*rd_hi = result >> 32;
*rd_lo = result;
if(!(rs & 0xFFFFFF00))
cpu->cycles += 3;
else if(!(rs & 0xFFFF0000))
cpu->cycles += 4;
else if(!(rs & 0xFF000000))
cpu->cycles += 5;
else
cpu->cycles += 6;
return; }
arm_multiply_long_0_1_1:{
u32 rm = cpu->r[opcode & 0xF];
u32 rs = cpu->r[(opcode >> 8) & 0xF];
u32* rd_lo = &cpu->r[(opcode >> 12) & 0xF];
u32* rd_hi = &cpu->r[(opcode >> 16) & 0xF];
u64 result;
cpu->fetch_seq = false;
result = ((u64)rm) * ((u64)rs);
result += (((u64)*rd_hi) << 32) | (u64)(*rd_lo);
*rd_hi = result >> 32;
*rd_lo = result;
cpu->Z_FLAG = !result;
cpu->N_FLAG = result >> 63;
if(!(rs & 0xFFFFFF00))
cpu->cycles += 3;
else if(!(rs & 0xFFFF0000))
cpu->cycles += 4;
else if(!(rs & 0xFF000000))
cpu->cycles += 5;
else
cpu->cycles += 6;
return; }
arm_multiply_long_1_0_0:{
u32 rm = cpu->r[opcode & 0xF];
u32 rs = cpu->r[(opcode >> 8) & 0xF];
u32* rd_lo = &cpu->r[(opcode >> 12) & 0xF];
u32* rd_hi = &cpu->r[(opcode >> 16) & 0xF];
u64 result;
cpu->fetch_seq = false;
result = ((i64)(i32)rm) * ((i64)(i32)rs);
*rd_hi = result >> 32;
*rd_lo = result;
if(!(rs & 0xFFFFFF00) || !((~rs) & 0xFFFFFF00))
cpu->cycles += 2;
else if(!(rs & 0xFFFF0000) || !((~rs) & 0xFFFF0000))
cpu->cycles += 3;
else if(!(rs & 0xFF000000) || !((~rs) & 0xFF000000))
cpu->cycles += 4;
else
cpu->cycles += 5;
return; }
arm_multiply_long_1_0_1:{
u32 rm = cpu->r[opcode & 0xF];
u32 rs = cpu->r[(opcode >> 8) & 0xF];
u32* rd_lo = &cpu->r[(opcode >> 12) & 0xF];
u32* rd_hi = &cpu->r[(opcode >> 16) & 0xF];
u64 result;
cpu->fetch_seq = false;
result = ((i64)(i32)rm) * ((i64)(i32)rs);
*rd_hi = result >> 32;
*rd_lo = result;
cpu->Z_FLAG = !result;
cpu->N_FLAG = result >> 63;
if(!(rs & 0xFFFFFF00) || !((~rs) & 0xFFFFFF00))
cpu->cycles += 2;
else if(!(rs & 0xFFFF0000) || !((~rs) & 0xFFFF0000))
cpu->cycles += 3;
else if(!(rs & 0xFF000000) || !((~rs) & 0xFF000000))
cpu->cycles += 4;
else
cpu->cycles += 5;
return; }
arm_multiply_long_1_1_0:{
u32 rm = cpu->r[opcode & 0xF];
u32 rs = cpu->r[(opcode >> 8) & 0xF];
u32* rd_lo = &cpu->r[(opcode >> 12) & 0xF];
u32* rd_hi = &cpu->r[(opcode >> 16) & 0xF];
u64 result;
cpu->fetch_seq = false;
result = ((i64)(i32)rm) * ((i64)(i32)rs);
result += (((u64)*rd_hi) << 32) | (u64)(*rd_lo);
*rd_hi = result >> 32;
*rd_lo = result;
if(!(rs & 0xFFFFFF00) || !((~rs) & 0xFFFFFF00))
cpu->cycles += 3;
else if(!(rs & 0xFFFF0000) || !((~rs) & 0xFFFF0000))
cpu->cycles += 4;
else if(!(rs & 0xFF000000) || !((~rs) & 0xFF000000))
cpu->cycles += 5;
else
cpu->cycles += 6;
return; }
arm_multiply_long_1_1_1:{
u32 rm = cpu->r[opcode & 0xF];
u32 rs = cpu->r[(opcode >> 8) & 0xF];
u32* rd_lo = &cpu->r[(opcode >> 12) & 0xF];
u32* rd_hi = &cpu->r[(opcode >> 16) & 0xF];
u64 result;
cpu->fetch_seq = false;
result = ((i64)(i32)rm) * ((i64)(i32)rs);
result += (((u64)*rd_hi) << 32) | (u64)(*rd_lo);
*rd_hi = result >> 32;
*rd_lo = result;
cpu->Z_FLAG = !result;
cpu->N_FLAG = result >> 63;
if(!(rs & 0xFFFFFF00) || !((~rs) & 0xFFFFFF00))
cpu->cycles += 3;
else if(!(rs & 0xFFFF0000) || !((~rs) & 0xFFFF0000))
cpu->cycles += 4;
else if(!(rs & 0xFF000000) || !((~rs) & 0xFF000000))
cpu->cycles += 5;
else
cpu->cycles += 6;
return; }
arm_not_decoded:{
printf("ARM OPCODE NOT DECODED!\n");
}
}

