/*
Q.1 Write a program to implement the toy shell. It should display the command 
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

void count_characters(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("File open failed");
        return;
    }
    char ch;
    int count = 0;
    while ((ch = fgetc(fp)) != EOF) {
        count++;
    }
    fclose(fp);
    printf("Total characters: %d\n", count);
}

void count_words(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("File open failed");
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
    if (fp == NULL) {
        perror("File open failed");
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
                count_characters(args[2]);
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


/*
Q.2 Write the program to simulate Non-preemptive priority scheduling. 
The arrival time and first CPU-burst of different jobs should be input 
to the system. Accept no. of Processes, arrival time, and burst time. 
The output should give Gantt chart, turnaround time, and waiting time 
for each process. Also find the average waiting time and turnaround time.
*/

#include <stdio.h>

typedef struct {
    int pid, bt, at, wt, tat, priority;
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
            if (proc[j].at <= time && (min_index == -1 || proc[j].priority < proc[min_index].priority) && proc[j].bt > 0) {
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
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &proc[i].at, &proc[i].bt, &proc[i].priority);
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
