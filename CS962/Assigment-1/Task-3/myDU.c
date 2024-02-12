#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024 //Constanct to improve code readability and maintainability

/*
Task 3: Directory Space Usage
Date:2024-02-05
Course: CS962
Name: Mohammed Jawed
Note: I have refactor the code as well as changed the logic, Removed Code Duplication and added proper commenst to make it understandble.
*/

void task3_printSize(long long size);// Function to print the size
long long task3_calculateTotalSize(const char* path); // Function to calculate the total size of a directory or file


// Main function
int main(int argc, char* argv[]) {
    // Check if the correct number of command-line arguments is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path>\n", argv[0]);
        return -1;
    }
    // Get the path from command-line arguments
    const char* path = argv[1];
    // Calculate the total size and handle errors
    long long total_size = task3_calculateTotalSize(path);
    // Check if the size calculation was successful
    if (total_size != -1) {
        // Print the total size
        task3_printSize(total_size);
        return 0;
    } else {
        // Return failure if there was an error
        return -1;
    }
}


// Function to print the size
void task3_printSize(long long size) { 
    char str[BUFFER_SIZE];
    snprintf(str, sizeof(str), "%lld", size);
    printf("%s\n", str);
}

// Function to calculate the total size of a directory or file
long long task3_calculateTotalSize(const char* path) {
    struct stat st;

    // Retrieve file information
    if (stat(path, &st) != 0) {
        perror("unable to execute");
        return -1;
    }

    if (S_ISDIR(st.st_mode) || S_ISLNK(st.st_mode)) {
        // Handling for directories and symbolic links
        long long total_size = 0;
        DIR *dir = NULL;

        if (S_ISDIR(st.st_mode)) {
            // For directories, calculate the total size of its contents
            total_size = st.st_size;
            dir = opendir(path);
        } else if (S_ISLNK(st.st_mode)) {
            // For symbolic links, provide a warning and skip size calculation
           // fprintf(stderr, "This is a symbolic link. Size calculation might not be accurate.\n");
		   perror("unable to execute");
            return -1;
        }

        if (dir == NULL) {
            perror("unable to execute");
            return -1;
        }

        struct dirent* entry;
        while ((entry = readdir(dir)) != NULL) {
            // Skip '.' and '..' entries
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                // Create the path for the child entry
                char child_path[BUFFER_SIZE];
                snprintf(child_path, sizeof(child_path), "%s/%s", path, entry->d_name);

                // Create a pipe for communication between parent and child
                int fd[2];
                if (pipe(fd) == -1) {
                   perror("unable to execute");
                    return -1;
                }

                // Fork to create a child process
                pid_t pid = fork();

                if (pid == -1) {
                    perror("unable to execute");
                    return -1;
                }

                if (pid == 0) {
                    // Code for the child process
                    dup2(fd[1], STDOUT_FILENO);
                    close(fd[1]);
                    close(fd[0]);
                    //Execute the same program recursively for the child entry
					/*
					I have used execlp command to execute another instance of the same program ("myDU") 
					with a different argument, effectively creating a new process to handle the calculation 
					of the size for a specific subdirectory.
					*/
                    execlp("./myDU", "./myDU", child_path, NULL); //this approach is same as TASK-2
                    
					perror("unable to execute");
                    exit(EXIT_FAILURE);
                } else {
                    // Code for the parent process
                    close(fd[1]);
                    dup2(fd[0], STDIN_FILENO);
                    close(fd[0]);

                    // Read from child's output and accumulate total size
                    char buffer[BUFFER_SIZE];
                    int nread;
                    while ((nread = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
                        write(STDIN_FILENO, buffer, nread);
                    }

                    // Convert child's output to a long long integer
                    char* endptr;
                    long long int temp = strtoll(buffer, &endptr, 10);
                    total_size += temp;

                    // Wait for the child process to finish
                    wait(NULL);
                }
            }
        }

        // Close the directory
        closedir(dir);
        return total_size;
    } else {
        // Handling for regular files
        long long int file_size = st.st_size;
        task3_printSize(file_size);
        return file_size;
    }
}

