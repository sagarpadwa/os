/*
Q.1 Write the simulation program to implement demand paging and show the 
page scheduling and total number of page faults according to the LRU 
(using counter method) page replacement algorithm. Assume the memory of n frames.
Reference String: 3,5,7,2,5,1,2,3,1,3,5,3,1,6,2
*/

#include <stdio.h>

int main() {
    int frames, pages, i, j, k, pageFaults = 0, counter = 0;
    int frame[10], page[20], flag[10], time[10], pos;

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
        int flag1 = 0, flag2 = 0;

        for (j = 0; j < frames; j++) {
            if (frame[j] == page[i]) {
                counter++;
                time[j] = counter;
                flag1 = 1;
                flag2 = 1;
                break;
            }
        }

        if (flag1 == 0) {
            for (j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    counter++;
                    frame[j] = page[i];
                    time[j] = counter;
                    flag2 = 1;
                    pageFaults++;
                    break;
                }
            }
        }

        if (flag2 == 0) {
            pos = 0;
            for (j = 1; j < frames; j++) {
                if (time[j] < time[pos]) {
                    pos = j;
                }
            }
            counter++;
            frame[pos] = page[i];
            time[pos] = counter;
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
Q.2 Write a program to implement the toy shell. It should display the command 
prompt “myshell$”. Tokenize the command line and execute the given command 
by creating the child process. Additionally, it should interpret the following commands:
count c filename :- To print number of characters in the file.
count w filename :- To print number of words in the file.
count l filename :- To print number of lines in the file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

void count_chars(char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return;
    }
    char buffer[1024];
    int n, total_chars = 0;
    while ((n = read(fd, buffer, sizeof(buffer))) > 0) {
        total_chars += n;
    }
    close(fd);
    printf("Total characters: %d\n", total_chars);
}

void count_words(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file");
        return;
    }
    char ch;
    int words = 0;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == ' ' || ch == '\n') {
            words++;
        }
    }
    fclose(fp);
    printf("Total words: %d\n", words);
}

void count_lines(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file");
        return;
    }
    char ch;
    int lines = 0;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }
    fclose(fp);
    printf("Total lines: %d\n", lines);
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

        if (strcmp(args[0], "count") == 0) {
            if (strcmp(args[1], "c") == 0) {
                count_chars(args[2]);
            } else if (strcmp(args[1], "w") == 0) {
                count_words(args[2]);
            } else if (strcmp(args[1], "l") == 0) {
                count_lines(args[2]);
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



