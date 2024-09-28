#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 1000
#define MAX_FIB_VALUE ULLONG_MAX

typedef unsigned long long (*FibMethod)(int);

unsigned long long int memo_cache[MAX] = {0};

FibMethod fibroutine;



int fibOverflow(unsigned long long a, unsigned long long b) {
    return (a > (ULLONG_MAX - b));
}

unsigned long long fib_i_core(int fibIndex) {
    if (fibIndex <= 2) {
        return fibIndex - 1;
    }
    unsigned long long previous = 0;
    unsigned long long current = 1;
    unsigned long long next;
    for (unsigned long long iter = 3; iter <= fibIndex; iter++) {
        if (fibOverflow(previous, current)) {
            fprintf(stderr, "Overflow detected at index %llu\n", iter + 2);
            return -1;
        }
        next = previous + current;
        previous = current;
        current = next;
    }
    return current;
}

unsigned long long fib_r_core(int fibIndex) {
    if (fibIndex <= 2) {
        return fibIndex - 1;
    }
    unsigned long long firstfibvalue = (*fibroutine)(fibIndex - 1);
    unsigned long long secondfibvalue = (*fibroutine)(fibIndex - 2);
    if (fibOverflow(firstfibvalue, secondfibvalue)) {
        fprintf(stderr, "Overflow detected at index %d\n", fibIndex);
        return -1;
    }
    return firstfibvalue + secondfibvalue;
}

// unsigned long long fib_r(int fibIndex) {
//     if (memo_cache[fibIndex] != 0) {
//         return memo_cache[fibIndex];
//     }
//         memo_cache[fibIndex] = fib_r_core(fibIndex);

//     return memo_cache[fibIndex];

// }

// unsigned long long fib_i(int fibIndex) {
//     if (memo_cache[fibIndex] != 0) {
//         return memo_cache[fibIndex];
//     }
    
//     memo_cache[fibIndex] = fib_i_core(fibIndex);
    
//     return memo_cache[fibIndex];

// }
FibMethod real_provider;


 unsigned long long int fib_memo(int fibIndex) {
    if (memo_cache[fibIndex] != 0)
      return memo_cache[fibIndex];


    if (fibIndex <= 2) {
       memo_cache[fibIndex] = fibIndex - 1;
       return memo_cache[fibIndex];
    } else {
     memo_cache[fibIndex] = (*real_provider)(fibIndex);
    }
   return memo_cache[fibIndex];
 }


int main(int argc, char *argv[]) {

   if (argc != 3 || (argv[2][0] != 'r' && argv[2][0] != 'i')) {
      printf("Invalid Input\n");
      return 0;
   }

   int input_number = atoi(argv[1]);
   char fib_method = argv[2][0];
   unsigned long long int result;

   fibroutine = fib_memo;
   
   if (fib_method == 'r') {
      real_provider = fib_r_core;
   }
   else if (fib_method == 'i') {
      real_provider = fib_i_core;
   } else {
       fprintf(stderr, "Invalid method. Use 'i' for iterative or 'r' for recursive.\n");
       return 1;
   }

   fibroutine = fib_memo;

   result = (*fibroutine)(input_number);
   
   printf("%llu\n", result);
   return 0;
}
