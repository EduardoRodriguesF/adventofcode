#include "lcm.h"
#include <stdbool.h>

bool is_prime(int num) {
    if (num == 0 || num == 1) return false;

    for (int i = 2; i < num / 2; i++) {
        if (num % i == 0) return false;
    }

    return true;
}

size_t lcm(size_t numbers[], size_t n) {
    size_t prime = 2;
    size_t result = 1;
    bool could_divide;
    size_t largest_num = 0;

    do {
        could_divide = false;

        for (size_t i = 0; i < n; i++) {
            if (numbers[i] % prime == 0) {
                numbers[i] /= prime;
                could_divide = true;
            }
        }

        largest_num = 0;
        for (size_t i = 0; i < n; i++)
            if (numbers[i] > largest_num) largest_num = numbers[i];

        if (could_divide) {
            result *= prime;
        }

        do prime++; while (!is_prime(prime)); // Find next prime number
    } while (largest_num >= prime);

    return result;
}
