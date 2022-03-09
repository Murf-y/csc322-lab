
#include<stdio.h>



// ****************************** - Op Codes - *********************************************************************************************************************
#define OP_HALT 0x00

#define OP_LD 0x01
#define OP_ST 0x02

#define OP_ADD 0x03
#define OP_SUB 0x04
#define OP_AND 0x05
#define OP_OR 0x06
#define OP_XOR 0x07

#define OP_ADDS 0x08
#define OP_SUBS 0x09
#define OP_ANDS 0x0A

#define OP_SL 0x0B
#define OP_SR 0x0C


#define OP_ADDI 0x0D
#define OP_SUBI 0x0E


#define OP_BR 0x0F
#define OP_BZ 0x10
#define OP_CBZ 0x11
#define OP_CBNZ 0x12
// **************************************************************************************************************************************************************





// ******************************** - Registers - ***************************************************************************************************************
#define W0 0x00
#define W1 0x01
#define W2 0x02
#define W3 0x03
#define W4 0x04
#define W5 0x05
#define W6 0x06
#define W7 0x07
// **************************************************************************************************************************************************************






// *************************** - D Format - Opcode | 0000 | Address | Destination/ Source - ************************************************************************
#define LOAD(DestReg, Address) (OP_LD << 12) | ( DestReg << 4) |  Address
#define STORE(SourceReg, Address) (OP_ST << 12) | (SourceReg << 4) | Address
// **************************************************************************************************************************************************************


// *************************** - R Format - Opcode | source1 | source2 | Destination - ****************************************************************************
#define ADD(Reg1,Reg2,Reg3) (OP_ADD << 12)      | (Reg2 << 8) | (Reg3 << 4) | Reg1
#define AND(Reg1,Reg2,Reg3) (OP_AND << 12)      | (Reg2 << 8) | (Reg3 << 4) | Reg1
#define HALT() OP_HALT
#define SUB(Reg1,Reg2,Reg3) (OP_SUB << 12)      | (Reg2 << 8) | (Reg3 << 4) | Reg1
#define OR(Reg1,Reg2,Reg3) (OP_OR << 12)        | (Reg2 << 8) | (Reg3 << 4) | Reg1
#define XOR(Reg1,Reg2,Reg3) (OP_XOR << 12)      | (Reg2 << 8) | (Reg3 << 4) | Reg1
#define SL(Reg1,Reg2,shiftAmount) (OP_SL << 12) | (Reg1 << 8) | (Reg2 << 4) | shiftAmount
#define SR(Reg1,Reg2,shiftAmount) (OP_SR << 12) | (Reg1 << 8) | (Reg2 << 4) | shiftAmount


#define ADDS(Reg1,Reg2,Reg3) (OP_ADDS << 12) | (Reg2 << 8) | (Reg3 << 4) | Reg1
#define SUBS(Reg1,Reg2,Reg3) (OP_SUBS << 12) | (Reg2 << 8) | (Reg3 << 4) | Reg1
#define ANDS(Reg1,Reg2,Reg3) (OP_ANDS << 12) | (Reg2 << 8) | (Reg3 << 4) | Reg1
// **************************************************************************************************************************************************************


// *************************** - B Format - **********************************************************************************************************************
#define BZ(newPC) (OP_BZ << 12) | newPC
#define BR(newPC) (OP_BR << 12) | newPC
// **************************************************************************************************************************************************************

// *************************** - CB Format - **********************************************************************************************************************
#define CBZ(Reg1,newPC)     (OP_CBZ << 12) | (newPC << 4) | Reg1
#define CBNZ(Reg1,newPC)    (OP_CBNZ << 12) | (newPC << 4) | Reg1
// **************************************************************************************************************************************************************


