#include <stdio.h>

static int factorial(int n) {
    int result = 1;

    for (int i = 2; i <= n; ++i) {
        result *= i;
    }

    return result;
}

int main(void) {
    printf("Q02: factorial 5 = %d\n", factorial(5));
    return 0;
}
