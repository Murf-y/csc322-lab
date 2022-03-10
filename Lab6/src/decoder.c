#include "op_codes.c"

// ********************************************************** - Decoder for an 20 bits instruction - *******************************************************************
unsigned short InstructionDecodeUnit(unsigned long uInstruction, unsigned short *uDest,
unsigned short *uReg1, unsigned short *uReg2)
{   
    unsigned short uOpCode = uInstruction >> 12;
    
    
    if(uOpCode == OP_HALT) return uOpCode;

    // D format instruction
    if(uOpCode == OP_LD || uOpCode == OP_ST){
        // uDest is the address of the memory location
        *uDest = uInstruction & 0xF;
        // uReg1 is the register to store the value in
        *uReg1 = (uInstruction >> 4) & 0xF;
        // not used
        *uReg2 = 0;        
    }
    // B format
    else if(uOpCode == OP_BZ || uOpCode == OP_BR ){
        // uDest is the newPC
        *uDest = uInstruction & 0xFF;
        // not used
        *uReg1 = 0;
        // not used
        *uReg2 = 0;        
    }
    else if(uOpCode == OP_CBZ || uOpCode == OP_CBNZ){
        // uDest is the register to check
        *uDest = uInstruction & 0xF;
        // uReg1 is the newPC
        *uReg1 = (uInstruction >> 4) & 0xFF;
        // not used
        *uReg2 = 0;        
    }
    // I-format
    else if(uOpCode == OP_ADDI || uOpCode == OP_SUBI){
        // uDest is register to store the result in
        *uDest = (uInstruction >> 8) & 0xF;
        // uReg1 is the register to be used
        *uReg1 = (uInstruction >> 4) & 0xF;
        // uReg2 is the immediate value
        *uReg2 = uInstruction & 0xF;
    }
    // R format instructions
    else{
        // destination register
        *uDest = uInstruction & 0xF;
        // register 1 
        *uReg1 = (uInstruction >> 8) & 0xF;
        // register 2
        *uReg2 = (uInstruction >> 4) & 0xF;        
    }
    
    return(uOpCode);
}
// ***********************************************************************************************************************************************************

