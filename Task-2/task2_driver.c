#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


// #define MAX_BUF 1024 //Constant for max buffer

int main(int argc, char **argv)
{
   if (argc != 5) {  //check for arguments passed to driver
        fprintf(stderr, "Usage: %s <user1_content> <user1_store> <user2_content> <user2_store>\n", argv[0]);
        exit(-1);
    }

//printf("In Main under driver\n");
 const char *task2_user_binary_path = "Task-2/task2_user";
 char *task2_user1_content = argv[1];
 char *task2_user1_store = argv[2];
 char *task2_user2_content = argv[3];
 char *task2_user2_store = argv[4];
 char *task2_user_binary_name="task2_user";
//Creation of Pipes
  int task2_user1_pipeFD[2];
  int task2_user2_pipeFD[2];
pid_t task2_user2_PID; //User 2 
pid_t task2_user1_PID;// User 1
   // Check if user binary file exists or not
  // const char *file_path = "Task-2/task2_user";
    if (access(task2_user_binary_path, F_OK) != 0) {
        //printf("File exists at %s\n", file_path);
        perror("ERROR: user binary File does not exist or cannot be accessed:");
    } 
	

//First pipe
  if (pipe(task2_user1_pipeFD)== -1)
  {
    perror("ERROR: Failed to create Pipe Error: ");
  }

  // Second pipe
  if (pipe(task2_user2_pipeFD) == -1)
  {
    perror("ERROR: Failed to create Pipe: ");
  }
// endregion

  // Fork again to create second user
  task2_user1_PID = fork();
  if (task2_user1_PID == -1)
  {
    perror("ERROR: Failed  to create child process_1:");
  }

  if (task2_user1_PID == 0) //User 1 child process
  {

    char str_readFD[10];
    char str_writeFD[10];;
    sprintf(str_readFD, "%d", task2_user1_pipeFD[0]); //convert this to string to pass on to user funtion
     
    sprintf(str_writeFD, "%d", task2_user2_pipeFD[1]); //convert this to string to pass on to user funtion
   //printf("after 2nd sprintf under driver\n");

    /*
    else {
        perror("File does not exist or cannot be accessed");
    }
    */
    // Exec to the first process
    //printf("Exec for 1st User");
     execl(task2_user_binary_path, task2_user_binary_name,str_readFD, str_writeFD, task2_user1_content, task2_user1_store, NULL);
    //execpl(user_program, "User 1 Process", readFDStr, writeFDStr, argv[1], argv[2], NULL);
    perror("ERROR:Unable to execute:");
  }
  else
  {

    // First Parent Process - Create another fork
    task2_user2_PID = fork();
    if (task2_user2_PID == -1)
    {
      perror("Failed to create user 2 child process. Error");
    }

    if (task2_user2_PID == 0)
    {
      // Second Child Process.

      // Convert the pipeFDs to the string to pass them as an arguments to the executable
      char task2_str_readFD2[10];
      char task2_str_writeFD2[10];

      sprintf(task2_str_readFD2, "%d", task2_user2_pipeFD[0]);//convert this to string to pass on to user funtion
      sprintf(task2_str_writeFD2, "%d", task2_user1_pipeFD[1]);//convert this to string to pass on to user funtion

      // Exec to the second process
       execl(task2_user_binary_path, task2_user_binary_name,task2_str_readFD2, task2_str_writeFD2, task2_user2_content, task2_user2_store, NULL);
      //execlp("./task2_user", "User 2 Process", readFDStr, writeFDStr, argv[3], argv[4], (char *)NULL);
      perror("ERROR:Unable to execute:");
    }
    else
    {
      // Second Parent Process - Wait for all childs to finish execution
      wait(NULL);
    }
  }
  
 // waitpid(pid, NULL, 0);
   // Now you can kill the child process if needed
   // Check if the child process still exists
     //This is not good programming but still i am using it :(
//Sometime user still hanging so i am using this kill user pid as we are end.
 //This issue occured during discusion with ARUN Sir, so i decided to use Kill here.
 
        if (kill(task2_user1_PID, 0) == 0) {
          // If the process exists, wait for 2 seconds
            sleep(1);
             kill(task2_user1_PID, SIGKILL); 
        }
        if (kill(task2_user2_PID, 0) == 0) {
          // If the process exists, wait for 2 seconds
            sleep(1);
             kill(task2_user2_PID, SIGKILL); 
        }
  


  return 0;
}
