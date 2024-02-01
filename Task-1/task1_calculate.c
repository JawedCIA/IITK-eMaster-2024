#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <calc.h>

// Utility function to check if a character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%');
}

// Utility function to get the precedence of an operator
int getPrecedence(char op) {
   //fprintf(stderr, "Operator is : %c\n",op);
	 if (op == '%')
		 return 1;
	 else if (op == '/')
		 return 2;
	  else if (op == '*')
		 return 3;
	  else if (op == '+')
		 return 4;
	  else if (op == '-')
		 return 5;
	  else
        return 0;  // Not an operator
}

// Utility function to perform the calculation based on operator
double performOperation(double operand1, double operand2, char op) {
    switch (op) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            if (operand2 != 0) {
                return operand1 / operand2;
            } else {
                fprintf(stderr, "Error: Division by zero\n");
                exit(EXIT_FAILURE);
            }
        case '%':
            if (operand2 != 0) {
                return (int)operand1 % (int)operand2;
            } else {
                fprintf(stderr, "Error: Modulo by zero\n");
                exit(EXIT_FAILURE);
            }
        default:
            fprintf(stderr, "Error: Unknown operator %c\n", op);
            exit(EXIT_FAILURE);
    }
}

double calculate(char *expression) {
    double operands[20];
    char operators[20];
    int operandIndex = 0;
    int operatorIndex = 0;

    char *token = strtok(expression, " ");
    while (token != NULL) {
        if (isOperator(token[0])) {
            while (operatorIndex > 0 &&
                   getPrecedence(operators[operatorIndex - 1]) >= getPrecedence(token[0])) {
                double operand2 = operands[--operandIndex];
                double operand1 = operands[--operandIndex];
                char op = operators[--operatorIndex];
                operands[operandIndex++] = performOperation(operand1, operand2, op);
            }
            operators[operatorIndex++] = token[0];
        } else {
            operands[operandIndex++] = atof(token);
        }

        token = strtok(NULL, " ");
    }

    while (operatorIndex > 0) {
        double operand2 = operands[--operandIndex];
        double operand1 = operands[--operandIndex];
        char op = operators[--operatorIndex];
        operands[operandIndex++] = performOperation(operand1, operand2, op);
    }

    return operands[0];
}

