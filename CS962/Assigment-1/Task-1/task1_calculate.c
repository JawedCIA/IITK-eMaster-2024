#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <calc.h>
#include <unistd.h>


// Function declarations
double task1_calculate(char *buf);
double task1_check_number_expression(char **ptr); //store whether provided expresison have operands or operators
double task1_precedence1(char **ptr); //To perform division, multiplication and modulo operators are at same precedence (say precedence-1)
double task1_precedence2(char **ptr); //To Perform addition and subtraction are at precedence-2


// Function to calculate expression result
double calculate(char *buf) {
    /*/
    char buf_check_condition[MAX_BUFF]={0};
	    // Copy the contents of buff1 to buff2
    strcpy(buf_check_condition, buf);
	double operands[20];
    char op[20];
    int oprnInd = 0;
    double result = 0.0;

    char *token = strtok(buf_check_condition, " ");

    while (token != NULL) {
        if (oprnInd % 2 == 0) {
            sscanf(token, "%lf", &operands[oprnInd / 2]);
        } else {
            op[oprnInd / 2] = token[0];
        }
        oprnInd++;
        token = strtok(NULL, " ");
        	if (token == NULL) {
				break;  // No more tokens found
			}
    }
	printf("print buf %s\n",buf);
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
   // printf("Total j : %d",j);
    //Check for expression length , as per the requirement it should be more than 20 (operands) + 19 (operators)
          return task1_precedence2(&buf);
    
	//printf("Expression without spaces: %s\n", buf);  // Print the modified buf
   
}

// Function to parse and evaluate a term (number or expression )
double task1_check_number_expression(char **ptr) {  
    double n = 0.0;
    int decimal_flag = 0;
    int decimal_places = 0;
    double decimal_multiplier = 1.0;
   // If the current character is a digit or a decimal point, parse the number
    while (('0' <= (*ptr)[0] && (*ptr)[0] <= '9') || (*ptr)[0] == '.') {
        if ((*ptr)[0] == '.') {
            decimal_flag = 1;
        } else {
            if (!decimal_flag) {
                n = n * 10 + ((*ptr)[0] - '0'); // Convert characters to integer and build the number
            } else {
                decimal_multiplier *= 0.1;
                n += ((*ptr)[0] - '0') * decimal_multiplier;
            }
        }
        (*ptr)++; // Move to the next character
    }   
    return n; // Return the parsed number
}

// Function to handle multiplication and division operations
double task1_precedence1(char **ptr) {
    double first, second;

    first = task1_check_number_expression(ptr); // Evaluate the first term

    for (;;) {
        if ((*ptr)[0] == '*') {
            (*ptr)++; // Move to the next character (operator)
            second = task1_check_number_expression(ptr); // Evaluate the second term
            first *= second; // Perform multiplication
        } else if ((*ptr)[0] == '/') {
            (*ptr)++; // Move to the next character (operator)
            second = task1_check_number_expression(ptr); // Evaluate the second term
            first /= second; // Perform division
        } else if ((*ptr)[0] == '%') {
            (*ptr)++; // Move to the next character (operator)
            second = task1_check_number_expression(ptr); // Evaluate the second term
            first = (int)first % (int)second; // Perform modulo (convert to int for modulo operation)
        } else {
            return first; // If no more operators, return the result
        }
    }
}

// Function to handle addition and subtraction operations
double task1_precedence2(char **ptr) {
    double first, second;

    first = task1_precedence1(ptr); // Evaluate the first term

    for (;;) {
        if ((*ptr)[0] == '+') {
            (*ptr)++; // Move to the next character (operator)
            second = task1_precedence1(ptr); // Evaluate the second term
            first += second; // Perform addition
        } else if ((*ptr)[0] == '-') {
            (*ptr)++; // Move to the next character (operator)
            second = task1_precedence1(ptr); // Evaluate the second term
            first -= second; // Perform subtraction
        } else {
            return first; // If no more operators, return the result
        }
    }
}




