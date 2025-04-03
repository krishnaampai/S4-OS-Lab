#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <time.h>

void printFileProperties(struct stat stats) {
    struct tm dt;

    // File permissions
    printf("\nFile access: ");
    if (stats.st_mode & S_IRUSR) printf("read ");
    if (stats.st_mode & S_IWUSR) printf("write ");
    if (stats.st_mode & S_IXUSR) printf("execute");

    // File size
    printf("\nFile size: %ld bytes", stats.st_size);

    // Creation time
    dt = *(gmtime(&stats.st_ctime));
    printf("\nCreated on: %d-%d-%d %d:%d:%d\n",
           dt.tm_mday, dt.tm_mon + 1, dt.tm_year + 1900,
           dt.tm_hour, dt.tm_min, dt.tm_sec);

    // Modification time
    dt = *(gmtime(&stats.st_mtime));
    printf("\nModified on: %d-%d-%d %d:%d:%d\n",
           dt.tm_mday, dt.tm_mon + 1, dt.tm_year + 1900,
           dt.tm_hour, dt.tm_min, dt.tm_sec);
}

void listDirectoryContents() {
    DIR *dir = opendir(".");
    if (dir) {
        struct dirent *entry;
        printf("\nDirectory Contents:\n");
        while ((entry = readdir(dir)) != NULL) {
            printf("%s\n", entry->d_name);
        }
        closedir(dir);
    } else {
        perror("opendir failed");
    }
}

int main() {
    pid_t pid;

    printf("Current Process ID: %d\n", getpid());

    pid = fork();

    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    // In the child process
    if (pid == 0) {
        printf("Child Process (PID %d):\n", getpid());
        
        // Execute a new program (execvp in child process)
        char *args[] = {"ls", "-l", NULL};
        execvp(args[0], args);
        
        perror("execvp failed");
        exit(EXIT_FAILURE);
    }
    else {
        printf("Parent Process (PID %d): Waiting for child to finish...\n", getpid());
        
        wait(NULL);
        printf("Parent Process: Child has finished execution.\n");
    }

    // File Operations with stat()
    char fname[100];
    struct stat stats;

    printf("Enter the file name to check properties: ");
    scanf("%s", fname);

    if (stat(fname, &stats) == 0) {
        printFileProperties(stats);
    } else {
        printf("Unable to get file properties.\n");
        printf("Please check whether '%s' file exists.\n", fname);
    }

    // List the contents of the current directory using opendir/readdir
    listDirectoryContents();

    return 0;
}

