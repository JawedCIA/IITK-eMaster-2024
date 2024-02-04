#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <calc.h>
#include <time.h>

time_t current_time;
struct tm *time_info;
void server(int readfd, int writefd){
  /*************************************************************
   write server code to be used by the child process
  *************************************************************/
  char buf[MAX_BUFF];
  size_t len;	
  double result;
  char result_withprecision[MAX_BUFF];
  
	//read(readfd, buf, sizeof(buf)); // Read the Input written by Cleint into Pipe
	// Read expressions and terminating word from the client
        if (read(readfd, buf, sizeof(buf)) <= 0) {
            // Handle potential pipe closure or error
            exit(1);
        }
	close(readfd);//Close the server read pipe end
// Split the received string into individual expressions
        char *token = strtok(buf, "\n;");
		while (token != NULL) {
			//printf("Server Processing: %s\n",token);
			if (strcmp(token, "END") == 0) {
				
				write(writefd,"END", sizeof("END"));
				break;
			}			
			//Call Calculator
			result=calculate(token); //Call calculate funtion to get calculation on provided input
			
			//printf("calc Result: %.3f\n",result);
			snprintf(result_withprecision, sizeof(result_withprecision), "%.3f", result);   
			write(writefd,result_withprecision, sizeof(result_withprecision));
			sleep(2);
			// Get the next token
			token = strtok(NULL, "\n;");
			if (token == NULL) {
				break;  // No more tokens found
			}
			//printf("Server Send Result: %s\n",result_withprecision);
			 //Close the server Writeebd
		}
		close(writefd); //Close the server Writeebd
		exit(0);
	// Check for termination
	/*
			if (strcmp(buf, "END") == 0) {
				exit(0);
			}
			*/
	
	
	
		// Using snprintf for safety
   // snprintf(result_withoutpresion, sizeof(result_withoutpresion), "%g", result); //convert double to string without any presion
	
    //printf("Using snprintf: %s\n", result_withprecision);
    //Write the Calculat result back to Client through pipe.
   
  /* Implement server functionlity here
    use calculate function to evaluate expression
    signature: calculate(char *buf)
  */
}
