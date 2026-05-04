#include "calculator.h"

CalculatorStatus calculator_calculate(double a, double b, char op, double *out_result) {
    if (out_result == 0) {
        return CALC_ERR_UNKNOWN_OPERATOR;
    }

    switch (op) {
        case '+':
            *out_result = a + b;
            return CALC_OK;
        case '-':
            *out_result = a - b;
            return CALC_OK;
        case '*':
            *out_result = a * b;
            return CALC_OK;
        case '/':
            if (b == 0.0) {
                return CALC_ERR_DIVISION_BY_ZERO;
            }
            *out_result = a / b;
            return CALC_OK;
        default:
            return CALC_ERR_UNKNOWN_OPERATOR;
    }
}
