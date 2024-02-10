#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <calc.h>

int main(int argc, char **argv){

  /*************************************************************
  TASK 1: Lets Do Some Calculation !!!! Client-Server Calculator
  Name: Mohammed Jawed
  Date: 03rd Feb 2024
  *************************************************************/
	
  pid_t pid;

  // TODO:
  int task1_fd1[2]; // Used to store two ends of first pipe
  int task1_fd2[2]; // Used to store two ends of second pipe
//Check for Pipe
	if (pipe(task1_fd1) == -1)
    {
        fprintf(stderr, "First Pipe creation Failed");
        return 1;
    }

    if (pipe(task1_fd2) == -1)
    {
        fprintf(stderr, "Second Pipe Creation Failed");
        return 1;
    }
	//Create Child Process
  pid = fork();
//Check for Child Porcess return value from form.
  if(pid < 0){
    perror("Child Proces creation failed\n");
    return 1;
  }
 
 // Child Process, Act as Server
  if(pid == 0){

	close(task1_fd1[1]); // Close writing end of first pipe
	close(task1_fd2[0]);
	server(task1_fd1[0],task1_fd2[1]); //Call to Server    
  exit(0);
  }
  else //Parent Process act as Client
  {

	close(task1_fd1[0]); // Close reading end of first pipe
	close(task1_fd2[1]); // Close writing end of second pipe	
	client(task1_fd2[0],task1_fd1[1]); //Call to Client 
  }
  return 0;
  
}
