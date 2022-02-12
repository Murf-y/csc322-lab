#include<stdio.h>
#include<string.h>
#include<math.h>

int htoi(char s[]);
int main(){

    char s[10] = "0X123";
    int i = htoi(s);
    printf("%d",i);
    return 0;
}


// Function to convert hexadecimal to decimal
// Including an optional 0x or 0X
int htoi(char s[]){
    int i, length;
    long  decimal = 0; 
    long base = 1;
    length = strlen(s);
    for(i = length--; i >= 0; i--)
    {
        if(s[i] >= '0' && s[i] <= '9')
        {
            decimal += (s[i] - 48) * base;
            base *= 16;
        }
        else if(s[i] >= 'A' && s[i] <= 'F')
        {
            decimal += (s[i] - 55) * base;
            base *= 16;
        }
        else if(s[i] >= 'a' && s[i] <= 'f')
        {
            decimal += (s[i] - 87) * base;
            base *= 16;
        }
    }
    return decimal;

}
