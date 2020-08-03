#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

union uint128_t{
    uint64_t qw[2];
    uint32_t dw[4];
    uint16_t w[8];
    uint8_t b[16];
} typedef uint128_t;

uint8_t mul_table[256][256];

uint16_t rev_l_mult[16] = {1, 148, 32, 133, 16, 194, 192, 1, 251, 1, 192, 194, 16, 133, 32, 148};

uint16_t polynom = 0b111000011;

uint16_t Pi[256] = {252, 238, 221, 17, 207, 110, 49, 22, 251, 196, 250, 218, 35, 197, 4, 77, 233,
                   119, 240, 219, 147, 46, 153, 186, 23, 54, 241, 187, 20, 205, 95, 193, 249, 24, 101,
        90, 226, 92, 239, 33, 129, 28, 60, 66, 139, 1, 142, 79, 5, 132, 2, 174, 227, 106, 143,
        160, 6, 11, 237, 152, 127, 212, 211, 31, 235, 52, 44, 81, 234, 200, 72, 171, 242, 42,
        104, 162, 253, 58, 206, 204, 181, 112, 14, 86, 8, 12, 118, 18, 191, 114, 19, 71, 156,
        183, 93, 135, 21, 161, 150, 41, 16, 123, 154, 199, 243, 145, 120, 111, 157, 158, 178,
        177, 50, 117, 25, 61, 255, 53, 138, 126, 109, 84, 198, 128, 195, 189, 13, 87, 223,
        245, 36, 169, 62, 168, 67, 201, 215, 121, 214, 246, 124, 34, 185, 3, 224, 15, 236,
        222, 122, 148, 176, 188, 220, 232, 40, 80, 78, 51, 10, 74, 167, 151, 96, 115, 30, 0,
        98, 68, 26, 184, 56, 130, 100, 159, 38, 65, 173, 69, 70, 146, 39, 94, 85, 47, 140, 163,
        165, 125, 105, 213, 149, 59, 7, 88, 179, 64, 134, 172, 29, 247, 48, 55, 107, 228, 136,
        217, 231, 137, 225, 27, 131, 73, 76, 63, 248, 254, 141, 83, 170, 144, 202, 216, 133,
        97, 32, 113, 103, 164, 45, 43, 9, 91, 203, 155, 37, 208, 190, 229, 108, 82, 89, 166,
        116, 210, 230, 244, 180, 192, 209, 102, 175, 194, 57, 75, 99, 182};

uint16_t rev_Pi[256] = {0xa5, 0x2d, 0x32, 0x8f, 0x0e, 0x30, 0x38, 0xc0, 0x54, 0xe6, 0x9e, 0x39,
                    0x55, 0x7e, 0x52, 0x91, 0x64, 0x03, 0x57, 0x5a, 0x1c, 0x60, 0x07, 0x18,
                    0x21, 0x72, 0xa8, 0xd1, 0x29, 0xc6, 0xa4, 0x3f, 0xe0, 0x27, 0x8d, 0x0c,
                    0x82, 0xea, 0xae, 0xb4, 0x9a, 0x63, 0x49, 0xe5, 0x42, 0xe4, 0x15, 0xb7,
                    0xc8, 0x06, 0x70, 0x9d, 0x41, 0x75, 0x19, 0xc9, 0xaa, 0xfc, 0x4d, 0xbf,
                    0x2a, 0x73, 0x84, 0xd5, 0xc3, 0xaf, 0x2b, 0x86, 0xa7, 0xb1, 0xb2, 0x5b,
                    0x46, 0xd3, 0x9f, 0xfd, 0xd4, 0x0f, 0x9c, 0x2f, 0x9b, 0x43, 0xef, 0xd9,
                    0x79, 0xb6, 0x53, 0x7f, 0xc1, 0xf0, 0x23, 0xe7, 0x25, 0x5e, 0xb5, 0x1e,
                    0xa2, 0xdf, 0xa6, 0xfe, 0xac, 0x22, 0xf9, 0xe2, 0x4a, 0xbc, 0x35, 0xca,
                    0xee, 0x78, 0x05, 0x6b, 0x51, 0xe1, 0x59, 0xa3, 0xf2, 0x71, 0x56, 0x11,
                    0x6a, 0x89, 0x94, 0x65, 0x8c, 0xbb, 0x77, 0x3c, 0x7b, 0x28, 0xab, 0xd2,
                    0x31, 0xde, 0xc4, 0x5f, 0xcc, 0xcf, 0x76, 0x2c, 0xb8, 0xd8, 0x2e, 0x36,
                    0xdb, 0x69, 0xb3, 0x14, 0x95, 0xbe, 0x62, 0xa1, 0x3b, 0x16, 0x66, 0xe9,
                    0x5c, 0x6c, 0x6d, 0xad, 0x37, 0x61, 0x4b, 0xb9, 0xe3, 0xba, 0xf1, 0xa0,
                    0x85, 0x83, 0xda, 0x47, 0xc5, 0xb0, 0x33, 0xfa, 0x96, 0x6f, 0x6e, 0xc2,
                    0xf6, 0x50, 0xff, 0x5d, 0xa9, 0x8e, 0x17, 0x1b, 0x97, 0x7d, 0xec, 0x58,
                    0xf7, 0x1f, 0xfb, 0x7c, 0x09, 0x0d, 0x7a, 0x67, 0x45, 0x87, 0xdc, 0xe8,
                    0x4f, 0x1d, 0x4e, 0x04, 0xeb, 0xf8, 0xf3, 0x3e, 0x3d, 0xbd, 0x8a, 0x88,
                    0xdd, 0xcd, 0x0b, 0x13, 0x98, 0x02, 0x93, 0x80, 0x90, 0xd0, 0x24, 0x34,
                    0xcb, 0xed, 0xf4, 0xce, 0x99, 0x10, 0x44, 0x40, 0x92, 0x3a, 0x01, 0x26,
                    0x12, 0x1a, 0x48, 0x68, 0xf5, 0x81, 0x8b, 0xc7, 0xd6, 0x20, 0x0a, 0x08,
                    0x00, 0x4c, 0xd7, 0x74};

