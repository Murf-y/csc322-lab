#include "op_codes.c"
#include "instruction_format.c"
#include "registers.c"
#include "logger.c"
#include<stdio.h>



// ********************************** - TASK 4 - ****************************************************** 
/* !! Task 4 !!
    C code:
        int n1 = 5, n2 = 20, n3 = 30;
        if (n1 >= n2 && n1 >= n3)
            printf("%.2f is the largest number.", n1);
        if (n2 >= n1 && n2 >= n3)
            printf("%.2f is the largest number.", n2);
        if (n3 >= n1 && n3 >= n2)
            printf("%.2f is the largest number.", n3)
    
    Instructions:
                LOAD(W19,0,0),    
                LOAD(W20,2,0), 
                LOAD(W21,3,0),   
                SUBS(W9, W19, W20),
                BN(7),
                SUBS(W10, W19, W21),
                BN(7),
                ...print 1
                SUBS(W11, W20, W19),
                BN(11),
                SUBS(W12, W20, W21),
                BN(11),
                ...print 2
                SUBS(W13, W21, W19),
                BN(15),
                SUBS(W14, W21, W20),
                BN(15),
                ...print 3
                HALT()
*/
// **************************************************************************************************** 


// ********************************** - TASK 5 - ****************************************************** 
/*
    C code:
        int i = 5, x = 10, z = 20;
        int y = x + 5;
        int w = z - 5;
        int output;
        if(w == y) output = w & y;
        else output = w | y;

        sum(y+x);

        int sum(x,y){
            return x+y;
        }

    Instructions:
            LOAD(W19,0,0),         
            LOAD(W20,1,0),        
            LOAD(W21,2,0),          
            ADDI(W22, W20, 5),      
            SUBI(W23, W21, 5),    
            ADD(W24, W31, W31),    
            SUBS(W8, W23, W22),     
            CBNZ(W8,10),
            AND(W24, W23, W22),    
            BR(12),   
            OR(W24, W23, W22),     
            BR(12),
            ADD(W0, W31, W22),      
            ADD(W1, W31, W23),      
            BL(16),                 
            BR(18),              
            ADD(W0, W0, W1),
            RET(),
            HALT()
*/
// **************************************************************************************************** 




// **************************************************** - Global vars defining our : DM, RF, IR - ***************************************************************
// Register file that stores 
// a 16 bit register value 
// where each register i.e W0-W31 the index//address of that value
signed short RF[64] = {

};

// Store the data in the data memory
signed short DM[64] = {
    5,      // Address: 0
    10,     // Address: 1
    20,     // Address: 2
    30,     // Address: 3
    0,      // Address: 4
    1,      // Address: 5
    2,      // Address: 6
    12      // Address: 7
};

// Store the instrucion to be executed
// !! Or we can use hexacdecimal 0xaaa to represent the constant                     !!
// You can write the instruction here in multiple formats:
//                                                         - ARMV8
//                                                         - Hexadecimal (0x..)
//                                                         - Binary      (0b..)
//                                                         - Decimal     (4096)

unsigned long IR[64] ={
    LOAD(W19,0,0),         
    LOAD(W20,1,0),        
    LOAD(W21,2,0),          
    ADDI(W22, W20, 5),      
    SUBI(W23, W21, 5),    
    ADD(W24, W31, W31),    
    SUBS(W8, W23, W22),     
    CBNZ(W8,10),
    AND(W24, W23, W22),    
    BR(12),   
    OR(W24, W23, W22),     
    BR(12),
    ADD(W0, W31, W22),      
    ADD(W1, W31, W23),      
    BL(16),                 
    BR(18),              
    ADD(W0, W0, W1),
    RET(),
    HALT(),     
};

// *** - Program counter - ***
unsigned long PC = 0;

// *** - Flags - ***    
unsigned short uZeroFlag = 0;
unsigned short uNegativeFlag = 0;

// *************************************************************************************************************************************************************






// *********************** - Specific function for each instruction (prefix : F) - *****************************************************************************

void loadF(unsigned short uDest, unsigned short uReg1, unsigned short displacement){
    printf("Loading value at address %d with displacement %d into register %d\n", uReg1, displacement, uDest);
    RF[uDest]= DM[uReg1 + displacement];
}

void storeF(unsigned short uDest, unsigned short uReg1, unsigned short displacement){
    printf("Storing the value at register %d into data memory at address %d with displacement %d\n", uDest, uReg1,displacement);
    DM[uDest] = RF[uReg1];
}



