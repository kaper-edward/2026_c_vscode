#include "calculator.h"
#include <stdio.h>

int main(void) {
    double a = 0.0;
    double b = 0.0;
    double result = 0.0;
    char op = '\0';

    printf("Enter expression (e.g., 10 / 5): ");
    if (scanf("%lf %c %lf", &a, &op, &b) != 3) {
        printf("Invalid input format.\n");
        return 1;
    }

    CalculatorStatus status = calculator_calculate(a, b, op, &result);
    if (status == CALC_OK) {
        printf("Result: %.2f\n", result);
        return 0;
    }

    if (status == CALC_ERR_DIVISION_BY_ZERO) {
        printf("Error: division by zero\n");
        return 1;
    }

    printf("Error: unknown operator '%c'\n", op);
    return 1;
}
