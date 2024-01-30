#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_BUFF 500
#define STDIN 0
#define STDOUT 1
#define STDERR  2

int main(int argc, char **argv){

  /*************************************************************
   Implement the user program that can be invoked by the
   driver program to establish chat communication channel
   bwtween two user.

   please implement your program which take 4 arguments
   as follows

   argv[1]: read handle of channel
   argv[2]: write handle of channel
   argv[3]: chat content
   argv[4]: file to store other party message

  *************************************************************/

  if(argc < 5)
  {
    perror("Required 5 arguments\n");
    exit(0);
  }

  int readfd = atoi(argv[1]);   // read handle of channel
  int writefd = atoi(argv[2]);  // write handle of channel
  char *chat_file = argv[3];    // chat content file
  char *store_file = argv[4];   // store file
  FILE *content, *store;        // file stream to read your chat content and store other user's message

  // Start your implementation

  return 0;
}
