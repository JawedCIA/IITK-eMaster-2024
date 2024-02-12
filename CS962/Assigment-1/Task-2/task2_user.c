
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

 #define MAX_BUF 1024 //Constant for max buffer


int main(int argc, char **argv)
{

 //printf("Inside User\n");
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <user1_content> <user1_store> <user2_content> <user2_store>\n", argv[0]);
        exit(-1);
    }

// read end of  pipe
  int task2_readfd = atoi(argv[1]); 
  // write end of  pipe
  int task2_writefd = atoi(argv[2]); 
  // Chat contents file path
  char *task2_chat_file = argv[3];   // chat content file
  // Store contents file path
  char *task2_store_file = argv[4];
  //To check which user is coming
  char *task2_user = argv[5]; 
  //To Store Chat and store File contents
  FILE *task2_content;
  FILE *task2_store;     

//printf("chat file: %s\n",chat_file);
//printf("store_file: %s\n",store_file);
  // Open the chat file and read its contents
  task2_content = fopen(task2_chat_file, "r");
 // printf("chat file contents: %s\n",content);
  if (task2_content == NULL)
  {
    perror("Unable to open chat content file. Error");
  }


  // Create the Store file if does not exist else clear the file.
  task2_store = fopen(task2_store_file, "w");
  
  if (task2_store == NULL)
  {

    perror("Unable to open chat store file. Error");
  }
  //Close Store file
  fclose(task2_store);
   //to get file contents
  char task2_buffer[MAX_BUF];
  // To get number of bytes to be read back, measure the file size
  fseek(task2_content, 0, SEEK_END);
  int task2_num_bytes_to_read = ftell(task2_content);
  // Point to the first location of the file. This will help read the file contents
  fseek(task2_content, 0, SEEK_SET);
  // Read the file contents
  fread(task2_buffer, task2_num_bytes_to_read, 1, task2_content);
  // Close the file after reading the contents
  fclose(task2_content);
  // Read each line of the file
 char task2_chatContentReadBack[MAX_BUF] ;
 char *token = strtok(task2_buffer,  "\n");
 // Send the remainder of the message(s)
  while (token != NULL)
  {
    // Check the length of the token
        size_t tokenLength = strlen(token);
        // Check if the length is within the desired limit
        if (tokenLength > 500) {
            perror("Each line in chat content can be a maximum of 500 characters");
            exit(0);
        } 
     
    // Clear the previous chat content
    memset(task2_chatContentReadBack, 0x00, MAX_BUF);
// printf("token:%s\n",token);
    // Check if we have any special words
    if (strncmp(token, "initiate", 8) == 0)
    {
      //TODO
    }
    else if (strncmp(token, "bye", 3) == 0)
    {

      break;
    }
    else
    {
      // Write to the write end of the pipe for the other user to read
      write(task2_writefd, token, strlen(token));
      // Read from the other user
      read(task2_readfd, task2_chatContentReadBack, MAX_BUF);
      sleep(1); //Sleep for 1 second
      // Append \n
      strcat(task2_chatContentReadBack, "\n");
      // Open the file in append mode
      task2_store = fopen(task2_store_file, "a");
      // Write the content into the file
      fwrite(task2_chatContentReadBack, 1, strlen(task2_chatContentReadBack), task2_store);
      // Closing the file after writing
      fclose(task2_store);
    }
    // Get he next token
    token = strtok(NULL, "\n");
    if (token == NULL) {
				break;  // No more tokens found
			}
  }
// printf("end of while loop");
  //exit(0);
  return 0;
}
