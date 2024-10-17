/*
Q.1 Write a C program that demonstrates file operations: create, write, read, and delete a file.
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char data[] = "Hello, World!\n";

    // Create and write to file
    fp = fopen("example.txt", "w");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }
    fprintf(fp, "%s", data);
    fclose(fp);

    // Read from file
    char buffer[100];
    fp = fopen("example.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }
    while (fgets(buffer, sizeof(buffer), fp)) {
        printf("%s", buffer);
    }
    fclose(fp);

    // Delete file
    if (remove("example.txt") == 0) {
        printf("File deleted successfully\n");
    } else {
        printf("Error deleting file\n");
    }

    return 0;
}



/*
Q.2 Write a C program to demonstrate the use of signals in process control. 
Create a child process that can be terminated using a signal sent from the parent.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int sig) {
    printf("Child process received signal %d. Terminating...\n", sig);
    exit(0);
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        signal(SIGTERM, signal_handler);
        while (1) {
            printf("Child process is running. PID: %d\n", getpid());
            sleep(1);
        }
    } else {
        // Parent process
        sleep(3); // Let the child run for a while
        printf("Parent process sending signal to terminate child...\n");
        kill(pid, SIGTERM); // Send signal to child
        wait(NULL); // Wait for child to terminate
    }

    return 0;
}
