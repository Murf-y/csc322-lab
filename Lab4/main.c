
#include<stdio.h>

// Op Code definitions
#define OP_HALT 0x00
#define OP_LD 0x01
#define OP_ST 0x02
#define OP_ADD 0x03
#define OP_SUB 0x04
#define OP_AND 0x05
#define OP_OR 0x06
#define OP_XOR 0x07
#define OP_SL 0x08
#define OP_SR 0x09


// Registers definitions
#define W0 0x00
#define W1 0x01
#define W2 0x02
#define W3 0x03
#define W4 0x04
#define W5 0x05
#define W6 0x06
#define W7 0x07


// Functions to each op code
// In the format 16 bit
// 0000 0000 0000 0000

// D-format OpCode | 0000 | Adress | Destination / Source
#define LOAD(DestReg, Address) (OP_LD << 12) | ( DestReg << 4) |  Address
#define STORE(SourceReg, Address) (OP_ST << 12) | (SourceReg << 4) | Address


// R-format Opcode | source1 | source2 | Destination
#define ADD(Reg1,Reg2,Reg3) (OP_ADD << 12) | (Reg1 << 8) | (Reg2 << 4) | Reg3
#define AND(Reg1,Reg2,Reg3) (OP_AND << 12) | (Reg1 << 8) | (Reg2 << 4) | Reg3
#define HALT OP_HALT
#define SUB(Reg1,Reg2,Reg3) (OP_SUB << 12) | (Reg1 << 8) | (Reg2 << 4) | Reg3
#define OR(Reg1,Reg2,Reg3) (OP_OR << 12) | (Reg1 << 8) | (Reg2 << 4) | Reg3
#define XOR(Reg1,Reg2,Reg3) (OP_XOR << 12) | (Reg1 << 8) | (Reg2 << 4) | Reg3
#define SL(Reg1,Reg2,shiftAmount) (OP_SL << 12) | (Reg1 << 8) | (Reg2 << 4) | shiftAmount
#define SR(Reg1,Reg2,shiftAmount) (OP_SR << 12) | (Reg1 << 8) | (Reg2 << 4) | shiftAmount




// Store the data in the data memory
unsigned short DM[64] = {
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

unsigned short RF[64] = {

};

unsigned short IR[64] ={
    LOAD(W0,3),         //  PC: 1
    LOAD(W1,2),         //  PC: 2
    SL(W2, W1,1),       //  PC: 3
    ADD(W3,W0,W2),      //  PC: 4
    STORE(W4, 5),       //  PC: 5
    LOAD(W5,3),         //  PC: 6
    SUB(W6,W5, W2),     //  PC: 7
    AND(W7, W6,W2),     //  PC: 8
    SR(W0,W7,1),        //  PC: 9

    HALT,

    
};


unsigned short InstructionDecodeUnit(unsigned short uInstruction, unsigned short *uDest,
unsigned short *uReg1, unsigned short *uReg2)
{   
    // The left most 4 bits are always the opCode
    unsigned short uOpCode = uInstruction >> 12;

    if(uOpCode == HALT) return uOpCode;

    // D format instruction
    if(uOpCode == OP_LD || uOpCode == OP_ST){
        // uDest is the address of the memory location
        *uDest = uInstruction & 0xF;
        // uReg1 is the register to store the value in
        *uReg1 = (uInstruction >> 4) & 0xF;
        // not used
        *uReg2 = 0;        
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

int main(){
    unsigned short uDest, uReg1, uReg2;
    unsigned short uInstruction;
    unsigned short uOpCode;
    unsigned short uPC = 0;
    
    // Loop over the IR

    // Get the length of the IR
    int IR_SIZE = sizeof(IR)/sizeof(IR[0]);
    while(uPC < IR_SIZE){

        // If the instruction is HALT, exit
        if(IR[uPC] == OP_HALT){
            break;
        }

        // Get the instruction
        uInstruction = IR[uPC];

        // Decode the instruction
        // Set the op code
        // and the Destination and Source Registers
        uOpCode = InstructionDecodeUnit(uInstruction, &uDest, &uReg1, &uReg2);

        // Print the instruction details [For Debugging]
        printInstructionThings(uInstruction);


        switch (uOpCode) {
            case OP_LD:
                printf("A Load instruction is being executed . . .\n");
                // uDest = adress of the memory location
                // uReg1 = the register to store the data
                // uReg2 = not used
                LDW(uDest, uReg1);
                printf("The value of the register at location %d is now equal to  %d\n", uReg1, RF[uReg1]);
                break;
            case OP_ST:
                printf("A Store instruction is executed . . .\n");
                STW(uDest, uReg1);
                printf("The value of data memory at address %d is now %d", uDest, RF[uReg1]);
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

    printf("\n\n");
    return 0;
}

