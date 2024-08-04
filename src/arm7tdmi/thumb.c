#include "arm7tdmi/arm7tdmi.h"
#include "arm7tdmi/thumb.h"
#include "arm7tdmi/arm7tdmi_util.h"

#include <stdio.h>
#include <stdlib.h>

void thumb_step(arm7tdmi_t* cpu){
u16 opcode = cpu->pipeline_opcode[0];
cpu->pipeline_opcode[0] = cpu->pipeline_opcode[1];
cpu->r[15] += 2;
cpu->pipeline_opcode[1] = readHalfWordAndTick(cpu, cpu->r[15], cpu->fetch_seq);
cpu->fetch_seq = true;

static void* thumb_table[1 << 10] = {&&thumb_move_shifted_register_0_0, &&thumb_move_shifted_register_1_0, &&thumb_move_shifted_register_2_0, &&thumb_move_shifted_register_3_0, &&thumb_move_shifted_register_4_0, &&thumb_move_shifted_register_5_0, &&thumb_move_shifted_register_6_0, &&thumb_move_shifted_register_7_0, &&thumb_move_shifted_register_8_0, &&thumb_move_shifted_register_9_0, &&thumb_move_shifted_register_A_0, &&thumb_move_shifted_register_B_0, &&thumb_move_shifted_register_C_0, &&thumb_move_shifted_register_D_0, &&thumb_move_shifted_register_E_0, &&thumb_move_shifted_register_F_0, &&thumb_move_shifted_register_10_0, &&thumb_move_shifted_register_11_0, &&thumb_move_shifted_register_12_0, &&thumb_move_shifted_register_13_0, &&thumb_move_shifted_register_14_0, &&thumb_move_shifted_register_15_0, &&thumb_move_shifted_register_16_0, &&thumb_move_shifted_register_17_0, &&thumb_move_shifted_register_18_0, &&thumb_move_shifted_register_19_0, &&thumb_move_shifted_register_1A_0, &&thumb_move_shifted_register_1B_0, &&thumb_move_shifted_register_1C_0, &&thumb_move_shifted_register_1D_0, &&thumb_move_shifted_register_1E_0, &&thumb_move_shifted_register_1F_0, &&thumb_move_shifted_register_0_1, &&thumb_move_shifted_register_1_1, &&thumb_move_shifted_register_2_1, &&thumb_move_shifted_register_3_1, &&thumb_move_shifted_register_4_1, &&thumb_move_shifted_register_5_1, &&thumb_move_shifted_register_6_1, &&thumb_move_shifted_register_7_1, &&thumb_move_shifted_register_8_1, &&thumb_move_shifted_register_9_1, &&thumb_move_shifted_register_A_1, &&thumb_move_shifted_register_B_1, &&thumb_move_shifted_register_C_1, &&thumb_move_shifted_register_D_1, &&thumb_move_shifted_register_E_1, &&thumb_move_shifted_register_F_1, &&thumb_move_shifted_register_10_1, &&thumb_move_shifted_register_11_1, &&thumb_move_shifted_register_12_1, &&thumb_move_shifted_register_13_1, &&thumb_move_shifted_register_14_1, &&thumb_move_shifted_register_15_1, &&thumb_move_shifted_register_16_1, &&thumb_move_shifted_register_17_1, &&thumb_move_shifted_register_18_1, &&thumb_move_shifted_register_19_1, &&thumb_move_shifted_register_1A_1, &&thumb_move_shifted_register_1B_1, &&thumb_move_shifted_register_1C_1, &&thumb_move_shifted_register_1D_1, &&thumb_move_shifted_register_1E_1, &&thumb_move_shifted_register_1F_1, &&thumb_move_shifted_register_0_2, &&thumb_move_shifted_register_1_2, &&thumb_move_shifted_register_2_2, &&thumb_move_shifted_register_3_2, &&thumb_move_shifted_register_4_2, &&thumb_move_shifted_register_5_2, &&thumb_move_shifted_register_6_2, &&thumb_move_shifted_register_7_2, &&thumb_move_shifted_register_8_2, &&thumb_move_shifted_register_9_2, &&thumb_move_shifted_register_A_2, &&thumb_move_shifted_register_B_2, &&thumb_move_shifted_register_C_2, &&thumb_move_shifted_register_D_2, &&thumb_move_shifted_register_E_2, &&thumb_move_shifted_register_F_2, &&thumb_move_shifted_register_10_2, &&thumb_move_shifted_register_11_2, &&thumb_move_shifted_register_12_2, &&thumb_move_shifted_register_13_2, &&thumb_move_shifted_register_14_2, &&thumb_move_shifted_register_15_2, &&thumb_move_shifted_register_16_2, &&thumb_move_shifted_register_17_2, &&thumb_move_shifted_register_18_2, &&thumb_move_shifted_register_19_2, &&thumb_move_shifted_register_1A_2, &&thumb_move_shifted_register_1B_2, &&thumb_move_shifted_register_1C_2, &&thumb_move_shifted_register_1D_2, &&thumb_move_shifted_register_1E_2, &&thumb_move_shifted_register_1F_2, &&thumb_add_subtract_0_0_0, &&thumb_add_subtract_0_0_1, &&thumb_add_subtract_0_0_2, &&thumb_add_subtract_0_0_3, &&thumb_add_subtract_0_0_4, &&thumb_add_subtract_0_0_5, &&thumb_add_subtract_0_0_6, &&thumb_add_subtract_0_0_7, &&thumb_add_subtract_0_1_0, &&thumb_add_subtract_0_1_1, &&thumb_add_subtract_0_1_2, &&thumb_add_subtract_0_1_3, &&thumb_add_subtract_0_1_4, &&thumb_add_subtract_0_1_5, &&thumb_add_subtract_0_1_6, &&thumb_add_subtract_0_1_7, &&thumb_add_subtract_1_0_0, &&thumb_add_subtract_1_0_1, &&thumb_add_subtract_1_0_2, &&thumb_add_subtract_1_0_3, &&thumb_add_subtract_1_0_4, &&thumb_add_subtract_1_0_5, &&thumb_add_subtract_1_0_6, &&thumb_add_subtract_1_0_7, &&thumb_add_subtract_1_1_0, &&thumb_add_subtract_1_1_1, &&thumb_add_subtract_1_1_2, &&thumb_add_subtract_1_1_3, &&thumb_add_subtract_1_1_4, &&thumb_add_subtract_1_1_5, &&thumb_add_subtract_1_1_6, &&thumb_add_subtract_1_1_7, &&thumb_misc_immediate_0_0, &&thumb_misc_immediate_0_0, &&thumb_misc_immediate_0_0, &&thumb_misc_immediate_0_0, &&thumb_misc_immediate_1_0, &&thumb_misc_immediate_1_0, &&thumb_misc_immediate_1_0, &&thumb_misc_immediate_1_0, &&thumb_misc_immediate_2_0, &&thumb_misc_immediate_2_0, &&thumb_misc_immediate_2_0, &&thumb_misc_immediate_2_0, &&thumb_misc_immediate_3_0, &&thumb_misc_immediate_3_0, &&thumb_misc_immediate_3_0, &&thumb_misc_immediate_3_0, &&thumb_misc_immediate_4_0, &&thumb_misc_immediate_4_0, &&thumb_misc_immediate_4_0, &&thumb_misc_immediate_4_0, &&thumb_misc_immediate_5_0, &&thumb_misc_immediate_5_0, &&thumb_misc_immediate_5_0, &&thumb_misc_immediate_5_0, &&thumb_misc_immediate_6_0, &&thumb_misc_immediate_6_0, &&thumb_misc_immediate_6_0, &&thumb_misc_immediate_6_0, &&thumb_misc_immediate_7_0, &&thumb_misc_immediate_7_0, &&thumb_misc_immediate_7_0, &&thumb_misc_immediate_7_0, &&thumb_misc_immediate_0_1, &&thumb_misc_immediate_0_1, &&thumb_misc_immediate_0_1, &&thumb_misc_immediate_0_1, &&thumb_misc_immediate_1_1, &&thumb_misc_immediate_1_1, &&thumb_misc_immediate_1_1, &&thumb_misc_immediate_1_1, &&thumb_misc_immediate_2_1, &&thumb_misc_immediate_2_1, &&thumb_misc_immediate_2_1, &&thumb_misc_immediate_2_1, &&thumb_misc_immediate_3_1, &&thumb_misc_immediate_3_1, &&thumb_misc_immediate_3_1, &&thumb_misc_immediate_3_1, &&thumb_misc_immediate_4_1, &&thumb_misc_immediate_4_1, &&thumb_misc_immediate_4_1, &&thumb_misc_immediate_4_1, &&thumb_misc_immediate_5_1, &&thumb_misc_immediate_5_1, &&thumb_misc_immediate_5_1, &&thumb_misc_immediate_5_1, &&thumb_misc_immediate_6_1, &&thumb_misc_immediate_6_1, &&thumb_misc_immediate_6_1, &&thumb_misc_immediate_6_1, &&thumb_misc_immediate_7_1, &&thumb_misc_immediate_7_1, &&thumb_misc_immediate_7_1, &&thumb_misc_immediate_7_1, &&thumb_misc_immediate_0_2, &&thumb_misc_immediate_0_2, &&thumb_misc_immediate_0_2, &&thumb_misc_immediate_0_2, &&thumb_misc_immediate_1_2, &&thumb_misc_immediate_1_2, &&thumb_misc_immediate_1_2, &&thumb_misc_immediate_1_2, &&thumb_misc_immediate_2_2, &&thumb_misc_immediate_2_2, &&thumb_misc_immediate_2_2, &&thumb_misc_immediate_2_2, &&thumb_misc_immediate_3_2, &&thumb_misc_immediate_3_2, &&thumb_misc_immediate_3_2, &&thumb_misc_immediate_3_2, &&thumb_misc_immediate_4_2, &&thumb_misc_immediate_4_2, &&thumb_misc_immediate_4_2, &&thumb_misc_immediate_4_2, &&thumb_misc_immediate_5_2, &&thumb_misc_immediate_5_2, &&thumb_misc_immediate_5_2, &&thumb_misc_immediate_5_2, &&thumb_misc_immediate_6_2, &&thumb_misc_immediate_6_2, &&thumb_misc_immediate_6_2, &&thumb_misc_immediate_6_2, &&thumb_misc_immediate_7_2, &&thumb_misc_immediate_7_2, &&thumb_misc_immediate_7_2, &&thumb_misc_immediate_7_2, &&thumb_misc_immediate_0_3, &&thumb_misc_immediate_0_3, &&thumb_misc_immediate_0_3, &&thumb_misc_immediate_0_3, &&thumb_misc_immediate_1_3, &&thumb_misc_immediate_1_3, &&thumb_misc_immediate_1_3, &&thumb_misc_immediate_1_3, &&thumb_misc_immediate_2_3, &&thumb_misc_immediate_2_3, &&thumb_misc_immediate_2_3, &&thumb_misc_immediate_2_3, &&thumb_misc_immediate_3_3, &&thumb_misc_immediate_3_3, &&thumb_misc_immediate_3_3, &&thumb_misc_immediate_3_3, &&thumb_misc_immediate_4_3, &&thumb_misc_immediate_4_3, &&thumb_misc_immediate_4_3, &&thumb_misc_immediate_4_3, &&thumb_misc_immediate_5_3, &&thumb_misc_immediate_5_3, &&thumb_misc_immediate_5_3, &&thumb_misc_immediate_5_3, &&thumb_misc_immediate_6_3, &&thumb_misc_immediate_6_3, &&thumb_misc_immediate_6_3, &&thumb_misc_immediate_6_3, &&thumb_misc_immediate_7_3, &&thumb_misc_immediate_7_3, &&thumb_misc_immediate_7_3, &&thumb_misc_immediate_7_3, &&thumb_alu_operations_0, &&thumb_alu_operations_1, &&thumb_alu_operations_2, &&thumb_alu_operations_3, &&thumb_alu_operations_4, &&thumb_alu_operations_5, &&thumb_alu_operations_6, &&thumb_alu_operations_7, &&thumb_alu_operations_8, &&thumb_alu_operations_9, &&thumb_alu_operations_A, &&thumb_alu_operations_B, &&thumb_alu_operations_C, &&thumb_alu_operations_D, &&thumb_alu_operations_E, &&thumb_alu_operations_F, &&thumb_hi_reg_op_0_0_0, &&thumb_hi_reg_op_0_1_0, &&thumb_hi_reg_op_1_0_0, &&thumb_hi_reg_op_1_1_0, &&thumb_hi_reg_op_0_0_1, &&thumb_hi_reg_op_0_1_1, &&thumb_hi_reg_op_1_0_1, &&thumb_hi_reg_op_1_1_1, &&thumb_hi_reg_op_0_0_2, &&thumb_hi_reg_op_0_1_2, &&thumb_hi_reg_op_1_0_2, &&thumb_hi_reg_op_1_1_2, &&thumb_hi_reg_op_0_0_3, &&thumb_hi_reg_op_0_1_3, &&thumb_hi_reg_op_1_0_3, &&thumb_hi_reg_op_1_1_3, &&thumb_pc_relative_load_0, &&thumb_pc_relative_load_0, &&thumb_pc_relative_load_0, &&thumb_pc_relative_load_0, &&thumb_pc_relative_load_1, &&thumb_pc_relative_load_1, &&thumb_pc_relative_load_1, &&thumb_pc_relative_load_1, &&thumb_pc_relative_load_2, &&thumb_pc_relative_load_2, &&thumb_pc_relative_load_2, &&thumb_pc_relative_load_2, &&thumb_pc_relative_load_3, &&thumb_pc_relative_load_3, &&thumb_pc_relative_load_3, &&thumb_pc_relative_load_3, &&thumb_pc_relative_load_4, &&thumb_pc_relative_load_4, &&thumb_pc_relative_load_4, &&thumb_pc_relative_load_4, &&thumb_pc_relative_load_5, &&thumb_pc_relative_load_5, &&thumb_pc_relative_load_5, &&thumb_pc_relative_load_5, &&thumb_pc_relative_load_6, &&thumb_pc_relative_load_6, &&thumb_pc_relative_load_6, &&thumb_pc_relative_load_6, &&thumb_pc_relative_load_7, &&thumb_pc_relative_load_7, &&thumb_pc_relative_load_7, &&thumb_pc_relative_load_7, &&thumb_load_store_register_offset_0_0_0, &&thumb_load_store_register_offset_0_0_1, &&thumb_load_store_register_offset_0_0_2, &&thumb_load_store_register_offset_0_0_3, &&thumb_load_store_register_offset_0_0_4, &&thumb_load_store_register_offset_0_0_5, &&thumb_load_store_register_offset_0_0_6, &&thumb_load_store_register_offset_0_0_7, &&thumb_load_store_sign_extended_0_0_0, &&thumb_load_store_sign_extended_0_0_1, &&thumb_load_store_sign_extended_0_0_2, &&thumb_load_store_sign_extended_0_0_3, &&thumb_load_store_sign_extended_0_0_4, &&thumb_load_store_sign_extended_0_0_5, &&thumb_load_store_sign_extended_0_0_6, &&thumb_load_store_sign_extended_0_0_7, &&thumb_load_store_register_offset_0_1_0, &&thumb_load_store_register_offset_0_1_1, &&thumb_load_store_register_offset_0_1_2, &&thumb_load_store_register_offset_0_1_3, &&thumb_load_store_register_offset_0_1_4, &&thumb_load_store_register_offset_0_1_5, &&thumb_load_store_register_offset_0_1_6, &&thumb_load_store_register_offset_0_1_7, &&thumb_load_store_sign_extended_0_1_0, &&thumb_load_store_sign_extended_0_1_1, &&thumb_load_store_sign_extended_0_1_2, &&thumb_load_store_sign_extended_0_1_3, &&thumb_load_store_sign_extended_0_1_4, &&thumb_load_store_sign_extended_0_1_5, &&thumb_load_store_sign_extended_0_1_6, &&thumb_load_store_sign_extended_0_1_7, &&thumb_load_store_register_offset_1_0_0, &&thumb_load_store_register_offset_1_0_1, &&thumb_load_store_register_offset_1_0_2, &&thumb_load_store_register_offset_1_0_3, &&thumb_load_store_register_offset_1_0_4, &&thumb_load_store_register_offset_1_0_5, &&thumb_load_store_register_offset_1_0_6, &&thumb_load_store_register_offset_1_0_7, &&thumb_load_store_sign_extended_1_0_0, &&thumb_load_store_sign_extended_1_0_1, &&thumb_load_store_sign_extended_1_0_2, &&thumb_load_store_sign_extended_1_0_3, &&thumb_load_store_sign_extended_1_0_4, &&thumb_load_store_sign_extended_1_0_5, &&thumb_load_store_sign_extended_1_0_6, &&thumb_load_store_sign_extended_1_0_7, &&thumb_load_store_register_offset_1_1_0, &&thumb_load_store_register_offset_1_1_1, &&thumb_load_store_register_offset_1_1_2, &&thumb_load_store_register_offset_1_1_3, &&thumb_load_store_register_offset_1_1_4, &&thumb_load_store_register_offset_1_1_5, &&thumb_load_store_register_offset_1_1_6, &&thumb_load_store_register_offset_1_1_7, &&thumb_load_store_sign_extended_1_1_0, &&thumb_load_store_sign_extended_1_1_1, &&thumb_load_store_sign_extended_1_1_2, &&thumb_load_store_sign_extended_1_1_3, &&thumb_load_store_sign_extended_1_1_4, &&thumb_load_store_sign_extended_1_1_5, &&thumb_load_store_sign_extended_1_1_6, &&thumb_load_store_sign_extended_1_1_7, &&thumb_load_store_immediate_offset_0_0_0, &&thumb_load_store_immediate_offset_0_0_1, &&thumb_load_store_immediate_offset_0_0_2, &&thumb_load_store_immediate_offset_0_0_3, &&thumb_load_store_immediate_offset_0_0_4, &&thumb_load_store_immediate_offset_0_0_5, &&thumb_load_store_immediate_offset_0_0_6, &&thumb_load_store_immediate_offset_0_0_7, &&thumb_load_store_immediate_offset_0_0_8, &&thumb_load_store_immediate_offset_0_0_9, &&thumb_load_store_immediate_offset_0_0_A, &&thumb_load_store_immediate_offset_0_0_B, &&thumb_load_store_immediate_offset_0_0_C, &&thumb_load_store_immediate_offset_0_0_D, &&thumb_load_store_immediate_offset_0_0_E, &&thumb_load_store_immediate_offset_0_0_F, &&thumb_load_store_immediate_offset_0_0_10, &&thumb_load_store_immediate_offset_0_0_11, &&thumb_load_store_immediate_offset_0_0_12, &&thumb_load_store_immediate_offset_0_0_13, &&thumb_load_store_immediate_offset_0_0_14, &&thumb_load_store_immediate_offset_0_0_15, &&thumb_load_store_immediate_offset_0_0_16, &&thumb_load_store_immediate_offset_0_0_17, &&thumb_load_store_immediate_offset_0_0_18, &&thumb_load_store_immediate_offset_0_0_19, &&thumb_load_store_immediate_offset_0_0_1A, &&thumb_load_store_immediate_offset_0_0_1B, &&thumb_load_store_immediate_offset_0_0_1C, &&thumb_load_store_immediate_offset_0_0_1D, &&thumb_load_store_immediate_offset_0_0_1E, &&thumb_load_store_immediate_offset_0_0_1F, &&thumb_load_store_immediate_offset_0_1_0, &&thumb_load_store_immediate_offset_0_1_1, &&thumb_load_store_immediate_offset_0_1_2, &&thumb_load_store_immediate_offset_0_1_3, &&thumb_load_store_immediate_offset_0_1_4, &&thumb_load_store_immediate_offset_0_1_5, &&thumb_load_store_immediate_offset_0_1_6, &&thumb_load_store_immediate_offset_0_1_7, &&thumb_load_store_immediate_offset_0_1_8, &&thumb_load_store_immediate_offset_0_1_9, &&thumb_load_store_immediate_offset_0_1_A, &&thumb_load_store_immediate_offset_0_1_B, &&thumb_load_store_immediate_offset_0_1_C, &&thumb_load_store_immediate_offset_0_1_D, &&thumb_load_store_immediate_offset_0_1_E, &&thumb_load_store_immediate_offset_0_1_F, &&thumb_load_store_immediate_offset_0_1_10, &&thumb_load_store_immediate_offset_0_1_11, &&thumb_load_store_immediate_offset_0_1_12, &&thumb_load_store_immediate_offset_0_1_13, &&thumb_load_store_immediate_offset_0_1_14, &&thumb_load_store_immediate_offset_0_1_15, &&thumb_load_store_immediate_offset_0_1_16, &&thumb_load_store_immediate_offset_0_1_17, &&thumb_load_store_immediate_offset_0_1_18, &&thumb_load_store_immediate_offset_0_1_19, &&thumb_load_store_immediate_offset_0_1_1A, &&thumb_load_store_immediate_offset_0_1_1B, &&thumb_load_store_immediate_offset_0_1_1C, &&thumb_load_store_immediate_offset_0_1_1D, &&thumb_load_store_immediate_offset_0_1_1E, &&thumb_load_store_immediate_offset_0_1_1F, &&thumb_load_store_immediate_offset_1_0_0, &&thumb_load_store_immediate_offset_1_0_1, &&thumb_load_store_immediate_offset_1_0_2, &&thumb_load_store_immediate_offset_1_0_3, &&thumb_load_store_immediate_offset_1_0_4, &&thumb_load_store_immediate_offset_1_0_5, &&thumb_load_store_immediate_offset_1_0_6, &&thumb_load_store_immediate_offset_1_0_7, &&thumb_load_store_immediate_offset_1_0_8, &&thumb_load_store_immediate_offset_1_0_9, &&thumb_load_store_immediate_offset_1_0_A, &&thumb_load_store_immediate_offset_1_0_B, &&thumb_load_store_immediate_offset_1_0_C, &&thumb_load_store_immediate_offset_1_0_D, &&thumb_load_store_immediate_offset_1_0_E, &&thumb_load_store_immediate_offset_1_0_F, &&thumb_load_store_immediate_offset_1_0_10, &&thumb_load_store_immediate_offset_1_0_11, &&thumb_load_store_immediate_offset_1_0_12, &&thumb_load_store_immediate_offset_1_0_13, &&thumb_load_store_immediate_offset_1_0_14, &&thumb_load_store_immediate_offset_1_0_15, &&thumb_load_store_immediate_offset_1_0_16, &&thumb_load_store_immediate_offset_1_0_17, &&thumb_load_store_immediate_offset_1_0_18, &&thumb_load_store_immediate_offset_1_0_19, &&thumb_load_store_immediate_offset_1_0_1A, &&thumb_load_store_immediate_offset_1_0_1B, &&thumb_load_store_immediate_offset_1_0_1C, &&thumb_load_store_immediate_offset_1_0_1D, &&thumb_load_store_immediate_offset_1_0_1E, &&thumb_load_store_immediate_offset_1_0_1F, &&thumb_load_store_immediate_offset_1_1_0, &&thumb_load_store_immediate_offset_1_1_1, &&thumb_load_store_immediate_offset_1_1_2, &&thumb_load_store_immediate_offset_1_1_3, &&thumb_load_store_immediate_offset_1_1_4, &&thumb_load_store_immediate_offset_1_1_5, &&thumb_load_store_immediate_offset_1_1_6, &&thumb_load_store_immediate_offset_1_1_7, &&thumb_load_store_immediate_offset_1_1_8, &&thumb_load_store_immediate_offset_1_1_9, &&thumb_load_store_immediate_offset_1_1_A, &&thumb_load_store_immediate_offset_1_1_B, &&thumb_load_store_immediate_offset_1_1_C, &&thumb_load_store_immediate_offset_1_1_D, &&thumb_load_store_immediate_offset_1_1_E, &&thumb_load_store_immediate_offset_1_1_F, &&thumb_load_store_immediate_offset_1_1_10, &&thumb_load_store_immediate_offset_1_1_11, &&thumb_load_store_immediate_offset_1_1_12, &&thumb_load_store_immediate_offset_1_1_13, &&thumb_load_store_immediate_offset_1_1_14, &&thumb_load_store_immediate_offset_1_1_15, &&thumb_load_store_immediate_offset_1_1_16, &&thumb_load_store_immediate_offset_1_1_17, &&thumb_load_store_immediate_offset_1_1_18, &&thumb_load_store_immediate_offset_1_1_19, &&thumb_load_store_immediate_offset_1_1_1A, &&thumb_load_store_immediate_offset_1_1_1B, &&thumb_load_store_immediate_offset_1_1_1C, &&thumb_load_store_immediate_offset_1_1_1D, &&thumb_load_store_immediate_offset_1_1_1E, &&thumb_load_store_immediate_offset_1_1_1F, &&thumb_load_store_halfword_0_0, &&thumb_load_store_halfword_0_2, &&thumb_load_store_halfword_0_4, &&thumb_load_store_halfword_0_6, &&thumb_load_store_halfword_0_8, &&thumb_load_store_halfword_0_A, &&thumb_load_store_halfword_0_C, &&thumb_load_store_halfword_0_E, &&thumb_load_store_halfword_0_10, &&thumb_load_store_halfword_0_12, &&thumb_load_store_halfword_0_14, &&thumb_load_store_halfword_0_16, &&thumb_load_store_halfword_0_18, &&thumb_load_store_halfword_0_1A, &&thumb_load_store_halfword_0_1C, &&thumb_load_store_halfword_0_1E, &&thumb_load_store_halfword_0_20, &&thumb_load_store_halfword_0_22, &&thumb_load_store_halfword_0_24, &&thumb_load_store_halfword_0_26, &&thumb_load_store_halfword_0_28, &&thumb_load_store_halfword_0_2A, &&thumb_load_store_halfword_0_2C, &&thumb_load_store_halfword_0_2E, &&thumb_load_store_halfword_0_30, &&thumb_load_store_halfword_0_32, &&thumb_load_store_halfword_0_34, &&thumb_load_store_halfword_0_36, &&thumb_load_store_halfword_0_38, &&thumb_load_store_halfword_0_3A, &&thumb_load_store_halfword_0_3C, &&thumb_load_store_halfword_0_3E, &&thumb_load_store_halfword_1_0, &&thumb_load_store_halfword_1_2, &&thumb_load_store_halfword_1_4, &&thumb_load_store_halfword_1_6, &&thumb_load_store_halfword_1_8, &&thumb_load_store_halfword_1_A, &&thumb_load_store_halfword_1_C, &&thumb_load_store_halfword_1_E, &&thumb_load_store_halfword_1_10, &&thumb_load_store_halfword_1_12, &&thumb_load_store_halfword_1_14, &&thumb_load_store_halfword_1_16, &&thumb_load_store_halfword_1_18, &&thumb_load_store_halfword_1_1A, &&thumb_load_store_halfword_1_1C, &&thumb_load_store_halfword_1_1E, &&thumb_load_store_halfword_1_20, &&thumb_load_store_halfword_1_22, &&thumb_load_store_halfword_1_24, &&thumb_load_store_halfword_1_26, &&thumb_load_store_halfword_1_28, &&thumb_load_store_halfword_1_2A, &&thumb_load_store_halfword_1_2C, &&thumb_load_store_halfword_1_2E, &&thumb_load_store_halfword_1_30, &&thumb_load_store_halfword_1_32, &&thumb_load_store_halfword_1_34, &&thumb_load_store_halfword_1_36, &&thumb_load_store_halfword_1_38, &&thumb_load_store_halfword_1_3A, &&thumb_load_store_halfword_1_3C, &&thumb_load_store_halfword_1_3E, &&thumb_sp_relative_load_store_0_0, &&thumb_sp_relative_load_store_0_0, &&thumb_sp_relative_load_store_0_0, &&thumb_sp_relative_load_store_0_0, &&thumb_sp_relative_load_store_0_1, &&thumb_sp_relative_load_store_0_1, &&thumb_sp_relative_load_store_0_1, &&thumb_sp_relative_load_store_0_1, &&thumb_sp_relative_load_store_0_2, &&thumb_sp_relative_load_store_0_2, &&thumb_sp_relative_load_store_0_2, &&thumb_sp_relative_load_store_0_2, &&thumb_sp_relative_load_store_0_3, &&thumb_sp_relative_load_store_0_3, &&thumb_sp_relative_load_store_0_3, &&thumb_sp_relative_load_store_0_3, &&thumb_sp_relative_load_store_0_4, &&thumb_sp_relative_load_store_0_4, &&thumb_sp_relative_load_store_0_4, &&thumb_sp_relative_load_store_0_4, &&thumb_sp_relative_load_store_0_5, &&thumb_sp_relative_load_store_0_5, &&thumb_sp_relative_load_store_0_5, &&thumb_sp_relative_load_store_0_5, &&thumb_sp_relative_load_store_0_6, &&thumb_sp_relative_load_store_0_6, &&thumb_sp_relative_load_store_0_6, &&thumb_sp_relative_load_store_0_6, &&thumb_sp_relative_load_store_0_7, &&thumb_sp_relative_load_store_0_7, &&thumb_sp_relative_load_store_0_7, &&thumb_sp_relative_load_store_0_7, &&thumb_sp_relative_load_store_1_0, &&thumb_sp_relative_load_store_1_0, &&thumb_sp_relative_load_store_1_0, &&thumb_sp_relative_load_store_1_0, &&thumb_sp_relative_load_store_1_1, &&thumb_sp_relative_load_store_1_1, &&thumb_sp_relative_load_store_1_1, &&thumb_sp_relative_load_store_1_1, &&thumb_sp_relative_load_store_1_2, &&thumb_sp_relative_load_store_1_2, &&thumb_sp_relative_load_store_1_2, &&thumb_sp_relative_load_store_1_2, &&thumb_sp_relative_load_store_1_3, &&thumb_sp_relative_load_store_1_3, &&thumb_sp_relative_load_store_1_3, &&thumb_sp_relative_load_store_1_3, &&thumb_sp_relative_load_store_1_4, &&thumb_sp_relative_load_store_1_4, &&thumb_sp_relative_load_store_1_4, &&thumb_sp_relative_load_store_1_4, &&thumb_sp_relative_load_store_1_5, &&thumb_sp_relative_load_store_1_5, &&thumb_sp_relative_load_store_1_5, &&thumb_sp_relative_load_store_1_5, &&thumb_sp_relative_load_store_1_6, &&thumb_sp_relative_load_store_1_6, &&thumb_sp_relative_load_store_1_6, &&thumb_sp_relative_load_store_1_6, &&thumb_sp_relative_load_store_1_7, &&thumb_sp_relative_load_store_1_7, &&thumb_sp_relative_load_store_1_7, &&thumb_sp_relative_load_store_1_7, &&thumb_load_address_0_0, &&thumb_load_address_0_0, &&thumb_load_address_0_0, &&thumb_load_address_0_0, &&thumb_load_address_0_1, &&thumb_load_address_0_1, &&thumb_load_address_0_1, &&thumb_load_address_0_1, &&thumb_load_address_0_2, &&thumb_load_address_0_2, &&thumb_load_address_0_2, &&thumb_load_address_0_2, &&thumb_load_address_0_3, &&thumb_load_address_0_3, &&thumb_load_address_0_3, &&thumb_load_address_0_3, &&thumb_load_address_0_4, &&thumb_load_address_0_4, &&thumb_load_address_0_4, &&thumb_load_address_0_4, &&thumb_load_address_0_5, &&thumb_load_address_0_5, &&thumb_load_address_0_5, &&thumb_load_address_0_5, &&thumb_load_address_0_6, &&thumb_load_address_0_6, &&thumb_load_address_0_6, &&thumb_load_address_0_6, &&thumb_load_address_0_7, &&thumb_load_address_0_7, &&thumb_load_address_0_7, &&thumb_load_address_0_7, &&thumb_load_address_1_0, &&thumb_load_address_1_0, &&thumb_load_address_1_0, &&thumb_load_address_1_0, &&thumb_load_address_1_1, &&thumb_load_address_1_1, &&thumb_load_address_1_1, &&thumb_load_address_1_1, &&thumb_load_address_1_2, &&thumb_load_address_1_2, &&thumb_load_address_1_2, &&thumb_load_address_1_2, &&thumb_load_address_1_3, &&thumb_load_address_1_3, &&thumb_load_address_1_3, &&thumb_load_address_1_3, &&thumb_load_address_1_4, &&thumb_load_address_1_4, &&thumb_load_address_1_4, &&thumb_load_address_1_4, &&thumb_load_address_1_5, &&thumb_load_address_1_5, &&thumb_load_address_1_5, &&thumb_load_address_1_5, &&thumb_load_address_1_6, &&thumb_load_address_1_6, &&thumb_load_address_1_6, &&thumb_load_address_1_6, &&thumb_load_address_1_7, &&thumb_load_address_1_7, &&thumb_load_address_1_7, &&thumb_load_address_1_7, &&thumb_add_offset_sp_0, &&thumb_add_offset_sp_0, &&thumb_add_offset_sp_1, &&thumb_add_offset_sp_1, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_push_pop_0_0, &&thumb_push_pop_0_0, &&thumb_push_pop_0_0, &&thumb_push_pop_0_0, &&thumb_push_pop_0_1, &&thumb_push_pop_0_1, &&thumb_push_pop_0_1, &&thumb_push_pop_0_1, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_push_pop_1_0, &&thumb_push_pop_1_0, &&thumb_push_pop_1_0, &&thumb_push_pop_1_0, &&thumb_push_pop_1_1, &&thumb_push_pop_1_1, &&thumb_push_pop_1_1, &&thumb_push_pop_1_1, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_multiple_load_store_0_0, &&thumb_multiple_load_store_0_0, &&thumb_multiple_load_store_0_0, &&thumb_multiple_load_store_0_0, &&thumb_multiple_load_store_1_0, &&thumb_multiple_load_store_1_0, &&thumb_multiple_load_store_1_0, &&thumb_multiple_load_store_1_0, &&thumb_multiple_load_store_2_0, &&thumb_multiple_load_store_2_0, &&thumb_multiple_load_store_2_0, &&thumb_multiple_load_store_2_0, &&thumb_multiple_load_store_3_0, &&thumb_multiple_load_store_3_0, &&thumb_multiple_load_store_3_0, &&thumb_multiple_load_store_3_0, &&thumb_multiple_load_store_4_0, &&thumb_multiple_load_store_4_0, &&thumb_multiple_load_store_4_0, &&thumb_multiple_load_store_4_0, &&thumb_multiple_load_store_5_0, &&thumb_multiple_load_store_5_0, &&thumb_multiple_load_store_5_0, &&thumb_multiple_load_store_5_0, &&thumb_multiple_load_store_6_0, &&thumb_multiple_load_store_6_0, &&thumb_multiple_load_store_6_0, &&thumb_multiple_load_store_6_0, &&thumb_multiple_load_store_7_0, &&thumb_multiple_load_store_7_0, &&thumb_multiple_load_store_7_0, &&thumb_multiple_load_store_7_0, &&thumb_multiple_load_store_0_1, &&thumb_multiple_load_store_0_1, &&thumb_multiple_load_store_0_1, &&thumb_multiple_load_store_0_1, &&thumb_multiple_load_store_1_1, &&thumb_multiple_load_store_1_1, &&thumb_multiple_load_store_1_1, &&thumb_multiple_load_store_1_1, &&thumb_multiple_load_store_2_1, &&thumb_multiple_load_store_2_1, &&thumb_multiple_load_store_2_1, &&thumb_multiple_load_store_2_1, &&thumb_multiple_load_store_3_1, &&thumb_multiple_load_store_3_1, &&thumb_multiple_load_store_3_1, &&thumb_multiple_load_store_3_1, &&thumb_multiple_load_store_4_1, &&thumb_multiple_load_store_4_1, &&thumb_multiple_load_store_4_1, &&thumb_multiple_load_store_4_1, &&thumb_multiple_load_store_5_1, &&thumb_multiple_load_store_5_1, &&thumb_multiple_load_store_5_1, &&thumb_multiple_load_store_5_1, &&thumb_multiple_load_store_6_1, &&thumb_multiple_load_store_6_1, &&thumb_multiple_load_store_6_1, &&thumb_multiple_load_store_6_1, &&thumb_multiple_load_store_7_1, &&thumb_multiple_load_store_7_1, &&thumb_multiple_load_store_7_1, &&thumb_multiple_load_store_7_1, &&thumb_conditional_branch_0, &&thumb_conditional_branch_0, &&thumb_conditional_branch_0, &&thumb_conditional_branch_0, &&thumb_conditional_branch_1, &&thumb_conditional_branch_1, &&thumb_conditional_branch_1, &&thumb_conditional_branch_1, &&thumb_conditional_branch_2, &&thumb_conditional_branch_2, &&thumb_conditional_branch_2, &&thumb_conditional_branch_2, &&thumb_conditional_branch_3, &&thumb_conditional_branch_3, &&thumb_conditional_branch_3, &&thumb_conditional_branch_3, &&thumb_conditional_branch_4, &&thumb_conditional_branch_4, &&thumb_conditional_branch_4, &&thumb_conditional_branch_4, &&thumb_conditional_branch_5, &&thumb_conditional_branch_5, &&thumb_conditional_branch_5, &&thumb_conditional_branch_5, &&thumb_conditional_branch_6, &&thumb_conditional_branch_6, &&thumb_conditional_branch_6, &&thumb_conditional_branch_6, &&thumb_conditional_branch_7, &&thumb_conditional_branch_7, &&thumb_conditional_branch_7, &&thumb_conditional_branch_7, &&thumb_conditional_branch_8, &&thumb_conditional_branch_8, &&thumb_conditional_branch_8, &&thumb_conditional_branch_8, &&thumb_conditional_branch_9, &&thumb_conditional_branch_9, &&thumb_conditional_branch_9, &&thumb_conditional_branch_9, &&thumb_conditional_branch_A, &&thumb_conditional_branch_A, &&thumb_conditional_branch_A, &&thumb_conditional_branch_A, &&thumb_conditional_branch_B, &&thumb_conditional_branch_B, &&thumb_conditional_branch_B, &&thumb_conditional_branch_B, &&thumb_conditional_branch_C, &&thumb_conditional_branch_C, &&thumb_conditional_branch_C, &&thumb_conditional_branch_C, &&thumb_conditional_branch_D, &&thumb_conditional_branch_D, &&thumb_conditional_branch_D, &&thumb_conditional_branch_D, &&thumb_conditional_branch_E, &&thumb_conditional_branch_E, &&thumb_conditional_branch_E, &&thumb_conditional_branch_E, &&thumb_software_interrupt, &&thumb_software_interrupt, &&thumb_software_interrupt, &&thumb_software_interrupt, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_unconditional_branch, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_not_encoded, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_0, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, &&thumb_long_branch_link_1, };

goto *thumb_table[opcode >> 6];

thumb_pc_relative_load_0:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[0];
u32 addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
*rd = readWordAndTick(cpu, addr, false);
return; }
thumb_pc_relative_load_1:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[1];
u32 addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
*rd = readWordAndTick(cpu, addr, false);
return; }
thumb_pc_relative_load_2:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[2];
u32 addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
*rd = readWordAndTick(cpu, addr, false);
return; }
thumb_pc_relative_load_3:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[3];
u32 addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
*rd = readWordAndTick(cpu, addr, false);
return; }
thumb_pc_relative_load_4:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[4];
u32 addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
*rd = readWordAndTick(cpu, addr, false);
return; }
thumb_pc_relative_load_5:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[5];
u32 addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
*rd = readWordAndTick(cpu, addr, false);
return; }
thumb_pc_relative_load_6:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[6];
u32 addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
*rd = readWordAndTick(cpu, addr, false);
return; }
thumb_pc_relative_load_7:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[7];
u32 addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
*rd = readWordAndTick(cpu, addr, false);
return; }
thumb_add_subtract_0_0_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, cpu->r[0], true);
return; }
thumb_add_subtract_0_0_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, cpu->r[1], true);
return; }
thumb_add_subtract_0_0_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, cpu->r[2], true);
return; }
thumb_add_subtract_0_0_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, cpu->r[3], true);
return; }
thumb_add_subtract_0_0_4:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, cpu->r[4], true);
return; }
thumb_add_subtract_0_0_5:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, cpu->r[5], true);
return; }
thumb_add_subtract_0_0_6:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, cpu->r[6], true);
return; }
thumb_add_subtract_0_0_7:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, cpu->r[7], true);
return; }
thumb_add_subtract_0_1_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, cpu->r[0], true);
return; }
thumb_add_subtract_0_1_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, cpu->r[1], true);
return; }
thumb_add_subtract_0_1_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, cpu->r[2], true);
return; }
thumb_add_subtract_0_1_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, cpu->r[3], true);
return; }
thumb_add_subtract_0_1_4:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, cpu->r[4], true);
return; }
thumb_add_subtract_0_1_5:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, cpu->r[5], true);
return; }
thumb_add_subtract_0_1_6:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, cpu->r[6], true);
return; }
thumb_add_subtract_0_1_7:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, cpu->r[7], true);
return; }
thumb_add_subtract_1_0_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, 0, true);
return; }
thumb_add_subtract_1_0_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, 1, true);
return; }
thumb_add_subtract_1_0_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, 2, true);
return; }
thumb_add_subtract_1_0_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, 3, true);
return; }
thumb_add_subtract_1_0_4:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, 4, true);
return; }
thumb_add_subtract_1_0_5:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, 5, true);
return; }
thumb_add_subtract_1_0_6:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, 6, true);
return; }
thumb_add_subtract_1_0_7:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, 7, true);
return; }
thumb_add_subtract_1_1_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, 0, true);
return; }
thumb_add_subtract_1_1_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, 1, true);
return; }
thumb_add_subtract_1_1_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, 2, true);
return; }
thumb_add_subtract_1_1_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, 3, true);
return; }
thumb_add_subtract_1_1_4:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, 4, true);
return; }
thumb_add_subtract_1_1_5:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, 5, true);
return; }
thumb_add_subtract_1_1_6:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, 6, true);
return; }
thumb_add_subtract_1_1_7:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, 7, true);
return; }
thumb_move_shifted_register_0_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 0, true), true);
return; }
thumb_move_shifted_register_0_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 32, true), true);
return; }
thumb_move_shifted_register_0_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 32, true), true);
return; }
thumb_move_shifted_register_0_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_1_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 1, true), true);
return; }
thumb_move_shifted_register_1_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 1, true), true);
return; }
thumb_move_shifted_register_1_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 1, true), true);
return; }
thumb_move_shifted_register_1_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_2_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 2, true), true);
return; }
thumb_move_shifted_register_2_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 2, true), true);
return; }
thumb_move_shifted_register_2_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 2, true), true);
return; }
thumb_move_shifted_register_2_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_3_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 3, true), true);
return; }
thumb_move_shifted_register_3_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 3, true), true);
return; }
thumb_move_shifted_register_3_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 3, true), true);
return; }
thumb_move_shifted_register_3_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_4_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 4, true), true);
return; }
thumb_move_shifted_register_4_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 4, true), true);
return; }
thumb_move_shifted_register_4_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 4, true), true);
return; }
thumb_move_shifted_register_4_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_5_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 5, true), true);
return; }
thumb_move_shifted_register_5_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 5, true), true);
return; }
thumb_move_shifted_register_5_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 5, true), true);
return; }
thumb_move_shifted_register_5_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_6_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 6, true), true);
return; }
thumb_move_shifted_register_6_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 6, true), true);
return; }
thumb_move_shifted_register_6_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 6, true), true);
return; }
thumb_move_shifted_register_6_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_7_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 7, true), true);
return; }
thumb_move_shifted_register_7_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 7, true), true);
return; }
thumb_move_shifted_register_7_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 7, true), true);
return; }
thumb_move_shifted_register_7_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_8_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 8, true), true);
return; }
thumb_move_shifted_register_8_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 8, true), true);
return; }
thumb_move_shifted_register_8_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 8, true), true);
return; }
thumb_move_shifted_register_8_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_9_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 9, true), true);
return; }
thumb_move_shifted_register_9_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 9, true), true);
return; }
thumb_move_shifted_register_9_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 9, true), true);
return; }
thumb_move_shifted_register_9_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_A_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 10, true), true);
return; }
thumb_move_shifted_register_A_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 10, true), true);
return; }
thumb_move_shifted_register_A_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 10, true), true);
return; }
thumb_move_shifted_register_A_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_B_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 11, true), true);
return; }
thumb_move_shifted_register_B_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 11, true), true);
return; }
thumb_move_shifted_register_B_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 11, true), true);
return; }
thumb_move_shifted_register_B_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_C_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 12, true), true);
return; }
thumb_move_shifted_register_C_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 12, true), true);
return; }
thumb_move_shifted_register_C_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 12, true), true);
return; }
thumb_move_shifted_register_C_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_D_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 13, true), true);
return; }
thumb_move_shifted_register_D_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 13, true), true);
return; }
thumb_move_shifted_register_D_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 13, true), true);
return; }
thumb_move_shifted_register_D_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_E_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 14, true), true);
return; }
thumb_move_shifted_register_E_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 14, true), true);
return; }
thumb_move_shifted_register_E_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 14, true), true);
return; }
thumb_move_shifted_register_E_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_F_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 15, true), true);
return; }
thumb_move_shifted_register_F_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 15, true), true);
return; }
thumb_move_shifted_register_F_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 15, true), true);
return; }
thumb_move_shifted_register_F_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_10_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 16, true), true);
return; }
thumb_move_shifted_register_10_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 16, true), true);
return; }
thumb_move_shifted_register_10_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 16, true), true);
return; }
thumb_move_shifted_register_10_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_11_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 17, true), true);
return; }
thumb_move_shifted_register_11_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 17, true), true);
return; }
thumb_move_shifted_register_11_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 17, true), true);
return; }
thumb_move_shifted_register_11_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_12_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 18, true), true);
return; }
thumb_move_shifted_register_12_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 18, true), true);
return; }
thumb_move_shifted_register_12_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 18, true), true);
return; }
thumb_move_shifted_register_12_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_13_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 19, true), true);
return; }
thumb_move_shifted_register_13_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 19, true), true);
return; }
thumb_move_shifted_register_13_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 19, true), true);
return; }
thumb_move_shifted_register_13_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_14_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 20, true), true);
return; }
thumb_move_shifted_register_14_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 20, true), true);
return; }
thumb_move_shifted_register_14_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 20, true), true);
return; }
thumb_move_shifted_register_14_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_15_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 21, true), true);
return; }
thumb_move_shifted_register_15_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 21, true), true);
return; }
thumb_move_shifted_register_15_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 21, true), true);
return; }
thumb_move_shifted_register_15_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_16_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 22, true), true);
return; }
thumb_move_shifted_register_16_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 22, true), true);
return; }
thumb_move_shifted_register_16_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 22, true), true);
return; }
thumb_move_shifted_register_16_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_17_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 23, true), true);
return; }
thumb_move_shifted_register_17_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 23, true), true);
return; }
thumb_move_shifted_register_17_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 23, true), true);
return; }
thumb_move_shifted_register_17_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_18_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 24, true), true);
return; }
thumb_move_shifted_register_18_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 24, true), true);
return; }
thumb_move_shifted_register_18_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 24, true), true);
return; }
thumb_move_shifted_register_18_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_19_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 25, true), true);
return; }
thumb_move_shifted_register_19_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 25, true), true);
return; }
thumb_move_shifted_register_19_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 25, true), true);
return; }
thumb_move_shifted_register_19_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_1A_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 26, true), true);
return; }
thumb_move_shifted_register_1A_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 26, true), true);
return; }
thumb_move_shifted_register_1A_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 26, true), true);
return; }
thumb_move_shifted_register_1A_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_1B_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 27, true), true);
return; }
thumb_move_shifted_register_1B_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 27, true), true);
return; }
thumb_move_shifted_register_1B_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 27, true), true);
return; }
thumb_move_shifted_register_1B_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_1C_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 28, true), true);
return; }
thumb_move_shifted_register_1C_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 28, true), true);
return; }
thumb_move_shifted_register_1C_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 28, true), true);
return; }
thumb_move_shifted_register_1C_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_1D_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 29, true), true);
return; }
thumb_move_shifted_register_1D_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 29, true), true);
return; }
thumb_move_shifted_register_1D_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 29, true), true);
return; }
thumb_move_shifted_register_1D_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_1E_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 30, true), true);
return; }
thumb_move_shifted_register_1E_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 30, true), true);
return; }
thumb_move_shifted_register_1E_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 30, true), true);
return; }
thumb_move_shifted_register_1E_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_move_shifted_register_1F_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 31, true), true);
return; }
thumb_move_shifted_register_1F_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 31, true), true);
return; }
thumb_move_shifted_register_1F_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 31, true), true);
return; }
thumb_move_shifted_register_1F_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
return; }
thumb_conditional_branch_0:{
u8 w8 = opcode & 0xFF;
if(cond_EQ(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
thumb_pipeline_refill(cpu);
return; }
thumb_conditional_branch_1:{
u8 w8 = opcode & 0xFF;
if(cond_NE(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
thumb_pipeline_refill(cpu);
return; }
thumb_conditional_branch_2:{
u8 w8 = opcode & 0xFF;
if(cond_CS(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
thumb_pipeline_refill(cpu);
return; }
thumb_conditional_branch_3:{
u8 w8 = opcode & 0xFF;
if(cond_CC(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
thumb_pipeline_refill(cpu);
return; }
thumb_conditional_branch_4:{
u8 w8 = opcode & 0xFF;
if(cond_MI(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
thumb_pipeline_refill(cpu);
return; }
thumb_conditional_branch_5:{
u8 w8 = opcode & 0xFF;
if(cond_PL(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
thumb_pipeline_refill(cpu);
return; }
thumb_conditional_branch_6:{
u8 w8 = opcode & 0xFF;
if(cond_VS(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
thumb_pipeline_refill(cpu);
return; }
thumb_conditional_branch_7:{
u8 w8 = opcode & 0xFF;
if(cond_VC(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
thumb_pipeline_refill(cpu);
return; }
thumb_conditional_branch_8:{
u8 w8 = opcode & 0xFF;
if(cond_HI(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
thumb_pipeline_refill(cpu);
return; }
thumb_conditional_branch_9:{
u8 w8 = opcode & 0xFF;
if(cond_LS(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
thumb_pipeline_refill(cpu);
return; }
thumb_conditional_branch_A:{
u8 w8 = opcode & 0xFF;
if(cond_GE(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
thumb_pipeline_refill(cpu);
return; }
thumb_conditional_branch_B:{
u8 w8 = opcode & 0xFF;
if(cond_LT(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
thumb_pipeline_refill(cpu);
return; }
thumb_conditional_branch_C:{
u8 w8 = opcode & 0xFF;
if(cond_GT(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
thumb_pipeline_refill(cpu);
return; }
thumb_conditional_branch_D:{
u8 w8 = opcode & 0xFF;
if(cond_LE(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
thumb_pipeline_refill(cpu);
return; }
thumb_conditional_branch_E:{
u8 w8 = opcode & 0xFF;
if(cond_AL(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
thumb_pipeline_refill(cpu);
return; }
thumb_conditional_branch_F:{
u8 w8 = opcode & 0xFF;
if(cond_Undefined(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
thumb_pipeline_refill(cpu);
return; }
thumb_unconditional_branch:{
u32 offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
thumb_pipeline_refill(cpu);
return; }
thumb_misc_immediate_0_0:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[0];
alu_MOV(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_0_1:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[0];
alu_CMP(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_0_2:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[0];
alu_ADD(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_0_3:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[0];
alu_SUB(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_1_0:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[1];
alu_MOV(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_1_1:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[1];
alu_CMP(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_1_2:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[1];
alu_ADD(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_1_3:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[1];
alu_SUB(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_2_0:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[2];
alu_MOV(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_2_1:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[2];
alu_CMP(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_2_2:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[2];
alu_ADD(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_2_3:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[2];
alu_SUB(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_3_0:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[3];
alu_MOV(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_3_1:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[3];
alu_CMP(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_3_2:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[3];
alu_ADD(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_3_3:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[3];
alu_SUB(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_4_0:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[4];
alu_MOV(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_4_1:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[4];
alu_CMP(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_4_2:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[4];
alu_ADD(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_4_3:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[4];
alu_SUB(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_5_0:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[5];
alu_MOV(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_5_1:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[5];
alu_CMP(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_5_2:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[5];
alu_ADD(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_5_3:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[5];
alu_SUB(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_6_0:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[6];
alu_MOV(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_6_1:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[6];
alu_CMP(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_6_2:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[6];
alu_ADD(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_6_3:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[6];
alu_SUB(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_7_0:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[7];
alu_MOV(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_7_1:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[7];
alu_CMP(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_7_2:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[7];
alu_ADD(cpu, rd, *rd, w8, true);
return; }
thumb_misc_immediate_7_3:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[7];
alu_SUB(cpu, rd, *rd, w8, true);
return; }
thumb_long_branch_link_0:{
u32 offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return; }
thumb_long_branch_link_1:{
u32 offset = (opcode & 0b11111111111);
u32 old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
thumb_pipeline_refill(cpu);
return; }
thumb_alu_operations_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_AND(cpu, rd, *rd, rs, true);
return; }
thumb_alu_operations_1:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_EOR(cpu, rd, *rd, rs, true);
return; }
thumb_alu_operations_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
alu_MOV(cpu, rd, 0, alu_LSL(cpu, *rd, rs, true), true);
return; }
thumb_alu_operations_3:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
alu_MOV(cpu, rd, 0, alu_LSR(cpu, *rd, rs, true), true);
return; }
thumb_alu_operations_4:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
alu_MOV(cpu, rd, 0, alu_ASR(cpu, *rd, rs, true), true);
return; }
thumb_alu_operations_5:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADC(cpu, rd, *rd, rs, true);
return; }
thumb_alu_operations_6:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_SBC(cpu, rd, *rd, rs, true);
return; }
thumb_alu_operations_7:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
alu_MOV(cpu, rd, 0, alu_ROR(cpu, *rd, rs, true), true);
return; }
thumb_alu_operations_8:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_TST(cpu, rd, *rd, rs, true);
return; }
thumb_alu_operations_9:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, 0, rs, true);
return; }
thumb_alu_operations_A:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_CMP(cpu, rd, *rd, rs, true);
return; }
thumb_alu_operations_B:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_CMN(cpu, rd, *rd, rs, true);
return; }
thumb_alu_operations_C:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_ORR(cpu, rd, *rd, rs, true);
return; }
thumb_alu_operations_D:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
u32 old_rd = *rd;
*rd = ((i32)*rd) * ((i32)rs);
cpu->Z_FLAG = !(*rd);
cpu->N_FLAG = *rd >> 31;
if(!(old_rd & 0xFFFFFF00) || !((~old_rd) & 0xFFFFFF00))
cpu->cycles += 1;
else if(!(old_rd & 0xFFFF0000) || !((~old_rd) & 0xFFFF0000))
cpu->cycles += 2;
else if(!(old_rd & 0xFF000000) || !((~old_rd) & 0xFF000000))
cpu->cycles += 3;
else
cpu->cycles += 4;
cpu->fetch_seq = false;
return; }
thumb_alu_operations_E:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_BIC(cpu, rd, *rd, rs, true);
return; }
thumb_alu_operations_F:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rs = cpu->r[(opcode >> 3) & 0b111];
alu_MVN(cpu, rd, *rd, rs, true);
return; }
thumb_load_store_immediate_offset_0_0_0:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 0, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_1:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 4, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_2:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 8, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_3:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 12, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_4:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 16, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_5:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 20, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_6:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 24, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_7:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 28, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_8:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 32, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_9:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 36, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_A:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 40, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_B:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 44, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_C:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 48, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_D:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 52, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_E:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 56, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_F:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 60, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_10:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 64, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_11:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 68, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_12:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 72, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_13:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 76, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_14:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 80, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_15:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 84, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_16:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 88, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_17:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 92, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_18:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 96, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_19:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 100, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_1A:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 104, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_1B:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 108, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_1C:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 112, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_1D:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 116, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_1E:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 120, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_0_1F:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeWordAndTick(cpu, rb + 124, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_0:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (0 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_1:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (1 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_2:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (2 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_3:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (3 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_4:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (4 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_5:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (5 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_6:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (6 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_7:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (7 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_8:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (8 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_9:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (9 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_A:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (10 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_B:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (11 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_C:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (12 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_D:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (13 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_E:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (14 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_F:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (15 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_10:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (16 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_11:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (17 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_12:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (18 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_13:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (19 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_14:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (20 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_15:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (21 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_16:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (22 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_17:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (23 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_18:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (24 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_19:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (25 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_1A:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (26 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_1B:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (27 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_1C:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (28 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_1D:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (29 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_1E:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (30 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_0_1_1F:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
u32 addr = rb + (31 << 2);
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_0:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 0, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_1:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 1, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_2:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 2, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_3:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 3, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_4:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 4, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_5:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 5, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_6:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 6, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_7:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 7, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_8:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 8, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_9:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 9, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_A:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 10, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_B:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 11, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_C:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 12, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_D:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 13, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_E:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 14, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_F:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 15, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_10:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 16, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_11:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 17, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_12:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 18, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_13:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 19, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_14:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 20, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_15:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 21, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_16:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 22, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_17:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 23, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_18:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 24, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_19:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 25, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_1A:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 26, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_1B:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 27, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_1C:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 28, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_1D:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 29, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_1E:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 30, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_0_1F:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
writeByteAndTick(cpu, rb + 31, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_0:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 0, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_1:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 1, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_2:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 2, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_3:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_4:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 4, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_5:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 5, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_6:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 6, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_7:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 7, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_8:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 8, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_9:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 9, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_A:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 10, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_B:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 11, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_C:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 12, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_D:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 13, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_E:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 14, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_F:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 15, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_10:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 16, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_11:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 17, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_12:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 18, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_13:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 19, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_14:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 20, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_15:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 21, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_16:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 22, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_17:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 23, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_18:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 24, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_19:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 25, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_1A:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 26, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_1B:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 27, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_1C:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 28, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_1D:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 29, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_1E:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 30, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_immediate_offset_1_1_1F:{
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, rb + 31, false);
cpu->fetch_seq = false;
return; }
thumb_multiple_load_store_0_0:{
u32 base = cpu->r[0];
u8 rlist = opcode & 0xFF;
cpu->fetch_seq = false;
u8 count = 0xFF;
if(!rlist){
writeWordAndTick(cpu, base, cpu->r[15] + 2, false);
cpu->r[0] += 0x40;
} else{
u8 rlist_size = __builtin_popcount(rlist);
bool first_transfer = true;
while(rlist){
bool should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 0 && !first_transfer)writeWordAndTick(cpu, base, cpu->r[count] + (rlist_size << 2), true);
else
writeWordAndTick(cpu, base, cpu->r[count], true);
base += 4;
first_transfer = false;
}
cpu->r[0] = base;
}
return; }
thumb_multiple_load_store_0_1:{
u32 base = cpu->r[0];
u8 rlist = opcode & 0xFF;
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
u8 count = 0xFF;
if(!rlist){
cpu->r[15] = readWordAndTick(cpu, base, false);
thumb_pipeline_refill(cpu);
cpu->r[0] += 0x40;
} else{
u8 rlist_size = __builtin_popcount(rlist);
bool first_transfer = true;
while(rlist){
bool should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = readWordAndTick(cpu, base, !first_transfer);
base += 4;
first_transfer = false;
}
cpu->r[0] = base;
}
return; }
thumb_multiple_load_store_1_0:{
u32 base = cpu->r[1];
u8 rlist = opcode & 0xFF;
cpu->fetch_seq = false;
u8 count = 0xFF;
if(!rlist){
writeWordAndTick(cpu, base, cpu->r[15] + 2, false);
cpu->r[1] += 0x40;
} else{
u8 rlist_size = __builtin_popcount(rlist);
bool first_transfer = true;
while(rlist){
bool should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 1 && !first_transfer)writeWordAndTick(cpu, base, cpu->r[count] + (rlist_size << 2), true);
else
writeWordAndTick(cpu, base, cpu->r[count], true);
base += 4;
first_transfer = false;
}
cpu->r[1] = base;
}
return; }
thumb_multiple_load_store_1_1:{
u32 base = cpu->r[1];
u8 rlist = opcode & 0xFF;
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
u8 count = 0xFF;
if(!rlist){
cpu->r[15] = readWordAndTick(cpu, base, false);
thumb_pipeline_refill(cpu);
cpu->r[1] += 0x40;
} else{
u8 rlist_size = __builtin_popcount(rlist);
bool first_transfer = true;
while(rlist){
bool should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = readWordAndTick(cpu, base, !first_transfer);
base += 4;
first_transfer = false;
}
cpu->r[1] = base;
}
return; }
thumb_multiple_load_store_2_0:{
u32 base = cpu->r[2];
u8 rlist = opcode & 0xFF;
cpu->fetch_seq = false;
u8 count = 0xFF;
if(!rlist){
writeWordAndTick(cpu, base, cpu->r[15] + 2, false);
cpu->r[2] += 0x40;
} else{
u8 rlist_size = __builtin_popcount(rlist);
bool first_transfer = true;
while(rlist){
bool should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 2 && !first_transfer)writeWordAndTick(cpu, base, cpu->r[count] + (rlist_size << 2), true);
else
writeWordAndTick(cpu, base, cpu->r[count], true);
base += 4;
first_transfer = false;
}
cpu->r[2] = base;
}
return; }
thumb_multiple_load_store_2_1:{
u32 base = cpu->r[2];
u8 rlist = opcode & 0xFF;
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
u8 count = 0xFF;
if(!rlist){
cpu->r[15] = readWordAndTick(cpu, base, false);
thumb_pipeline_refill(cpu);
cpu->r[2] += 0x40;
} else{
u8 rlist_size = __builtin_popcount(rlist);
bool first_transfer = true;
while(rlist){
bool should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = readWordAndTick(cpu, base, !first_transfer);
base += 4;
first_transfer = false;
}
cpu->r[2] = base;
}
return; }
thumb_multiple_load_store_3_0:{
u32 base = cpu->r[3];
u8 rlist = opcode & 0xFF;
cpu->fetch_seq = false;
u8 count = 0xFF;
if(!rlist){
writeWordAndTick(cpu, base, cpu->r[15] + 2, false);
cpu->r[3] += 0x40;
} else{
u8 rlist_size = __builtin_popcount(rlist);
bool first_transfer = true;
while(rlist){
bool should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 3 && !first_transfer)writeWordAndTick(cpu, base, cpu->r[count] + (rlist_size << 2), true);
else
writeWordAndTick(cpu, base, cpu->r[count], true);
base += 4;
first_transfer = false;
}
cpu->r[3] = base;
}
return; }
thumb_multiple_load_store_3_1:{
u32 base = cpu->r[3];
u8 rlist = opcode & 0xFF;
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
u8 count = 0xFF;
if(!rlist){
cpu->r[15] = readWordAndTick(cpu, base, false);
thumb_pipeline_refill(cpu);
cpu->r[3] += 0x40;
} else{
u8 rlist_size = __builtin_popcount(rlist);
bool first_transfer = true;
while(rlist){
bool should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = readWordAndTick(cpu, base, !first_transfer);
base += 4;
first_transfer = false;
}
cpu->r[3] = base;
}
return; }
thumb_multiple_load_store_4_0:{
u32 base = cpu->r[4];
u8 rlist = opcode & 0xFF;
cpu->fetch_seq = false;
u8 count = 0xFF;
if(!rlist){
writeWordAndTick(cpu, base, cpu->r[15] + 2, false);
cpu->r[4] += 0x40;
} else{
u8 rlist_size = __builtin_popcount(rlist);
bool first_transfer = true;
while(rlist){
bool should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 4 && !first_transfer)writeWordAndTick(cpu, base, cpu->r[count] + (rlist_size << 2), true);
else
writeWordAndTick(cpu, base, cpu->r[count], true);
base += 4;
first_transfer = false;
}
cpu->r[4] = base;
}
return; }
thumb_multiple_load_store_4_1:{
u32 base = cpu->r[4];
u8 rlist = opcode & 0xFF;
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
u8 count = 0xFF;
if(!rlist){
cpu->r[15] = readWordAndTick(cpu, base, false);
thumb_pipeline_refill(cpu);
cpu->r[4] += 0x40;
} else{
u8 rlist_size = __builtin_popcount(rlist);
bool first_transfer = true;
while(rlist){
bool should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = readWordAndTick(cpu, base, !first_transfer);
base += 4;
first_transfer = false;
}
cpu->r[4] = base;
}
return; }
thumb_multiple_load_store_5_0:{
u32 base = cpu->r[5];
u8 rlist = opcode & 0xFF;
cpu->fetch_seq = false;
u8 count = 0xFF;
if(!rlist){
writeWordAndTick(cpu, base, cpu->r[15] + 2, false);
cpu->r[5] += 0x40;
} else{
u8 rlist_size = __builtin_popcount(rlist);
bool first_transfer = true;
while(rlist){
bool should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 5 && !first_transfer)writeWordAndTick(cpu, base, cpu->r[count] + (rlist_size << 2), true);
else
writeWordAndTick(cpu, base, cpu->r[count], true);
base += 4;
first_transfer = false;
}
cpu->r[5] = base;
}
return; }
thumb_multiple_load_store_5_1:{
u32 base = cpu->r[5];
u8 rlist = opcode & 0xFF;
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
u8 count = 0xFF;
if(!rlist){
cpu->r[15] = readWordAndTick(cpu, base, false);
thumb_pipeline_refill(cpu);
cpu->r[5] += 0x40;
} else{
u8 rlist_size = __builtin_popcount(rlist);
bool first_transfer = true;
while(rlist){
bool should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = readWordAndTick(cpu, base, !first_transfer);
base += 4;
first_transfer = false;
}
cpu->r[5] = base;
}
return; }
thumb_multiple_load_store_6_0:{
u32 base = cpu->r[6];
u8 rlist = opcode & 0xFF;
cpu->fetch_seq = false;
u8 count = 0xFF;
if(!rlist){
writeWordAndTick(cpu, base, cpu->r[15] + 2, false);
cpu->r[6] += 0x40;
} else{
u8 rlist_size = __builtin_popcount(rlist);
bool first_transfer = true;
while(rlist){
bool should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 6 && !first_transfer)writeWordAndTick(cpu, base, cpu->r[count] + (rlist_size << 2), true);
else
writeWordAndTick(cpu, base, cpu->r[count], true);
base += 4;
first_transfer = false;
}
cpu->r[6] = base;
}
return; }
thumb_multiple_load_store_6_1:{
u32 base = cpu->r[6];
u8 rlist = opcode & 0xFF;
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
u8 count = 0xFF;
if(!rlist){
cpu->r[15] = readWordAndTick(cpu, base, false);
thumb_pipeline_refill(cpu);
cpu->r[6] += 0x40;
} else{
u8 rlist_size = __builtin_popcount(rlist);
bool first_transfer = true;
while(rlist){
bool should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = readWordAndTick(cpu, base, !first_transfer);
base += 4;
first_transfer = false;
}
cpu->r[6] = base;
}
return; }
thumb_multiple_load_store_7_0:{
u32 base = cpu->r[7];
u8 rlist = opcode & 0xFF;
cpu->fetch_seq = false;
u8 count = 0xFF;
if(!rlist){
writeWordAndTick(cpu, base, cpu->r[15] + 2, false);
cpu->r[7] += 0x40;
} else{
u8 rlist_size = __builtin_popcount(rlist);
bool first_transfer = true;
while(rlist){
bool should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 7 && !first_transfer)writeWordAndTick(cpu, base, cpu->r[count] + (rlist_size << 2), true);
else
writeWordAndTick(cpu, base, cpu->r[count], true);
base += 4;
first_transfer = false;
}
cpu->r[7] = base;
}
return; }
thumb_multiple_load_store_7_1:{
u32 base = cpu->r[7];
u8 rlist = opcode & 0xFF;
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
u8 count = 0xFF;
if(!rlist){
cpu->r[15] = readWordAndTick(cpu, base, false);
thumb_pipeline_refill(cpu);
cpu->r[7] += 0x40;
} else{
u8 rlist_size = __builtin_popcount(rlist);
bool first_transfer = true;
while(rlist){
bool should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = readWordAndTick(cpu, base, !first_transfer);
base += 4;
first_transfer = false;
}
cpu->r[7] = base;
}
return; }
thumb_hi_reg_op_0_0_0:{
u8 rd_idx = (opcode & 0b111) ;
u8 rs_idx = ((opcode >> 3) & 0b111) ;
u32* rd = &cpu->r[rd_idx];
u32 rs = cpu->r[rs_idx];
alu_ADD(cpu, rd, *rd, rs, false);
if(rd_idx == 15){
cpu->r[15] &= 0xFFFFFFFE;
thumb_pipeline_refill(cpu);
}
return; }
thumb_hi_reg_op_0_0_1:{
u8 rd_idx = (opcode & 0b111) ;
u8 rs_idx = ((opcode >> 3) & 0b111) ;
u32* rd = &cpu->r[rd_idx];
u32 rs = cpu->r[rs_idx];
alu_CMP(cpu, rd, *rd, rs, true);
return; }
thumb_hi_reg_op_0_0_2:{
u8 rd_idx = (opcode & 0b111) ;
u8 rs_idx = ((opcode >> 3) & 0b111) ;
u32* rd = &cpu->r[rd_idx];
u32 rs = cpu->r[rs_idx];
alu_MOV(cpu, rd, *rd, rs, false);
if(rd_idx == 15){
cpu->r[15] &= 0xFFFFFFFE;
thumb_pipeline_refill(cpu);
}
return; }
thumb_hi_reg_op_0_0_3:{
u8 rs_idx = ((opcode >> 3) & 0b111) ;
u32 rs = cpu->r[rs_idx];
cpu->r[15] = rs;
cpu->thumb_mode = (cpu->r[15] & 0b1);
cpu->r[15] &= 0xFFFFFFFE;
arm7tdmi_pipeline_refill(cpu);
return; }
thumb_hi_reg_op_0_1_0:{
u8 rd_idx = (opcode & 0b111) ;
u8 rs_idx = ((opcode >> 3) & 0b111) + 8;
u32* rd = &cpu->r[rd_idx];
u32 rs = cpu->r[rs_idx];
alu_ADD(cpu, rd, *rd, rs, false);
if(rd_idx == 15){
cpu->r[15] &= 0xFFFFFFFE;
thumb_pipeline_refill(cpu);
}
return; }
thumb_hi_reg_op_0_1_1:{
u8 rd_idx = (opcode & 0b111) ;
u8 rs_idx = ((opcode >> 3) & 0b111) + 8;
u32* rd = &cpu->r[rd_idx];
u32 rs = cpu->r[rs_idx];
alu_CMP(cpu, rd, *rd, rs, true);
return; }
thumb_hi_reg_op_0_1_2:{
u8 rd_idx = (opcode & 0b111) ;
u8 rs_idx = ((opcode >> 3) & 0b111) + 8;
u32* rd = &cpu->r[rd_idx];
u32 rs = cpu->r[rs_idx];
alu_MOV(cpu, rd, *rd, rs, false);
if(rd_idx == 15){
cpu->r[15] &= 0xFFFFFFFE;
thumb_pipeline_refill(cpu);
}
return; }
thumb_hi_reg_op_0_1_3:{
u8 rs_idx = ((opcode >> 3) & 0b111) + 8;
u32 rs = cpu->r[rs_idx];
cpu->r[15] = rs;
cpu->thumb_mode = (cpu->r[15] & 0b1);
cpu->r[15] &= 0xFFFFFFFE;
arm7tdmi_pipeline_refill(cpu);
return; }
thumb_hi_reg_op_1_0_0:{
u8 rd_idx = (opcode & 0b111) + 8;
u8 rs_idx = ((opcode >> 3) & 0b111) ;
u32* rd = &cpu->r[rd_idx];
u32 rs = cpu->r[rs_idx];
alu_ADD(cpu, rd, *rd, rs, false);
if(rd_idx == 15){
cpu->r[15] &= 0xFFFFFFFE;
thumb_pipeline_refill(cpu);
}
return; }
thumb_hi_reg_op_1_0_1:{
u8 rd_idx = (opcode & 0b111) + 8;
u8 rs_idx = ((opcode >> 3) & 0b111) ;
u32* rd = &cpu->r[rd_idx];
u32 rs = cpu->r[rs_idx];
alu_CMP(cpu, rd, *rd, rs, true);
return; }
thumb_hi_reg_op_1_0_2:{
u8 rd_idx = (opcode & 0b111) + 8;
u8 rs_idx = ((opcode >> 3) & 0b111) ;
u32* rd = &cpu->r[rd_idx];
u32 rs = cpu->r[rs_idx];
alu_MOV(cpu, rd, *rd, rs, false);
if(rd_idx == 15){
cpu->r[15] &= 0xFFFFFFFE;
thumb_pipeline_refill(cpu);
}
return; }
thumb_hi_reg_op_1_0_3:{
u8 rs_idx = ((opcode >> 3) & 0b111) ;
u32 rs = cpu->r[rs_idx];
cpu->r[15] = rs;
cpu->thumb_mode = (cpu->r[15] & 0b1);
cpu->r[15] &= 0xFFFFFFFE;
arm7tdmi_pipeline_refill(cpu);
return; }
thumb_hi_reg_op_1_1_0:{
u8 rd_idx = (opcode & 0b111) + 8;
u8 rs_idx = ((opcode >> 3) & 0b111) + 8;
u32* rd = &cpu->r[rd_idx];
u32 rs = cpu->r[rs_idx];
alu_ADD(cpu, rd, *rd, rs, false);
if(rd_idx == 15){
cpu->r[15] &= 0xFFFFFFFE;
thumb_pipeline_refill(cpu);
}
return; }
thumb_hi_reg_op_1_1_1:{
u8 rd_idx = (opcode & 0b111) + 8;
u8 rs_idx = ((opcode >> 3) & 0b111) + 8;
u32* rd = &cpu->r[rd_idx];
u32 rs = cpu->r[rs_idx];
alu_CMP(cpu, rd, *rd, rs, true);
return; }
thumb_hi_reg_op_1_1_2:{
u8 rd_idx = (opcode & 0b111) + 8;
u8 rs_idx = ((opcode >> 3) & 0b111) + 8;
u32* rd = &cpu->r[rd_idx];
u32 rs = cpu->r[rs_idx];
alu_MOV(cpu, rd, *rd, rs, false);
if(rd_idx == 15){
cpu->r[15] &= 0xFFFFFFFE;
thumb_pipeline_refill(cpu);
}
return; }
thumb_hi_reg_op_1_1_3:{
u8 rs_idx = ((opcode >> 3) & 0b111) + 8;
u32 rs = cpu->r[rs_idx];
cpu->r[15] = rs;
cpu->thumb_mode = (cpu->r[15] & 0b1);
cpu->r[15] &= 0xFFFFFFFE;
arm7tdmi_pipeline_refill(cpu);
return; }
thumb_push_pop_0_0:{
u8 rlist = opcode & 0xFF;
u8 count = __builtin_popcount(rlist);
cpu->r[13] -= (count + 0) * 4;
rlist = opcode & 0xFF;
cpu->fetch_seq = false;
for(int i = 0; i < 16 && rlist; i++){
bool should_transfer = rlist & 1;
rlist >>= 1;
if(!should_transfer)
continue;
writeWordAndTick(cpu, cpu->r[13], cpu->r[i], false);
cpu->r[13] += 4;
}
cpu->r[13] -= (count + 0) * 4;
return; }
thumb_push_pop_0_1:{
u8 rlist = opcode & 0xFF;
u8 count = __builtin_popcount(rlist);
cpu->r[13] -= (count + 1) * 4;
rlist = opcode & 0xFF;
cpu->fetch_seq = false;
for(int i = 0; i < 16 && rlist; i++){
bool should_transfer = rlist & 1;
rlist >>= 1;
if(!should_transfer)
continue;
writeWordAndTick(cpu, cpu->r[13], cpu->r[i], false);
cpu->r[13] += 4;
}
writeWordAndTick(cpu, cpu->r[13], cpu->r[14], false);
cpu->r[13] += 4;
cpu->r[13] -= (count + 1) * 4;
return; }
thumb_push_pop_1_0:{
u8 rlist = opcode & 0xFF;
u8 count = __builtin_popcount(rlist);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
for(int i = 0; i < 16 && rlist; i++){
bool should_transfer = rlist & 1;
rlist >>= 1;
if(!should_transfer)
continue;
cpu->r[i] = readWordAndTick(cpu, cpu->r[13], false);
cpu->r[13] += 4;
}
return; }
thumb_push_pop_1_1:{
u8 rlist = opcode & 0xFF;
u8 count = __builtin_popcount(rlist);
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
for(int i = 0; i < 16 && rlist; i++){
bool should_transfer = rlist & 1;
rlist >>= 1;
if(!should_transfer)
continue;
cpu->r[i] = readWordAndTick(cpu, cpu->r[13], false);
cpu->r[13] += 4;
}
cpu->r[15] = readWordAndTick(cpu, cpu->r[13], false);
cpu->r[15] &= 0xFFFFFFFE;
thumb_pipeline_refill(cpu);
cpu->r[13] += 4;
return; }
thumb_load_store_halfword_0_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 0, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 2, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_4:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 4, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_6:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 6, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_8:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 8, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_A:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 10, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_C:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 12, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_E:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 14, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_10:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 16, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_12:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 18, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_14:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 20, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_16:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 22, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_18:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 24, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_1A:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 26, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_1C:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 28, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_1E:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 30, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_20:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 32, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_22:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 34, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_24:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 36, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_26:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 38, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_28:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 40, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_2A:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 42, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_2C:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 44, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_2E:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 46, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_30:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 48, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_32:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 50, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_34:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 52, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_36:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 54, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_38:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 56, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_3A:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 58, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_3C:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 60, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_0_3E:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
writeHalfWordAndTick(cpu, rb + 62, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_0:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 0, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_2:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 2, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_4:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 4, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_6:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 6, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_8:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 8, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_A:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 10, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_C:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 12, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_E:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 14, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_10:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 16, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_12:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 18, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_14:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 20, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_16:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 22, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_18:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 24, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_1A:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 26, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_1C:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 28, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_1E:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 30, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_20:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 32, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_22:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 34, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_24:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 36, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_26:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 38, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_28:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 40, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_2A:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 42, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_2C:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 44, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_2E:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 46, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_30:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 48, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_32:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 50, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_34:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 52, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_36:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 54, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_38:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 56, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_3A:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 58, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_3C:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 60, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_halfword_1_3E:{
u32* rd = &cpu->r[opcode & 0b111];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
cpu->cycles += I_CYCLES;
*rd = readHalfWordAndTick(cpu, rb + 62, false);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
cpu->fetch_seq = false;
return; }
thumb_load_store_sign_extended_0_0_0:{
u32 ro = cpu->r[0];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
writeHalfWordAndTick(cpu, addr, *rd, false);
return; }
thumb_load_store_sign_extended_0_0_1:{
u32 ro = cpu->r[1];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
writeHalfWordAndTick(cpu, addr, *rd, false);
return; }
thumb_load_store_sign_extended_0_0_2:{
u32 ro = cpu->r[2];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
writeHalfWordAndTick(cpu, addr, *rd, false);
return; }
thumb_load_store_sign_extended_0_0_3:{
u32 ro = cpu->r[3];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
writeHalfWordAndTick(cpu, addr, *rd, false);
return; }
thumb_load_store_sign_extended_0_0_4:{
u32 ro = cpu->r[4];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
writeHalfWordAndTick(cpu, addr, *rd, false);
return; }
thumb_load_store_sign_extended_0_0_5:{
u32 ro = cpu->r[5];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
writeHalfWordAndTick(cpu, addr, *rd, false);
return; }
thumb_load_store_sign_extended_0_0_6:{
u32 ro = cpu->r[6];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
writeHalfWordAndTick(cpu, addr, *rd, false);
return; }
thumb_load_store_sign_extended_0_0_7:{
u32 ro = cpu->r[7];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
writeHalfWordAndTick(cpu, addr, *rd, false);
return; }
thumb_load_store_sign_extended_0_1_0:{
u32 ro = cpu->r[0];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
return; }
thumb_load_store_sign_extended_0_1_1:{
u32 ro = cpu->r[1];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
return; }
thumb_load_store_sign_extended_0_1_2:{
u32 ro = cpu->r[2];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
return; }
thumb_load_store_sign_extended_0_1_3:{
u32 ro = cpu->r[3];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
return; }
thumb_load_store_sign_extended_0_1_4:{
u32 ro = cpu->r[4];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
return; }
thumb_load_store_sign_extended_0_1_5:{
u32 ro = cpu->r[5];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
return; }
thumb_load_store_sign_extended_0_1_6:{
u32 ro = cpu->r[6];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
return; }
thumb_load_store_sign_extended_0_1_7:{
u32 ro = cpu->r[7];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
return; }
thumb_load_store_sign_extended_1_0_0:{
u32 ro = cpu->r[0];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(addr & 1){
*rd = readHalfWordAndTick(cpu, addr, false);
*rd = (*rd >> 8) | (*rd << 24);
} else {
*rd = readHalfWordAndTick(cpu, addr, false);
}
return; }
thumb_load_store_sign_extended_1_0_1:{
u32 ro = cpu->r[1];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(addr & 1){
*rd = readHalfWordAndTick(cpu, addr, false);
*rd = (*rd >> 8) | (*rd << 24);
} else {
*rd = readHalfWordAndTick(cpu, addr, false);
}
return; }
thumb_load_store_sign_extended_1_0_2:{
u32 ro = cpu->r[2];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(addr & 1){
*rd = readHalfWordAndTick(cpu, addr, false);
*rd = (*rd >> 8) | (*rd << 24);
} else {
*rd = readHalfWordAndTick(cpu, addr, false);
}
return; }
thumb_load_store_sign_extended_1_0_3:{
u32 ro = cpu->r[3];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(addr & 1){
*rd = readHalfWordAndTick(cpu, addr, false);
*rd = (*rd >> 8) | (*rd << 24);
} else {
*rd = readHalfWordAndTick(cpu, addr, false);
}
return; }
thumb_load_store_sign_extended_1_0_4:{
u32 ro = cpu->r[4];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(addr & 1){
*rd = readHalfWordAndTick(cpu, addr, false);
*rd = (*rd >> 8) | (*rd << 24);
} else {
*rd = readHalfWordAndTick(cpu, addr, false);
}
return; }
thumb_load_store_sign_extended_1_0_5:{
u32 ro = cpu->r[5];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(addr & 1){
*rd = readHalfWordAndTick(cpu, addr, false);
*rd = (*rd >> 8) | (*rd << 24);
} else {
*rd = readHalfWordAndTick(cpu, addr, false);
}
return; }
thumb_load_store_sign_extended_1_0_6:{
u32 ro = cpu->r[6];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(addr & 1){
*rd = readHalfWordAndTick(cpu, addr, false);
*rd = (*rd >> 8) | (*rd << 24);
} else {
*rd = readHalfWordAndTick(cpu, addr, false);
}
return; }
thumb_load_store_sign_extended_1_0_7:{
u32 ro = cpu->r[7];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(addr & 1){
*rd = readHalfWordAndTick(cpu, addr, false);
*rd = (*rd >> 8) | (*rd << 24);
} else {
*rd = readHalfWordAndTick(cpu, addr, false);
}
return; }
thumb_load_store_sign_extended_1_1_0:{
u32 ro = cpu->r[0];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(addr & 1){
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
} else {
*rd = readHalfWordAndTick(cpu, addr, false);
if(*rd & 0xFFFF8000)
*rd |= 0xFFFF0000;
}
return; }
thumb_load_store_sign_extended_1_1_1:{
u32 ro = cpu->r[1];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(addr & 1){
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
} else {
*rd = readHalfWordAndTick(cpu, addr, false);
if(*rd & 0xFFFF8000)
*rd |= 0xFFFF0000;
}
return; }
thumb_load_store_sign_extended_1_1_2:{
u32 ro = cpu->r[2];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(addr & 1){
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
} else {
*rd = readHalfWordAndTick(cpu, addr, false);
if(*rd & 0xFFFF8000)
*rd |= 0xFFFF0000;
}
return; }
thumb_load_store_sign_extended_1_1_3:{
u32 ro = cpu->r[3];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(addr & 1){
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
} else {
*rd = readHalfWordAndTick(cpu, addr, false);
if(*rd & 0xFFFF8000)
*rd |= 0xFFFF0000;
}
return; }
thumb_load_store_sign_extended_1_1_4:{
u32 ro = cpu->r[4];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(addr & 1){
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
} else {
*rd = readHalfWordAndTick(cpu, addr, false);
if(*rd & 0xFFFF8000)
*rd |= 0xFFFF0000;
}
return; }
thumb_load_store_sign_extended_1_1_5:{
u32 ro = cpu->r[5];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(addr & 1){
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
} else {
*rd = readHalfWordAndTick(cpu, addr, false);
if(*rd & 0xFFFF8000)
*rd |= 0xFFFF0000;
}
return; }
thumb_load_store_sign_extended_1_1_6:{
u32 ro = cpu->r[6];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(addr & 1){
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
} else {
*rd = readHalfWordAndTick(cpu, addr, false);
if(*rd & 0xFFFF8000)
*rd |= 0xFFFF0000;
}
return; }
thumb_load_store_sign_extended_1_1_7:{
u32 ro = cpu->r[7];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
cpu->fetch_seq = false;
if(addr & 1){
*rd = readByteAndTick(cpu, addr, false);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
} else {
*rd = readHalfWordAndTick(cpu, addr, false);
if(*rd & 0xFFFF8000)
*rd |= 0xFFFF0000;
}
return; }
thumb_load_address_0_0:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[0];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return; }
thumb_load_address_0_1:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[1];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return; }
thumb_load_address_0_2:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[2];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return; }
thumb_load_address_0_3:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[3];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return; }
thumb_load_address_0_4:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[4];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return; }
thumb_load_address_0_5:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[5];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return; }
thumb_load_address_0_6:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[6];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return; }
thumb_load_address_0_7:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[7];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return; }
thumb_load_address_1_0:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[0];
*rd = cpu->r[13];
*rd += w8 << 2;
return; }
thumb_load_address_1_1:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[1];
*rd = cpu->r[13];
*rd += w8 << 2;
return; }
thumb_load_address_1_2:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[2];
*rd = cpu->r[13];
*rd += w8 << 2;
return; }
thumb_load_address_1_3:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[3];
*rd = cpu->r[13];
*rd += w8 << 2;
return; }
thumb_load_address_1_4:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[4];
*rd = cpu->r[13];
*rd += w8 << 2;
return; }
thumb_load_address_1_5:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[5];
*rd = cpu->r[13];
*rd += w8 << 2;
return; }
thumb_load_address_1_6:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[6];
*rd = cpu->r[13];
*rd += w8 << 2;
return; }
thumb_load_address_1_7:{
u8 w8 = opcode & 0xFF;
u32* rd = &cpu->r[7];
*rd = cpu->r[13];
*rd += w8 << 2;
return; }
thumb_load_store_register_offset_0_0_0:{
u32 ro = cpu->r[0];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
writeWordAndTick(cpu, addr, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_0_0_1:{
u32 ro = cpu->r[1];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
writeWordAndTick(cpu, addr, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_0_0_2:{
u32 ro = cpu->r[2];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
writeWordAndTick(cpu, addr, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_0_0_3:{
u32 ro = cpu->r[3];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
writeWordAndTick(cpu, addr, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_0_0_4:{
u32 ro = cpu->r[4];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
writeWordAndTick(cpu, addr, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_0_0_5:{
u32 ro = cpu->r[5];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
writeWordAndTick(cpu, addr, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_0_0_6:{
u32 ro = cpu->r[6];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
writeWordAndTick(cpu, addr, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_0_0_7:{
u32 ro = cpu->r[7];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
writeWordAndTick(cpu, addr, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_0_1_0:{
u32 ro = cpu->r[0];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
writeByteAndTick(cpu, addr, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_0_1_1:{
u32 ro = cpu->r[1];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
writeByteAndTick(cpu, addr, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_0_1_2:{
u32 ro = cpu->r[2];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
writeByteAndTick(cpu, addr, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_0_1_3:{
u32 ro = cpu->r[3];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
writeByteAndTick(cpu, addr, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_0_1_4:{
u32 ro = cpu->r[4];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
writeByteAndTick(cpu, addr, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_0_1_5:{
u32 ro = cpu->r[5];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
writeByteAndTick(cpu, addr, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_0_1_6:{
u32 ro = cpu->r[6];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
writeByteAndTick(cpu, addr, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_0_1_7:{
u32 ro = cpu->r[7];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
writeByteAndTick(cpu, addr, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_1_0_0:{
u32 ro = cpu->r[0];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_1_0_1:{
u32 ro = cpu->r[1];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_1_0_2:{
u32 ro = cpu->r[2];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_1_0_3:{
u32 ro = cpu->r[3];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_1_0_4:{
u32 ro = cpu->r[4];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_1_0_5:{
u32 ro = cpu->r[5];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_1_0_6:{
u32 ro = cpu->r[6];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_1_0_7:{
u32 ro = cpu->r[7];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_1_1_0:{
u32 ro = cpu->r[0];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, addr, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_1_1_1:{
u32 ro = cpu->r[1];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, addr, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_1_1_2:{
u32 ro = cpu->r[2];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, addr, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_1_1_3:{
u32 ro = cpu->r[3];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, addr, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_1_1_4:{
u32 ro = cpu->r[4];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, addr, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_1_1_5:{
u32 ro = cpu->r[5];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, addr, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_1_1_6:{
u32 ro = cpu->r[6];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, addr, false);
cpu->fetch_seq = false;
return; }
thumb_load_store_register_offset_1_1_7:{
u32 ro = cpu->r[7];
u32 rb = cpu->r[(opcode >> 3) & 0b111];
u32* rd = &cpu->r[opcode & 0b111];
u32 addr = rb + ro;
cpu->cycles += I_CYCLES;
*rd = readByteAndTick(cpu, addr, false);
cpu->fetch_seq = false;
return; }
thumb_add_offset_sp_0:{
u16 w9 = (opcode & 0b1111111) << 2;
cpu->r[13] += w9;
return; }
thumb_add_offset_sp_1:{
u16 w9 = (opcode & 0b1111111) << 2;
cpu->r[13] -= w9;
return; }
thumb_sp_relative_load_store_0_0:{
u32* rd = &cpu->r[0];
u8 w8 = opcode & 0xFF;
u32 addr = cpu->r[13] + (w8 << 2);
writeWordAndTick(cpu, addr, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_sp_relative_load_store_0_1:{
u32* rd = &cpu->r[1];
u8 w8 = opcode & 0xFF;
u32 addr = cpu->r[13] + (w8 << 2);
writeWordAndTick(cpu, addr, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_sp_relative_load_store_0_2:{
u32* rd = &cpu->r[2];
u8 w8 = opcode & 0xFF;
u32 addr = cpu->r[13] + (w8 << 2);
writeWordAndTick(cpu, addr, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_sp_relative_load_store_0_3:{
u32* rd = &cpu->r[3];
u8 w8 = opcode & 0xFF;
u32 addr = cpu->r[13] + (w8 << 2);
writeWordAndTick(cpu, addr, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_sp_relative_load_store_0_4:{
u32* rd = &cpu->r[4];
u8 w8 = opcode & 0xFF;
u32 addr = cpu->r[13] + (w8 << 2);
writeWordAndTick(cpu, addr, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_sp_relative_load_store_0_5:{
u32* rd = &cpu->r[5];
u8 w8 = opcode & 0xFF;
u32 addr = cpu->r[13] + (w8 << 2);
writeWordAndTick(cpu, addr, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_sp_relative_load_store_0_6:{
u32* rd = &cpu->r[6];
u8 w8 = opcode & 0xFF;
u32 addr = cpu->r[13] + (w8 << 2);
writeWordAndTick(cpu, addr, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_sp_relative_load_store_0_7:{
u32* rd = &cpu->r[7];
u8 w8 = opcode & 0xFF;
u32 addr = cpu->r[13] + (w8 << 2);
writeWordAndTick(cpu, addr, *rd, false);
cpu->fetch_seq = false;
return; }
thumb_sp_relative_load_store_1_0:{
u32* rd = &cpu->r[0];
u8 w8 = opcode & 0xFF;
u32 addr = cpu->r[13] + (w8 << 2);
cpu->cycles += I_CYCLES;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_sp_relative_load_store_1_1:{
u32* rd = &cpu->r[1];
u8 w8 = opcode & 0xFF;
u32 addr = cpu->r[13] + (w8 << 2);
cpu->cycles += I_CYCLES;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_sp_relative_load_store_1_2:{
u32* rd = &cpu->r[2];
u8 w8 = opcode & 0xFF;
u32 addr = cpu->r[13] + (w8 << 2);
cpu->cycles += I_CYCLES;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_sp_relative_load_store_1_3:{
u32* rd = &cpu->r[3];
u8 w8 = opcode & 0xFF;
u32 addr = cpu->r[13] + (w8 << 2);
cpu->cycles += I_CYCLES;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_sp_relative_load_store_1_4:{
u32* rd = &cpu->r[4];
u8 w8 = opcode & 0xFF;
u32 addr = cpu->r[13] + (w8 << 2);
cpu->cycles += I_CYCLES;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_sp_relative_load_store_1_5:{
u32* rd = &cpu->r[5];
u8 w8 = opcode & 0xFF;
u32 addr = cpu->r[13] + (w8 << 2);
cpu->cycles += I_CYCLES;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_sp_relative_load_store_1_6:{
u32* rd = &cpu->r[6];
u8 w8 = opcode & 0xFF;
u32 addr = cpu->r[13] + (w8 << 2);
cpu->cycles += I_CYCLES;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_sp_relative_load_store_1_7:{
u32* rd = &cpu->r[7];
u8 w8 = opcode & 0xFF;
u32 addr = cpu->r[13] + (w8 << 2);
cpu->cycles += I_CYCLES;
*rd = readWordAndTick(cpu, addr, false);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
cpu->fetch_seq = false;
return; }
thumb_software_interrupt:{
arm7tdmi_trigger_exception(cpu, 0x8, 0x13);
return; }
thumb_not_encoded:{
printf("THUMB ILLEGAL OPCODE!\n");
}
}