uint16_t remainder_of_division(uint16_t dividend){
    uint16_t tmp_polynom = polynom;
    tmp_polynom <<= 7;
    while((dividend >= polynom)||(tmp_polynom >= polynom)){
        if ((tmp_polynom ^ dividend) <= dividend)
            dividend ^= tmp_polynom;
        tmp_polynom >>= 1;
    }
    return dividend;
}

uint128_t X_transform(uint128_t a, uint128_t b){
    uint128_t res;
    unsigned i;
    for(i = 0; i < 2; ++i){
        res.qw[i] = a.qw[i] ^ b.qw[i];
    }
    return res;
}

uint16_t fast_mul(uint16_t a, uint16_t b){
    return mul_table[a][b];
}

uint8_t summ(uint16_t a, uint16_t b){

    return a^b;
}

uint16_t multiplication(uint16_t a, uint16_t b){
    int x = 0;
    while(b) {
        if (b & 1)
            x ^= a;
        b >>= 1;
        a <<= 1;
    }
    return remainder_of_division(x);
}

uint8_t l(uint128_t a){
    uint8_t res = 0;
    int i;
    for(i = 15; i >= 0; --i){
        res = res ^ fast_mul(rev_l_mult[i], a.b[i]);
    }
    return res;
}

uint128_t R(uint128_t a){
    uint128_t res = a;
    int i;
    uint8_t l_res = l(a);
    for (i = 0; i < 15; ++i){
        res.b[i] = res.b[i + 1];
    }
    res.b[15] = l_res;
    return res;
}

uint128_t S(uint128_t a){
    uint128_t res;
    unsigned i;
    for(i = 0; i < 16; ++i){
        res.b[i] = Pi[a.b[i]];
    }
    return res;
}

uint128_t L(uint128_t a) {
    int i = 0;
    for (; i < 16; ++i)
        a = R(a);
    return a;
}

uint128_t rev_R(uint128_t a){
    int i;
    uint8_t tmp;
    tmp = a.b[15];
    for(i = 15; i > 0; --i)
        a.b[i] = a.b[i - 1];
    a.b[0] = tmp;
    a.b[0] = l(a);
    return a;
}

uint128_t rev_L(uint128_t a){
    int i = 0;
    for (; i < 16; ++i)
        a = rev_R(a);
    return a;
}

uint128_t rev_S(uint128_t a){
    uint128_t res;
    unsigned i;
    for(i = 0; i < 16; ++i){
        res.b[i] = rev_Pi[a.b[i]];
    }
    return res;
}

uint8_t** mul_forming(){
    uint16_t a,b;
    for (a = 0; a < 256; ++a)
        for (b = 0; b < 256; ++b)
            mul_table[a][b] = multiplication(a, b);
}

void print_128 (uint128_t a){
    int i;
    for(i = 15; i >= 0; --i){
         printf("%02x", a.b[i]);
    }
    printf("\n");
}

int main() {
    mul_forming();
//
    uint128_t a;
    uint128_t res;
//
    a.qw[1] = 0x559d8dd7bd06cbfe;
    a.qw[0] = 0x7e7b262523280d39;
    res = S(a);
    print_128(res);

    a.qw[1] = 0x64a5940000000000;
    a.qw[0] = 0x0000000000000000;
    res = R(a);
    print_128(res);

    a.qw[1] = 0xd456584dd0e3e84c;
    a.qw[0] = 0xc3166e4b7fa2890d;
    res = L(a);
    print_128(res);

    a.qw[1] = 0x9400000000000000;
    a.qw[0] = 0x0000000000000001;
    res = rev_R(a);
    print_128(res);

    a.qw[1] = 0x0c3322fed531e463;
    a.qw[0] = 0x0d80ef5c5a81c50b;
    res = rev_S(a);
    print_128(res);

    a.qw[1] = 0x0e93691a0cfc6040;
    a.qw[0] = 0x8b7b68f66b513c13;
    res = rev_L(a);
    print_128(res);

    return 0;
}
