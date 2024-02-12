#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <calc.h>


void client(int readfd, int writefd){
  /*************************************************************
   Client used by the parent process
  *************************************************************/
  char buf[MAX_BUFF];
  char buf_calc_result[MAX_BUFF];
  size_t len;
	
	
     //read the inout provided by user on STDIN	
		if (read(STDIN_FILENO, buf, sizeof(buf)) <= 0) {
            fprintf(stderr, "Client - Error reading input\n");
            exit(1);
        }
 
			
	 // write pipe for client
            write(writefd, buf, strlen(buf) + 1);
            close(writefd); //Close the end
	 // Wait for server to send a string
            wait(NULL);
			/*
			 // Check for termination
			if (strcmp(buf, "END") == 0) {
				exit(0);
			}
			*/
	// Read string from child, print it and close
            // reading end.
           // read(readfd, buf_calc_result, sizeof(buf_calc_result));
			 while (read(readfd, buf_calc_result, sizeof(buf_calc_result)) > 0) {
				 // Check for termination
				if (strcmp(buf_calc_result, "END") == 0) {
						//printf("RESULT: %s\n", buf_calc_result);
						exit(0);
					}
					else
					{
						printf("RESULT: %s\n", buf_calc_result); //Display Result recieved by Client from server.
					}
			}
			close(readfd); //Close the read end
			wait(NULL);
			 // Check for termination	
            
           // sleep(2);
		
}
