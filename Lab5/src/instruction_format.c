#include "op_codes.c"
// *************************** - D Format - 0000 Opcode | 0000 | Address | Destination/ Source - ************************************************************************
#define LOAD(DestReg, Address)      (OP_LD << 12) | ( DestReg << 4) |  Address
#define STORE(SourceReg, Address)   (OP_ST << 12) | (SourceReg << 4) | Address
// **************************************************************************************************************************************************************


// *************************** - R Format - 0000 Opcode | source1 | source2 | Destination - ****************************************************************************
#define ADD(Reg1,Reg2,Reg3)         (OP_ADD << 12)      | (Reg2 << 8) | (Reg3 << 4) | Reg1
#define AND(Reg1,Reg2,Reg3)         (OP_AND << 12)      | (Reg2 << 8) | (Reg3 << 4) | Reg1
#define HALT()                      OP_HALT
#define SUB(Reg1,Reg2,Reg3)         (OP_SUB << 12)      | (Reg2 << 8) | (Reg3 << 4) | Reg1
#define OR(Reg1,Reg2,Reg3)          (OP_OR << 12)        | (Reg2 << 8) | (Reg3 << 4) | Reg1
#define XOR(Reg1,Reg2,Reg3)         (OP_XOR << 12)      | (Reg2 << 8) | (Reg3 << 4) | Reg1
#define SL(Reg1,Reg2,shiftAmount)   (OP_SL << 12) | (Reg1 << 8) | (Reg2 << 4) | shiftAmount
#define SR(Reg1,Reg2,shiftAmount)   (OP_SR << 12) | (Reg1 << 8) | (Reg2 << 4) | shiftAmount


#define ADDS(Reg1,Reg2,Reg3) (OP_ADDS << 12) | (Reg2 << 8) | (Reg3 << 4) | Reg1
#define SUBS(Reg1,Reg2,Reg3) (OP_SUBS << 12) | (Reg2 << 8) | (Reg3 << 4) | Reg1
#define ANDS(Reg1,Reg2,Reg3) (OP_ANDS << 12) | (Reg2 << 8) | (Reg3 << 4) | Reg1
// **************************************************************************************************************************************************************


// *************************** - B Format opCode (8 bits) - **********************************************************************************************************************
#define BZ(newPC) (OP_BZ << 12) | newPC
#define BR(newPC) (OP_BR << 12) | newPC
// **************************************************************************************************************************************************************

// *************************** - CB Format opCode (8 bits) - **********************************************************************************************************************
#define CBZ(Reg1,newPC)     (OP_CBZ << 12) | (newPC << 4) | Reg1
#define CBNZ(Reg1,newPC)    (OP_CBNZ << 12) | (newPC << 4) | Reg1
// **************************************************************************************************************************************************************


// ***************************- I Format - **********************************************************************************************************************
// !! We cannot put the immediate value in the middle of the instruction, we need to put it in the end !!
#define ADDI(Reg1,Reg2,Immediate) (OP_ADDI << 12) | (Reg1 << 8) | (Reg2 << 4) | Immediate
#define SUBI(Reg1,Reg2,Immediate) (OP_SUBI << 12) | (Reg1 << 8) | (Reg2 << 4) | Immediate
// **************************************************************************************************************************************************************

