/* 
Q.1 Write a C program to implement the shell which displays the command 
prompt “myshell$”. It accepts the command, tokenizes the command line and 
executes it by creating the child process. Also implement the additional 
command ‘typeline’ as:
typeline -a filename :- To print all lines in the file.
typeline +n filename :- To print first n lines in the file.
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

void print_first_n_lines(char *filename, int n) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("File open failed");
        return;
    }
    char line[256];
    for (int i = 0; i < n; i++) {
        if (fgets(line, sizeof(line), fp) != NULL) {
            printf("%s", line);
        } else {
            break;
        }
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

        if (strcmp(args[0], "typeline") == 0) {
            if (strcmp(args[1], "-a") == 0) {
                print_all_lines(args[2]);
            } else if (strcmp(args[1], "+") == 0) {
                int n = atoi(args[2]);
                print_first_n_lines(args[3], n);
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


/*
Q.2 Write a C program to simulate Non-preemptive Shortest Job First (SJF) – 
scheduling. The arrival time and first CPU-burst of different jobs should be 
input to the system. Accept no. of Processes, arrival time, and burst time. 
The output should give Gantt chart, turnaround time, and waiting time 
for each process. Also find the average waiting time and turnaround time.
*/

#include <stdio.h>

typedef struct {
    int pid, bt, at, wt, tat;
} Process;

void find_waiting_time(Process proc[], int n) {
    int complete_time[n];
    for (int i = 0; i < n; i++) {
        proc[i].wt = 0;
        proc[i].tat = 0;
    }
    
    for (int time = 0; time < n;) {
        int min_index = -1;
        for (int j = 0; j < n; j++) {
            if (proc[j].at <= time && (min_index == -1 || proc[j].bt < proc[min_index].bt) && proc[j].bt > 0) {
                min_index = j;
            }
        }
        if (min_index != -1) {
            time += proc[min_index].bt;
            complete_time[time] = time;
            proc[min_index].bt = 0;
            proc[min_index].tat = time - proc[min_index].at;
            proc[min_index].wt = proc[min_index].tat - proc[min_index].bt;
        } else {
            time++;
        }
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    Process proc[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &proc[i].at, &proc[i].bt);
        proc[i].pid = i + 1;
    }

    find_waiting_time(proc, n);

    float total_wt = 0, total_tat = 0;
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].wt;
        total_tat += proc[i].tat;
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].at, proc[i].bt, proc[i].wt, proc[i].tat);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
