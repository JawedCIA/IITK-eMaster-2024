#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <calc.h>


void client(int readfd, int writefd){
  /*************************************************************
   write client code to be used by the parent process
  *************************************************************/
  char buf[MAX_BUFF];
  char buf_calc_result[MAX_BUFF];
  size_t len;
	
	printf("Enter your input : ");
    fgets(buf, sizeof(buf), stdin);
  // implement client functionality
  // Remove the newline character at the end if present
            if (buf[strlen(buf) - 1] == '\n')
            {
                buf[strlen(buf) - 1] = '\0';
            }
	 // write pipe for client
            write(writefd, buf, strlen(buf) + 1);
            close(writefd);
	 // Wait for child to send a string
            wait(NULL);
			 // Check for termination
			if (strcmp(buf, "END") == 0) {
				exit(0);
			}
	// Read string from child, print it and close
            // reading end.
            read(readfd, buf_calc_result, sizeof(buf_calc_result));
            printf("RESULT: %s\n", buf_calc_result);
            close(readfd);
           // sleep(2);
		wait(NULL);
}