void addF(unsigned short uReg1, unsigned short uReg2, unsigned short uDest){
    printf("Adding the value at register %d and at register %d into register %d\n", uReg1, uReg2, uDest);
    RF[uDest] = RF[uReg1] + RF[uReg2];
}
void subF(unsigned short uReg1, unsigned short uReg2, unsigned short uDest){
    printf("Subtracting the value at register %d and at register %d into register %d\n", uReg1, uReg2, uDest);
    RF[uDest] = RF[uReg1] - RF[uReg2];
}
void andF(unsigned short uReg1, unsigned short uReg2, unsigned short uDest){
    printf("Doing an AND operation on the value at register %d and at register %d into register %d\n", uReg1, uReg2, uDest);
    RF[uDest] = RF[uReg1] & RF[uReg2];
}
void orF(unsigned short uReg1, unsigned short uReg2, unsigned short uDest){
    printf("Doing an OR operation on the value at register %d and at register %d into register %d\n", uReg1, uReg2, uDest);
    RF[uDest] = RF[uReg1] | RF[uReg2];
}
void xorF(unsigned short uReg1, unsigned short uReg2, unsigned short uDest){
    printf("Doing an XOR operation on  the value at register %d and at register %d into register %d\n", uReg1, uReg2, uDest);
    RF[uDest] = RF[uReg1] ^ RF[uReg2];
}

void slF(unsigned short uReg1, unsigned short uDest, unsigned short shiftAmount){
    printf("Doing a Shift Left operation on the value at register %d storing it at register %d into register shift amount is %d\n", uReg1, uDest, shiftAmount);
    RF[uDest] = RF[uReg1] << shiftAmount;
}
void srF(unsigned short uReg1,unsigned short uDest, unsigned short shiftAmount){
    printf("Doing a Shift Right operation on the value at register %d storing it at register %d into register shift amount is %d\n", uReg1, uDest, shiftAmount);
    RF[uDest] = RF[uReg1] >> shiftAmount;
}



void addIF(unsigned short uReg1, unsigned short uDest, unsigned short immediate){
    printf("Adding the value at register %d and imediate %d into register %d\n", uReg1, immediate, uDest);
    RF[uDest] = RF[uReg1] + immediate;
}
void subIF(unsigned short uReg1, unsigned short uDest, unsigned short immediate){
    printf("Subtracting the value at register %d and imediate %d into register %d\n", uReg1, immediate, uDest);
    RF[uDest] = RF[uReg1] - immediate;
}
// ***********************************************************************************************************************************************************





