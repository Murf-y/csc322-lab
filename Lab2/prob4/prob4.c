#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>


#define OP_ALU_ADD 0
#define OP_ALU_SUB 1
void add_sub(int16_t A, int16_t B, uint8_t ALUOp, int16_t *Result);
void or(int16_t A, int16_t B, int16_t *Result);
void and(int16_t A, int16_t B, int16_t *Result);
int16_t mux(int16_t , int16_t , uint8_t );
int main(int argc, char **argv);
void add_sub(int16_t A, int16_t B, uint8_t ALUOp, int16_t *Result)
{
    switch (ALUOp & 0x01) {
        case OP_ALU_ADD:
            *Result = A + B;
            break;
        case OP_ALU_SUB:
            *Result = A - B;
            break;
        default:
            perror("OpCode Error. Aborting");
            exit(1);

    }
}
void and(int16_t A, int16_t B, int16_t *Result)
{
    *Result = A & B;
}
void or(int16_t A, int16_t B, int16_t *Result)
{
    *Result = A | B;
}
int16_t mux(int16_t Input1, int16_t Input2, uint8_t selector)
{
    return(selector == 0 ? Input1 : Input2);
}

/*What type of changes you need to implement in order to modify the design so that it
can perform the following operations: 1) XOR, 2) NOT, 3) Multiply, and 4) Divide. Assume
that the ALU can perform complex operations such as divisions (although not a practical design
consideration). Implement your changes and make sure that the program takes its inputs from
the command line at the following order A, B, sel0, sel1, sel2. Test the correctness of
your program using a testbench. Write your report and upload it to Lab 1 on Google Classroom */
int xor(int16_t A, int16_t B, int16_t *Result)
{
    *Result = A ^ B;
}
int not(int16_t A, int16_t *Result)
{
    *Result = ~A;
}
int mul(int16_t A, int16_t B, int16_t *Result)
{
    *Result = A * B;
}
int divs(int16_t A, int16_t B, int16_t *Result)
{
    *Result = A / B;
}
int main(int argc, char **argv)
{
    int16_t A, B, Result;
    uint8_t sel0, sel1, sel2;
    if (argc != 6) {
        perror("Usage: ./prob4 A B sel0 sel1 sel2");
        exit(1);
    }
    A = atoi(argv[1]);
    B = atoi(argv[2]);
    sel0 = atoi(argv[3]);
    sel1 = atoi(argv[4]);
    sel2 = atoi(argv[5]);
    printf("A = %d, B = %d, sel0 = %d, sel1 = %d, sel2 = %d\n", A, B, sel0, sel1, sel2);
    add_sub(A, B, sel0, &Result);
    printf("add_sub(A, B, sel0) = %d\n", Result);
    add_sub(A, B, sel1, &Result);
    printf("add_sub(A, B, sel1) = %d\n", Result);
    add_sub(A, B, sel2, &Result);
    printf("add_sub(A, B, sel2) = %d\n", Result);
    or(A, B, &Result);
    printf("or(A, B) = %d\n", Result);
    and(A, B, &Result);
    printf("and(A, B) = %d\n", Result);
    xor(A, B, &Result);
    printf("xor(A, B) = %d\n", Result);
    mul(A, B, &Result);
    printf("mul(A, B) = %d\n", Result);
    divs(A, B, &Result);
    printf("div(A, B) = %d\n", Result);
    return 0;
}