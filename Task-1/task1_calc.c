#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <calc.h>

int main(int argc, char **argv){

  /*************************************************************
   write code for the main process that will establish
   the communication channel between cleint and server using
   pipes
  *************************************************************/
	
  pid_t pid;

  // TODO:
  int fd1[2]; // Used to store two ends of first pipe
  int fd2[2]; // Used to store two ends of second pipe
 // int loopCount;
 //for (loopCount = 0; loopCount < 10; loopCount++)
//while(1)
  //{
	if (pipe(fd1) == -1)
    {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }

    if (pipe(fd2) == -1)
    {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }
	
  pid = fork();

  if(pid < 0){
    perror("Fork failed\n");
    return 1;
  }

  if(pid == 0){

    // TODO:
	close(fd1[1]); // Close writing end of first pipe
	 close(fd2[0]);
	 server(fd1[0],fd2[1]);
    //call to server here: server(int readfd, int writefd);
    exit(0);
  }

  // TODO:
	close(fd1[0]); // Close reading end of first pipe
	close(fd2[1]); // Close writing end of second pipe
	
	client(fd2[0],fd1[1]);
  //call to client here client(int readfd, int writefd);
  //} //End of For Loop
  return 0;
  
}