// ***************************************************- Main Function - ***************************************************************************************
int main(){

    // *** - Instruction Parts - ***
    unsigned short  uReg1, uReg2, uShiftAmount;
    signed short uDest;
    unsigned long  uInstruction;
    unsigned short uOpCode, uAluCode;


    // Get the length of the IR
    int IR_SIZE = sizeof(IR)/sizeof(IR[0]);

    while(PC < IR_SIZE){

        // For visual purposes only
        print_line_ending();

        // Get the instruction
        uInstruction = IR[PC];
        if(uInstruction == HALT()){
            printf("HALTING\n\n");
            break;
        }
        
        // Decode the instruction Set the op code and the Destination and Source Registers
        uOpCode = InstructionDecodeUnit(uInstruction, &uDest, &uReg1, &uReg2, &uShiftAmount, &uAluCode);

        // Print the instruction details [For Debugging]
        printInstructionThings(uInstruction);

        printf("PC: %d\n", PC);
        switch (uOpCode) {
            case OP_LD:
                printf("A Load instruction is being executed . . .\n");
                loadF(uDest, uReg1, uReg2);
                printf("The value of register %d is now equal to  %d\n", uDest, RF[uDest]);
                break;
            case OP_ST:
                printf("A Store instruction is executed . . .\n");
                storeF(uDest, uReg1, uReg2);
                printf("The value of data memory at address %d is now %d\n", uReg1+uReg2, DM[uReg1 + uReg2]);
                break;

            
            case OP_ALU:{
                printf("A ALU instruction is being executed . . .\n");

                switch(uAluCode){
                    case ALU_ADD:{
                        printf("An Add instruction is being executed . . .\n");
                        addF(uReg1, uReg2, uDest);
                        printf("The value of register %d is now %d\n", uDest, RF[uDest]);
                        break;
                    }
                    case ALU_SUB:{
                        printf("An Sub instruction is being executed . . .\n");
                        subF(uReg1, uReg2, uDest);
                        printf("The value of register %d is now %d\n", uDest, RF[uDest]);
                        break;
                    }
                    case ALU_AND:{
                        printf("An AND instruction is being executed . . .\n");
                        andF(uReg1, uReg2, uDest);
                        printf("The value of register %d is now %d\n", uDest, RF[uDest]);
                        break;
                    }
                    case ALU_OR:{
                        printf("An OR instruction is being executed . . .\n");
                        orF(uReg1, uReg2, uDest);
                        printf("The value of register %d is now %d\n", uDest, RF[uDest]);
                        break;
                    }
                    case ALU_XOR:{
                        printf("An XOR instruction is being executed . . .\n");
                        xorF(uReg1, uReg2, uDest);
                        printf("The value of register %d is now %d\n", uDest, RF[uDest]);
                        break;
                    }
                    case ALU_ADDS:{
                        printf("An Add with flags instruction is being executed . . .\n");
                        addF(uReg1, uReg2, uDest);
                        uZeroFlag = (RF[uDest] == 0);
                        uNegativeFlag = (RF[uDest] < 0);
                        printf("The value of register %d is now %d\n", uDest, RF[uDest]);
                        printf("The Zero Flag is now %d\n", uZeroFlag);
                        printf("The Negative Flag is now %d\n", uNegativeFlag);
                        break;
                    }
                    case ALU_SUBS:{
                        printf("An Sub with flags instruction is being executed . . .\n");
                        subF(uReg1, uReg2, uDest);
                        uZeroFlag = (RF[uDest] == 0);
                        uNegativeFlag = (RF[uDest] < 0);
                        printf("The value of register %d is now %d\n", uDest, RF[uDest]);
                        printf("The Zero Flag is now %d\n", uZeroFlag);
                        printf("The Negative Flag is now %d\n", uNegativeFlag);
                        break;
                    }
                    case ALU_ANDS:{
                        printf("An AND with flags instruction is being executed . . .\n");
                        andF(uReg1, uReg2, uDest);
                        uZeroFlag = (RF[uDest] == 0);
                        uNegativeFlag = (RF[uDest] < 0);
                        printf("The value of register %d is now %d\n", uDest, RF[uDest]);
                        printf("The Zero Flag is now %d\n", uZeroFlag);
                        printf("The Negative Flag is now %d\n", uNegativeFlag);
                        break;
                    }
                }
                break;
            }


            case OP_SL:
                printf("An Shift Left instruction is being executed . . .\n");
                slF(uReg1, uDest, uShiftAmount);
                printf("The value of register %d is now %d\n", uDest, RF[uDest]);
                break;
            case OP_SR:
                printf("An Shift Right instruction is being executed . . .\n");
                srF(uReg1, uDest, uShiftAmount);
                printf("The value of register %d is now %d\n", uDest, RF[uDest]);
                break;  


                  
            case OP_ADDI:
                printf("An Add immediate instruction is being executed . . .\n");
                addIF(uReg1, uDest, uReg2);
                printf("The value of register %d is now %d\n", uDest, RF[uDest]);
                break;
            case OP_SUBI:
                printf("An Sub immediate instruction is being executed . . .\n");
                subIF(uReg1, uDest, uReg2);
                printf("The value of register %d is now %d\n", uDest, RF[uDest]);
                break;
            


            case OP_BZ:
                printf("An Branch if zero instruction is being executed . . .\n");
                if(uZeroFlag == 1){
                    printf("Branching to instruction at index %d\n", uDest);
                    // minus one because uPc is incremented after this instruction thus we should remove that incrementation
                    PC = uDest - 1;
                }
                else{
                    printf("Not branching\n");
                }
                break;
            case OP_BN:
                printf("An Branch if negative instruction is being executed . . .\n");
                if(uNegativeFlag == 1){
                    printf("Branching to instruction at index %d\n", uDest);
                    // minus one because uPc is incremented after this instruction thus we should remove that incrementation
                    PC =  uDest - 1;
                }
                else{
                    printf("Not branching\n");
                }
                break;
            case OP_CBZ:
                printf("An Compare and Branch if zero instruction is being executed . . .\n");
                if(RF[uReg1] == 0){
                    printf("Branching to instruction at index %d\n", uDest);
                     // minus one because uPc is incremented after this instruction thus we should remove that incrementation
                    PC = uDest - 1;
                }
                else{
                    printf("Not branching\n");
                }
                break;
            case OP_CBNZ:
                printf("An Compare and Branch if not zero instruction is being executed . . .\n");
                if(RF[uReg1] != 0){
                    printf("Branching to instruction at index %d\n", uDest);
                     // minus one because uPc is incremented after this instruction thus we should remove that incrementation
                    PC = uDest - 1;
                }
                else{
                    printf("Not branching\n");
                }
                break;

            
            case OP_BR:
                printf("An Branch unconditionally instruction is being executed . . .\n");
                printf("Branching to instruction at index %d\n", uDest);
                 // minus one because uPc is incremented after this instruction thus we should remove that incrementation
                PC = uDest - 1;
                break;
            case OP_BL:
                printf("An Branch and Link instruction is being executed . . .\n");

                // plus one because we dont want to come back to the BL instruction , instead to the instruction ahead of it
                RF[W30] = PC + 1;
                printf("Register 30 (w30) is now: %d\n", RF[W30]);
                printf("Branching to instruction at index %d\n", uDest);
                 // minus one because uPc is incremented after this instruction thus we should remove that incrementation
                PC = uDest - 1;
                break;
            
            case OP_RET:
                printf("A Return instruction is being executed . . .\n");
                 // minus one because uPc is incremented after this instruction thus we should remove that incrementation
                PC = RF[W30] - 1;
                printf("Returning to instruction at PC: %d\n", RF[30]);
                break;
            default:
                printf("Invalid Instruction , Ignoring . . .\n");
                break;
        }
        PC++;
        print_line_ending();
    }

    printf("RUNTIME ENDING . . .\n\n");
    return 0;
}
// ***********************************************************************************************************************************************************