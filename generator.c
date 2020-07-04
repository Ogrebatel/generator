#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <memory.h>

#define bool char
#define false 0
#define true 1

//формируется массив из true/false, номера элементов которого равены значениям в последовательности;
//если число в последовательности встречается 2 раза, то последовательность неправильная
bool sequence_is_right (const uint32_t* sequence_to_check, const uint32_t size_seq) {
    uint32_t i;
    bool *check_array;
    if (sequence_to_check[size_seq - 1] != 1)
        return false;
    check_array = malloc((size_seq - 1) * sizeof(bool));
    memset(check_array, 0, size_seq - 1);

    for (i = 0; i < size_seq - 1; ++i) {
        if (check_array[sequence_to_check[i] - 1] == false) {
            check_array[sequence_to_check[i] - 1] = true;
        } else {
            free(check_array);
            return false;
        }
    }
    free(check_array);
    return true;
}

void fill_sequence_with_generator(uint32_t* sequence_to_fill, const uint32_t size_seq, const uint32_t generator){
    uint32_t i;
    sequence_to_fill[0] = 1;
    for (i = 1; i < size_seq; ++i){
        //мне подсказали эту строчку, когда я сказал, что использую pow
        sequence_to_fill[i]=(sequence_to_fill[i-1]*generator) % size_seq;
    }
}

int main() {
    uint32_t size_seq;
    uint32_t generator;
    uint32_t i;
    uint32_t* sequence;
    bool existion = false;

    printf("enter number:");
    scanf("%u", &size_seq);

    sequence = malloc(size_seq * sizeof(uint32_t));

    for (generator = 2; generator < size_seq; ++generator){
        fill_sequence_with_generator(sequence, size_seq, generator);
        if (sequence_is_right(sequence, size_seq)) {
            existion = true;
            printf("true generator for %u: %u\n", size_seq, generator);
            for (i = 0; i < size_seq; ++i) {
                printf("%u ", sequence[i]);
            }
            putchar('\n');
        }
    }
    if (!existion)
        printf("generator doesn't exist :(\n");
    free(sequence);
    return 0;
}