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

    for (unsigned long long iter = 2; iter <= fibIndex; iter++) {
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


unsigned long long *memo_cache = NULL;

unsigned long long fib_memo(int fibIndex, unsigned long long (*fib_func)(int)) {
    memo_cache = (unsigned long long *)malloc((fibIndex + 1) * sizeof(unsigned long long));
    for (int i = 0; i <= fibIndex; i++) {
        memo_cache[i] = -1;
    }

    if (memo_cache[fibIndex] != -1) {
        return memo_cache[fibIndex];
    }
    if (fibIndex == 0) {
        memo_cache[fibIndex] = 0;
    } else if (fibIndex == 1) {
        memo_cache[fibIndex] = 1;
    } else {
        memo_cache[fibIndex] = fib_func(fibIndex);
    }
    return memo_cache[fibIndex];
}


unsigned long long fib_i(int fibIndex) {
    return fib_memo(fibIndex, fib_i_core);
}


unsigned long long fib_r(int fibIndex) {
    return fib_memo(fibIndex, fib_r_core);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <integer> <method>\n", argv[0]);
        return 1;
    }

    
    int input_number = atoi(argv[1]);
    char fib_method = argv[2][0];
    unsigned long long result;

    if (fib_method == 'i') {
        result = fib_i(input_number);
    } else if (fib_method == 'r') {
        result = fib_r(input_number);
    } else {
        fprintf(stderr, "Invalid method. Use 'i' for iterative or 'r' for recursive.\n");
        return 1;
    }

    printf("%llu\n", result);

    if (memo_cache != NULL) {
        free(memo_cache);
        memo_cache = NULL;
    }

    return 0;
}