// ***************************- I Format - **********************************************************************************************************************
// !! We cannot put the immediate value in the middle of the instruction, we need to put it in the end !!
#define ADDI(Reg1,Reg2,Immediate) (OP_ADDI << 12) | (Reg1 << 8) | (Reg2 << 4) | Immediate
#define SUBI(Reg1,Reg2,Immediate) (OP_SUBI << 12) | (Reg1 << 8) | (Reg2 << 4) | Immediate
// **************************************************************************************************************************************************************






// **************************************************** - Global vars defining our : DM, RF, IR - ***************************************************************
// Store the data in the data memory
signed short DM[64] = {
    5,      // Address: 0
    10,     // Address: 1
    7,      // Address: 2
    20,     // Address: 3
    0,      // Address: 4
    1,      // Address: 5
    2,      // Address: 6
    12      // Address: 7
};

// Register file that stores 
// a 16 bit register value 
// where each register i.e W0-W7 the index//address of that value
signed short RF[64] = {

};


// Store the instrucion to be executed
// !! We need to cast to (unsigned short) when using constants inside the instruction !!
unsigned short IR[64] ={
    LOAD(W0,0),
    LOAD(W1, 4),
    SUBS(W2, W1, W0),
    ADDI(W0, W2, (unsigned short)5),
    HALT(),
};
// *************************************************************************************************************************************************************



