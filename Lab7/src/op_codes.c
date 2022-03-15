
// ****************************** - Op Codes - *********************************************************************************************************************
// !! OO_CODE will be represented by 4 bits !!
// !! ALU_CODE will be represented by 3 bits !!


#define OP_HALT 0x0

#define OP_LD 0x1
#define OP_ST 0x2

#define OP_ALU 0x3

#define ALU_ADD 0x0
#define ALU_SUB 0x1
#define ALU_AND 0x2
#define ALU_OR 0x3
#define ALU_XOR 0x4
#define ALU_ADDS 0x5
#define ALU_SUBS 0x6
#define ALU_ANDS 0x7


#define OP_SL 0x4
#define OP_SR 0x5

#define OP_ADDI 0x6
#define OP_SUBI 0x7

#define OP_CBZ 0x8
#define OP_CBNZ 0x9

#define OP_BZ 0xA
#define OP_BN  0xB
#define OP_BR 0xC
#define OP_BL 0xD

#define OP_RET 0xE


// **************************************************************************************************************************************************************

