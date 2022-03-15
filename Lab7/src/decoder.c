#include "op_codes.c"

#include<stdio.h>
// ********************************************************** - Decoder for an 32 bits instruction - *******************************************************************
unsigned short InstructionDecodeUnit(unsigned long uInstruction, signed short *uDest,
unsigned short *uReg1, unsigned short *uReg2, unsigned short *uShiftAmount, unsigned short *uAluCode)
{   
    unsigned short uOpCode = uInstruction >> 28;
    
    // Halt and Return instructions
    if(uOpCode == OP_HALT || uOpCode == OP_RET){
        *uDest = 0;
        *uReg1 = 0;
        *uReg2 = 0;
        *uShiftAmount = 0;
        *uAluCode = 0;
        return uOpCode;
    }

    // D format 
    if(uOpCode == OP_LD || uOpCode == OP_ST){
        
        // Destination / source regiser
        *uDest = uInstruction & 0x1F;
        // base register
        *uReg1 = (uInstruction >> 5) & 0x1F;
        // displacement
        *uReg2 = (uInstruction >> 10) & 0x3FFFF;
        // not used
        *uShiftAmount = 0;
        //not used
        *uAluCode = 0;
    }
    // CB format
    else if(uOpCode == OP_BZ || uOpCode == OP_BN || uOpCode == OP_CBZ || uOpCode == OP_CBNZ){

        // Address to go to
        *uDest = (uInstruction >> 5) & 0x7FFFFF;
        // Register to check
        *uReg1 = uInstruction & 0x1F;
        // not used
        *uReg2 = 0; 
        // not used
        *uShiftAmount = 0; 
        //not used
        *uAluCode = 0;      
    }
    // B format
    else if(uOpCode == OP_BR || uOpCode == OP_BL){
        // newPC
        *uDest = uInstruction & 0xFFFFFFF;
        // not used
        *uReg1 = 0;
        // not used
        *uReg2 = 0; 
        // not used
        *uShiftAmount = 0;
        //not used
        *uAluCode = 0;   
    }
    // I-format
    else if(uOpCode == OP_ADDI || uOpCode == OP_SUBI){
        // Destination register
        *uDest = uInstruction & 0x1F;
        // Source register
        *uReg1 = (uInstruction >> 5) & 0x1F;
        // immediate value
        *uReg2 = (uInstruction >> 10) & 0x3FFF;
        // not used
        *uShiftAmount = 0;
        //not used
        *uAluCode = 0;
    }
    // R format 
    else{
        if(uOpCode == OP_ALU){
            // destination register
            *uDest = uInstruction & 0x1F;
            // register source 1
            *uReg1 = (uInstruction >> 5) & 0x1F;
            // register source 2
            *uReg2 = (uInstruction >> 20) & 0x1F;
            // not used
            *uShiftAmount = 0;
            // ALU code of the instruction
            *uAluCode = (uInstruction >> 25) & 0x7;
        }else{
            // destination register
            *uDest = uInstruction & 0x1F;
            // register source 1
            *uReg1 = (uInstruction >> 5) & 0x1F;
            // not used
            *uReg2 = 0;
            // shiftAmount
            *uShiftAmount = (uInstruction >> 10) & 0x3FF;
            // not used
            *uAluCode = 0;
        }
    }
    
    return(uOpCode);
}
// ***********************************************************************************************************************************************************

