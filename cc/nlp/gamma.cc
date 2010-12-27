#include <math.h>
#include <stdint.h>
#include <iostream>
using namespace std;

uint32_t encode_unary(uint32_t x) {
    uint32_t result = 0;
    for (uint32_t i = 0; i < x-1; i++) {
        result |= (1<<(i+1));
    }
    return result;
}
uint32_t decode_unary(uint32_t x) {
    uint32_t result = 0;
    for (uint32_t i = 0; i < 32; i++) {
        if ((x >> i) & 1) {
            result ++;
        }
    }
    return result + 1;
}

uint32_t encode_gamma(uint32_t x) {
    uint32_t n = 1 + (uint32_t) log2(x);
    uint32_t r = x - pow(2, (uint32_t)log2(x));
    return (encode_unary(n) << (n-1)) + r;
}

uint32_t decode_gamma(uint32_t x) {
    bool flag = false;
    int u = 0;
    uint32_t i = 0;
    for (; i < 32; i++) {
        if ((x >> (31-i)) & 1) {
            u ++;
            flag = true;
        } else if (flag) {
            break;
        }
    }
    uint32_t b = (x << (i+1)) >> (i+1);
    return pow(2, u) + b;
}

int main() {
    for (int i = 1; i <= 10; i++) {
        printf("%d : 0x%x\n", i, encode_gamma(i));
    }
    for (int i = 1; i <= 10; i++) {
        printf("%d : %d\n", i, decode_gamma(encode_gamma(i)));
    }
    return 0;
}
