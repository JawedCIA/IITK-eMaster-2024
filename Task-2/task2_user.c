#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE_LENGTH 500

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *input_file = fopen(argv[1], "r");
    FILE *output_file = fopen(argv[2], "w");

    if (input_file == NULL || output_file == NULL) {
        perror("Error opening files");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];

    // Read the first line to determine if this user is the initiator
    fgets(line, sizeof(line), input_file);
    if (strstr(line, "initiate") != NULL) {
        // User is the initiator, start the chat
        printf("Initiating the chat...\n");

        // Read and write messages until "bye" or end of file is encountered
        while (fgets(line, sizeof(line), input_file) != NULL && strstr(line, "bye") == NULL) {
            printf("User: %s", line);
            fprintf(output_file, "User (Reply): %s", line);
        }
    } else {
        // User is not the initiator, wait for the initiator's message
        printf("Waiting for the initiator's message...\n");

        // Read and write messages until "bye" or end of file is encountered
        while (fgets(line, sizeof(line), input_file) != NULL && strstr(line, "bye") == NULL) {
            printf("User: %s", line);
            fprintf(output_file, "User (Reply): %s", line);
        }
    }

    // Close files
    fclose(input_file);
    fclose(output_file);

    printf("Chat communication completed.\n");

    return 0;
}
