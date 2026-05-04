#ifndef CALCULATOR_H
#define CALCULATOR_H

typedef enum CalculatorStatus {
    CALC_OK = 0,
    CALC_ERR_DIVISION_BY_ZERO,
    CALC_ERR_UNKNOWN_OPERATOR
} CalculatorStatus;

CalculatorStatus calculator_calculate(double a, double b, char op, double *out_result);

#endif