// ********************************************************** - Decoder for an instruction - *******************************************************************
unsigned short InstructionDecodeUnit(unsigned short uInstruction, unsigned short *uDest,
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




// ****************************************************** - Specific function for each instruction - ********************************************************
void LDW(unsigned short uDest, unsigned short uReg1){
    printf("Loading %d into register %d\n", DM[uDest], uReg1);
    RF[uReg1]= DM[uDest];
}

void STW(unsigned short uDest, unsigned short uReg1){
    printf("Storing the value at register %d into data memory at address %d\n", uReg1, uDest);
    DM[uDest] = RF[uReg1];
}
void ADDW(unsigned short uReg1, unsigned short uReg2, unsigned short uDest){
    printf("Adding the value at register %d and at register %d into register %d\n", uReg1, uReg2, uDest);
    RF[uDest] = RF[uReg1] + RF[uReg2];
}
void SUBW(unsigned short uReg1, unsigned short uReg2, unsigned short uDest){
    printf("Subtracting the value at register %d and at register %d into register %d\n", uReg1, uReg2, uDest);
    RF[uDest] = RF[uReg1] - RF[uReg2];
}
void ANDW(unsigned short uReg1, unsigned short uReg2, unsigned short uDest){
    printf("Doing an AND operation on the value at register %d and at register %d into register %d\n", uReg1, uReg2, uDest);
    RF[uDest] = RF[uReg1] & RF[uReg2];
}
void ORW(unsigned short uReg1, unsigned short uReg2, unsigned short uDest){
    printf("Doing an OR operation on the value at register %d and at register %d into register %d\n", uReg1, uReg2, uDest);
    RF[uDest] = RF[uReg1] | RF[uReg2];
}
void XORW(unsigned short uReg1, unsigned short uReg2, unsigned short uDest){
    printf("Doing an XOR operation on  the value at register %d and at register %d into register %d\n", uReg1, uReg2, uDest);
    RF[uDest] = RF[uReg1] ^ RF[uReg2];
}
void SLW(unsigned short uReg1, unsigned short uReg2, unsigned short uDest){
    printf("Doing a Shift left operation on the value at register %d storing it at register %d into register shift amount is %d\n", uReg2, uReg1, uDest);
    RF[uReg1] = RF[uReg2] << uDest;
   
}
void SRW(unsigned short uReg1, unsigned short uReg2, unsigned short uDest){
    printf("Doing a Shift Right operation on the value at register %d storing it at register %d into register shift amount is %d\n", uReg2, uReg1, uDest);
    RF[uReg1] = RF[uReg2] >> uDest;
}

void ADDIW(unsigned short uReg1, unsigned short uReg2, unsigned short uDest){
    printf("Adding the value at register %d and imediate %d into register %d\n", uReg1, uReg2, uDest);
    RF[uDest] = RF[uReg1] + uReg2;
}
void SUBIW(unsigned short uReg1, unsigned short uReg2, unsigned short uDest){
    printf("Subtracting the value at register %d and imediate %d into register %d\n", uReg1, uReg2, uDest);
    RF[uDest] = RF[uReg1] - uReg2;
}
// ***********************************************************************************************************************************************************




// ****************************************************** - Helper function for debugging - ******************************************************************
void printBinary(unsigned short n){
    int i;
    for(i = 15; i >= 0; i--){
        printf("%d", (n >> i) & 1);
    }
    printf("\n");
}
void print_line_ending(){
    printf("\n--------------------------\n");
}
void printInstructionThings(unsigned short instruction){
    unsigned short uDest, uReg1, uReg2;
    unsigned short uOpCode;
    uOpCode = InstructionDecodeUnit(instruction, &uDest, &uReg1, &uReg2);
    printf("Instruction in binary : ");
    printBinary(instruction);
    printf("\n");
    printf("OpCode: %d\n", uOpCode); // print 1
    printf("Dest: %d\n", uDest); // print 
    printf("Reg1: %d\n", uReg1);
    printf("Reg2: %d\n", uReg2);
}
// ***********************************************************************************************************************************************************



// ***************************************************- Main Function - ***************************************************************************************
int main(){

    // *** - Instruction Parts - ***
    unsigned short uDest, uReg1, uReg2;
    unsigned short uInstruction;
    unsigned short uOpCode;
    unsigned long uPC = 0;

    // *** - Flags - ***
    unsigned short uZeroFlag = 0;
    unsigned short uNegativeFlag = 0;

    // Get the length of the IR
    int IR_SIZE = sizeof(IR)/sizeof(IR[0]);

    while(uPC < IR_SIZE){

        // For visual purposes only
        print_line_ending();

        // Get the instruction
        uInstruction = IR[uPC];

        if(uInstruction == HALT()){
            printf("HALTING\n\n");
            break;
        }

        // Decode the instruction Set the op code and the Destination and Source Registers
        uOpCode = InstructionDecodeUnit(uInstruction, &uDest, &uReg1, &uReg2);

        // Print the instruction details [For Debugging]
        printInstructionThings(uInstruction);

        printf("PC: %d\n", uPC);
        switch (uOpCode) {
            case OP_LD:
                printf("A Load instruction is being executed . . .\n");
                LDW(uDest, uReg1);
                printf("The value of the register at location %d is now equal to  %d\n", uReg1, RF[uReg1]);
                break;
            case OP_ST:
                printf("A Store instruction is executed . . .\n");
                STW(uDest, uReg1);
                printf("The value of data memory at address %d is now %d", uDest, DM[uDest]);
                break;
            case OP_ADD:
                printf("An Add instruction is being executed . . .\n");
                ADDW(uReg1, uReg2, uDest);
                printf("The value of register %d is now %d", uDest, RF[uDest]);
                break;
            case OP_SUB:
                printf("An Sub instruction is being executed . . .\n");
                SUBW(uReg1, uReg2, uDest);
                printf("The value of register %d is now %d", uDest, RF[uDest]);
                break;
            case OP_AND:
                printf("An AND instruction is being executed . . .\n");
                ANDW(uReg1, uReg2, uDest);
                printf("The value of register %d is now %d", uDest, RF[uDest]);
                break;
            case OP_OR:
                printf("An OR instruction is being executed . . .\n");
                ORW(uReg1, uReg2, uDest);
                printf("The value of register %d is now %d", uDest, RF[uDest]);
                break;
            case OP_XOR:
                printf("An XOR instruction is being executed . . .\n");
                XORW(uReg1, uReg2, uDest);
                printf("The value of register %d is now %d", uDest, RF[uDest]);
                break;
            case OP_SL:
                printf("An Shift Left instruction is being executed . . .\n");
                SLW(uReg1, uReg2, uDest);
                printf("The value of register %d is now %d", uReg1, RF[uReg1]);
                break;
            case OP_SR:
                printf("An Shift Right instruction is being executed . . .\n");
                SRW(uReg1, uReg2, uDest);
                printf("The value of register %d is now %d", uReg1, RF[uReg1]);
                break;
            
            case OP_ADDS:
                printf("An Add with flags instruction is being executed . . .\n");
                ADDW(uReg1, uReg2, uDest);
                uZeroFlag = (RF[uDest] == 0);
                uNegativeFlag = (RF[uDest] < 0);
                printf("The value of register %d is now %d\n", uDest, RF[uDest]);
                printf("The Zero Flag is now %d\n", uZeroFlag);
                printf("The Negative Flag is now %d\n", uNegativeFlag);
                break;
            case OP_SUBS:
                printf("An Sub with flags instruction is being executed . . .\n");
                SUBW(uReg1, uReg2, uDest);
                uZeroFlag = (RF[uDest] == 0);
                uNegativeFlag = (RF[uDest] < 0);
                printf("The value of register %d is now %d\n", uDest, RF[uDest]);
                printf("The Zero Flag is now %d\n", uZeroFlag);
                printf("The Negative Flag is now %d\n", uNegativeFlag);
                break;

            case OP_ANDS:
                printf("An AND with flags instruction is being executed . . .\n");
                ANDW(uReg1, uReg2, uDest);
                uZeroFlag = (RF[uDest] == 0);
                uNegativeFlag = (RF[uDest] < 0);
                printf("The value of register %d is now %d\n", uDest, RF[uDest]);
                printf("The Zero Flag is now %d\n", uZeroFlag);
                printf("The Negative Flag is now %d\n", uNegativeFlag);
                break;
            
            case OP_ADDI:
                printf("An Add immediate instruction is being executed . . .\n");
                ADDIW(uReg1, uReg2, uDest);
                printf("The value of register %d is now %d\n", uDest, RF[uDest]);
                break;
            case OP_SUBI:
                printf("An Sub immediate instruction is being executed . . .\n");
                SUBIW(uReg1, uReg2, uDest);
                printf("The value of register %d is now %d\n", uDest, RF[uDest]);
                break;

            
            case OP_BZ:
                printf("An Branch if zero instruction is being executed . . .\n");
                if(uZeroFlag == 1){
                    printf("Branching to instruction at index %d\n", uDest);
                    // minus one because uPc is incremented after this instruction thus we should remove that incrementation
                    uPC = uDest-1;
                }
                else{
                    printf("Not branching\n");
                }
                break;
            case OP_BR:
                printf("An Branch unconditionally instruction is being executed . . .\n");
                printf("Branching to instruction at index %d\n", uDest);
                 // minus one because uPc is incremented after this instruction thus we should remove that incrementation
                uPC = uDest-1;
                break;
            case OP_CBZ:
                printf("An Compare and Branch if zero instruction is being executed . . .\n");
                if(RF[uDest] == 0){
                    printf("Branching to instruction at index %d\n", uDest);
                     // minus one because uPc is incremented after this instruction thus we should remove that incrementation
                    uPC = uReg1 - 1;
                }
                else{
                    printf("Not branching\n");
                }
                break;
            case OP_CBNZ:
                printf("An Compare and Branch if not zero instruction is being executed . . .\n");
                if(RF[uDest] != 0){
                    printf("Branching to instruction at index %d\n", uDest);
                     // minus one because uPc is incremented after this instruction thus we should remove that incrementation
                    uPC = uReg1 - 1;
                }
                else{
                    printf("Not branching\n");
                }
                break;


            case OP_HALT:
                printf("HALT\n");
                break;
            default:
                printf("Invalid Instruction . . .\n");
                break;
        }
        uPC++;
        print_line_ending();
    }

    printf("RUNTIME ENDING . . .\n\n");
    return 0;
}
// ***********************************************************************************************************************************************************