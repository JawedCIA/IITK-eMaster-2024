#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <calc.h>
#include <time.h>


void server(int readfd, int writefd){
  /*************************************************************
    server code to be used by the child process
  *************************************************************/
  char buf[MAX_BUFF];
  size_t len;	
  double result;
 char result_buf[MAX_BUFF]; //Added this to convert double result to string before writing for client

	// Read the Input written by Cleint into Pipe	
        if (read(readfd, buf, sizeof(buf)) <= 0) {
            // Handle potential pipe closure or error
            exit(1);
        }
	close(readfd);//Close the server read pipe end
// Split the received string into individual expressions
        char *token = strtok(buf, "\n");
		while (token != NULL) {
			//printf("Server Processing: %s\n",token);
			// Read Token and terminating word from the client
			if (strcmp(token, "END") == 0) {
				
				write(writefd,"END", sizeof("END"));
				break;
			}			
			//Call Calculator
			result=calculate(token); //Call calculate funtion to get calculation on provided input
			
			//printf("calc Result: %.3f\n",result);
			// Reset the content of buf to 0 to reuse it for result
    			 memset(result_buf, 0, sizeof(result_buf));
			// Convert the double value to a string
    		 len = snprintf(result_buf, sizeof(result_buf), "%.3f", result);
			//snprintf(result_withprecision, sizeof(result_withprecision), "%.3f", result); 
			 // Check for result snprintf  length for any error 
			if (len < 0) {
				perror("Error converting result double to string");
				break;;
			}
			write(writefd,result_buf, sizeof(result_buf)); // write the result to the file descriptor for client
			usleep(300000);
			//sleep(1); //Sleep for 1 second
			// Get the next token
			token = strtok(NULL, "\n");
			//printf("Next Token Processing: %s\n",token);
			if (token == NULL) {
				break;  // No more tokens found
			}
			//printf("Server Send Result: %s\n",result_withprecision);
			 //Close the server Writeebd
		}
		close(writefd); //Close the server Writeebd
		exit(0);
}
