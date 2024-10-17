/*
Q.1 Write the simulation program for demand paging and show the 
page scheduling and total number of page faults according to 
the LRU page replacement algorithm. Assume the memory of n frames.
Reference String: 3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6
*/

#include <stdio.h>

int main() {
    int frames, pages, i, j, pageFaults = 0, counter = 0;
    int frame[10], page[20], time[10], pos;

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("Enter number of pages: ");
    scanf("%d", &pages);

    printf("Enter page reference string:\n");
    for (i = 0; i < pages; i++) {
        scanf("%d", &page[i]);
    }

    for (i = 0; i < frames; i++) {
        frame[i] = -1;
    }

    printf("\nPage reference string\t\tFrames\n");
    for (i = 0; i < pages; i++) {
        int flag1 = 0;

        for (j = 0; j < frames; j++) {
            if (frame[j] == page[i]) {
                time[j] = ++counter; // Update time
                flag1 = 1;
                break;
            }
        }

        if (flag1 == 0) {
            pos = 0;
            for (j = 1; j < frames; j++) {
                if (time[j] < time[pos]) {
                    pos = j; // Find the LRU frame
                }
            }
            frame[pos] = page[i];
            time[pos] = ++counter; // Update time for new page
            pageFaults++;
        }

        printf("%d\t\t\t", page[i]);
        for (j = 0; j < frames; j++) {
            if (frame[j] != -1) {
                printf("%d ", frame[j]);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);

    return 0;
}


/* 
Q.2 Write a program to implement the shell. It should display the command 
prompt “myshell$”. Tokenize the command line and execute the given command 
by creating the child process. Additionally, it should interpret the following ‘list’ commands:
myshell$ list f dirname :- To print names of all the files in current directory.
myshell$ list n dirname :- To print the number of all entries in the current directory.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

void list_files(char *dirname) {
    struct dirent *de;
    DIR *dr = opendir(dirname);
    if (dr == NULL) {
        printf("Could not open current directory\n");
        return;
    }
    while ((de = readdir(dr)) != NULL) {
        printf("%s\n", de->d_name);
    }
    closedir(dr);
}

void count_files(char *dirname) {
    struct dirent *de;
    int count = 0;
    DIR *dr = opendir(dirname);
    if (dr == NULL) {
        printf("Could not open directory\n");
        return;
    }
    while ((de = readdir(dr)) != NULL) {
        count++;
    }
    printf("Total entries: %d\n", count);
    closedir(dr);
}

int main() {
    char command[100];
    char *args[10];
    char *token;

    while (1) {
        printf("myshell$ ");
        fgets(command, sizeof(command), stdin);
        command[strlen(command) - 1] = '\0'; // Remove newline
        
        token = strtok(command, " ");
        int i = 0;
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (strcmp(args[0], "list") == 0) {
            if (strcmp(args[1], "f") == 0) {
                list_files(args[2]);
            } else if (strcmp(args[1], "n") == 0) {
                count_files(args[2]);
            }
        } else {
            pid_t pid = fork();
            if (pid == 0) {
                execvp(args[0], args);
            } else {
                wait(NULL);
            }
        }
    }
    return 0;
}
