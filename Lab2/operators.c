
// This file contains the operators and the operations that you can preform with them

int main(int argc, char **argv){

    // A : 1010
    int A = 10;
    
    // B : 1110
    int B = 14;

    // C : 0010
    int C = 2;

    printf("A = %d\n", A);
    printf("B = %d\n", B);
    printf("C = %d\n", C);

    // A & B : 1010 & 1110 = 1010 => 10
    int AB = A & B;
    printf("A & B = %d\n", AB);

    // A | B : 1010 | 1110 = 1110 => 14
    int AB_OR = A | B;
    printf("A | B = %d\n", AB_OR);

    // A ^ B : 1010 ^ 1110 = 0100 => 4
    int AB_XOR = A ^ B;
    printf("A ^ B = %d\n", AB_XOR);

    // ~A : ~1010 = 1s complement 0101 => 2s complement 0101 - 1 = 1011 => -11
    int A_NOT = ~A;
    printf("~A = %d\n", A_NOT);


    // A << 2 : 1010 << 2 = 101000 => 40
    // equivalent to A * 2^2
    int A_LSHIFT = A << 2;
    printf("A << 2 = %d\n", A_LSHIFT);

    // A >> 2 : 1010 >> 2 = 0010 => 2
    // equivalent to A / 2^2
    int A_RSHIFT = A >> 2;
    printf("A >> 2 = %d\n", A_RSHIFT);



    return 0;
}