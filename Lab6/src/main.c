#include "op_codes.c"
#include "instruction_format.c"
#include<stdio.h>
#include "logger.c"


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
// !! Or we can use hexacdecimal 0xaaa to represent the constant                     !!
// You can write the instruction here in multiple formats:
//                                                         - ARMV8
//                                                         - Hexadecimal (0x..)
//                                                         - Binary      (0b..)
//                                                         - Decimal     (4096)
unsigned long IR[64] ={
    0b00000001000000000000,
    LOAD(W1, 4),
    CBZ(W1, 0x5),
    ADDI(W2,W0, 0x3),
    HALT(),
};
// *************************************************************************************************************************************************************






// *********************** - Specific function for each instruction (prefix : W) - *****************************************************************************
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





// ***************************************************- Main Function - ***************************************************************************************
int main(){

    // *** - Instruction Parts - ***
    unsigned short uDest, uReg1, uReg2;
    unsigned long  uInstruction;
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
                printf("Invalid Instruction , Ignoring . . .\n");
                break;
        }
        uPC++;
        print_line_ending();
    }

    printf("RUNTIME ENDING . . .\n\n");
    return 0;
}
// ***********************************************************************************************************************************************************