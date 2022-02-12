#include<stdio.h>
#include<string.h>




typedef enum {False,True} bool;

int main(){
    int a_int;
    a_int = 100;
    printf("A number : %d\n", a_int);

    float a_float;
    a_float = 1.10;
    printf("A float : %f\n", a_float);

    double a_double;
    a_double = 11.131231;
    printf("A double : %lf\n", a_double);

    char a_char;
    a_char = 'a';
    printf("A char : %c\n", a_char);

    char a_string[10] = "Hello";
    printf("A string : %s\n", a_string);

    bool a_bool;
    a_bool = True;
    printf("A bool : %d\n", a_bool);

    int another_number;
    printf("Enter Another number : ");
    scanf("%d", &another_number);
    printf("Another number : %d\n", another_number);
    return 0;
}
