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
	char buf_result[MAX_BUFF];
	double result;
	read(readfd, buf, sizeof(buf));
	// Check for termination
			if (strcmp(buf, "END") == 0) {
				exit(0);
			}
	close(readfd);
	//Call Calculator
	result=calculate(buf);
	
		// Using snprintf for safety
    snprintf(buf_result, sizeof(buf_result), "%lf", result);
    printf("Using snprintf: %s\n", buf_result);
        write(writefd, buf_result, sizeof(buf_result));
        close(writefd);
        exit(0);
  /* Implement server functionlity here
    use calculate function to evaluate expression
    signature: calculate(char *buf)
  */
}
