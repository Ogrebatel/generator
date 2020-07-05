#include <stdio.h>
#include <stdint.h>

uint16_t get_length(uint16_t var){
    uint16_t length=0;
    while(var){
        var >>= 1;
        ++length;
    }
    return length;
}

uint16_t remainder_of_division(uint16_t dividend, uint16_t divider){
    uint16_t len_divider = get_length(divider);
    while(dividend >= divider){
        dividend ^= divider << (get_length(dividend) - len_divider);
    }
    return dividend;
}

int multiplication(uint16_t a, uint16_t b, uint16_t poly){
    int x = 0;
    while(b) {
        if (b & 1)
        x ^= a;
        b >>= 1;
        a <<= 1;
    }
    return remainder_of_division(x, poly);
}

int summation(uint16_t a, uint16_t b, uint16_t poly){
    return remainder_of_division((a^b), poly);
}

int main() {
    uint16_t a = 0b1010011;
    uint16_t b = 0b1001;
    uint16_t poly = 0b111000011;

    printf("summ: %d + %d = %d\n", a, b, summation(a, b, poly));
    printf("multiplication: %d * %d = %d\n", a, b, multiplication(a, b, poly));
    return 0;
}