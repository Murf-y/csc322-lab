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
    unsigned short uOpCode, uDest, uReg1, uReg2, uShiftAmount, uAluCode;
    uOpCode = InstructionDecodeUnit(instruction, &uDest, &uReg1, &uReg2, &uShiftAmount, &uAluCode);
    printf("Instruction in binary (32 bits): ");
    printBinary(instruction, 31);
    printf("\n");
}
// ***********************************************************************************************************************************************************
