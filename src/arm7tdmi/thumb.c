#include "arm7tdmi/arm7tdmi.h"
#include "arm7tdmi/thumb.h"
#include "arm7tdmi/alu.h"

#include <stdio.h>
#include <stdlib.h>

void thumb_step(arm7tdmi_t* cpu){
if(!cpu->pipeline_valid){
cpu->pipeline_opcode = cpu->readHalfWord(cpu, cpu->r[15]);
cpu->r[15] += 2;
cpu->pipeline_valid = true;
return;
}

u16 opcode = cpu->pipeline_opcode;
cpu->pipeline_opcode = cpu->readHalfWord(cpu, cpu->r[15]);
cpu->r[15] += 2;

static void* thumb_table[1 << 10] = {&&thumb_op_0000, &&thumb_op_0001, &&thumb_op_0002, &&thumb_op_0003, &&thumb_op_0004, &&thumb_op_0005, &&thumb_op_0006, &&thumb_op_0007, &&thumb_op_0008, &&thumb_op_0009, &&thumb_op_000A, &&thumb_op_000B, &&thumb_op_000C, &&thumb_op_000D, &&thumb_op_000E, &&thumb_op_000F, &&thumb_op_0010, &&thumb_op_0011, &&thumb_op_0012, &&thumb_op_0013, &&thumb_op_0014, &&thumb_op_0015, &&thumb_op_0016, &&thumb_op_0017, &&thumb_op_0018, &&thumb_op_0019, &&thumb_op_001A, &&thumb_op_001B, &&thumb_op_001C, &&thumb_op_001D, &&thumb_op_001E, &&thumb_op_001F, &&thumb_op_0020, &&thumb_op_0021, &&thumb_op_0022, &&thumb_op_0023, &&thumb_op_0024, &&thumb_op_0025, &&thumb_op_0026, &&thumb_op_0027, &&thumb_op_0028, &&thumb_op_0029, &&thumb_op_002A, &&thumb_op_002B, &&thumb_op_002C, &&thumb_op_002D, &&thumb_op_002E, &&thumb_op_002F, &&thumb_op_0030, &&thumb_op_0031, &&thumb_op_0032, &&thumb_op_0033, &&thumb_op_0034, &&thumb_op_0035, &&thumb_op_0036, &&thumb_op_0037, &&thumb_op_0038, &&thumb_op_0039, &&thumb_op_003A, &&thumb_op_003B, &&thumb_op_003C, &&thumb_op_003D, &&thumb_op_003E, &&thumb_op_003F, &&thumb_op_0040, &&thumb_op_0041, &&thumb_op_0042, &&thumb_op_0043, &&thumb_op_0044, &&thumb_op_0045, &&thumb_op_0046, &&thumb_op_0047, &&thumb_op_0048, &&thumb_op_0049, &&thumb_op_004A, &&thumb_op_004B, &&thumb_op_004C, &&thumb_op_004D, &&thumb_op_004E, &&thumb_op_004F, &&thumb_op_0050, &&thumb_op_0051, &&thumb_op_0052, &&thumb_op_0053, &&thumb_op_0054, &&thumb_op_0055, &&thumb_op_0056, &&thumb_op_0057, &&thumb_op_0058, &&thumb_op_0059, &&thumb_op_005A, &&thumb_op_005B, &&thumb_op_005C, &&thumb_op_005D, &&thumb_op_005E, &&thumb_op_005F, &&thumb_op_0060, &&thumb_op_0061, &&thumb_op_0062, &&thumb_op_0063, &&thumb_op_0064, &&thumb_op_0065, &&thumb_op_0066, &&thumb_op_0067, &&thumb_op_0068, &&thumb_op_0069, &&thumb_op_006A, &&thumb_op_006B, &&thumb_op_006C, &&thumb_op_006D, &&thumb_op_006E, &&thumb_op_006F, &&thumb_op_0070, &&thumb_op_0071, &&thumb_op_0072, &&thumb_op_0073, &&thumb_op_0074, &&thumb_op_0075, &&thumb_op_0076, &&thumb_op_0077, &&thumb_op_0078, &&thumb_op_0079, &&thumb_op_007A, &&thumb_op_007B, &&thumb_op_007C, &&thumb_op_007D, &&thumb_op_007E, &&thumb_op_007F, &&thumb_op_0080, &&thumb_op_0081, &&thumb_op_0082, &&thumb_op_0083, &&thumb_op_0084, &&thumb_op_0085, &&thumb_op_0086, &&thumb_op_0087, &&thumb_op_0088, &&thumb_op_0089, &&thumb_op_008A, &&thumb_op_008B, &&thumb_op_008C, &&thumb_op_008D, &&thumb_op_008E, &&thumb_op_008F, &&thumb_op_0090, &&thumb_op_0091, &&thumb_op_0092, &&thumb_op_0093, &&thumb_op_0094, &&thumb_op_0095, &&thumb_op_0096, &&thumb_op_0097, &&thumb_op_0098, &&thumb_op_0099, &&thumb_op_009A, &&thumb_op_009B, &&thumb_op_009C, &&thumb_op_009D, &&thumb_op_009E, &&thumb_op_009F, &&thumb_op_00A0, &&thumb_op_00A1, &&thumb_op_00A2, &&thumb_op_00A3, &&thumb_op_00A4, &&thumb_op_00A5, &&thumb_op_00A6, &&thumb_op_00A7, &&thumb_op_00A8, &&thumb_op_00A9, &&thumb_op_00AA, &&thumb_op_00AB, &&thumb_op_00AC, &&thumb_op_00AD, &&thumb_op_00AE, &&thumb_op_00AF, &&thumb_op_00B0, &&thumb_op_00B1, &&thumb_op_00B2, &&thumb_op_00B3, &&thumb_op_00B4, &&thumb_op_00B5, &&thumb_op_00B6, &&thumb_op_00B7, &&thumb_op_00B8, &&thumb_op_00B9, &&thumb_op_00BA, &&thumb_op_00BB, &&thumb_op_00BC, &&thumb_op_00BD, &&thumb_op_00BE, &&thumb_op_00BF, &&thumb_op_00C0, &&thumb_op_00C1, &&thumb_op_00C2, &&thumb_op_00C3, &&thumb_op_00C4, &&thumb_op_00C5, &&thumb_op_00C6, &&thumb_op_00C7, &&thumb_op_00C8, &&thumb_op_00C9, &&thumb_op_00CA, &&thumb_op_00CB, &&thumb_op_00CC, &&thumb_op_00CD, &&thumb_op_00CE, &&thumb_op_00CF, &&thumb_op_00D0, &&thumb_op_00D1, &&thumb_op_00D2, &&thumb_op_00D3, &&thumb_op_00D4, &&thumb_op_00D5, &&thumb_op_00D6, &&thumb_op_00D7, &&thumb_op_00D8, &&thumb_op_00D9, &&thumb_op_00DA, &&thumb_op_00DB, &&thumb_op_00DC, &&thumb_op_00DD, &&thumb_op_00DE, &&thumb_op_00DF, &&thumb_op_00E0, &&thumb_op_00E1, &&thumb_op_00E2, &&thumb_op_00E3, &&thumb_op_00E4, &&thumb_op_00E5, &&thumb_op_00E6, &&thumb_op_00E7, &&thumb_op_00E8, &&thumb_op_00E9, &&thumb_op_00EA, &&thumb_op_00EB, &&thumb_op_00EC, &&thumb_op_00ED, &&thumb_op_00EE, &&thumb_op_00EF, &&thumb_op_00F0, &&thumb_op_00F1, &&thumb_op_00F2, &&thumb_op_00F3, &&thumb_op_00F4, &&thumb_op_00F5, &&thumb_op_00F6, &&thumb_op_00F7, &&thumb_op_00F8, &&thumb_op_00F9, &&thumb_op_00FA, &&thumb_op_00FB, &&thumb_op_00FC, &&thumb_op_00FD, &&thumb_op_00FE, &&thumb_op_00FF, &&thumb_op_0100, &&thumb_op_0101, &&thumb_op_0102, &&thumb_op_0103, &&thumb_op_0104, &&thumb_op_0105, &&thumb_op_0106, &&thumb_op_0107, &&thumb_op_0108, &&thumb_op_0109, &&thumb_op_010A, &&thumb_op_010B, &&thumb_op_010C, &&thumb_op_010D, &&thumb_op_010E, &&thumb_op_010F, &&thumb_op_0110, &&thumb_op_0111, &&thumb_op_0112, &&thumb_op_0113, &&thumb_op_0114, &&thumb_op_0115, &&thumb_op_0116, &&thumb_op_0117, &&thumb_op_0118, &&thumb_op_0119, &&thumb_op_011A, &&thumb_op_011B, &&thumb_op_011C, &&thumb_op_011D, &&thumb_op_011E, &&thumb_op_011F, &&thumb_op_0120, &&thumb_op_0121, &&thumb_op_0122, &&thumb_op_0123, &&thumb_op_0124, &&thumb_op_0125, &&thumb_op_0126, &&thumb_op_0127, &&thumb_op_0128, &&thumb_op_0129, &&thumb_op_012A, &&thumb_op_012B, &&thumb_op_012C, &&thumb_op_012D, &&thumb_op_012E, &&thumb_op_012F, &&thumb_op_0130, &&thumb_op_0131, &&thumb_op_0132, &&thumb_op_0133, &&thumb_op_0134, &&thumb_op_0135, &&thumb_op_0136, &&thumb_op_0137, &&thumb_op_0138, &&thumb_op_0139, &&thumb_op_013A, &&thumb_op_013B, &&thumb_op_013C, &&thumb_op_013D, &&thumb_op_013E, &&thumb_op_013F, &&thumb_op_0140, &&thumb_op_0141, &&thumb_op_0142, &&thumb_op_0143, &&thumb_op_0144, &&thumb_op_0145, &&thumb_op_0146, &&thumb_op_0147, &&thumb_op_0148, &&thumb_op_0149, &&thumb_op_014A, &&thumb_op_014B, &&thumb_op_014C, &&thumb_op_014D, &&thumb_op_014E, &&thumb_op_014F, &&thumb_op_0150, &&thumb_op_0151, &&thumb_op_0152, &&thumb_op_0153, &&thumb_op_0154, &&thumb_op_0155, &&thumb_op_0156, &&thumb_op_0157, &&thumb_op_0158, &&thumb_op_0159, &&thumb_op_015A, &&thumb_op_015B, &&thumb_op_015C, &&thumb_op_015D, &&thumb_op_015E, &&thumb_op_015F, &&thumb_op_0160, &&thumb_op_0161, &&thumb_op_0162, &&thumb_op_0163, &&thumb_op_0164, &&thumb_op_0165, &&thumb_op_0166, &&thumb_op_0167, &&thumb_op_0168, &&thumb_op_0169, &&thumb_op_016A, &&thumb_op_016B, &&thumb_op_016C, &&thumb_op_016D, &&thumb_op_016E, &&thumb_op_016F, &&thumb_op_0170, &&thumb_op_0171, &&thumb_op_0172, &&thumb_op_0173, &&thumb_op_0174, &&thumb_op_0175, &&thumb_op_0176, &&thumb_op_0177, &&thumb_op_0178, &&thumb_op_0179, &&thumb_op_017A, &&thumb_op_017B, &&thumb_op_017C, &&thumb_op_017D, &&thumb_op_017E, &&thumb_op_017F, &&thumb_op_0180, &&thumb_op_0181, &&thumb_op_0182, &&thumb_op_0183, &&thumb_op_0184, &&thumb_op_0185, &&thumb_op_0186, &&thumb_op_0187, &&thumb_op_0188, &&thumb_op_0189, &&thumb_op_018A, &&thumb_op_018B, &&thumb_op_018C, &&thumb_op_018D, &&thumb_op_018E, &&thumb_op_018F, &&thumb_op_0190, &&thumb_op_0191, &&thumb_op_0192, &&thumb_op_0193, &&thumb_op_0194, &&thumb_op_0195, &&thumb_op_0196, &&thumb_op_0197, &&thumb_op_0198, &&thumb_op_0199, &&thumb_op_019A, &&thumb_op_019B, &&thumb_op_019C, &&thumb_op_019D, &&thumb_op_019E, &&thumb_op_019F, &&thumb_op_01A0, &&thumb_op_01A1, &&thumb_op_01A2, &&thumb_op_01A3, &&thumb_op_01A4, &&thumb_op_01A5, &&thumb_op_01A6, &&thumb_op_01A7, &&thumb_op_01A8, &&thumb_op_01A9, &&thumb_op_01AA, &&thumb_op_01AB, &&thumb_op_01AC, &&thumb_op_01AD, &&thumb_op_01AE, &&thumb_op_01AF, &&thumb_op_01B0, &&thumb_op_01B1, &&thumb_op_01B2, &&thumb_op_01B3, &&thumb_op_01B4, &&thumb_op_01B5, &&thumb_op_01B6, &&thumb_op_01B7, &&thumb_op_01B8, &&thumb_op_01B9, &&thumb_op_01BA, &&thumb_op_01BB, &&thumb_op_01BC, &&thumb_op_01BD, &&thumb_op_01BE, &&thumb_op_01BF, &&thumb_op_01C0, &&thumb_op_01C1, &&thumb_op_01C2, &&thumb_op_01C3, &&thumb_op_01C4, &&thumb_op_01C5, &&thumb_op_01C6, &&thumb_op_01C7, &&thumb_op_01C8, &&thumb_op_01C9, &&thumb_op_01CA, &&thumb_op_01CB, &&thumb_op_01CC, &&thumb_op_01CD, &&thumb_op_01CE, &&thumb_op_01CF, &&thumb_op_01D0, &&thumb_op_01D1, &&thumb_op_01D2, &&thumb_op_01D3, &&thumb_op_01D4, &&thumb_op_01D5, &&thumb_op_01D6, &&thumb_op_01D7, &&thumb_op_01D8, &&thumb_op_01D9, &&thumb_op_01DA, &&thumb_op_01DB, &&thumb_op_01DC, &&thumb_op_01DD, &&thumb_op_01DE, &&thumb_op_01DF, &&thumb_op_01E0, &&thumb_op_01E1, &&thumb_op_01E2, &&thumb_op_01E3, &&thumb_op_01E4, &&thumb_op_01E5, &&thumb_op_01E6, &&thumb_op_01E7, &&thumb_op_01E8, &&thumb_op_01E9, &&thumb_op_01EA, &&thumb_op_01EB, &&thumb_op_01EC, &&thumb_op_01ED, &&thumb_op_01EE, &&thumb_op_01EF, &&thumb_op_01F0, &&thumb_op_01F1, &&thumb_op_01F2, &&thumb_op_01F3, &&thumb_op_01F4, &&thumb_op_01F5, &&thumb_op_01F6, &&thumb_op_01F7, &&thumb_op_01F8, &&thumb_op_01F9, &&thumb_op_01FA, &&thumb_op_01FB, &&thumb_op_01FC, &&thumb_op_01FD, &&thumb_op_01FE, &&thumb_op_01FF, &&thumb_op_0200, &&thumb_op_0201, &&thumb_op_0202, &&thumb_op_0203, &&thumb_op_0204, &&thumb_op_0205, &&thumb_op_0206, &&thumb_op_0207, &&thumb_op_0208, &&thumb_op_0209, &&thumb_op_020A, &&thumb_op_020B, &&thumb_op_020C, &&thumb_op_020D, &&thumb_op_020E, &&thumb_op_020F, &&thumb_op_0210, &&thumb_op_0211, &&thumb_op_0212, &&thumb_op_0213, &&thumb_op_0214, &&thumb_op_0215, &&thumb_op_0216, &&thumb_op_0217, &&thumb_op_0218, &&thumb_op_0219, &&thumb_op_021A, &&thumb_op_021B, &&thumb_op_021C, &&thumb_op_021D, &&thumb_op_021E, &&thumb_op_021F, &&thumb_op_0220, &&thumb_op_0221, &&thumb_op_0222, &&thumb_op_0223, &&thumb_op_0224, &&thumb_op_0225, &&thumb_op_0226, &&thumb_op_0227, &&thumb_op_0228, &&thumb_op_0229, &&thumb_op_022A, &&thumb_op_022B, &&thumb_op_022C, &&thumb_op_022D, &&thumb_op_022E, &&thumb_op_022F, &&thumb_op_0230, &&thumb_op_0231, &&thumb_op_0232, &&thumb_op_0233, &&thumb_op_0234, &&thumb_op_0235, &&thumb_op_0236, &&thumb_op_0237, &&thumb_op_0238, &&thumb_op_0239, &&thumb_op_023A, &&thumb_op_023B, &&thumb_op_023C, &&thumb_op_023D, &&thumb_op_023E, &&thumb_op_023F, &&thumb_op_0240, &&thumb_op_0241, &&thumb_op_0242, &&thumb_op_0243, &&thumb_op_0244, &&thumb_op_0245, &&thumb_op_0246, &&thumb_op_0247, &&thumb_op_0248, &&thumb_op_0249, &&thumb_op_024A, &&thumb_op_024B, &&thumb_op_024C, &&thumb_op_024D, &&thumb_op_024E, &&thumb_op_024F, &&thumb_op_0250, &&thumb_op_0251, &&thumb_op_0252, &&thumb_op_0253, &&thumb_op_0254, &&thumb_op_0255, &&thumb_op_0256, &&thumb_op_0257, &&thumb_op_0258, &&thumb_op_0259, &&thumb_op_025A, &&thumb_op_025B, &&thumb_op_025C, &&thumb_op_025D, &&thumb_op_025E, &&thumb_op_025F, &&thumb_op_0260, &&thumb_op_0261, &&thumb_op_0262, &&thumb_op_0263, &&thumb_op_0264, &&thumb_op_0265, &&thumb_op_0266, &&thumb_op_0267, &&thumb_op_0268, &&thumb_op_0269, &&thumb_op_026A, &&thumb_op_026B, &&thumb_op_026C, &&thumb_op_026D, &&thumb_op_026E, &&thumb_op_026F, &&thumb_op_0270, &&thumb_op_0271, &&thumb_op_0272, &&thumb_op_0273, &&thumb_op_0274, &&thumb_op_0275, &&thumb_op_0276, &&thumb_op_0277, &&thumb_op_0278, &&thumb_op_0279, &&thumb_op_027A, &&thumb_op_027B, &&thumb_op_027C, &&thumb_op_027D, &&thumb_op_027E, &&thumb_op_027F, &&thumb_op_0280, &&thumb_op_0281, &&thumb_op_0282, &&thumb_op_0283, &&thumb_op_0284, &&thumb_op_0285, &&thumb_op_0286, &&thumb_op_0287, &&thumb_op_0288, &&thumb_op_0289, &&thumb_op_028A, &&thumb_op_028B, &&thumb_op_028C, &&thumb_op_028D, &&thumb_op_028E, &&thumb_op_028F, &&thumb_op_0290, &&thumb_op_0291, &&thumb_op_0292, &&thumb_op_0293, &&thumb_op_0294, &&thumb_op_0295, &&thumb_op_0296, &&thumb_op_0297, &&thumb_op_0298, &&thumb_op_0299, &&thumb_op_029A, &&thumb_op_029B, &&thumb_op_029C, &&thumb_op_029D, &&thumb_op_029E, &&thumb_op_029F, &&thumb_op_02A0, &&thumb_op_02A1, &&thumb_op_02A2, &&thumb_op_02A3, &&thumb_op_02A4, &&thumb_op_02A5, &&thumb_op_02A6, &&thumb_op_02A7, &&thumb_op_02A8, &&thumb_op_02A9, &&thumb_op_02AA, &&thumb_op_02AB, &&thumb_op_02AC, &&thumb_op_02AD, &&thumb_op_02AE, &&thumb_op_02AF, &&thumb_op_02B0, &&thumb_op_02B1, &&thumb_op_02B2, &&thumb_op_02B3, &&thumb_op_02B4, &&thumb_op_02B5, &&thumb_op_02B6, &&thumb_op_02B7, &&thumb_op_02B8, &&thumb_op_02B9, &&thumb_op_02BA, &&thumb_op_02BB, &&thumb_op_02BC, &&thumb_op_02BD, &&thumb_op_02BE, &&thumb_op_02BF, &&thumb_op_02C0, &&thumb_op_02C1, &&thumb_op_02C2, &&thumb_op_02C3, &&thumb_op_02C4, &&thumb_op_02C5, &&thumb_op_02C6, &&thumb_op_02C7, &&thumb_op_02C8, &&thumb_op_02C9, &&thumb_op_02CA, &&thumb_op_02CB, &&thumb_op_02CC, &&thumb_op_02CD, &&thumb_op_02CE, &&thumb_op_02CF, &&thumb_op_02D0, &&thumb_op_02D1, &&thumb_op_02D2, &&thumb_op_02D3, &&thumb_op_02D4, &&thumb_op_02D5, &&thumb_op_02D6, &&thumb_op_02D7, &&thumb_op_02D8, &&thumb_op_02D9, &&thumb_op_02DA, &&thumb_op_02DB, &&thumb_op_02DC, &&thumb_op_02DD, &&thumb_op_02DE, &&thumb_op_02DF, &&thumb_op_02E0, &&thumb_op_02E1, &&thumb_op_02E2, &&thumb_op_02E3, &&thumb_op_02E4, &&thumb_op_02E5, &&thumb_op_02E6, &&thumb_op_02E7, &&thumb_op_02E8, &&thumb_op_02E9, &&thumb_op_02EA, &&thumb_op_02EB, &&thumb_op_02EC, &&thumb_op_02ED, &&thumb_op_02EE, &&thumb_op_02EF, &&thumb_op_02F0, &&thumb_op_02F1, &&thumb_op_02F2, &&thumb_op_02F3, &&thumb_op_02F4, &&thumb_op_02F5, &&thumb_op_02F6, &&thumb_op_02F7, &&thumb_op_02F8, &&thumb_op_02F9, &&thumb_op_02FA, &&thumb_op_02FB, &&thumb_op_02FC, &&thumb_op_02FD, &&thumb_op_02FE, &&thumb_op_02FF, &&thumb_op_0300, &&thumb_op_0301, &&thumb_op_0302, &&thumb_op_0303, &&thumb_op_0304, &&thumb_op_0305, &&thumb_op_0306, &&thumb_op_0307, &&thumb_op_0308, &&thumb_op_0309, &&thumb_op_030A, &&thumb_op_030B, &&thumb_op_030C, &&thumb_op_030D, &&thumb_op_030E, &&thumb_op_030F, &&thumb_op_0310, &&thumb_op_0311, &&thumb_op_0312, &&thumb_op_0313, &&thumb_op_0314, &&thumb_op_0315, &&thumb_op_0316, &&thumb_op_0317, &&thumb_op_0318, &&thumb_op_0319, &&thumb_op_031A, &&thumb_op_031B, &&thumb_op_031C, &&thumb_op_031D, &&thumb_op_031E, &&thumb_op_031F, &&thumb_op_0320, &&thumb_op_0321, &&thumb_op_0322, &&thumb_op_0323, &&thumb_op_0324, &&thumb_op_0325, &&thumb_op_0326, &&thumb_op_0327, &&thumb_op_0328, &&thumb_op_0329, &&thumb_op_032A, &&thumb_op_032B, &&thumb_op_032C, &&thumb_op_032D, &&thumb_op_032E, &&thumb_op_032F, &&thumb_op_0330, &&thumb_op_0331, &&thumb_op_0332, &&thumb_op_0333, &&thumb_op_0334, &&thumb_op_0335, &&thumb_op_0336, &&thumb_op_0337, &&thumb_op_0338, &&thumb_op_0339, &&thumb_op_033A, &&thumb_op_033B, &&thumb_op_033C, &&thumb_op_033D, &&thumb_op_033E, &&thumb_op_033F, &&thumb_op_0340, &&thumb_op_0341, &&thumb_op_0342, &&thumb_op_0343, &&thumb_op_0344, &&thumb_op_0345, &&thumb_op_0346, &&thumb_op_0347, &&thumb_op_0348, &&thumb_op_0349, &&thumb_op_034A, &&thumb_op_034B, &&thumb_op_034C, &&thumb_op_034D, &&thumb_op_034E, &&thumb_op_034F, &&thumb_op_0350, &&thumb_op_0351, &&thumb_op_0352, &&thumb_op_0353, &&thumb_op_0354, &&thumb_op_0355, &&thumb_op_0356, &&thumb_op_0357, &&thumb_op_0358, &&thumb_op_0359, &&thumb_op_035A, &&thumb_op_035B, &&thumb_op_035C, &&thumb_op_035D, &&thumb_op_035E, &&thumb_op_035F, &&thumb_op_0360, &&thumb_op_0361, &&thumb_op_0362, &&thumb_op_0363, &&thumb_op_0364, &&thumb_op_0365, &&thumb_op_0366, &&thumb_op_0367, &&thumb_op_0368, &&thumb_op_0369, &&thumb_op_036A, &&thumb_op_036B, &&thumb_op_036C, &&thumb_op_036D, &&thumb_op_036E, &&thumb_op_036F, &&thumb_op_0370, &&thumb_op_0371, &&thumb_op_0372, &&thumb_op_0373, &&thumb_op_0374, &&thumb_op_0375, &&thumb_op_0376, &&thumb_op_0377, &&thumb_op_0378, &&thumb_op_0379, &&thumb_op_037A, &&thumb_op_037B, &&thumb_op_037C, &&thumb_op_037D, &&thumb_op_037E, &&thumb_op_037F, &&thumb_op_0380, &&thumb_op_0381, &&thumb_op_0382, &&thumb_op_0383, &&thumb_op_0384, &&thumb_op_0385, &&thumb_op_0386, &&thumb_op_0387, &&thumb_op_0388, &&thumb_op_0389, &&thumb_op_038A, &&thumb_op_038B, &&thumb_op_038C, &&thumb_op_038D, &&thumb_op_038E, &&thumb_op_038F, &&thumb_op_0390, &&thumb_op_0391, &&thumb_op_0392, &&thumb_op_0393, &&thumb_op_0394, &&thumb_op_0395, &&thumb_op_0396, &&thumb_op_0397, &&thumb_op_0398, &&thumb_op_0399, &&thumb_op_039A, &&thumb_op_039B, &&thumb_op_039C, &&thumb_op_039D, &&thumb_op_039E, &&thumb_op_039F, &&thumb_op_03A0, &&thumb_op_03A1, &&thumb_op_03A2, &&thumb_op_03A3, &&thumb_op_03A4, &&thumb_op_03A5, &&thumb_op_03A6, &&thumb_op_03A7, &&thumb_op_03A8, &&thumb_op_03A9, &&thumb_op_03AA, &&thumb_op_03AB, &&thumb_op_03AC, &&thumb_op_03AD, &&thumb_op_03AE, &&thumb_op_03AF, &&thumb_op_03B0, &&thumb_op_03B1, &&thumb_op_03B2, &&thumb_op_03B3, &&thumb_op_03B4, &&thumb_op_03B5, &&thumb_op_03B6, &&thumb_op_03B7, &&thumb_op_03B8, &&thumb_op_03B9, &&thumb_op_03BA, &&thumb_op_03BB, &&thumb_op_03BC, &&thumb_op_03BD, &&thumb_op_03BE, &&thumb_op_03BF, &&thumb_op_03C0, &&thumb_op_03C1, &&thumb_op_03C2, &&thumb_op_03C3, &&thumb_op_03C4, &&thumb_op_03C5, &&thumb_op_03C6, &&thumb_op_03C7, &&thumb_op_03C8, &&thumb_op_03C9, &&thumb_op_03CA, &&thumb_op_03CB, &&thumb_op_03CC, &&thumb_op_03CD, &&thumb_op_03CE, &&thumb_op_03CF, &&thumb_op_03D0, &&thumb_op_03D1, &&thumb_op_03D2, &&thumb_op_03D3, &&thumb_op_03D4, &&thumb_op_03D5, &&thumb_op_03D6, &&thumb_op_03D7, &&thumb_op_03D8, &&thumb_op_03D9, &&thumb_op_03DA, &&thumb_op_03DB, &&thumb_op_03DC, &&thumb_op_03DD, &&thumb_op_03DE, &&thumb_op_03DF, &&thumb_op_03E0, &&thumb_op_03E1, &&thumb_op_03E2, &&thumb_op_03E3, &&thumb_op_03E4, &&thumb_op_03E5, &&thumb_op_03E6, &&thumb_op_03E7, &&thumb_op_03E8, &&thumb_op_03E9, &&thumb_op_03EA, &&thumb_op_03EB, &&thumb_op_03EC, &&thumb_op_03ED, &&thumb_op_03EE, &&thumb_op_03EF, &&thumb_op_03F0, &&thumb_op_03F1, &&thumb_op_03F2, &&thumb_op_03F3, &&thumb_op_03F4, &&thumb_op_03F5, &&thumb_op_03F6, &&thumb_op_03F7, &&thumb_op_03F8, &&thumb_op_03F9, &&thumb_op_03FA, &&thumb_op_03FB, &&thumb_op_03FC, &&thumb_op_03FD, &&thumb_op_03FE, &&thumb_op_03FF};

goto *thumb_table[opcode >> 6];
u32* rd;
u32 rs;
u32 addr;
u32 offset;
u32 old_r15;
u32 rb;
u32 ro;
u32 base;
u16 w9;
u8 w8;
u8 rd_idx;
u8 rs_idx;
u8 count;
u8 rlist;
u8 rlist_size;
bool should_transfer;
bool first_transfer;
thumb_op_0000:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 0, true), true);
return;
thumb_op_0001:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 1, true), true);
return;
thumb_op_0002:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 2, true), true);
return;
thumb_op_0003:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 3, true), true);
return;
thumb_op_0004:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 4, true), true);
return;
thumb_op_0005:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 5, true), true);
return;
thumb_op_0006:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 6, true), true);
return;
thumb_op_0007:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 7, true), true);
return;
thumb_op_0008:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 8, true), true);
return;
thumb_op_0009:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 9, true), true);
return;
thumb_op_000A:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 10, true), true);
return;
thumb_op_000B:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 11, true), true);
return;
thumb_op_000C:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 12, true), true);
return;
thumb_op_000D:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 13, true), true);
return;
thumb_op_000E:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 14, true), true);
return;
thumb_op_000F:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 15, true), true);
return;
thumb_op_0010:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 16, true), true);
return;
thumb_op_0011:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 17, true), true);
return;
thumb_op_0012:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 18, true), true);
return;
thumb_op_0013:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 19, true), true);
return;
thumb_op_0014:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 20, true), true);
return;
thumb_op_0015:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 21, true), true);
return;
thumb_op_0016:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 22, true), true);
return;
thumb_op_0017:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 23, true), true);
return;
thumb_op_0018:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 24, true), true);
return;
thumb_op_0019:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 25, true), true);
return;
thumb_op_001A:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 26, true), true);
return;
thumb_op_001B:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 27, true), true);
return;
thumb_op_001C:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 28, true), true);
return;
thumb_op_001D:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 29, true), true);
return;
thumb_op_001E:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 30, true), true);
return;
thumb_op_001F:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, rs, 31, true), true);
return;
thumb_op_0020:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 32, true), true);
return;
thumb_op_0021:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 1, true), true);
return;
thumb_op_0022:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 2, true), true);
return;
thumb_op_0023:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 3, true), true);
return;
thumb_op_0024:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 4, true), true);
return;
thumb_op_0025:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 5, true), true);
return;
thumb_op_0026:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 6, true), true);
return;
thumb_op_0027:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 7, true), true);
return;
thumb_op_0028:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 8, true), true);
return;
thumb_op_0029:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 9, true), true);
return;
thumb_op_002A:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 10, true), true);
return;
thumb_op_002B:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 11, true), true);
return;
thumb_op_002C:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 12, true), true);
return;
thumb_op_002D:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 13, true), true);
return;
thumb_op_002E:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 14, true), true);
return;
thumb_op_002F:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 15, true), true);
return;
thumb_op_0030:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 16, true), true);
return;
thumb_op_0031:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 17, true), true);
return;
thumb_op_0032:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 18, true), true);
return;
thumb_op_0033:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 19, true), true);
return;
thumb_op_0034:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 20, true), true);
return;
thumb_op_0035:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 21, true), true);
return;
thumb_op_0036:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 22, true), true);
return;
thumb_op_0037:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 23, true), true);
return;
thumb_op_0038:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 24, true), true);
return;
thumb_op_0039:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 25, true), true);
return;
thumb_op_003A:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 26, true), true);
return;
thumb_op_003B:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 27, true), true);
return;
thumb_op_003C:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 28, true), true);
return;
thumb_op_003D:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 29, true), true);
return;
thumb_op_003E:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 30, true), true);
return;
thumb_op_003F:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, rs, 31, true), true);
return;
thumb_op_0040:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 32, true), true);
return;
thumb_op_0041:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 1, true), true);
return;
thumb_op_0042:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 2, true), true);
return;
thumb_op_0043:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 3, true), true);
return;
thumb_op_0044:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 4, true), true);
return;
thumb_op_0045:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 5, true), true);
return;
thumb_op_0046:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 6, true), true);
return;
thumb_op_0047:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 7, true), true);
return;
thumb_op_0048:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 8, true), true);
return;
thumb_op_0049:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 9, true), true);
return;
thumb_op_004A:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 10, true), true);
return;
thumb_op_004B:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 11, true), true);
return;
thumb_op_004C:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 12, true), true);
return;
thumb_op_004D:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 13, true), true);
return;
thumb_op_004E:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 14, true), true);
return;
thumb_op_004F:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 15, true), true);
return;
thumb_op_0050:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 16, true), true);
return;
thumb_op_0051:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 17, true), true);
return;
thumb_op_0052:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 18, true), true);
return;
thumb_op_0053:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 19, true), true);
return;
thumb_op_0054:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 20, true), true);
return;
thumb_op_0055:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 21, true), true);
return;
thumb_op_0056:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 22, true), true);
return;
thumb_op_0057:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 23, true), true);
return;
thumb_op_0058:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 24, true), true);
return;
thumb_op_0059:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 25, true), true);
return;
thumb_op_005A:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 26, true), true);
return;
thumb_op_005B:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 27, true), true);
return;
thumb_op_005C:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 28, true), true);
return;
thumb_op_005D:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 29, true), true);
return;
thumb_op_005E:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 30, true), true);
return;
thumb_op_005F:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, rs, 31, true), true);
return;
thumb_op_0060:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, cpu->r[0], true);
return;
thumb_op_0061:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, cpu->r[1], true);
return;
thumb_op_0062:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, cpu->r[2], true);
return;
thumb_op_0063:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, cpu->r[3], true);
return;
thumb_op_0064:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, cpu->r[4], true);
return;
thumb_op_0065:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, cpu->r[5], true);
return;
thumb_op_0066:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, cpu->r[6], true);
return;
thumb_op_0067:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, cpu->r[7], true);
return;
thumb_op_0068:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, cpu->r[0], true);
return;
thumb_op_0069:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, cpu->r[1], true);
return;
thumb_op_006A:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, cpu->r[2], true);
return;
thumb_op_006B:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, cpu->r[3], true);
return;
thumb_op_006C:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, cpu->r[4], true);
return;
thumb_op_006D:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, cpu->r[5], true);
return;
thumb_op_006E:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, cpu->r[6], true);
return;
thumb_op_006F:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, cpu->r[7], true);
return;
thumb_op_0070:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, 0, true);
return;
thumb_op_0071:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, 1, true);
return;
thumb_op_0072:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, 2, true);
return;
thumb_op_0073:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, 3, true);
return;
thumb_op_0074:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, 4, true);
return;
thumb_op_0075:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, 5, true);
return;
thumb_op_0076:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, 6, true);
return;
thumb_op_0077:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADD(cpu, rd, rs, 7, true);
return;
thumb_op_0078:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, 0, true);
return;
thumb_op_0079:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, 1, true);
return;
thumb_op_007A:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, 2, true);
return;
thumb_op_007B:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, 3, true);
return;
thumb_op_007C:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, 4, true);
return;
thumb_op_007D:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, 5, true);
return;
thumb_op_007E:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, 6, true);
return;
thumb_op_007F:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, rs, 7, true);
return;
thumb_op_0080:
w8 = opcode & 0xFF;
rd = &cpu->r[0];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_0081:
w8 = opcode & 0xFF;
rd = &cpu->r[0];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_0082:
w8 = opcode & 0xFF;
rd = &cpu->r[0];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_0083:
w8 = opcode & 0xFF;
rd = &cpu->r[0];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_0084:
w8 = opcode & 0xFF;
rd = &cpu->r[1];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_0085:
w8 = opcode & 0xFF;
rd = &cpu->r[1];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_0086:
w8 = opcode & 0xFF;
rd = &cpu->r[1];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_0087:
w8 = opcode & 0xFF;
rd = &cpu->r[1];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_0088:
w8 = opcode & 0xFF;
rd = &cpu->r[2];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_0089:
w8 = opcode & 0xFF;
rd = &cpu->r[2];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_008A:
w8 = opcode & 0xFF;
rd = &cpu->r[2];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_008B:
w8 = opcode & 0xFF;
rd = &cpu->r[2];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_008C:
w8 = opcode & 0xFF;
rd = &cpu->r[3];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_008D:
w8 = opcode & 0xFF;
rd = &cpu->r[3];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_008E:
w8 = opcode & 0xFF;
rd = &cpu->r[3];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_008F:
w8 = opcode & 0xFF;
rd = &cpu->r[3];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_0090:
w8 = opcode & 0xFF;
rd = &cpu->r[4];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_0091:
w8 = opcode & 0xFF;
rd = &cpu->r[4];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_0092:
w8 = opcode & 0xFF;
rd = &cpu->r[4];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_0093:
w8 = opcode & 0xFF;
rd = &cpu->r[4];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_0094:
w8 = opcode & 0xFF;
rd = &cpu->r[5];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_0095:
w8 = opcode & 0xFF;
rd = &cpu->r[5];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_0096:
w8 = opcode & 0xFF;
rd = &cpu->r[5];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_0097:
w8 = opcode & 0xFF;
rd = &cpu->r[5];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_0098:
w8 = opcode & 0xFF;
rd = &cpu->r[6];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_0099:
w8 = opcode & 0xFF;
rd = &cpu->r[6];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_009A:
w8 = opcode & 0xFF;
rd = &cpu->r[6];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_009B:
w8 = opcode & 0xFF;
rd = &cpu->r[6];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_009C:
w8 = opcode & 0xFF;
rd = &cpu->r[7];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_009D:
w8 = opcode & 0xFF;
rd = &cpu->r[7];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_009E:
w8 = opcode & 0xFF;
rd = &cpu->r[7];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_009F:
w8 = opcode & 0xFF;
rd = &cpu->r[7];
alu_MOV(cpu, rd, *rd, w8, true);
return;
thumb_op_00A0:
w8 = opcode & 0xFF;
rd = &cpu->r[0];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00A1:
w8 = opcode & 0xFF;
rd = &cpu->r[0];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00A2:
w8 = opcode & 0xFF;
rd = &cpu->r[0];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00A3:
w8 = opcode & 0xFF;
rd = &cpu->r[0];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00A4:
w8 = opcode & 0xFF;
rd = &cpu->r[1];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00A5:
w8 = opcode & 0xFF;
rd = &cpu->r[1];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00A6:
w8 = opcode & 0xFF;
rd = &cpu->r[1];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00A7:
w8 = opcode & 0xFF;
rd = &cpu->r[1];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00A8:
w8 = opcode & 0xFF;
rd = &cpu->r[2];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00A9:
w8 = opcode & 0xFF;
rd = &cpu->r[2];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00AA:
w8 = opcode & 0xFF;
rd = &cpu->r[2];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00AB:
w8 = opcode & 0xFF;
rd = &cpu->r[2];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00AC:
w8 = opcode & 0xFF;
rd = &cpu->r[3];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00AD:
w8 = opcode & 0xFF;
rd = &cpu->r[3];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00AE:
w8 = opcode & 0xFF;
rd = &cpu->r[3];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00AF:
w8 = opcode & 0xFF;
rd = &cpu->r[3];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00B0:
w8 = opcode & 0xFF;
rd = &cpu->r[4];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00B1:
w8 = opcode & 0xFF;
rd = &cpu->r[4];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00B2:
w8 = opcode & 0xFF;
rd = &cpu->r[4];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00B3:
w8 = opcode & 0xFF;
rd = &cpu->r[4];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00B4:
w8 = opcode & 0xFF;
rd = &cpu->r[5];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00B5:
w8 = opcode & 0xFF;
rd = &cpu->r[5];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00B6:
w8 = opcode & 0xFF;
rd = &cpu->r[5];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00B7:
w8 = opcode & 0xFF;
rd = &cpu->r[5];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00B8:
w8 = opcode & 0xFF;
rd = &cpu->r[6];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00B9:
w8 = opcode & 0xFF;
rd = &cpu->r[6];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00BA:
w8 = opcode & 0xFF;
rd = &cpu->r[6];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00BB:
w8 = opcode & 0xFF;
rd = &cpu->r[6];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00BC:
w8 = opcode & 0xFF;
rd = &cpu->r[7];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00BD:
w8 = opcode & 0xFF;
rd = &cpu->r[7];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00BE:
w8 = opcode & 0xFF;
rd = &cpu->r[7];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00BF:
w8 = opcode & 0xFF;
rd = &cpu->r[7];
alu_CMP(cpu, rd, *rd, w8, true);
return;
thumb_op_00C0:
w8 = opcode & 0xFF;
rd = &cpu->r[0];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00C1:
w8 = opcode & 0xFF;
rd = &cpu->r[0];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00C2:
w8 = opcode & 0xFF;
rd = &cpu->r[0];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00C3:
w8 = opcode & 0xFF;
rd = &cpu->r[0];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00C4:
w8 = opcode & 0xFF;
rd = &cpu->r[1];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00C5:
w8 = opcode & 0xFF;
rd = &cpu->r[1];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00C6:
w8 = opcode & 0xFF;
rd = &cpu->r[1];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00C7:
w8 = opcode & 0xFF;
rd = &cpu->r[1];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00C8:
w8 = opcode & 0xFF;
rd = &cpu->r[2];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00C9:
w8 = opcode & 0xFF;
rd = &cpu->r[2];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00CA:
w8 = opcode & 0xFF;
rd = &cpu->r[2];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00CB:
w8 = opcode & 0xFF;
rd = &cpu->r[2];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00CC:
w8 = opcode & 0xFF;
rd = &cpu->r[3];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00CD:
w8 = opcode & 0xFF;
rd = &cpu->r[3];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00CE:
w8 = opcode & 0xFF;
rd = &cpu->r[3];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00CF:
w8 = opcode & 0xFF;
rd = &cpu->r[3];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00D0:
w8 = opcode & 0xFF;
rd = &cpu->r[4];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00D1:
w8 = opcode & 0xFF;
rd = &cpu->r[4];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00D2:
w8 = opcode & 0xFF;
rd = &cpu->r[4];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00D3:
w8 = opcode & 0xFF;
rd = &cpu->r[4];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00D4:
w8 = opcode & 0xFF;
rd = &cpu->r[5];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00D5:
w8 = opcode & 0xFF;
rd = &cpu->r[5];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00D6:
w8 = opcode & 0xFF;
rd = &cpu->r[5];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00D7:
w8 = opcode & 0xFF;
rd = &cpu->r[5];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00D8:
w8 = opcode & 0xFF;
rd = &cpu->r[6];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00D9:
w8 = opcode & 0xFF;
rd = &cpu->r[6];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00DA:
w8 = opcode & 0xFF;
rd = &cpu->r[6];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00DB:
w8 = opcode & 0xFF;
rd = &cpu->r[6];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00DC:
w8 = opcode & 0xFF;
rd = &cpu->r[7];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00DD:
w8 = opcode & 0xFF;
rd = &cpu->r[7];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00DE:
w8 = opcode & 0xFF;
rd = &cpu->r[7];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00DF:
w8 = opcode & 0xFF;
rd = &cpu->r[7];
alu_ADD(cpu, rd, *rd, w8, true);
return;
thumb_op_00E0:
w8 = opcode & 0xFF;
rd = &cpu->r[0];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00E1:
w8 = opcode & 0xFF;
rd = &cpu->r[0];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00E2:
w8 = opcode & 0xFF;
rd = &cpu->r[0];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00E3:
w8 = opcode & 0xFF;
rd = &cpu->r[0];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00E4:
w8 = opcode & 0xFF;
rd = &cpu->r[1];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00E5:
w8 = opcode & 0xFF;
rd = &cpu->r[1];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00E6:
w8 = opcode & 0xFF;
rd = &cpu->r[1];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00E7:
w8 = opcode & 0xFF;
rd = &cpu->r[1];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00E8:
w8 = opcode & 0xFF;
rd = &cpu->r[2];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00E9:
w8 = opcode & 0xFF;
rd = &cpu->r[2];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00EA:
w8 = opcode & 0xFF;
rd = &cpu->r[2];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00EB:
w8 = opcode & 0xFF;
rd = &cpu->r[2];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00EC:
w8 = opcode & 0xFF;
rd = &cpu->r[3];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00ED:
w8 = opcode & 0xFF;
rd = &cpu->r[3];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00EE:
w8 = opcode & 0xFF;
rd = &cpu->r[3];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00EF:
w8 = opcode & 0xFF;
rd = &cpu->r[3];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00F0:
w8 = opcode & 0xFF;
rd = &cpu->r[4];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00F1:
w8 = opcode & 0xFF;
rd = &cpu->r[4];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00F2:
w8 = opcode & 0xFF;
rd = &cpu->r[4];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00F3:
w8 = opcode & 0xFF;
rd = &cpu->r[4];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00F4:
w8 = opcode & 0xFF;
rd = &cpu->r[5];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00F5:
w8 = opcode & 0xFF;
rd = &cpu->r[5];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00F6:
w8 = opcode & 0xFF;
rd = &cpu->r[5];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00F7:
w8 = opcode & 0xFF;
rd = &cpu->r[5];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00F8:
w8 = opcode & 0xFF;
rd = &cpu->r[6];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00F9:
w8 = opcode & 0xFF;
rd = &cpu->r[6];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00FA:
w8 = opcode & 0xFF;
rd = &cpu->r[6];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00FB:
w8 = opcode & 0xFF;
rd = &cpu->r[6];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00FC:
w8 = opcode & 0xFF;
rd = &cpu->r[7];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00FD:
w8 = opcode & 0xFF;
rd = &cpu->r[7];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00FE:
w8 = opcode & 0xFF;
rd = &cpu->r[7];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_00FF:
w8 = opcode & 0xFF;
rd = &cpu->r[7];
alu_SUB(cpu, rd, *rd, w8, true);
return;
thumb_op_0100:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_AND(cpu, rd, *rd, rs, true);
return;
thumb_op_0101:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_EOR(cpu, rd, *rd, rs, true);
return;
thumb_op_0102:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSL(cpu, *rd, rs, true), true);
return;
thumb_op_0103:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_LSR(cpu, *rd, rs, true), true);
return;
thumb_op_0104:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ASR(cpu, *rd, rs, true), true);
return;
thumb_op_0105:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_ADC(cpu, rd, *rd, rs, true);
return;
thumb_op_0106:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_SBC(cpu, rd, *rd, rs, true);
return;
thumb_op_0107:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MOV(cpu, rd, 0, alu_ROR(cpu, *rd, rs, true), true);
return;
thumb_op_0108:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_TST(cpu, rd, *rd, rs, true);
return;
thumb_op_0109:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_SUB(cpu, rd, 0, rs, true);
return;
thumb_op_010A:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_CMP(cpu, rd, *rd, rs, true);
return;
thumb_op_010B:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_CMN(cpu, rd, *rd, rs, true);
return;
thumb_op_010C:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_ORR(cpu, rd, *rd, rs, true);
return;
thumb_op_010D:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
*rd = ((i32)*rd) * ((i32)rs);
cpu->Z_FLAG = !(*rd);
cpu->N_FLAG = *rd >> 31;
return;
thumb_op_010E:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_BIC(cpu, rd, *rd, rs, true);
return;
thumb_op_010F:
rd = &cpu->r[opcode & 0b111];
rs = cpu->r[(opcode >> 3) & 0b111];
alu_MVN(cpu, rd, *rd, rs, true);
return;
thumb_op_0110:
rd_idx = (opcode & 0b111) ;
rs_idx = ((opcode >> 3) & 0b111) ;
rd = &cpu->r[rd_idx];
rs = cpu->r[rs_idx];
alu_ADD(cpu, rd, *rd, rs, false);
cpu->pipeline_valid = rd_idx != 15;
cpu->r[15] &= 0xFFFFFFFE;
return;
thumb_op_0111:
rd_idx = (opcode & 0b111) ;
rs_idx = ((opcode >> 3) & 0b111) + 8;
rd = &cpu->r[rd_idx];
rs = cpu->r[rs_idx];
alu_ADD(cpu, rd, *rd, rs, false);
cpu->pipeline_valid = rd_idx != 15;
cpu->r[15] &= 0xFFFFFFFE;
return;
thumb_op_0112:
rd_idx = (opcode & 0b111) + 8;
rs_idx = ((opcode >> 3) & 0b111) ;
rd = &cpu->r[rd_idx];
rs = cpu->r[rs_idx];
alu_ADD(cpu, rd, *rd, rs, false);
cpu->pipeline_valid = rd_idx != 15;
cpu->r[15] &= 0xFFFFFFFE;
return;
thumb_op_0113:
rd_idx = (opcode & 0b111) + 8;
rs_idx = ((opcode >> 3) & 0b111) + 8;
rd = &cpu->r[rd_idx];
rs = cpu->r[rs_idx];
alu_ADD(cpu, rd, *rd, rs, false);
cpu->pipeline_valid = rd_idx != 15;
cpu->r[15] &= 0xFFFFFFFE;
return;
thumb_op_0114:
rd_idx = (opcode & 0b111) ;
rs_idx = ((opcode >> 3) & 0b111) ;
rd = &cpu->r[rd_idx];
rs = cpu->r[rs_idx];
alu_CMP(cpu, rd, *rd, rs, true);
return;
thumb_op_0115:
rd_idx = (opcode & 0b111) ;
rs_idx = ((opcode >> 3) & 0b111) + 8;
rd = &cpu->r[rd_idx];
rs = cpu->r[rs_idx];
alu_CMP(cpu, rd, *rd, rs, true);
return;
thumb_op_0116:
rd_idx = (opcode & 0b111) + 8;
rs_idx = ((opcode >> 3) & 0b111) ;
rd = &cpu->r[rd_idx];
rs = cpu->r[rs_idx];
alu_CMP(cpu, rd, *rd, rs, true);
return;
thumb_op_0117:
rd_idx = (opcode & 0b111) + 8;
rs_idx = ((opcode >> 3) & 0b111) + 8;
rd = &cpu->r[rd_idx];
rs = cpu->r[rs_idx];
alu_CMP(cpu, rd, *rd, rs, true);
return;
thumb_op_0118:
rd_idx = (opcode & 0b111) ;
rs_idx = ((opcode >> 3) & 0b111) ;
rd = &cpu->r[rd_idx];
rs = cpu->r[rs_idx];
alu_MOV(cpu, rd, *rd, rs, false);
cpu->pipeline_valid = rd_idx != 15;
if(rd_idx == 15)
cpu->r[15] &= 0xFFFFFFFE;
return;
thumb_op_0119:
rd_idx = (opcode & 0b111) ;
rs_idx = ((opcode >> 3) & 0b111) + 8;
rd = &cpu->r[rd_idx];
rs = cpu->r[rs_idx];
alu_MOV(cpu, rd, *rd, rs, false);
cpu->pipeline_valid = rd_idx != 15;
if(rd_idx == 15)
cpu->r[15] &= 0xFFFFFFFE;
return;
thumb_op_011A:
rd_idx = (opcode & 0b111) + 8;
rs_idx = ((opcode >> 3) & 0b111) ;
rd = &cpu->r[rd_idx];
rs = cpu->r[rs_idx];
alu_MOV(cpu, rd, *rd, rs, false);
cpu->pipeline_valid = rd_idx != 15;
if(rd_idx == 15)
cpu->r[15] &= 0xFFFFFFFE;
return;
thumb_op_011B:
rd_idx = (opcode & 0b111) + 8;
rs_idx = ((opcode >> 3) & 0b111) + 8;
rd = &cpu->r[rd_idx];
rs = cpu->r[rs_idx];
alu_MOV(cpu, rd, *rd, rs, false);
cpu->pipeline_valid = rd_idx != 15;
if(rd_idx == 15)
cpu->r[15] &= 0xFFFFFFFE;
return;
thumb_op_011C:
rs_idx = ((opcode >> 3) & 0b111) ;
rs = cpu->r[rs_idx];
cpu->r[15] = rs;
cpu->thumb_mode = (cpu->r[15] & 0b1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->pipeline_valid = false;
return;
thumb_op_011D:
rs_idx = ((opcode >> 3) & 0b111) + 8;
rs = cpu->r[rs_idx];
cpu->r[15] = rs;
cpu->thumb_mode = (cpu->r[15] & 0b1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->pipeline_valid = false;
return;
thumb_op_011E:
rs_idx = ((opcode >> 3) & 0b111) ;
rs = cpu->r[rs_idx];
cpu->r[15] = rs;
cpu->thumb_mode = (cpu->r[15] & 0b1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->pipeline_valid = false;
return;
thumb_op_011F:
rs_idx = ((opcode >> 3) & 0b111) + 8;
rs = cpu->r[rs_idx];
cpu->r[15] = rs;
cpu->thumb_mode = (cpu->r[15] & 0b1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->pipeline_valid = false;
return;
thumb_op_0120:
w8 = opcode & 0xFF;
rd = &cpu->r[0];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_0121:
w8 = opcode & 0xFF;
rd = &cpu->r[0];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_0122:
w8 = opcode & 0xFF;
rd = &cpu->r[0];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_0123:
w8 = opcode & 0xFF;
rd = &cpu->r[0];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_0124:
w8 = opcode & 0xFF;
rd = &cpu->r[1];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_0125:
w8 = opcode & 0xFF;
rd = &cpu->r[1];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_0126:
w8 = opcode & 0xFF;
rd = &cpu->r[1];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_0127:
w8 = opcode & 0xFF;
rd = &cpu->r[1];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_0128:
w8 = opcode & 0xFF;
rd = &cpu->r[2];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_0129:
w8 = opcode & 0xFF;
rd = &cpu->r[2];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_012A:
w8 = opcode & 0xFF;
rd = &cpu->r[2];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_012B:
w8 = opcode & 0xFF;
rd = &cpu->r[2];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_012C:
w8 = opcode & 0xFF;
rd = &cpu->r[3];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_012D:
w8 = opcode & 0xFF;
rd = &cpu->r[3];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_012E:
w8 = opcode & 0xFF;
rd = &cpu->r[3];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_012F:
w8 = opcode & 0xFF;
rd = &cpu->r[3];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_0130:
w8 = opcode & 0xFF;
rd = &cpu->r[4];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_0131:
w8 = opcode & 0xFF;
rd = &cpu->r[4];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_0132:
w8 = opcode & 0xFF;
rd = &cpu->r[4];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_0133:
w8 = opcode & 0xFF;
rd = &cpu->r[4];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_0134:
w8 = opcode & 0xFF;
rd = &cpu->r[5];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_0135:
w8 = opcode & 0xFF;
rd = &cpu->r[5];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_0136:
w8 = opcode & 0xFF;
rd = &cpu->r[5];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_0137:
w8 = opcode & 0xFF;
rd = &cpu->r[5];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_0138:
w8 = opcode & 0xFF;
rd = &cpu->r[6];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_0139:
w8 = opcode & 0xFF;
rd = &cpu->r[6];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_013A:
w8 = opcode & 0xFF;
rd = &cpu->r[6];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_013B:
w8 = opcode & 0xFF;
rd = &cpu->r[6];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_013C:
w8 = opcode & 0xFF;
rd = &cpu->r[7];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_013D:
w8 = opcode & 0xFF;
rd = &cpu->r[7];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_013E:
w8 = opcode & 0xFF;
rd = &cpu->r[7];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_013F:
w8 = opcode & 0xFF;
rd = &cpu->r[7];
addr = (cpu->r[15] & 0xFFFFFFFC) + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
return;
thumb_op_0140:
ro = cpu->r[0];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_0141:
ro = cpu->r[1];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_0142:
ro = cpu->r[2];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_0143:
ro = cpu->r[3];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_0144:
ro = cpu->r[4];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_0145:
ro = cpu->r[5];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_0146:
ro = cpu->r[6];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_0147:
ro = cpu->r[7];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_0148:
ro = cpu->r[0];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
cpu->writeHalfWord(cpu, addr, *rd);
return;
thumb_op_0149:
ro = cpu->r[1];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
cpu->writeHalfWord(cpu, addr, *rd);
return;
thumb_op_014A:
ro = cpu->r[2];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
cpu->writeHalfWord(cpu, addr, *rd);
return;
thumb_op_014B:
ro = cpu->r[3];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
cpu->writeHalfWord(cpu, addr, *rd);
return;
thumb_op_014C:
ro = cpu->r[4];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
cpu->writeHalfWord(cpu, addr, *rd);
return;
thumb_op_014D:
ro = cpu->r[5];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
cpu->writeHalfWord(cpu, addr, *rd);
return;
thumb_op_014E:
ro = cpu->r[6];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
cpu->writeHalfWord(cpu, addr, *rd);
return;
thumb_op_014F:
ro = cpu->r[7];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
cpu->writeHalfWord(cpu, addr, *rd);
return;
thumb_op_0150:
ro = cpu->r[0];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
cpu->writeByte(cpu, addr, *rd);
return;
thumb_op_0151:
ro = cpu->r[1];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
cpu->writeByte(cpu, addr, *rd);
return;
thumb_op_0152:
ro = cpu->r[2];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
cpu->writeByte(cpu, addr, *rd);
return;
thumb_op_0153:
ro = cpu->r[3];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
cpu->writeByte(cpu, addr, *rd);
return;
thumb_op_0154:
ro = cpu->r[4];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
cpu->writeByte(cpu, addr, *rd);
return;
thumb_op_0155:
ro = cpu->r[5];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
cpu->writeByte(cpu, addr, *rd);
return;
thumb_op_0156:
ro = cpu->r[6];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
cpu->writeByte(cpu, addr, *rd);
return;
thumb_op_0157:
ro = cpu->r[7];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
cpu->writeByte(cpu, addr, *rd);
return;
thumb_op_0158:
ro = cpu->r[0];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readByte(cpu, addr);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
return;
thumb_op_0159:
ro = cpu->r[1];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readByte(cpu, addr);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
return;
thumb_op_015A:
ro = cpu->r[2];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readByte(cpu, addr);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
return;
thumb_op_015B:
ro = cpu->r[3];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readByte(cpu, addr);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
return;
thumb_op_015C:
ro = cpu->r[4];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readByte(cpu, addr);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
return;
thumb_op_015D:
ro = cpu->r[5];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readByte(cpu, addr);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
return;
thumb_op_015E:
ro = cpu->r[6];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readByte(cpu, addr);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
return;
thumb_op_015F:
ro = cpu->r[7];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readByte(cpu, addr);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
return;
thumb_op_0160:
ro = cpu->r[0];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_0161:
ro = cpu->r[1];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_0162:
ro = cpu->r[2];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_0163:
ro = cpu->r[3];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_0164:
ro = cpu->r[4];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_0165:
ro = cpu->r[5];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_0166:
ro = cpu->r[6];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_0167:
ro = cpu->r[7];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_0168:
ro = cpu->r[0];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readHalfWord(cpu, addr);
if(addr & 1){
*rd = (*rd >> 8) | (*rd << 24);
} else {
}
return;
thumb_op_0169:
ro = cpu->r[1];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readHalfWord(cpu, addr);
if(addr & 1){
*rd = (*rd >> 8) | (*rd << 24);
} else {
}
return;
thumb_op_016A:
ro = cpu->r[2];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readHalfWord(cpu, addr);
if(addr & 1){
*rd = (*rd >> 8) | (*rd << 24);
} else {
}
return;
thumb_op_016B:
ro = cpu->r[3];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readHalfWord(cpu, addr);
if(addr & 1){
*rd = (*rd >> 8) | (*rd << 24);
} else {
}
return;
thumb_op_016C:
ro = cpu->r[4];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readHalfWord(cpu, addr);
if(addr & 1){
*rd = (*rd >> 8) | (*rd << 24);
} else {
}
return;
thumb_op_016D:
ro = cpu->r[5];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readHalfWord(cpu, addr);
if(addr & 1){
*rd = (*rd >> 8) | (*rd << 24);
} else {
}
return;
thumb_op_016E:
ro = cpu->r[6];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readHalfWord(cpu, addr);
if(addr & 1){
*rd = (*rd >> 8) | (*rd << 24);
} else {
}
return;
thumb_op_016F:
ro = cpu->r[7];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readHalfWord(cpu, addr);
if(addr & 1){
*rd = (*rd >> 8) | (*rd << 24);
} else {
}
return;
thumb_op_0170:
ro = cpu->r[0];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readByte(cpu, addr);
return;
thumb_op_0171:
ro = cpu->r[1];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readByte(cpu, addr);
return;
thumb_op_0172:
ro = cpu->r[2];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readByte(cpu, addr);
return;
thumb_op_0173:
ro = cpu->r[3];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readByte(cpu, addr);
return;
thumb_op_0174:
ro = cpu->r[4];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readByte(cpu, addr);
return;
thumb_op_0175:
ro = cpu->r[5];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readByte(cpu, addr);
return;
thumb_op_0176:
ro = cpu->r[6];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readByte(cpu, addr);
return;
thumb_op_0177:
ro = cpu->r[7];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readByte(cpu, addr);
return;
thumb_op_0178:
ro = cpu->r[0];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readHalfWord(cpu, addr);
if(addr & 1){
*rd = cpu->readByte(cpu, addr);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
} else {
if(*rd & 0xFFFF8000)
*rd |= 0xFFFF0000;
}
return;
thumb_op_0179:
ro = cpu->r[1];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readHalfWord(cpu, addr);
if(addr & 1){
*rd = cpu->readByte(cpu, addr);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
} else {
if(*rd & 0xFFFF8000)
*rd |= 0xFFFF0000;
}
return;
thumb_op_017A:
ro = cpu->r[2];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readHalfWord(cpu, addr);
if(addr & 1){
*rd = cpu->readByte(cpu, addr);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
} else {
if(*rd & 0xFFFF8000)
*rd |= 0xFFFF0000;
}
return;
thumb_op_017B:
ro = cpu->r[3];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readHalfWord(cpu, addr);
if(addr & 1){
*rd = cpu->readByte(cpu, addr);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
} else {
if(*rd & 0xFFFF8000)
*rd |= 0xFFFF0000;
}
return;
thumb_op_017C:
ro = cpu->r[4];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readHalfWord(cpu, addr);
if(addr & 1){
*rd = cpu->readByte(cpu, addr);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
} else {
if(*rd & 0xFFFF8000)
*rd |= 0xFFFF0000;
}
return;
thumb_op_017D:
ro = cpu->r[5];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readHalfWord(cpu, addr);
if(addr & 1){
*rd = cpu->readByte(cpu, addr);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
} else {
if(*rd & 0xFFFF8000)
*rd |= 0xFFFF0000;
}
return;
thumb_op_017E:
ro = cpu->r[6];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readHalfWord(cpu, addr);
if(addr & 1){
*rd = cpu->readByte(cpu, addr);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
} else {
if(*rd & 0xFFFF8000)
*rd |= 0xFFFF0000;
}
return;
thumb_op_017F:
ro = cpu->r[7];
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + ro;
*rd = cpu->readHalfWord(cpu, addr);
if(addr & 1){
*rd = cpu->readByte(cpu, addr);
if(*rd & 0x80)
*rd |= 0xFFFFFF00;
} else {
if(*rd & 0xFFFF8000)
*rd |= 0xFFFF0000;
}
return;
thumb_op_0180:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 0, *rd);
return;
thumb_op_0181:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 4, *rd);
return;
thumb_op_0182:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 8, *rd);
return;
thumb_op_0183:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 12, *rd);
return;
thumb_op_0184:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 16, *rd);
return;
thumb_op_0185:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 20, *rd);
return;
thumb_op_0186:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 24, *rd);
return;
thumb_op_0187:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 28, *rd);
return;
thumb_op_0188:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 32, *rd);
return;
thumb_op_0189:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 36, *rd);
return;
thumb_op_018A:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 40, *rd);
return;
thumb_op_018B:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 44, *rd);
return;
thumb_op_018C:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 48, *rd);
return;
thumb_op_018D:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 52, *rd);
return;
thumb_op_018E:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 56, *rd);
return;
thumb_op_018F:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 60, *rd);
return;
thumb_op_0190:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 64, *rd);
return;
thumb_op_0191:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 68, *rd);
return;
thumb_op_0192:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 72, *rd);
return;
thumb_op_0193:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 76, *rd);
return;
thumb_op_0194:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 80, *rd);
return;
thumb_op_0195:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 84, *rd);
return;
thumb_op_0196:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 88, *rd);
return;
thumb_op_0197:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 92, *rd);
return;
thumb_op_0198:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 96, *rd);
return;
thumb_op_0199:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 100, *rd);
return;
thumb_op_019A:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 104, *rd);
return;
thumb_op_019B:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 108, *rd);
return;
thumb_op_019C:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 112, *rd);
return;
thumb_op_019D:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 116, *rd);
return;
thumb_op_019E:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 120, *rd);
return;
thumb_op_019F:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeWord(cpu, rb + 124, *rd);
return;
thumb_op_01A0:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (0 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01A1:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (1 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01A2:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (2 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01A3:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (3 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01A4:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (4 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01A5:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (5 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01A6:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (6 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01A7:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (7 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01A8:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01A9:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (9 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01AA:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (10 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01AB:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (11 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01AC:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (12 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01AD:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (13 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01AE:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (14 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01AF:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (15 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01B0:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (16 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01B1:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (17 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01B2:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (18 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01B3:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (19 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01B4:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (20 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01B5:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (21 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01B6:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (22 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01B7:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (23 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01B8:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (24 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01B9:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (25 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01BA:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (26 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01BB:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (27 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01BC:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (28 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01BD:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (29 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01BE:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (30 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01BF:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
addr = rb + (31 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_01C0:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 0, *rd);
return;
thumb_op_01C1:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 1, *rd);
return;
thumb_op_01C2:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 2, *rd);
return;
thumb_op_01C3:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 3, *rd);
return;
thumb_op_01C4:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 4, *rd);
return;
thumb_op_01C5:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 5, *rd);
return;
thumb_op_01C6:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 6, *rd);
return;
thumb_op_01C7:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 7, *rd);
return;
thumb_op_01C8:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 8, *rd);
return;
thumb_op_01C9:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 9, *rd);
return;
thumb_op_01CA:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 10, *rd);
return;
thumb_op_01CB:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 11, *rd);
return;
thumb_op_01CC:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 12, *rd);
return;
thumb_op_01CD:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 13, *rd);
return;
thumb_op_01CE:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 14, *rd);
return;
thumb_op_01CF:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 15, *rd);
return;
thumb_op_01D0:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 16, *rd);
return;
thumb_op_01D1:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 17, *rd);
return;
thumb_op_01D2:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 18, *rd);
return;
thumb_op_01D3:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 19, *rd);
return;
thumb_op_01D4:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 20, *rd);
return;
thumb_op_01D5:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 21, *rd);
return;
thumb_op_01D6:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 22, *rd);
return;
thumb_op_01D7:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 23, *rd);
return;
thumb_op_01D8:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 24, *rd);
return;
thumb_op_01D9:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 25, *rd);
return;
thumb_op_01DA:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 26, *rd);
return;
thumb_op_01DB:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 27, *rd);
return;
thumb_op_01DC:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 28, *rd);
return;
thumb_op_01DD:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 29, *rd);
return;
thumb_op_01DE:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 30, *rd);
return;
thumb_op_01DF:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
cpu->writeByte(cpu, rb + 31, *rd);
return;
thumb_op_01E0:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 0);
return;
thumb_op_01E1:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 1);
return;
thumb_op_01E2:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 2);
return;
thumb_op_01E3:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 3);
return;
thumb_op_01E4:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 4);
return;
thumb_op_01E5:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 5);
return;
thumb_op_01E6:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 6);
return;
thumb_op_01E7:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 7);
return;
thumb_op_01E8:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 8);
return;
thumb_op_01E9:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 9);
return;
thumb_op_01EA:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 10);
return;
thumb_op_01EB:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 11);
return;
thumb_op_01EC:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 12);
return;
thumb_op_01ED:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 13);
return;
thumb_op_01EE:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 14);
return;
thumb_op_01EF:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 15);
return;
thumb_op_01F0:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 16);
return;
thumb_op_01F1:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 17);
return;
thumb_op_01F2:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 18);
return;
thumb_op_01F3:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 19);
return;
thumb_op_01F4:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 20);
return;
thumb_op_01F5:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 21);
return;
thumb_op_01F6:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 22);
return;
thumb_op_01F7:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 23);
return;
thumb_op_01F8:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 24);
return;
thumb_op_01F9:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 25);
return;
thumb_op_01FA:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 26);
return;
thumb_op_01FB:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 27);
return;
thumb_op_01FC:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 28);
return;
thumb_op_01FD:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 29);
return;
thumb_op_01FE:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 30);
return;
thumb_op_01FF:
rb = cpu->r[(opcode >> 3) & 0b111];
rd = &cpu->r[opcode & 0b111];
*rd = cpu->readByte(cpu, rb + 31);
return;
thumb_op_0200:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 0, *rd);
return;
thumb_op_0201:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 2, *rd);
return;
thumb_op_0202:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 4, *rd);
return;
thumb_op_0203:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 6, *rd);
return;
thumb_op_0204:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 8, *rd);
return;
thumb_op_0205:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 10, *rd);
return;
thumb_op_0206:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 12, *rd);
return;
thumb_op_0207:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 14, *rd);
return;
thumb_op_0208:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 16, *rd);
return;
thumb_op_0209:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 18, *rd);
return;
thumb_op_020A:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 20, *rd);
return;
thumb_op_020B:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 22, *rd);
return;
thumb_op_020C:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 24, *rd);
return;
thumb_op_020D:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 26, *rd);
return;
thumb_op_020E:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 28, *rd);
return;
thumb_op_020F:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 30, *rd);
return;
thumb_op_0210:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 32, *rd);
return;
thumb_op_0211:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 34, *rd);
return;
thumb_op_0212:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 36, *rd);
return;
thumb_op_0213:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 38, *rd);
return;
thumb_op_0214:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 40, *rd);
return;
thumb_op_0215:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 42, *rd);
return;
thumb_op_0216:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 44, *rd);
return;
thumb_op_0217:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 46, *rd);
return;
thumb_op_0218:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 48, *rd);
return;
thumb_op_0219:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 50, *rd);
return;
thumb_op_021A:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 52, *rd);
return;
thumb_op_021B:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 54, *rd);
return;
thumb_op_021C:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 56, *rd);
return;
thumb_op_021D:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 58, *rd);
return;
thumb_op_021E:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 60, *rd);
return;
thumb_op_021F:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
cpu->writeHalfWord(cpu, rb + 62, *rd);
return;
thumb_op_0220:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 0);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_0221:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 2);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_0222:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 4);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_0223:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 6);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_0224:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 8);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_0225:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 10);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_0226:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 12);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_0227:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 14);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_0228:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 16);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_0229:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 18);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_022A:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 20);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_022B:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 22);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_022C:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 24);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_022D:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 26);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_022E:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 28);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_022F:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 30);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_0230:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 32);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_0231:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 34);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_0232:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 36);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_0233:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 38);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_0234:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 40);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_0235:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 42);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_0236:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 44);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_0237:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 46);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_0238:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 48);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_0239:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 50);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_023A:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 52);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_023B:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 54);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_023C:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 56);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_023D:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 58);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_023E:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 60);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_023F:
rd = &cpu->r[opcode & 0b111];
rb = cpu->r[(opcode >> 3) & 0b111];
*rd = cpu->readHalfWord(cpu, rb + 62);
if(rb & 1)
*rd = (*rd << 24) | (*rd >> 8);
return;
thumb_op_0240:
rd = &cpu->r[0];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_0241:
rd = &cpu->r[0];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_0242:
rd = &cpu->r[0];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_0243:
rd = &cpu->r[0];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_0244:
rd = &cpu->r[1];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_0245:
rd = &cpu->r[1];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_0246:
rd = &cpu->r[1];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_0247:
rd = &cpu->r[1];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_0248:
rd = &cpu->r[2];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_0249:
rd = &cpu->r[2];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_024A:
rd = &cpu->r[2];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_024B:
rd = &cpu->r[2];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_024C:
rd = &cpu->r[3];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_024D:
rd = &cpu->r[3];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_024E:
rd = &cpu->r[3];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_024F:
rd = &cpu->r[3];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_0250:
rd = &cpu->r[4];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_0251:
rd = &cpu->r[4];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_0252:
rd = &cpu->r[4];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_0253:
rd = &cpu->r[4];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_0254:
rd = &cpu->r[5];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_0255:
rd = &cpu->r[5];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_0256:
rd = &cpu->r[5];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_0257:
rd = &cpu->r[5];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_0258:
rd = &cpu->r[6];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_0259:
rd = &cpu->r[6];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_025A:
rd = &cpu->r[6];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_025B:
rd = &cpu->r[6];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_025C:
rd = &cpu->r[7];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_025D:
rd = &cpu->r[7];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_025E:
rd = &cpu->r[7];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_025F:
rd = &cpu->r[7];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
cpu->writeWord(cpu, addr, *rd);
return;
thumb_op_0260:
rd = &cpu->r[0];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_0261:
rd = &cpu->r[0];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_0262:
rd = &cpu->r[0];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_0263:
rd = &cpu->r[0];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_0264:
rd = &cpu->r[1];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_0265:
rd = &cpu->r[1];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_0266:
rd = &cpu->r[1];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_0267:
rd = &cpu->r[1];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_0268:
rd = &cpu->r[2];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_0269:
rd = &cpu->r[2];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_026A:
rd = &cpu->r[2];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_026B:
rd = &cpu->r[2];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_026C:
rd = &cpu->r[3];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_026D:
rd = &cpu->r[3];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_026E:
rd = &cpu->r[3];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_026F:
rd = &cpu->r[3];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_0270:
rd = &cpu->r[4];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_0271:
rd = &cpu->r[4];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_0272:
rd = &cpu->r[4];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_0273:
rd = &cpu->r[4];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_0274:
rd = &cpu->r[5];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_0275:
rd = &cpu->r[5];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_0276:
rd = &cpu->r[5];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_0277:
rd = &cpu->r[5];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_0278:
rd = &cpu->r[6];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_0279:
rd = &cpu->r[6];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_027A:
rd = &cpu->r[6];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_027B:
rd = &cpu->r[6];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_027C:
rd = &cpu->r[7];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_027D:
rd = &cpu->r[7];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_027E:
rd = &cpu->r[7];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_027F:
rd = &cpu->r[7];
w8 = opcode & 0xFF;
addr = cpu->r[13] + (w8 << 2);
*rd = cpu->readWord(cpu, addr);
*rd = alu_ROR(cpu, *rd, (addr & 0b11) << 3, false);
return;
thumb_op_0280:
w8 = opcode & 0xFF;
rd = &cpu->r[0];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_0281:
w8 = opcode & 0xFF;
rd = &cpu->r[0];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_0282:
w8 = opcode & 0xFF;
rd = &cpu->r[0];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_0283:
w8 = opcode & 0xFF;
rd = &cpu->r[0];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_0284:
w8 = opcode & 0xFF;
rd = &cpu->r[1];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_0285:
w8 = opcode & 0xFF;
rd = &cpu->r[1];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_0286:
w8 = opcode & 0xFF;
rd = &cpu->r[1];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_0287:
w8 = opcode & 0xFF;
rd = &cpu->r[1];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_0288:
w8 = opcode & 0xFF;
rd = &cpu->r[2];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_0289:
w8 = opcode & 0xFF;
rd = &cpu->r[2];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_028A:
w8 = opcode & 0xFF;
rd = &cpu->r[2];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_028B:
w8 = opcode & 0xFF;
rd = &cpu->r[2];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_028C:
w8 = opcode & 0xFF;
rd = &cpu->r[3];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_028D:
w8 = opcode & 0xFF;
rd = &cpu->r[3];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_028E:
w8 = opcode & 0xFF;
rd = &cpu->r[3];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_028F:
w8 = opcode & 0xFF;
rd = &cpu->r[3];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_0290:
w8 = opcode & 0xFF;
rd = &cpu->r[4];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_0291:
w8 = opcode & 0xFF;
rd = &cpu->r[4];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_0292:
w8 = opcode & 0xFF;
rd = &cpu->r[4];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_0293:
w8 = opcode & 0xFF;
rd = &cpu->r[4];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_0294:
w8 = opcode & 0xFF;
rd = &cpu->r[5];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_0295:
w8 = opcode & 0xFF;
rd = &cpu->r[5];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_0296:
w8 = opcode & 0xFF;
rd = &cpu->r[5];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_0297:
w8 = opcode & 0xFF;
rd = &cpu->r[5];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_0298:
w8 = opcode & 0xFF;
rd = &cpu->r[6];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_0299:
w8 = opcode & 0xFF;
rd = &cpu->r[6];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_029A:
w8 = opcode & 0xFF;
rd = &cpu->r[6];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_029B:
w8 = opcode & 0xFF;
rd = &cpu->r[6];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_029C:
w8 = opcode & 0xFF;
rd = &cpu->r[7];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_029D:
w8 = opcode & 0xFF;
rd = &cpu->r[7];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_029E:
w8 = opcode & 0xFF;
rd = &cpu->r[7];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_029F:
w8 = opcode & 0xFF;
rd = &cpu->r[7];
*rd = cpu->r[15] & 0xFFFFFFFC;
*rd += w8 << 2;
return;
thumb_op_02A0:
w8 = opcode & 0xFF;
rd = &cpu->r[0];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02A1:
w8 = opcode & 0xFF;
rd = &cpu->r[0];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02A2:
w8 = opcode & 0xFF;
rd = &cpu->r[0];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02A3:
w8 = opcode & 0xFF;
rd = &cpu->r[0];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02A4:
w8 = opcode & 0xFF;
rd = &cpu->r[1];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02A5:
w8 = opcode & 0xFF;
rd = &cpu->r[1];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02A6:
w8 = opcode & 0xFF;
rd = &cpu->r[1];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02A7:
w8 = opcode & 0xFF;
rd = &cpu->r[1];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02A8:
w8 = opcode & 0xFF;
rd = &cpu->r[2];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02A9:
w8 = opcode & 0xFF;
rd = &cpu->r[2];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02AA:
w8 = opcode & 0xFF;
rd = &cpu->r[2];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02AB:
w8 = opcode & 0xFF;
rd = &cpu->r[2];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02AC:
w8 = opcode & 0xFF;
rd = &cpu->r[3];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02AD:
w8 = opcode & 0xFF;
rd = &cpu->r[3];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02AE:
w8 = opcode & 0xFF;
rd = &cpu->r[3];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02AF:
w8 = opcode & 0xFF;
rd = &cpu->r[3];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02B0:
w8 = opcode & 0xFF;
rd = &cpu->r[4];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02B1:
w8 = opcode & 0xFF;
rd = &cpu->r[4];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02B2:
w8 = opcode & 0xFF;
rd = &cpu->r[4];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02B3:
w8 = opcode & 0xFF;
rd = &cpu->r[4];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02B4:
w8 = opcode & 0xFF;
rd = &cpu->r[5];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02B5:
w8 = opcode & 0xFF;
rd = &cpu->r[5];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02B6:
w8 = opcode & 0xFF;
rd = &cpu->r[5];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02B7:
w8 = opcode & 0xFF;
rd = &cpu->r[5];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02B8:
w8 = opcode & 0xFF;
rd = &cpu->r[6];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02B9:
w8 = opcode & 0xFF;
rd = &cpu->r[6];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02BA:
w8 = opcode & 0xFF;
rd = &cpu->r[6];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02BB:
w8 = opcode & 0xFF;
rd = &cpu->r[6];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02BC:
w8 = opcode & 0xFF;
rd = &cpu->r[7];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02BD:
w8 = opcode & 0xFF;
rd = &cpu->r[7];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02BE:
w8 = opcode & 0xFF;
rd = &cpu->r[7];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02BF:
w8 = opcode & 0xFF;
rd = &cpu->r[7];
*rd = cpu->r[13];
*rd += w8 << 2;
return;
thumb_op_02C0:
w9 = (opcode & 0b1111111) << 2;
cpu->r[13] += w9;
return;
thumb_op_02C1:
w9 = (opcode & 0b1111111) << 2;
cpu->r[13] += w9;
return;
thumb_op_02C2:
w9 = (opcode & 0b1111111) << 2;
cpu->r[13] -= w9;
return;
thumb_op_02C3:
w9 = (opcode & 0b1111111) << 2;
cpu->r[13] -= w9;
return;
thumb_op_02C4:
return;
thumb_op_02C5:
return;
thumb_op_02C6:
return;
thumb_op_02C7:
return;
thumb_op_02C8:
return;
thumb_op_02C9:
return;
thumb_op_02CA:
return;
thumb_op_02CB:
return;
thumb_op_02CC:
return;
thumb_op_02CD:
return;
thumb_op_02CE:
return;
thumb_op_02CF:
return;
thumb_op_02D0:
rlist = opcode & 0xFF;
count = __builtin_popcount(rlist);
cpu->r[13] -= (count + 0) * 4;
rlist = opcode & 0xFF;
for(int i = 0; i < 16 && rlist; i++){
should_transfer = rlist & 1;
rlist >>= 1;
if(!should_transfer)
continue;
cpu->writeWord(cpu, cpu->r[13], cpu->r[i]);
cpu->r[13] += 4;
}
cpu->r[13] -= (count + 0) * 4;
return;
thumb_op_02D1:
rlist = opcode & 0xFF;
count = __builtin_popcount(rlist);
cpu->r[13] -= (count + 0) * 4;
rlist = opcode & 0xFF;
for(int i = 0; i < 16 && rlist; i++){
should_transfer = rlist & 1;
rlist >>= 1;
if(!should_transfer)
continue;
cpu->writeWord(cpu, cpu->r[13], cpu->r[i]);
cpu->r[13] += 4;
}
cpu->r[13] -= (count + 0) * 4;
return;
thumb_op_02D2:
rlist = opcode & 0xFF;
count = __builtin_popcount(rlist);
cpu->r[13] -= (count + 0) * 4;
rlist = opcode & 0xFF;
for(int i = 0; i < 16 && rlist; i++){
should_transfer = rlist & 1;
rlist >>= 1;
if(!should_transfer)
continue;
cpu->writeWord(cpu, cpu->r[13], cpu->r[i]);
cpu->r[13] += 4;
}
cpu->r[13] -= (count + 0) * 4;
return;
thumb_op_02D3:
rlist = opcode & 0xFF;
count = __builtin_popcount(rlist);
cpu->r[13] -= (count + 0) * 4;
rlist = opcode & 0xFF;
for(int i = 0; i < 16 && rlist; i++){
should_transfer = rlist & 1;
rlist >>= 1;
if(!should_transfer)
continue;
cpu->writeWord(cpu, cpu->r[13], cpu->r[i]);
cpu->r[13] += 4;
}
cpu->r[13] -= (count + 0) * 4;
return;
thumb_op_02D4:
rlist = opcode & 0xFF;
count = __builtin_popcount(rlist);
cpu->r[13] -= (count + 1) * 4;
rlist = opcode & 0xFF;
for(int i = 0; i < 16 && rlist; i++){
should_transfer = rlist & 1;
rlist >>= 1;
if(!should_transfer)
continue;
cpu->writeWord(cpu, cpu->r[13], cpu->r[i]);
cpu->r[13] += 4;
}
cpu->writeWord(cpu, cpu->r[13], cpu->r[14]);
cpu->r[13] += 4;
cpu->r[13] -= (count + 1) * 4;
return;
thumb_op_02D5:
rlist = opcode & 0xFF;
count = __builtin_popcount(rlist);
cpu->r[13] -= (count + 1) * 4;
rlist = opcode & 0xFF;
for(int i = 0; i < 16 && rlist; i++){
should_transfer = rlist & 1;
rlist >>= 1;
if(!should_transfer)
continue;
cpu->writeWord(cpu, cpu->r[13], cpu->r[i]);
cpu->r[13] += 4;
}
cpu->writeWord(cpu, cpu->r[13], cpu->r[14]);
cpu->r[13] += 4;
cpu->r[13] -= (count + 1) * 4;
return;
thumb_op_02D6:
rlist = opcode & 0xFF;
count = __builtin_popcount(rlist);
cpu->r[13] -= (count + 1) * 4;
rlist = opcode & 0xFF;
for(int i = 0; i < 16 && rlist; i++){
should_transfer = rlist & 1;
rlist >>= 1;
if(!should_transfer)
continue;
cpu->writeWord(cpu, cpu->r[13], cpu->r[i]);
cpu->r[13] += 4;
}
cpu->writeWord(cpu, cpu->r[13], cpu->r[14]);
cpu->r[13] += 4;
cpu->r[13] -= (count + 1) * 4;
return;
thumb_op_02D7:
rlist = opcode & 0xFF;
count = __builtin_popcount(rlist);
cpu->r[13] -= (count + 1) * 4;
rlist = opcode & 0xFF;
for(int i = 0; i < 16 && rlist; i++){
should_transfer = rlist & 1;
rlist >>= 1;
if(!should_transfer)
continue;
cpu->writeWord(cpu, cpu->r[13], cpu->r[i]);
cpu->r[13] += 4;
}
cpu->writeWord(cpu, cpu->r[13], cpu->r[14]);
cpu->r[13] += 4;
cpu->r[13] -= (count + 1) * 4;
return;
thumb_op_02D8:
return;
thumb_op_02D9:
return;
thumb_op_02DA:
return;
thumb_op_02DB:
return;
thumb_op_02DC:
return;
thumb_op_02DD:
return;
thumb_op_02DE:
return;
thumb_op_02DF:
return;
thumb_op_02E0:
return;
thumb_op_02E1:
return;
thumb_op_02E2:
return;
thumb_op_02E3:
return;
thumb_op_02E4:
return;
thumb_op_02E5:
return;
thumb_op_02E6:
return;
thumb_op_02E7:
return;
thumb_op_02E8:
return;
thumb_op_02E9:
return;
thumb_op_02EA:
return;
thumb_op_02EB:
return;
thumb_op_02EC:
return;
thumb_op_02ED:
return;
thumb_op_02EE:
return;
thumb_op_02EF:
return;
thumb_op_02F0:
rlist = opcode & 0xFF;
count = __builtin_popcount(rlist);
for(int i = 0; i < 16 && rlist; i++){
should_transfer = rlist & 1;
rlist >>= 1;
if(!should_transfer)
continue;
cpu->r[i] = cpu->readWord(cpu, cpu->r[13]);
cpu->r[13] += 4;
}
return;
thumb_op_02F1:
rlist = opcode & 0xFF;
count = __builtin_popcount(rlist);
for(int i = 0; i < 16 && rlist; i++){
should_transfer = rlist & 1;
rlist >>= 1;
if(!should_transfer)
continue;
cpu->r[i] = cpu->readWord(cpu, cpu->r[13]);
cpu->r[13] += 4;
}
return;
thumb_op_02F2:
rlist = opcode & 0xFF;
count = __builtin_popcount(rlist);
for(int i = 0; i < 16 && rlist; i++){
should_transfer = rlist & 1;
rlist >>= 1;
if(!should_transfer)
continue;
cpu->r[i] = cpu->readWord(cpu, cpu->r[13]);
cpu->r[13] += 4;
}
return;
thumb_op_02F3:
rlist = opcode & 0xFF;
count = __builtin_popcount(rlist);
for(int i = 0; i < 16 && rlist; i++){
should_transfer = rlist & 1;
rlist >>= 1;
if(!should_transfer)
continue;
cpu->r[i] = cpu->readWord(cpu, cpu->r[13]);
cpu->r[13] += 4;
}
return;
thumb_op_02F4:
rlist = opcode & 0xFF;
count = __builtin_popcount(rlist);
for(int i = 0; i < 16 && rlist; i++){
should_transfer = rlist & 1;
rlist >>= 1;
if(!should_transfer)
continue;
cpu->r[i] = cpu->readWord(cpu, cpu->r[13]);
cpu->r[13] += 4;
}
cpu->r[15] = cpu->readWord(cpu, cpu->r[13]);
cpu->r[15] &= 0xFFFFFFFE;
cpu->pipeline_valid = false;
cpu->r[13] += 4;
return;
thumb_op_02F5:
rlist = opcode & 0xFF;
count = __builtin_popcount(rlist);
for(int i = 0; i < 16 && rlist; i++){
should_transfer = rlist & 1;
rlist >>= 1;
if(!should_transfer)
continue;
cpu->r[i] = cpu->readWord(cpu, cpu->r[13]);
cpu->r[13] += 4;
}
cpu->r[15] = cpu->readWord(cpu, cpu->r[13]);
cpu->r[15] &= 0xFFFFFFFE;
cpu->pipeline_valid = false;
cpu->r[13] += 4;
return;
thumb_op_02F6:
rlist = opcode & 0xFF;
count = __builtin_popcount(rlist);
for(int i = 0; i < 16 && rlist; i++){
should_transfer = rlist & 1;
rlist >>= 1;
if(!should_transfer)
continue;
cpu->r[i] = cpu->readWord(cpu, cpu->r[13]);
cpu->r[13] += 4;
}
cpu->r[15] = cpu->readWord(cpu, cpu->r[13]);
cpu->r[15] &= 0xFFFFFFFE;
cpu->pipeline_valid = false;
cpu->r[13] += 4;
return;
thumb_op_02F7:
rlist = opcode & 0xFF;
count = __builtin_popcount(rlist);
for(int i = 0; i < 16 && rlist; i++){
should_transfer = rlist & 1;
rlist >>= 1;
if(!should_transfer)
continue;
cpu->r[i] = cpu->readWord(cpu, cpu->r[13]);
cpu->r[13] += 4;
}
cpu->r[15] = cpu->readWord(cpu, cpu->r[13]);
cpu->r[15] &= 0xFFFFFFFE;
cpu->pipeline_valid = false;
cpu->r[13] += 4;
return;
thumb_op_02F8:
return;
thumb_op_02F9:
return;
thumb_op_02FA:
return;
thumb_op_02FB:
return;
thumb_op_02FC:
return;
thumb_op_02FD:
return;
thumb_op_02FE:
return;
thumb_op_02FF:
return;
thumb_op_0300:
base = cpu->r[0];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[0] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 0 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[0] = base;
}
return;
thumb_op_0301:
base = cpu->r[0];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[0] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 0 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[0] = base;
}
return;
thumb_op_0302:
base = cpu->r[0];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[0] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 0 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[0] = base;
}
return;
thumb_op_0303:
base = cpu->r[0];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[0] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 0 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[0] = base;
}
return;
thumb_op_0304:
base = cpu->r[1];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[1] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 1 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[1] = base;
}
return;
thumb_op_0305:
base = cpu->r[1];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[1] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 1 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[1] = base;
}
return;
thumb_op_0306:
base = cpu->r[1];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[1] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 1 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[1] = base;
}
return;
thumb_op_0307:
base = cpu->r[1];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[1] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 1 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[1] = base;
}
return;
thumb_op_0308:
base = cpu->r[2];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[2] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 2 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[2] = base;
}
return;
thumb_op_0309:
base = cpu->r[2];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[2] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 2 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[2] = base;
}
return;
thumb_op_030A:
base = cpu->r[2];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[2] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 2 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[2] = base;
}
return;
thumb_op_030B:
base = cpu->r[2];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[2] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 2 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[2] = base;
}
return;
thumb_op_030C:
base = cpu->r[3];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[3] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 3 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[3] = base;
}
return;
thumb_op_030D:
base = cpu->r[3];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[3] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 3 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[3] = base;
}
return;
thumb_op_030E:
base = cpu->r[3];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[3] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 3 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[3] = base;
}
return;
thumb_op_030F:
base = cpu->r[3];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[3] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 3 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[3] = base;
}
return;
thumb_op_0310:
base = cpu->r[4];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[4] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 4 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[4] = base;
}
return;
thumb_op_0311:
base = cpu->r[4];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[4] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 4 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[4] = base;
}
return;
thumb_op_0312:
base = cpu->r[4];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[4] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 4 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[4] = base;
}
return;
thumb_op_0313:
base = cpu->r[4];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[4] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 4 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[4] = base;
}
return;
thumb_op_0314:
base = cpu->r[5];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[5] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 5 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[5] = base;
}
return;
thumb_op_0315:
base = cpu->r[5];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[5] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 5 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[5] = base;
}
return;
thumb_op_0316:
base = cpu->r[5];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[5] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 5 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[5] = base;
}
return;
thumb_op_0317:
base = cpu->r[5];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[5] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 5 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[5] = base;
}
return;
thumb_op_0318:
base = cpu->r[6];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[6] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 6 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[6] = base;
}
return;
thumb_op_0319:
base = cpu->r[6];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[6] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 6 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[6] = base;
}
return;
thumb_op_031A:
base = cpu->r[6];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[6] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 6 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[6] = base;
}
return;
thumb_op_031B:
base = cpu->r[6];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[6] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 6 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[6] = base;
}
return;
thumb_op_031C:
base = cpu->r[7];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[7] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 7 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[7] = base;
}
return;
thumb_op_031D:
base = cpu->r[7];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[7] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 7 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[7] = base;
}
return;
thumb_op_031E:
base = cpu->r[7];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[7] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 7 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[7] = base;
}
return;
thumb_op_031F:
base = cpu->r[7];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->writeWord(cpu, base, cpu->r[15] + 2);
cpu->r[7] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
if(count == 7 && !first_transfer)cpu->writeWord(cpu, base, cpu->r[count] + (rlist_size << 2));
else
cpu->writeWord(cpu, base, cpu->r[count]);
base += 4;
first_transfer = false;
}
cpu->r[7] = base;
}
return;
thumb_op_0320:
base = cpu->r[0];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[0] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[0] = base;
}
return;
thumb_op_0321:
base = cpu->r[0];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[0] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[0] = base;
}
return;
thumb_op_0322:
base = cpu->r[0];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[0] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[0] = base;
}
return;
thumb_op_0323:
base = cpu->r[0];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[0] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[0] = base;
}
return;
thumb_op_0324:
base = cpu->r[1];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[1] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[1] = base;
}
return;
thumb_op_0325:
base = cpu->r[1];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[1] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[1] = base;
}
return;
thumb_op_0326:
base = cpu->r[1];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[1] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[1] = base;
}
return;
thumb_op_0327:
base = cpu->r[1];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[1] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[1] = base;
}
return;
thumb_op_0328:
base = cpu->r[2];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[2] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[2] = base;
}
return;
thumb_op_0329:
base = cpu->r[2];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[2] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[2] = base;
}
return;
thumb_op_032A:
base = cpu->r[2];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[2] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[2] = base;
}
return;
thumb_op_032B:
base = cpu->r[2];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[2] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[2] = base;
}
return;
thumb_op_032C:
base = cpu->r[3];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[3] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[3] = base;
}
return;
thumb_op_032D:
base = cpu->r[3];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[3] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[3] = base;
}
return;
thumb_op_032E:
base = cpu->r[3];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[3] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[3] = base;
}
return;
thumb_op_032F:
base = cpu->r[3];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[3] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[3] = base;
}
return;
thumb_op_0330:
base = cpu->r[4];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[4] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[4] = base;
}
return;
thumb_op_0331:
base = cpu->r[4];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[4] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[4] = base;
}
return;
thumb_op_0332:
base = cpu->r[4];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[4] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[4] = base;
}
return;
thumb_op_0333:
base = cpu->r[4];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[4] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[4] = base;
}
return;
thumb_op_0334:
base = cpu->r[5];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[5] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[5] = base;
}
return;
thumb_op_0335:
base = cpu->r[5];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[5] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[5] = base;
}
return;
thumb_op_0336:
base = cpu->r[5];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[5] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[5] = base;
}
return;
thumb_op_0337:
base = cpu->r[5];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[5] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[5] = base;
}
return;
thumb_op_0338:
base = cpu->r[6];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[6] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[6] = base;
}
return;
thumb_op_0339:
base = cpu->r[6];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[6] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[6] = base;
}
return;
thumb_op_033A:
base = cpu->r[6];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[6] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[6] = base;
}
return;
thumb_op_033B:
base = cpu->r[6];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[6] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[6] = base;
}
return;
thumb_op_033C:
base = cpu->r[7];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[7] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[7] = base;
}
return;
thumb_op_033D:
base = cpu->r[7];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[7] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[7] = base;
}
return;
thumb_op_033E:
base = cpu->r[7];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[7] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[7] = base;
}
return;
thumb_op_033F:
base = cpu->r[7];
rlist = opcode & 0xFF;
count = 0xFF;
if(!rlist){
cpu->r[15] = cpu->readWord(cpu, base);
cpu->pipeline_valid = false;
cpu->r[7] += 0x40;
} else{
rlist_size = __builtin_popcount(rlist);
first_transfer = true;
while(rlist){
should_transfer = rlist & 1;
rlist >>= 1;
count += 1;
if(!should_transfer)
continue;
cpu->r[count] = cpu->readWord(cpu, base);
base += 4;
first_transfer = false;
}
cpu->r[7] = base;
}
return;
thumb_op_0340:
w8 = opcode & 0xFF;
if(cond_EQ(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0341:
w8 = opcode & 0xFF;
if(cond_EQ(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0342:
w8 = opcode & 0xFF;
if(cond_EQ(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0343:
w8 = opcode & 0xFF;
if(cond_EQ(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0344:
w8 = opcode & 0xFF;
if(cond_NE(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0345:
w8 = opcode & 0xFF;
if(cond_NE(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0346:
w8 = opcode & 0xFF;
if(cond_NE(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0347:
w8 = opcode & 0xFF;
if(cond_NE(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0348:
w8 = opcode & 0xFF;
if(cond_CS(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0349:
w8 = opcode & 0xFF;
if(cond_CS(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_034A:
w8 = opcode & 0xFF;
if(cond_CS(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_034B:
w8 = opcode & 0xFF;
if(cond_CS(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_034C:
w8 = opcode & 0xFF;
if(cond_CC(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_034D:
w8 = opcode & 0xFF;
if(cond_CC(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_034E:
w8 = opcode & 0xFF;
if(cond_CC(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_034F:
w8 = opcode & 0xFF;
if(cond_CC(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0350:
w8 = opcode & 0xFF;
if(cond_MI(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0351:
w8 = opcode & 0xFF;
if(cond_MI(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0352:
w8 = opcode & 0xFF;
if(cond_MI(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0353:
w8 = opcode & 0xFF;
if(cond_MI(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0354:
w8 = opcode & 0xFF;
if(cond_PL(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0355:
w8 = opcode & 0xFF;
if(cond_PL(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0356:
w8 = opcode & 0xFF;
if(cond_PL(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0357:
w8 = opcode & 0xFF;
if(cond_PL(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0358:
w8 = opcode & 0xFF;
if(cond_VS(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0359:
w8 = opcode & 0xFF;
if(cond_VS(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_035A:
w8 = opcode & 0xFF;
if(cond_VS(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_035B:
w8 = opcode & 0xFF;
if(cond_VS(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_035C:
w8 = opcode & 0xFF;
if(cond_VC(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_035D:
w8 = opcode & 0xFF;
if(cond_VC(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_035E:
w8 = opcode & 0xFF;
if(cond_VC(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_035F:
w8 = opcode & 0xFF;
if(cond_VC(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0360:
w8 = opcode & 0xFF;
if(cond_HI(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0361:
w8 = opcode & 0xFF;
if(cond_HI(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0362:
w8 = opcode & 0xFF;
if(cond_HI(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0363:
w8 = opcode & 0xFF;
if(cond_HI(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0364:
w8 = opcode & 0xFF;
if(cond_LS(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0365:
w8 = opcode & 0xFF;
if(cond_LS(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0366:
w8 = opcode & 0xFF;
if(cond_LS(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0367:
w8 = opcode & 0xFF;
if(cond_LS(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0368:
w8 = opcode & 0xFF;
if(cond_GE(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0369:
w8 = opcode & 0xFF;
if(cond_GE(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_036A:
w8 = opcode & 0xFF;
if(cond_GE(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_036B:
w8 = opcode & 0xFF;
if(cond_GE(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_036C:
w8 = opcode & 0xFF;
if(cond_LT(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_036D:
w8 = opcode & 0xFF;
if(cond_LT(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_036E:
w8 = opcode & 0xFF;
if(cond_LT(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_036F:
w8 = opcode & 0xFF;
if(cond_LT(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0370:
w8 = opcode & 0xFF;
if(cond_GT(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0371:
w8 = opcode & 0xFF;
if(cond_GT(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0372:
w8 = opcode & 0xFF;
if(cond_GT(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0373:
w8 = opcode & 0xFF;
if(cond_GT(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0374:
w8 = opcode & 0xFF;
if(cond_LE(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0375:
w8 = opcode & 0xFF;
if(cond_LE(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0376:
w8 = opcode & 0xFF;
if(cond_LE(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0377:
w8 = opcode & 0xFF;
if(cond_LE(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0378:
w8 = opcode & 0xFF;
if(cond_AL(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_0379:
w8 = opcode & 0xFF;
if(cond_AL(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_037A:
w8 = opcode & 0xFF;
if(cond_AL(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_037B:
w8 = opcode & 0xFF;
if(cond_AL(cpu) == false) return;
cpu->r[15] += w8 & 0x80 ? (0xFFFFFF00 | w8) << 1 : w8 << 1;
cpu->pipeline_valid = false;
return;
thumb_op_037C:
arm7tdmi_trigger_exception(cpu, 0x8, 0x13);
return;
thumb_op_037D:
arm7tdmi_trigger_exception(cpu, 0x8, 0x13);
return;
thumb_op_037E:
arm7tdmi_trigger_exception(cpu, 0x8, 0x13);
return;
thumb_op_037F:
arm7tdmi_trigger_exception(cpu, 0x8, 0x13);
return;
thumb_op_0380:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_0381:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_0382:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_0383:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_0384:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_0385:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_0386:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_0387:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_0388:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_0389:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_038A:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_038B:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_038C:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_038D:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_038E:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_038F:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_0390:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_0391:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_0392:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_0393:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_0394:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_0395:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_0396:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_0397:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_0398:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_0399:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_039A:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_039B:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_039C:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_039D:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_039E:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_039F:
offset = (opcode & 0b11111111111) << 1;
cpu->r[15] += offset & 0x800 ? 0xFFFFF000 | offset : offset;
cpu->pipeline_valid = false;
return;
thumb_op_03A0:
return;
thumb_op_03A1:
return;
thumb_op_03A2:
return;
thumb_op_03A3:
return;
thumb_op_03A4:
return;
thumb_op_03A5:
return;
thumb_op_03A6:
return;
thumb_op_03A7:
return;
thumb_op_03A8:
return;
thumb_op_03A9:
return;
thumb_op_03AA:
return;
thumb_op_03AB:
return;
thumb_op_03AC:
return;
thumb_op_03AD:
return;
thumb_op_03AE:
return;
thumb_op_03AF:
return;
thumb_op_03B0:
return;
thumb_op_03B1:
return;
thumb_op_03B2:
return;
thumb_op_03B3:
return;
thumb_op_03B4:
return;
thumb_op_03B5:
return;
thumb_op_03B6:
return;
thumb_op_03B7:
return;
thumb_op_03B8:
return;
thumb_op_03B9:
return;
thumb_op_03BA:
return;
thumb_op_03BB:
return;
thumb_op_03BC:
return;
thumb_op_03BD:
return;
thumb_op_03BE:
return;
thumb_op_03BF:
return;
thumb_op_03C0:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03C1:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03C2:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03C3:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03C4:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03C5:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03C6:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03C7:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03C8:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03C9:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03CA:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03CB:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03CC:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03CD:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03CE:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03CF:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03D0:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03D1:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03D2:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03D3:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03D4:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03D5:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03D6:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03D7:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03D8:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03D9:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03DA:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03DB:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03DC:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03DD:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03DE:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03DF:
offset = (opcode & 0b11111111111);
offset <<= 1;
if(offset & 0x800)
offset |= 0xFFFFF000;
cpu->r[14] = cpu->r[15] + (offset << 11);
return;
thumb_op_03E0:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03E1:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03E2:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03E3:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03E4:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03E5:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03E6:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03E7:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03E8:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03E9:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03EA:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03EB:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03EC:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03ED:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03EE:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03EF:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03F0:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03F1:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03F2:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03F3:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03F4:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03F5:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03F6:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03F7:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03F8:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03F9:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03FA:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03FB:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03FC:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03FD:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03FE:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
thumb_op_03FF:
offset = (opcode & 0b11111111111);
old_r15 = cpu->r[15];
cpu->r[15] = cpu->r[14] + (offset << 1);
cpu->r[15] &= 0xFFFFFFFE;
cpu->r[14] = (old_r15 - 2) | 1;
cpu->pipeline_valid = false;
return;
printf("NOT DECODED THUMB %X %X!\n", opcode, cpu->r[15]);
arm7tdmi_print(cpu);
exit(0);
}

