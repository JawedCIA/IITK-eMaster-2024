include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

long long calculateSpace(const char *path) {
    DIR *dir;
    struct dirent *entry;
    struct stat info;
    long long totalSpace = 0;

    if ((dir = opendir(path)) == NULL) {
        perror("Unable to open directory");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        // Ignore "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char filePath[PATH_MAX];
        snprintf(filePath, PATH_MAX, "%s/%s", path, entry->d_name);

        if (stat(filePath, &info) == -1) {
            perror("Unable to get file information");
            exit(EXIT_FAILURE);
        }

        if (S_ISDIR(info.st_mode)) {
            // If it's a directory, recursively calculate space
            totalSpace += calculateSpace(filePath);
        } else {
            // If it's a file, add its size to total space
            totalSpace += info.st_size;
        }
    }

    closedir(dir);
    return totalSpace;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
     r   exit(EXIT_FAILURE);
    }

    const char *rootDirectory = argv[1];

    long long totalSpace = calculateSpace(rootDirectory);

    printf("Space used by directory %s: %lld bytes\n", rootDirectory, totalSpace);

    return 0;
}
