#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <calc.h>
#include <unistd.h>

//REF: https://www.w3resource.com/c-programming-exercises/basic-declarations-and-expressions/c-programming-basic-exercises-150.php

// Function declarations
double calculate(char *buf);
double term(char **ptr);
double muldivmodulo(char **ptr);
double addsub(char **ptr);

char input[101]; // Declare character array to store user input
int pos = 0;    // Initialize a global variable to keep track of the position in the input string

// Function to calculate expression result
double calculate(char *buf) {
	///////////////
	/*
	double operands[20];
    char op[20];
    int oprnInd = 0;
    double result = 0.0;

    char *token = strtok(buf, " ");

    while (token != NULL) {
        if (oprnInd % 2 == 0) {
            sscanf(token, "%lf", &operands[oprnInd / 2]);
        } else {
            op[oprnInd / 2] = token[0];
        }
        oprnInd++;
        token = strtok(NULL, " ");
    }
	*/
	////////////////////////
	// Remove spaces from the input string in place as it is required to input the operation with space.
    int i, j;
    for (i = 0, j = 0; buf[i] != '\0'; i++) {
         if (buf[i] != ' ' && buf[i] != '\n') {
            buf[j++] = buf[i];
        }
    }
    buf[j] = '\0';  // Null-terminate the modified string
	//printf("Expression without spaces: %s\n", buf);  // Print the modified buf
    return addsub(&buf);
}

// Function to parse and evaluate a term (number or expression )
double term(char **ptr) {
    double n = 0;

        // If the current character is a digit, parse the number
        while ('0' <= (*ptr)[0] && (*ptr)[0] <= '9') {
            n = n * 10 + ((*ptr)[0] - '0'); // Convert characters to integer and build the number
            (*ptr)++; // Move to the next character
        }
  
    return n; // Return the parsed number
}

// Function to handle multiplication and division operations
double muldivmodulo(char **ptr) {
    double first, second;

    first = term(ptr); // Evaluate the first term

    for (;;) {
        if ((*ptr)[0] == '*') {
            (*ptr)++; // Move to the next character (operator)
            second = term(ptr); // Evaluate the second term
            first *= second; // Perform multiplication
        } else if ((*ptr)[0] == '/') {
            (*ptr)++; // Move to the next character (operator)
            second = term(ptr); // Evaluate the second term
            first /= second; // Perform division
        } else if ((*ptr)[0] == '%') {
            (*ptr)++; // Move to the next character (operator)
            second = term(ptr); // Evaluate the second term
            first = (int)first % (int)second; // Perform modulo (convert to int for modulo operation)
        } else {
            return first; // If no more operators, return the result
        }
    }
}

// Function to handle addition and subtraction operations
double addsub(char **ptr) {
    double first, second;

    first = muldivmodulo(ptr); // Evaluate the first term

    for (;;) {
        if ((*ptr)[0] == '+') {
            (*ptr)++; // Move to the next character (operator)
            second = muldivmodulo(ptr); // Evaluate the second term
            first += second; // Perform addition
        } else if ((*ptr)[0] == '-') {
            (*ptr)++; // Move to the next character (operator)
            second = muldivmodulo(ptr); // Evaluate the second term
            first -= second; // Perform subtraction
        } else {
            return first; // If no more operators, return the result
        }
    }
}




