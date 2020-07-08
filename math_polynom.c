#include <stdio.h>
#include <stdint.h>

uint16_t remainder_of_division(uint16_t dividend, uint16_t polynom){
    uint16_t tmp_polynom = polynom;
    tmp_polynom <<= 7;
    while(dividend >= polynom){
        if ((tmp_polynom ^ dividend) <= dividend)
            dividend ^= tmp_polynom;
        tmp_polynom >>= 1;
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

int summation(uint16_t a, uint16_t b, uint16_t polynom){
    return a^b;
}

int main() {
    uint16_t a = 83;
    uint16_t b = 9;
    uint16_t poly = 0b111000011;

    printf("summ: %d + %d = %d\n", a, b, summation(a, b, poly));
    printf("remainder: %d / %d = %d\n", a, poly, remainder_of_division(a, poly));
    printf("multiplication: %d * %d = %d\n", a, b, multiplication(a, b, poly));

    return 0;
}
