/* 
Q.1 Write a C program to implement the shell which displays the command 
prompt “myshell$”. It accepts the command, tokenizes the command line and 
executes it by creating the child process. Also implement the additional 
command ‘typeline’ as:
typeline -a filename :- To print all lines in the file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_all_lines(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("File open failed");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
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

        if (strcmp(args[0], "typeline") == 0 && strcmp(args[1], "-a") == 0) {
            print_all_lines(args[2]);
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

/*
Q.2 Write the simulation program for Round Robin scheduling for given time quantum.
The arrival time and first CPU-burst of different jobs should be input to the system.
Accept no. of Processes, arrival time and burst time.
The output should give the Gantt chart, turnaround time, and waiting time for each process.
Also display the average turnaround time and average waiting time.
*/

#include <stdio.h>

int main() {
    int n, quantum, i, j;
    int wait_time = 0, turnaround_time = 0, remain, time = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int burst_time[n], arrival_time[n], temp[n];

    for (i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &arrival_time[i], &burst_time[i]);
        temp[i] = burst_time[i]; // Store initial burst times
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);
    remain = n;

    printf("\nGantt Chart:\n");
    for (time = 0; remain != 0;) {
        for (i = 0; i < n; i++) {
            if (arrival_time[i] <= time && temp[i] > 0) {
                if (temp[i] > quantum) {
                    time += quantum;
                    printf("P%d ", i + 1);
                    temp[i] -= quantum;
                } else {
                    time += temp[i];
                    printf("P%d ", i + 1);
                    wait_time += time - arrival_time[i] - burst_time[i];
                    temp[i] = 0;
                    remain--;
                }
            }
        }
    }

    for (i = 0; i < n; i++) {
        turnaround_time += burst_time[i] + wait_time;
    }

    printf("\n\nAverage Waiting Time: %.2f\n", (float)wait_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)turnaround_time / n);

    return 0;
}
