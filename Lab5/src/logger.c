#include "decoder.c"
#include<stdio.h>

// ****************************************************** - Helper function for debugging - ******************************************************************
void printBinary(unsigned long n, int length){
    int i;
    for(i = length; i >= 0; i--){
        printf("%d", (n >> i) & 1);
    }
    printf("\n");
}
void print_line_ending(){
    printf("\n--------------------------\n");
}
void printInstructionThings(unsigned long instruction){
    unsigned short uDest, uReg1, uReg2;
    unsigned short uOpCode;
    uOpCode = InstructionDecodeUnit(instruction, &uDest, &uReg1, &uReg2);
    printf("Instruction in binary (20 bits): ");
    printBinary(instruction, 19);
    printf("\n");
    printf("OpCode: %2d => ", uOpCode);
    printBinary(uOpCode, 7);
    printf("Dest: %4d => ", uDest);
    printBinary(uDest, 3);
    printf("Reg1: %4d => ", uReg1);
    printBinary(uReg1, 3);
    printf("Reg2: %4d => ", uReg2);
    printBinary(uReg2, 3);
}
// ***********************************************************************************************************************************************************
