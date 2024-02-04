#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <user1_content> <user1_store> <user2_content> <user2_store>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int pipe_user1_to_user2[2];
    int pipe_user2_to_user1[2];

    // Create pipes
    if (pipe(pipe_user1_to_user2) == -1 || pipe(pipe_user2_to_user1) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    pid_t user1_pid, user2_pid;

    // Fork for user-1
    user1_pid = fork();

    if (user1_pid == -1) {
        perror("Fork failed for user-1");
        exit(EXIT_FAILURE);
    }

    if (user1_pid == 0) {
        // Child process (user-1)
        close(pipe_user1_to_user2[1]); // Close write end of pipe_user1_to_user2
        close(pipe_user2_to_user1[0]); // Close read end of pipe_user2_to_user1

        dup2(pipe_user1_to_user2[0], STDIN_FILENO);  // Redirect stdin to read from pipe_user1_to_user2
        dup2(pipe_user2_to_user1[1], STDOUT_FILENO); // Redirect stdout to write to pipe_user2_to_user1

        execlp("./task2_user", "./task2_user", argv[1], argv[2], NULL);
        perror("User-1: exec failed");
        exit(EXIT_FAILURE);
    }

    // Fork for user-2
    user2_pid = fork();

    if (user2_pid == -1) {
        perror("Fork failed for user-2");
        exit(EXIT_FAILURE);
    }

    if (user2_pid == 0) {
        // Child process (user-2)
        close(pipe_user1_to_user2[0]); // Close read end of pipe_user1_to_user2
        close(pipe_user2_to_user1[1]); // Close write end of pipe_user2_to_user1

        dup2(pipe_user2_to_user1[0], STDIN_FILENO);  // Redirect stdin to read from pipe_user2_to_user1
        dup2(pipe_user1_to_user2[1], STDOUT_FILENO); // Redirect stdout to write to pipe_user1_to_user2

        execlp("./task2_user", "./task2_user", argv[3], argv[4], NULL);
        perror("User-2: exec failed");
        exit(EXIT_FAILURE);
    }

    // Close unnecessary pipe ends in the parent
    close(pipe_user1_to_user2[0]);
    close(pipe_user1_to_user2[1]);
    close(pipe_user2_to_user1[0]);
    close(pipe_user2_to_user1[1]);

    // Wait for both user processes to finish
    waitpid(user1_pid, NULL, 0);
    waitpid(user2_pid, NULL, 0);

    return 0;
