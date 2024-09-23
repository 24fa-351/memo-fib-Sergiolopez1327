#include <stdio.h>
#include <stdlib.h>
#include <string.h>


unsigned long long fib_i_core(int fibIndex) {
    if (fibIndex == 0) {
        return 0; 
    } 
    if (fibIndex == 1) {
        return 1;  
    } 
    unsigned long long previous_num = 0;
    unsigned long long current_num = 1;
    unsigned long long next_num;
    for (int index = 2; index <= fibIndex; index++) {
        next_num = previous_num + current_num;
        previous_num = current_num;
        current_num = next_num;
    }
    return current_num;
}
unsigned long long fib_r_core(int fibIndex) {
    if (fibIndex == 0) {
        return 0; 
    } 
    if (fibIndex == 1) {
        return 1;  
    } 
    return fib_r_core(fibIndex - 1) + fib_r_core(fibIndex - 2);
}

unsigned long long *memo_cache;

unsigned long long memoized_fib_r_core(int fibIndex) {
    if (memo_cache[fibIndex] != -1) {
        return memo_cache[fibIndex];
    }

    if (fibIndex == 0) {
        memo_cache[fibIndex] = 0;
    } else if (fibIndex == 1) {
        memo_cache[fibIndex] = 1;
    } else {
        memo_cache[fibIndex] = memoized_fib_r_core(fibIndex - 1) + memoized_fib_r_core(fibIndex - 2);
    }
    return memo_cache[fibIndex];
}

unsigned long long fib_wrapper(int fibIndex, char fib_method) {
    if (fib_method == 'r') {
        return fib_r_core(fibIndex);
    } else if (fib_method == 'i') {
        return fib_i_core(fibIndex);
    }
    return 0;
}

unsigned long long memoized_fib_wrapper(int fibIndex, char fib_method) {
    if (fib_method == 'r') {
        return memoized_fib_r_core(fibIndex);
    } else if (fib_method == 'i') {
        return fib_i_core(fibIndex);
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <integer> <r|i>\n", argv[0]);
        return 1;
    }

    int fibIndex = atoi(argv[1]);
    char fib_method = argv[2][0];
    unsigned long long result;

    if (fib_method == 'r') {
        memo_cache = (unsigned long long *)malloc((fibIndex + 1) * sizeof(unsigned long long));
        for (int i = 0; i <= fibIndex; i++) {
            memo_cache[i] = -1;
        }
        result = memoized_fib_wrapper(fibIndex - 1, fib_method);
        free(memo_cache);
    } else {
        result = fib_wrapper(fibIndex - 1, fib_method);
    }

    printf("%llu\n", result);

    return 0;
}