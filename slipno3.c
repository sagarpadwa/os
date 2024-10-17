/*
Q.1 Write the simulation program for demand paging and show the 
page scheduling and total number of page faults according to 
the MFU page replacement algorithm. Assume the memory of n frames.
Reference String: 8, 5, 7, 8, 5, 7, 2, 3, 7, 3, 5, 9, 4, 6, 2
*/

#include <stdio.h>

int main() {
    int frames, pages, i, j, k, pageFaults = 0, max, pos;
    int frame[10], page[20], freq[10];

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
        freq[i] = 0;
    }

    printf("\nPage reference string\t\tFrames\n");
    for (i = 0; i < pages; i++) {
        int flag1 = 0, flag2 = 0;

        for (j = 0; j < frames; j++) {
            if (frame[j] == page[i]) {
                freq[j]++;
                flag1 = 1;
                flag2 = 1;
                break;
            }
        }

        if (flag1 == 0) {
            for (j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    frame[j] = page[i];
                    freq[j]++;
                    flag2 = 1;
                    pageFaults++;
                    break;
                }
            }
        }

        if (flag2 == 0) {
            pos = 0;
            max = freq[0];
            for (j = 1; j < frames; j++) {
                if (freq[j] > max) {
                    max = freq[j];
                    pos = j;
                }
            }
            frame[pos] = page[i];
            freq[pos] = 1;
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
by creating the child process. Additionally, it should interpret the following commands:
myshell$ search a filename pattern :- To search all the occurrences of pattern in the file.
myshell$ search c filename pattern :- To count the number of occurrences of pattern in the file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void search_all_occurrences(char *filename, char *pattern) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("File open failed");
        return;
    }
    char line[256];
    int line_num = 1;
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, pattern)) {
            printf("Found at line %d: %s", line_num, line);
        }
        line_num++;
    }
    fclose(fp);
}

void count_occurrences(char *filename, char *pattern) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("File open failed");
        return;
    }
    char line[256];
    int count = 0;
    while (fgets(line, sizeof(line), fp)) {
        char *ptr = strstr(line, pattern);
        while (ptr) {
            count++;
            ptr = strstr(ptr + 1, pattern);
        }
    }
    printf("Total occurrences: %d\n", count);
    fclose(fp);
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

        if (strcmp(args[0], "search") == 0) {
            if (strcmp(args[1], "a") == 0) {
                search_all_occurrences(args[2], args[3]);
            } else if (strcmp(args[1], "c") == 0) {
                count_occurrences(args[2], args[3]);
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

