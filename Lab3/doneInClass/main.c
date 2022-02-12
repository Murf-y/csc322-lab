#include<stdio.h>
#include<string.h>


int in_use;

int main(){
    
    // 10111
    in_use = 16 + 4 + 2 + 1;
    // in_use 10111 i.e. 23

    in_use = toggle_bit(1);
    // now in_use should be 10101 = 21
    // because at index 1 it was 1 and now it is 0

    // it should print 21
    printf("%d\n", in_use);

    // ----------------------------------------------------

    // i is 10001
    int i = 17;
    int e = count_bits_in_num(i);
    
    // it should print 2 (because there are 2 1's in i)
    printf("%d\n", e);
}


int get_bit(int objNum){
    return (in_use & (1 << objNum)) >> objNum;
}
int set_bit_on(int objNum){
    return in_use | (1 << objNum);
}
int set_bit_off(int objNum){
    return in_use & ~(1 << objNum);
}
int toggle_bit(int objNum){
    int a = get_bit(objNum);
    if(a == 0){
        return set_bit_on(objNum);
    }
    else{
        return set_bit_off(objNum);
    }
}

int count_bits_in_num(int num){

    // it should count how many 1s is in num
    int count = 0;
    while(num > 0){
        // if the last bit is 1
        // incease the count
        if(num & 1){
            count++;
        }
        // shift the number to the right
        num = num >> 1;
    }
    return count;
}